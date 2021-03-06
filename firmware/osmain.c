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
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "platform.h"
#include "gui.h"
#include "osmain.h"
#include "home.h"

void vApplicationTickHook(void) {
	gui_tick();
}

void startup_task(void *pvParameters) {
	UNUSED(pvParameters);

	gui_init();

	xTaskCreate(gui_task, "GUI Task", GUI_TASK_STACKSIZE, NULL,
			GUI_TASK_PRIORITY, NULL);

	xTaskCreate(home_task, "Home Task", APP_TASK_STACKSIZE, NULL, 
			APP_TASK_PRIORITY, NULL);

	vTaskDelete(NULL);
}
