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
#include "assets.h"

// Layout constants
#define OBJ_OFFSET_X (35)
#define OBJ_OFFSET_Y (10)
#define OBJ_SEPARATION_Y (45)
#define OBJ_FOCUS_OPA (255)
#define OBJ_NORMAL_OPA (160)
#define OBJ_INVIS_OPA (0)
#define OBJ_INVIS_Y (320)
#define TASK_SEPARATION_X (100)
#define TASK_ICON_HEIGHT (90)
#define TASK_HEIGHT (140)
#define TASK_FOCUS_ICON_Y (OBJ_OFFSET_Y + OBJ_SEPARATION_Y * 2)
#define TASK_INVIS_Y_TOP (OBJ_OFFSET_Y - TASK_HEIGHT)
#define TASK_INVIS_Y_BOTTOM (OBJ_OFFSET_Y + OBJ_SEPARATION_Y * 2 + TASK_HEIGHT)
#define ANMI_DURATION_MS (200)

typedef struct {
    const char *title;
    const lv_img_dsc_t *icon;
    const int id;
    lv_obj_t *label_obj;
    lv_obj_t *icon_obj;
    lv_event_cb_t *cb;
} menu_task_t;

typedef struct {
    const char *title;
    int task_count;
    int index;
    lv_obj_t *title_obj;
    menu_task_t *tasks[];
} menu_app_t;

typedef struct {
    int app_count;
    int index;
    menu_app_t *apps[];
} home_menu_t;

menu_task_t home_music_favorite_task = {"Favorite", &heart, 1, NULL, NULL, NULL};
menu_task_t home_music_shuffle_task = {"Shuffle", &shuffle, 2, NULL, NULL, NULL};
menu_task_t home_music_playlist_task = {"Playlist", &menu, 3, NULL, NULL, NULL};
menu_task_t home_music_folder_task = {"Folder", &folder, 4, NULL, NULL, NULL};

menu_app_t home_music_app = {
    .title = "Music",
    .task_count = 4,
    .index = 0, 
    .tasks = {
        &home_music_favorite_task,
        &home_music_shuffle_task,
        &home_music_playlist_task,
        &home_music_folder_task
    }
};

menu_task_t home_game_recent_task = {"Recent", &copy, 5, NULL, NULL, NULL};
menu_task_t home_game_folder_task = {"Folder", &folder, 6, NULL, NULL, NULL};

menu_app_t home_game_app = {
    .title = "Games",
    .task_count = 2,
    .index = 0,
    .tasks = {
        &home_game_recent_task,
        &home_game_folder_task
    }
};

home_menu_t home_menu = {
    .app_count = 2,
    .index = 0,
    .apps = {
        &home_music_app,
        &home_game_app
    }
};

static lv_group_t * g;
static lv_style_t style;

static lv_signal_cb_t ancestor_signal;

void home_animate_horizontal(int is_moving_left);
void home_animate_vertical(int is_moving_up);

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked: %s\n", lv_list_get_btn_text(obj));
    }
}

#ifndef LV_USE_GROUP
#error "The home screen is designed to use keypad input."
#endif

static lv_res_t signal_handler(lv_obj_t *obj, lv_signal_t sign, void *param) {
    lv_res_t res;

    res = ancestor_signal(obj, sign, param);
    if (res != LV_RES_OK) return res;

    home_menu_t *menu = &home_menu;
    menu_app_t *app = menu->apps[menu->index];

    if (sign == LV_SIGNAL_CONTROL) {
        char c = *((char *)param);
        if (c == LV_KEY_RIGHT) {
            if (app->index < (app->task_count - 1)) {
                home_animate_horizontal(1);
                app->index++;
            }
        }
        else if (c == LV_KEY_LEFT) {
            if (app->index > 0) {
                home_animate_horizontal(0);
                app->index--;
            }
        }
        else if (c == LV_KEY_UP) {
            if (menu->index > 0) {
                home_animate_vertical(0);
                menu->index--;
            }
        }
        else if (c == LV_KEY_DOWN) {
            if (menu->index < (menu->app_count - 1)) {
                home_animate_vertical(1);
                menu->index++;
            }
        }
    }

    return LV_RES_OK;
}

void lv_obj_set_image_opa(lv_obj_t * obj, lv_anim_value_t value) {
    lv_obj_set_style_local_image_opa(obj, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, (lv_opa_t)value);
}

void lv_obj_set_text_opa(lv_obj_t * obj, lv_anim_value_t value) {
    lv_obj_set_style_local_text_opa(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, (lv_opa_t)value);
}

