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
// File : gui.c
// Brief: GUI abstraction layer
//
#include <stdint.h>
#include "common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "os_display.h"
#include "os_input.h"
#include "gui.h"

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area,
        lv_color_t * color_p);
static bool keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);
void lv_port_disp_init(void);
void lv_port_indev_init(void);

lv_indev_t * indev_keypad;
SemaphoreHandle_t gui_sem;
Canvas *fb0;

int gui_init(void) {
    gui_sem = xSemaphoreCreateMutex();
    if (gui_sem == NULL) {
        return -1;
    }

    os_disp_init();

	fb0 = os_disp_create(DISP_WIDTH, DISP_HEIGHT, PIXFMT_RGB565);

    lv_init();

    lv_port_disp_init();
    lv_port_indev_init();

    return 0;
}

#if (configTICK_RATE_HZ > 1000)
#error "Current GUI implementation requires the tick rate to be below 1kHz"
#endif

void gui_tick(void) {
    lv_tick_inc(1000 / configTICK_RATE_HZ);
}

void gui_task(void *pvParameters) {
    UNUSED(pvParameters);
    while (1) {
        xSemaphoreTake(gui_sem, portMAX_DELAY);
        lv_task_handler();
        xSemaphoreGive(gui_sem);
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void lv_port_disp_init(void) {
    os_disp_init();

    // For buffer configuration, a global live screen-sized buffer and a local
    // buffer for lvgl are used. This means no full double buffering is used for
    // GUI, in order to save some on-chip memory (~200KB).
    // TODO:
    // If application (such as a game) demands high graphics performance, it
    // needs to be able to claim the screen (exclusive mode) and switch to 
    // double buffering mode.
    static lv_disp_buf_t draw_buf_dsc_1;
    static lv_color_t draw_buf_1[LV_HOR_RES_MAX * 10];
    lv_disp_buf_init(&draw_buf_dsc_1, draw_buf_1, NULL, LV_HOR_RES_MAX * 10);

    // Register the display in LVGL

    lv_disp_drv_t disp_drv;            // Descriptor of a display driver
    lv_disp_drv_init(&disp_drv);       // Basic initialization

    // Set up the functions to access to your display

    // Set the resolution of the display
    disp_drv.hor_res = DISP_WIDTH;
    disp_drv.ver_res = DISP_HEIGHT;

    // Used to copy the buffer's content to the display
    disp_drv.flush_cb = disp_flush;

    // Set a display buffer
    disp_drv.buffer = &draw_buf_dsc_1;

#if LV_USE_GPU
    // Optionally add functions to access the GPU. 
    // (Only in buffered mode, LV_VDB_SIZE != 0)
#error "GPU support is not supported yet"

    // Blend two color array using opacity
    disp_drv.gpu_blend_cb = gpu_blend;

    // Fill a memory array with a color
    disp_drv.gpu_fill_cb = gpu_fill;
#endif

    // Finally register the driver
    lv_disp_drv_register(&disp_drv);
}

// Flush the content of the internal buffer the specific area on the display
// You can use DMA or any hardware acceleration to do this operation in the
// background but 'lv_disp_flush_ready()' has to be called when finished.
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area,
        lv_color_t * color_p) {
    os_disp_bilt_raw(fb0, (uint8_t *)color_p, area->x1, area->y1, 0, 0,
            area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
    os_disp_draw(fb0);
    lv_disp_flush_ready(disp_drv);
}


void lv_port_indev_init(void) {
    lv_indev_drv_t indev_drv;

    // Initialize your keypad or keyboard if you have
    os_input_init();

    // Register a keypad input device
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);
}

// Will be called by the library to read the keypad
static bool keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data) {
    static uint32_t last_key = 0;

    UNUSED(indev_drv);

    // Get whether the a key is pressed and save the pressed key
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;
        last_key = act_key;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;

    // Return `false` because we are not buffering and no more data to read
    return false;
}

// Get the currently being pressed key. 0 if no key is pressed
static uint32_t keypad_get_key(void) {
    uint32_t key_mask = os_input_get_keys();

    if (key_mask & KEY_MASK_DOWN)
        return LV_KEY_DOWN;
    else if (key_mask & KEY_MASK_LEFT)
        return LV_KEY_LEFT;
    else if (key_mask & KEY_MASK_NO)
        return LV_KEY_ESC;
    else if (key_mask & KEY_MASK_RIGHT)
        return LV_KEY_RIGHT;
    else if (key_mask & KEY_MASK_SELECT)
        return LV_KEY_END;
    else if (key_mask & KEY_MASK_START)
        return LV_KEY_HOME;
    else if (key_mask & KEY_MASK_UP)
        return LV_KEY_UP;
    else if (key_mask & KEY_MASK_YES)
        return LV_KEY_ENTER;    

    return 0;
}