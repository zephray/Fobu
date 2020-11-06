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
// File : os_input.c
// Brief: Keypad input OS Abstraction Layer
//
#include <SDL/SDL.h>
#include "os_input.h"

uint32_t key_state;

void os_input_init(void) {
    key_state = 0;
}

uint32_t os_input_get_keys(void) {
    return key_state;
}

void _os_input_handle_sdl_keyevent(SDL_KeyboardEvent event) {
    uint32_t key_mask;

    switch (event.keysym.sym) {
    case SDLK_LEFT:
        key_mask = KEY_MASK_LEFT;
        break;
    case SDLK_RIGHT:
        key_mask = KEY_MASK_RIGHT;
        break;
    case SDLK_UP:
        key_mask = KEY_MASK_UP;
        break;
    case SDLK_DOWN:
        key_mask = KEY_MASK_DOWN;
        break;
    case SDLK_RETURN:
        key_mask = KEY_MASK_YES;
        break;
    case SDLK_ESCAPE:
        key_mask = KEY_MASK_NO;
        break;
    case SDLK_z:
        key_mask = KEY_MASK_SELECT;
        break;
    case SDLK_x:
        key_mask = KEY_MASK_START;
        break;
    default:
        // Ignore
        return;
    }

    if (event.type == SDL_KEYDOWN) {
        key_state |= key_mask;
    }
    else {
        key_state &= ~key_mask;
    }
}