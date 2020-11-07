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
// File : home.c
// Brief: Home screen of the firmware
//
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "platform.h"
#include "gui.h"
#include "home.h"

static lv_group_t * g;
static lv_obj_t * list;
static lv_style_t style;
static lv_obj_t * status;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked: %s\n", lv_list_get_btn_text(obj));
    }
}

void home_task(void *pvParameters) {
    UNUSED(pvParameters);

    gui_enter();

    g = lv_group_create();
    //lv_group_set_focus_cb(g, focus_cb);

    lv_indev_set_group(indev_keypad, g);

    lv_style_init(&style);
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 0);
    lv_style_set_border_width(&style, LV_STATE_DEFAULT, 0);

    list = lv_list_create(lv_scr_act(), NULL);
    lv_obj_set_size(list, 320, 288);
    lv_obj_add_style(list, LV_OBJ_PART_MAIN, &style);
    lv_obj_align(list, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    /*Add buttons to the list*/
    lv_obj_t * list_btn;

    list_btn = lv_list_add_btn(list, LV_SYMBOL_FILE, "New");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "Open");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_CLOSE, "Delete");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_EDIT, "Edit");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_SAVE, "Save");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_BELL, "Notify");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_BATTERY_FULL, "Battery");
    lv_obj_set_event_cb(list_btn, event_handler);

    lv_group_add_obj(g, list);

    lv_obj_t * status = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(status, 320, 320 - 288);
    lv_obj_align(status, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_add_style(status, LV_OBJ_PART_MAIN, &style);
    lv_obj_set_style_local_bg_color(status, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,
            lv_color_hex(0x000000));

    lv_obj_t * label_battery = lv_label_create(status, NULL);
    lv_label_set_text(label_battery, LV_SYMBOL_BATTERY_FULL);
    lv_obj_set_style_local_text_color(label_battery, LV_LABEL_PART_MAIN, 
            LV_STATE_DEFAULT, lv_color_hex(0xaaaaaa));
    lv_obj_align(label_battery, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);

    lv_obj_t * label_time = lv_label_create(status, NULL);
    lv_label_set_text(label_time, "15:39");
    lv_obj_set_style_local_text_color(label_time, LV_LABEL_PART_MAIN, 
            LV_STATE_DEFAULT, lv_color_hex(0xaaaaaa));
    lv_obj_align(label_time, label_battery, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    gui_exit();

    vTaskSuspend(NULL);
}
