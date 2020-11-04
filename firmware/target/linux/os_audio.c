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
// File : os_audio.c
// Brief: Audio Abstraction Layer.
//
#include <SDL/SDL.h>
#include "os_audio.h"

static AudioCallback user_cb;
static int volume;

#define HAL_AUDIO_BUFFER_SIZE (8192)
uint8_t audio_buffer[HAL_AUDIO_BUFFER_SIZE];
int buffer_level;

int os_audio_init() {
    // SDL should be initialized in SDL_Init called in video init
    return 0;
}

void os_audio_sdl_callback(void *userdata, uint8_t *stream, int len) {
    while (buffer_level < len) {
        buffer_level += user_cb(userdata, &(audio_buffer[buffer_level]),
                HAL_AUDIO_BUFFER_SIZE - buffer_level);
    }
    SDL_MixAudio(stream, audio_buffer, len, volume);
    memmove(audio_buffer, &audio_buffer[len], buffer_level-len);
    buffer_level -= len;
}

int os_audio_start(int samplerate, AudioFormat format, AudioCallback cb, void *userdata) {
    SDL_AudioSpec as_request;
    SDL_AudioSpec as_got;

    if (format != AF_S16LE) {
        fprintf(stderr, "Format other than S16 is not yet supported in linux framework\n");
        return -1;
    }

    as_request.freq = samplerate;
    as_request.format = AUDIO_S16;
    as_request.channels = 2;
    as_request.samples = HAL_AUDIO_BUFFER_SIZE / 4;
    as_request.callback = os_audio_sdl_callback;
    as_request.userdata = userdata;
    if (SDL_OpenAudio(&as_request, &as_got) < 0)
    {
        fprintf(stderr, "couldn't open audio: %s\n", SDL_GetError());
        return -1;
    }
    
    user_cb = cb;
    
    buffer_level = 0;

    SDL_PauseAudio(0);

    return 0;
}

int os_audio_stop() {
    SDL_PauseAudio(1);
    SDL_CloseAudio();
    return 0;
}

// 0 - minimum (mute), 255 - maximum
int os_audio_set_volume(uint8_t vol) {
    fprintf(stdout, "Volume set to %d\r\n", vol);
    volume = vol / 2;
    return 0;
}
