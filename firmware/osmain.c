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
// File : osmain.c
// Brief: Main entry point of the firmware / operating system
//
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include <stdio.h>
#include <stdbool.h>
#include "platform.h"
#include "os_filesystem.h"
#include "os_display.h"
#include "os_audio.h"
#include "minimp3.h"
#include "decoder.h"
#include "osmain.h"

void startup_task(void *pvParameters) {
	os_disp_init();

	Canvas *fb = os_disp_create(256, 128, PIXFMT_Y1);
	os_disp_fill(fb, 0, 0, 256, 128, 1);

	os_fs_chdir(APP_ROOT);

	Directory *directory; /* Directory object */
	FileInfo fileInformation;
	int y = 0;

	printf("\r\nList the file in that directory......\r\n");
	directory = os_fs_opendir(".");
	if (directory == NULL)
	{
		printf("Open directory failed.\r\n");
		vTaskSuspend(NULL);
	}
	for (;;)
	{
		int result = os_fs_readdir(directory, &fileInformation);

		if ((result < 0) || (fileInformation.fname[0U] == 0U))
		{
		   break;
		}
		if (fileInformation.fname[0] == '.')
		{
		   continue;
		}
		if (fileInformation.type == FT_DIRECTORY)
		{
			printf("Directory file : %s.\r\n", fileInformation.fname);
		}
		else
		{
			printf("General file : %s.\r\n", fileInformation.fname);
			if (fileInformation.fname[0] == 'o')
				continue;
			if (fileInformation.fname[0] == 'O')
				continue;
			break; // Play the first file for now
		}
	}

	os_audio_init();
	os_audio_set_volume(0xa0);

	DecoderContext *ctx = NULL;
	ctx = pvPortMalloc(sizeof(DecoderContext));
	if (!ctx) {
		printf("Unable to allocate memory for decoder context.\r\n");
		vTaskSuspend(NULL);
	}
	dec_openfile(ctx, fileInformation.fname);
	
	// Playback
	if (os_audio_start(44100, AF_S16LE, dec_audio_callback, ctx) < 0) {
		printf("Unable to start audio subsystem.\r\n");
		vTaskSuspend(NULL);
	}
	dec_play(ctx);

	while (!ctx->finished) {
		vTaskDelay(pdMS_TO_TICKS(10));
	}

	dec_close(ctx);
	os_audio_stop();

	vPortFree(ctx);

	vTaskSuspend(NULL);
}