void home_animate_horizontal(int is_moving_left) {
    lv_anim_t anim;
    lv_anim_path_t path;
    home_menu_t *menu = &home_menu;
    
    menu_app_t *app = menu->apps[menu->index];
    menu_task_t *task;

    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_ease_in_out);

    lv_anim_init(&anim);
    lv_anim_set_time(&anim, ANMI_DURATION_MS);
    lv_anim_set_path(&anim, &path);

    // Visible range is -1 to +2, -2 or +3 will be moved in
    int range_left = (is_moving_left) ? (app->index - 1) : (app->index - 2);
    int range_right = (is_moving_left) ? (app->index + 3) : (app->index + 2);
    if (range_left < 0) range_left = 0;
    if (range_right >= app->task_count) range_right = app->task_count - 1;
    for (int task_id = range_left; task_id <= range_right; task_id ++) {
        task = app->tasks[task_id];

        // Move label and icon
        int old_x = (task_id - app->index) * TASK_SEPARATION_X + OBJ_OFFSET_X;
        int new_x = (is_moving_left) ? (old_x - TASK_SEPARATION_X) : (old_x + TASK_SEPARATION_X);

        lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&anim, old_x, new_x);
        lv_anim_set_var(&anim, task->label_obj);
        lv_anim_start(&anim);

        lv_anim_set_var(&anim, task->icon_obj);
        lv_anim_start(&anim);

        // Set opacity
        bool is_fading = false;
        int old_text_opa, new_text_opa, old_icon_opa, new_icon_opa;
        if (task_id == app->index) {
            // Fading out
            is_fading = true;
            old_text_opa = old_icon_opa = OBJ_FOCUS_OPA;
            new_text_opa = OBJ_INVIS_OPA;
            new_icon_opa = OBJ_NORMAL_OPA;
        }
        else if (task_id == ((is_moving_left) ? (app->index + 1) : (app->index - 1))) {
            // Fading in
            is_fading = true;
            old_text_opa = OBJ_INVIS_OPA;
            old_icon_opa = OBJ_NORMAL_OPA;
            new_text_opa = new_icon_opa = OBJ_FOCUS_OPA;
        }

        if (is_fading) {
            lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_image_opa);
            lv_anim_set_values(&anim, old_icon_opa, new_icon_opa);
            lv_anim_set_var(&anim, task->icon_obj);
            lv_anim_start(&anim);

            lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_text_opa);
            lv_anim_set_values(&anim, old_text_opa, new_text_opa);
            lv_anim_set_var(&anim, task->label_obj);
            lv_anim_start(&anim);
        }
    }
}

static int home_get_app_label_y(int app_id, int index) {
    home_menu_t *menu = &home_menu;

    if (app_id < (index - 2))
        return OBJ_INVIS_Y;
    else if (app_id > (index + 2))
        return OBJ_INVIS_Y;

    int y = OBJ_OFFSET_Y + OBJ_SEPARATION_Y * (app_id - index + 1);
    if (app_id > index)
        y += TASK_HEIGHT;

    return y;
}

