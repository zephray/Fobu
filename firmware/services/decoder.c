//
// Project Fobu
// Copyright 2020 Wenting Zhang
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// File : decoder.c
// Brief: Handles filesystem, audio output and decoder interaction
//
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "os_filesystem.h"
#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"
#include "decoder.h"

static int16_t pcm_buffer[MAX_FRAME_SIZE];
// 0: waiting for DMA CB, 1: waiting for decoder
// DMA CB can set this from 0 to 1, decoder can reset this from 1 to 0.
static SemaphoreHandle_t pcm_buffer_sem = NULL;
static volatile size_t pcm_buffer_ready;
static volatile uint32_t pcm_buffer_size;

void dec_fetch_thread(void *arg) {
    DecoderContext *ctx = (DecoderContext *)arg;
    uint8_t *buf;

    buf = pvPortMalloc(QUEUE_OBJECT);
	if (!buf) {
		printf("Unable to allocate memory for fetcher buffer!\n");
	}

    while (ctx->offset < ctx->file_size) {
        int bytes;
        bytes = os_fs_read(ctx->file, buf, QUEUE_OBJECT); // Could be -1
        if (bytes < 0)
            break;
        if (bytes < QUEUE_OBJECT)
            memset(buf + bytes, 0, QUEUE_OBJECT - bytes);
        xQueueSendToBack(ctx->input_queue, buf, portMAX_DELAY);
        ctx->offset = os_fs_tell(ctx->file);
    }

	vPortFree(buf);
	vTaskSuspend(NULL);
}

void dec_decode_thread(void *arg) {
    DecoderContext *ctx = (DecoderContext *)arg;
    uint8_t *buf = NULL;
    int buf_level = 0;
    int samples;
    mp3dec_frame_info_t info;

    buf = pvPortMalloc(QUEUE_OBJECT * 2);
    if (!buf) {
    	printf("Unable to allocate memory for decoder buffer!\n");
    }

    while (ctx->processed < ctx->file_size) {
        // Try to decode samples
        if ((buf_level < QUEUE_OBJECT) // buffer it not filled up
        		// and there is more than one queue object that is not fetched
        		&& (ctx->file_size - ctx->processed - buf_level > QUEUE_OBJECT)) {
            xQueueReceive(ctx->input_queue, buf + buf_level, portMAX_DELAY);
            buf_level += QUEUE_OBJECT;
        }
        // Wait for the output buffer to be available
        if (pcm_buffer_ready == 1)
        	xSemaphoreTake(pcm_buffer_sem, portMAX_DELAY);
        // Decode audio
        // This things need ~16KB stack space
        samples = mp3dec_decode_frame(&(ctx->mp3d), buf, buf_level, pcm_buffer, &info);
        buf_level -= info.frame_bytes;
        ctx->processed += info.frame_bytes;
        memmove(buf, buf + info.frame_bytes, buf_level);
        // If any samples has been decoded, mark the buffer as used
        if (samples != 0) {
            pcm_buffer_size = samples * 2 * info.channels;
            pcm_buffer_ready = 1;
        }
        else if (info.frame_bytes == 0) {
        	// nothing has been processed and not moving forward
        	ctx->processed = ctx->file_size;
        }
    }
    printf("Decoding finished.\n");
    ctx->finished = true;

    vPortFree(buf);
    vTaskSuspend(NULL);
}

// Return actual sample size filled
size_t dec_audio_callback(void *userdata, uint8_t *stream, uint32_t len) {
    DecoderContext *ctx = (DecoderContext *)userdata;

    if (!(ctx->playing)) {
        // Not playing, return silence
        memset(stream, 0, len);
        return len;
    }

    if (len < pcm_buffer_size) {
    	// Not supported
    	printf("Given buffer too small! Given %d, expected %d\n", len, pcm_buffer_size);
    	return 0;
    }

    if (pcm_buffer_ready != 1) {
        // Nothing to return for now
    	// If this is called from an ISR, this is pretty much
    	// impossible to delay it?
    	// Even if it can try later, does this mean the decoding is
    	// simply too slow and there is little we can do about that?
        return 0;
    }

    memcpy(stream, pcm_buffer, pcm_buffer_size);

    // Reset dma buffer and signal the decode thread
    size_t buf_size = pcm_buffer_size; // need to save the value before reset the variable
    pcm_buffer_ready = 0;
    xSemaphoreGiveFromISR(pcm_buffer_sem, NULL); // May need to use from ISR version
    //xTaskResumeFromISR(ctx->decode_handle);

    return buf_size;
}

int dec_openfile(DecoderContext *ctx, char *fname) {
    if ((!ctx) || (!fname))
        return -1;
    memset(ctx, 0, sizeof(DecoderContext));

    pcm_buffer_sem = xSemaphoreCreateBinary();

    // Open file
    ctx->file = os_fs_open(fname, OM_READ);
    if (ctx->file == NULL) {
    	printf("Unable to open audio file.\n");
    	return -1;
    }
    ctx->file_size = os_fs_size(ctx->file);

    // Setup queues
    ctx->input_queue = xQueueCreate(QUEUE_LENGTH, QUEUE_OBJECT);

    // Initialize status
    ctx->offset = 0;
    ctx->processed = 0;
    ctx->playing = false;
    ctx->finished = false;

    // Setup decoder
    mp3dec_init(&(ctx->mp3d));

    // Start threads
    xTaskCreate(dec_fetch_thread, "fetcher", 512, (void *)ctx, 4,
            &(ctx->fetch_handle));
    if (ctx->fetch_handle == NULL) {
    	printf("Unable to create task for audio file fetcher.\n");
        return -1;
    }

    // 24 KB stack for decoder as the MP3 decoder needs around 16KB stack space
    xTaskCreate(dec_decode_thread, "decoder", 6144, (void *)ctx, 4,
            &(ctx->decode_handle));
    if (ctx->decode_handle == NULL) {
    	printf("Unable to create task for audio file decoder.\n");
        return -1;
    }

    pcm_buffer_ready = 0;
    xSemaphoreGive(pcm_buffer_sem);

    return 0;
}

int dec_play(DecoderContext *ctx) {
    ctx->playing = true;
    return 0;
}

int dec_pause(DecoderContext *ctx) {
    ctx->playing = false;
    return 0;
}

int dec_close(DecoderContext *ctx) {
    vTaskDelete(ctx->fetch_handle);
    vTaskDelete(ctx->decode_handle);
    vSemaphoreDelete(pcm_buffer_sem);
    os_fs_close(ctx->file);
    return 0;
}
