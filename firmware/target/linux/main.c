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
#include <signal.h>
#include <SDL/SDL.h>
#include "common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "osmain.h"
#include "os_input.h"

void housekeepingTask(void *pvParameters){
    SDL_Event event;

    UNUSED(pvParameters);

    while(1){
        if (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                printf("Exiting...\n");
                vTaskEndScheduler();
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                _os_input_handle_sdl_keyevent(event.key);
                break;
            
            default:
                break;
            }
        }
        // Yield
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

int main(){
    xTaskCreate(housekeepingTask, "Housekeeping Task", 128,
            NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(startup_task, "Startup Task", STARTUP_TASK_STACKSIZE,
            NULL, STARTUP_TASK_PRIORITY, NULL);
    vTaskStartScheduler();

    return 0;
}

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
    printf("Assert Failed: %s : %d\n", pcFileName, (int)ulLine);
    return;
}

void vApplicationMallocFailedHook(void)
{
    printf("Malloc failed\n");
    return;
}
