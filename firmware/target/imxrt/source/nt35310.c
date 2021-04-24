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
// File : nt35310.c
// Brief: Driver for NT35310 LCD controller
//
#include "fsl_gpio.h"
#include "fsl_mipi_dsi.h"

#include "utils.h"

#define BOARD_LCD_BL_GPIO GPIO9
#define BOARD_LCD_BL_PIN  29
#define BOARD_LCD_RST_GPIO GPIO9
#define BOARD_LCD_RST_PIN 1

typedef struct {
    const uint8_t *dat;
    uint8_t length;
} cmd_sequence_t;

static const uint8_t initCmd0[]  = {0x11}; // Sleep out
static const uint8_t initCmd1[]  = {0xED, 0x01, 0xFE}; // CMD2 Unlock
static const uint8_t initCmd2[]  = {0xC4, 0x5F}; // VCOM
static const uint8_t initCmd3[]  = {0xC6, 0x00, 0xE2, 0xE2, 0xE2, 0xBF, 0xAA}; // VGH VGL Clamp
static const uint8_t initCmd4[]  = {0x3A, 0x76}; // Set MIPI Pixel Format to RGB888
static const uint8_t initCmd5[]  = {0xB3, 0x40}; // Bypass
static const uint8_t initCmd6[]  = {0xB3, 0x41}; // External Clock
static const uint8_t initCmd7[]  = {0x2A, 0x00, 0x00, 0x01, 0x3f};
static const uint8_t initCmd8[]  = {0x2B, 0x00, 0x00, 0x01, 0x3f};
static const uint8_t initCmd9[]  = {0x2C}; // Memory write start
static const uint8_t initCmd10[] = {0x29}; // Display On

static cmd_sequence_t initSequence[] = {
    initCmd1, sizeof(initCmd1),
    initCmd2, sizeof(initCmd2),
    initCmd3, sizeof(initCmd3),
    initCmd4, sizeof(initCmd4),
    initCmd5, sizeof(initCmd5),
    initCmd6, sizeof(initCmd6),
    initCmd7, sizeof(initCmd7),
    initCmd8, sizeof(initCmd8),
    initCmd9, sizeof(initCmd9),
    initCmd10, sizeof(initCmd10),
};

#define INIT_SEQ_LENGTH (sizeof(initSequence) / sizeof(cmd_sequence_t))

void nt35310_init(void) {
    const gpio_pin_config_t pinConfig = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
    GPIO_PinInit(BOARD_LCD_BL_GPIO, BOARD_LCD_BL_PIN, &pinConfig);
    GPIO_PinInit(BOARD_LCD_RST_GPIO, BOARD_LCD_RST_PIN, &pinConfig);

    GPIO_PinWrite(BOARD_LCD_RST_GPIO, BOARD_LCD_RST_PIN, 0);
    utils_sleep_ms(1);
    GPIO_PinWrite(BOARD_LCD_RST_GPIO, BOARD_LCD_RST_PIN, 1);
    utils_sleep_ms(5);

    // Sleep out
    video_dsi_write(initCmd0, sizeof(initCmd0));
    utils_sleep_ms(200);

    // Initialization sequence
    for (int i = 0; i < INIT_SEQ_LENGTH; i++) {
        video_dsi_write(initSequence[i],dat, initSequence[i].length);
    }
}
