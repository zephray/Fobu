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
// File : main.c
// Brief: Platform-specific program entry point
//
#include <stdio.h>
#include "MIMXRT1176_cm7.h"
#include "fsl_cache.h"
#include "mpu.h"
#include "clock.h"
#include "sdram.h"
#include "utils.h"
#include "vout.h"

void lcd_set_color(uint16_t cl) {
	uint16_t *wrptr = (uint16_t *)framebuffer;
	for (int i = 0; i < 320*320; i++) {
		*wrptr++ = cl;
	}
	DCACHE_CleanInvalidateByRange((uint32_t)framebuffer, (320 * 320 * 2));
}

int main(void) {
	mpu_init();
	clock_init_default();
	sdram_init();
	vout_init();
	while (1) {
		lcd_set_color(0xf800);
		util_sleep_ms(1000);
		lcd_set_color(0x07e0);
		util_sleep_ms(1000);
		lcd_set_color(0x001f);
		util_sleep_ms(1000);
	}
    return 0 ;
}
