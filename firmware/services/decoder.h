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
// File : decoder.h
// Brief: Handles filesystem, audio output and decoder interaction
//
#ifndef __DECODER_H__
#define __DECODER_H__

// The decoder subsystem owns two threads, one fetcher thread, one decoder
// thread. The fetcher thread pushes raw data read from SD card into the FIFO,
// the decoder decodes the audio and send the audio frame into audio DMA.
// The core of the audio subsystem is an FIFO: the producer (decoder) thread
// pushes decoded audio frame into the FIFO, the consumer (which is connect to 
// audio DMA) takes decoded audio frame from the FIFO.

// The producer will keeps pushing raw audio file into the FIFO until it reaches
// the definied size. Request to pushing more frames into the FIFO should be
// rejected.
#define QUEUE_OBJECT (8192)
// The fetcher hold one additional buffer and the decoder holds
#define QUEUE_LENGTH (1)

#define MAX_FRAME_SIZE (1152*2*2)

typedef struct {
    // Decoder handle
    mp3dec_t mp3d;
    // Input file
    File * file;
    size_t file_size;
    // For communication between fetch and decode
    QueueHandle_t input_queue; // allocated dynamically
    // Input file counting
    size_t offset; // Current input file offset
    size_t processed; // Current processed byte count
    // File information
    int samples;
    int channels;
    // Playing status
    volatile bool playing;
    volatile bool finished;
    // Threads
    TaskHandle_t fetch_handle;
    TaskHandle_t decode_handle;
} DecoderContext;

int dec_openfile(DecoderContext *ctx, char *fname);
void dec_decode(DecoderContext *ctx, uint8_t *buf, int bytes);
size_t dec_audio_callback(void *userdata, uint8_t *stream, uint32_t len);
int dec_play(DecoderContext *ctx);
int dec_pause(DecoderContext *ctx);
int dec_close(DecoderContext *ctx);

#endif