void home_animate_vertical(int is_moving_up) {
    lv_anim_t anim;
    lv_anim_path_t path;
    home_menu_t *menu = &home_menu;
    
    menu_app_t *app;
    menu_task_t *task;

    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_ease_in_out);

    lv_anim_init(&anim);
    lv_anim_set_time(&anim, ANMI_DURATION_MS);
    lv_anim_set_path(&anim, &path);

    // Visible range is -1 to +1, -2 or +2 will be moved in
    int range_top = (is_moving_up) ? (menu->index - 1) : (menu->index - 2);
    int range_bottom = (is_moving_up) ? (menu->index + 2) : (menu->index + 1);
    if (range_top < 0) range_top = 0;
    if (range_bottom >= menu->app_count) range_bottom = menu->app_count - 1;
    for (int app_id = range_top; app_id <= range_bottom; app_id ++) {
        app = menu->apps[app_id];

        int old_index = menu->index;
        int new_index = (is_moving_up) ? (menu->index + 1) : (menu->index - 1);
        
        // Move app label
        int old_y = home_get_app_label_y(app_id, old_index);
        int new_y = home_get_app_label_y(app_id, new_index);

        lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&anim, old_y, new_y);
        lv_anim_set_var(&anim, app->title_obj);
        lv_anim_start(&anim);

        // Set opacity
        bool is_fading = false;
        bool is_fading_in = false;
        int old_opa, new_opa;
        if (app_id == old_index) {
            is_fading = true;
            is_fading_in = false;
            // For labels
            old_opa = OBJ_FOCUS_OPA;
            new_opa = OBJ_NORMAL_OPA;
            // For tasks
            old_y = TASK_FOCUS_ICON_Y;
            new_y = (is_moving_up) ? TASK_INVIS_Y_TOP : TASK_INVIS_Y_BOTTOM;
        }
        else if (app_id == new_index) {
            is_fading = true;
            is_fading_in = true;
            old_opa = OBJ_NORMAL_OPA;
            new_opa = OBJ_FOCUS_OPA;
            old_y = (is_moving_up) ? TASK_INVIS_Y_BOTTOM : TASK_INVIS_Y_TOP;
            new_y = TASK_FOCUS_ICON_Y;
        }

        if (is_fading) {
            // Set label opacity
            lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_text_opa);
            lv_anim_set_values(&anim, old_opa, new_opa);
            lv_anim_set_var(&anim, app->title_obj);
            lv_anim_start(&anim);

            // Animate tasks
            for (int task_id = 0; task_id < app->task_count; task_id++) {
                menu_task_t *task = app->tasks[task_id];

                // Animate locations of icons and labels
                lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
                lv_anim_set_values(&anim, old_y, new_y);
                lv_anim_set_var(&anim, task->icon_obj);
                lv_anim_start(&anim);

                lv_anim_set_values(&anim, old_y + TASK_ICON_HEIGHT, new_y + TASK_ICON_HEIGHT);
                lv_anim_set_var(&anim, task->label_obj);
                lv_anim_start(&anim);

                // Animate opacity of icons and labels
                int old_text_opa, new_text_opa, old_icon_opa, new_icon_opa;
                int icon_opa, text_opa;
                if (task_id == app->index) {
                    // Highlighted
                    text_opa = OBJ_FOCUS_OPA;
                    icon_opa = OBJ_FOCUS_OPA;
                }
                else {
                    text_opa = OBJ_INVIS_OPA;
                    icon_opa = OBJ_NORMAL_OPA;
                }
                old_text_opa = (is_fading_in) ? (OBJ_INVIS_OPA) : (text_opa);
                new_text_opa = (is_fading_in) ? (text_opa) : (OBJ_INVIS_OPA);
                old_icon_opa = (is_fading_in) ? (OBJ_INVIS_OPA) : (icon_opa);
                new_icon_opa = (is_fading_in) ? (icon_opa) : (OBJ_INVIS_OPA);

                if (old_text_opa != new_text_opa) {
                    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_text_opa);
                    lv_anim_set_values(&anim, old_text_opa, new_text_opa);
                    lv_anim_set_var(&anim, task->label_obj);
                    lv_anim_start(&anim);
                }

                lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_image_opa);
                lv_anim_set_values(&anim, old_icon_opa, new_icon_opa);
                lv_anim_set_var(&anim, task->icon_obj);
                lv_anim_start(&anim);
            }
        }
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

    lv_obj_t *cont = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_size(cont, 320, 288);
    lv_obj_clean_style_list(cont, LV_CONT_PART_MAIN);
    lv_obj_align(cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_obj_set_style_local_bg_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_text_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    /*lv_obj_t *background = lv_img_create(cont, NULL);
    lv_obj_align(background, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_obj_set_image_opa(background, 100);*/

    lv_style_t app_label_style;
    lv_style_init(&app_label_style);
    lv_style_set_text_font(&app_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_36);

    lv_style_t task_label_style;
    lv_style_init(&task_label_style);
    lv_style_set_text_font(&task_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_30);

    home_menu_t *menu = &home_menu;
    
    for (int app_id = 0; app_id < menu->app_count; app_id++) {
        menu_app_t *app = menu->apps[app_id];
        lv_obj_t *label = lv_label_create(cont, NULL);
        lv_label_set_text(label, app->title);
        lv_obj_add_style(label, LV_LABEL_PART_MAIN, &app_label_style);
        app->title_obj = label;
        for (int task_id = 0; task_id < app->task_count; task_id++) {
            menu_task_t *task = app->tasks[task_id];
            lv_obj_t *label = lv_label_create(cont, NULL);
            lv_label_set_text(label, task->title);
            lv_obj_add_style(label, LV_LABEL_PART_MAIN, &task_label_style);
            task->label_obj = label;
            lv_obj_t *icon = lv_img_create(cont, NULL);
            lv_img_set_src(icon, task->icon);
            task->icon_obj = icon;
        }
    }
    
    // Set object locations and default opacity
    // TODO: Remember last location instead of using 1, 1?

    for (int app_id = 0; app_id < menu->app_count; app_id++) {
        menu_app_t *app = menu->apps[app_id];

        // Set label location and opacity, hide invisible labels
        int y = home_get_app_label_y(app_id, menu->index);
        lv_obj_align(app->title_obj, NULL, LV_ALIGN_IN_TOP_LEFT, OBJ_OFFSET_X, y);
        if (app_id != menu->index)
            lv_obj_set_text_opa(app->title_obj, OBJ_NORMAL_OPA);

        // Set task location and opacity, hide invisible tasks
        y = (app_id == menu->index) ? (TASK_FOCUS_ICON_Y) : (OBJ_INVIS_Y);
        for (int task_id = 0; task_id < app->task_count; task_id++) {
            menu_task_t *task = app->tasks[task_id];
            int x = OBJ_OFFSET_X + task_id * TASK_SEPARATION_X;
            lv_obj_align(task->icon_obj, NULL, LV_ALIGN_IN_TOP_LEFT, x, y);
            lv_obj_align(task->label_obj, NULL, LV_ALIGN_IN_TOP_LEFT, x, y + TASK_ICON_HEIGHT);
            if (task_id != 0) {
                lv_obj_set_image_opa(task->icon_obj, OBJ_NORMAL_OPA);
                lv_obj_set_text_opa(task->label_obj, OBJ_INVIS_OPA);
            }
        }
    }

    if(ancestor_signal == NULL) ancestor_signal = lv_obj_get_signal_cb(cont);
    lv_obj_set_signal_cb(cont, signal_handler);

    lv_group_add_obj(g, cont);

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
