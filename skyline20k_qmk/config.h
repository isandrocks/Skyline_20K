// Copyright 2024 iSandRocks (@iSandRocks)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
// The pin connected to the data pin of the LEDs
#define WS2812_DI_PIN C4
// The number of LEDs connected
#define RGBLED_NUM 12

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_SLEEP
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD
#define RGBLIGHT_DEFAULT_HUE 0
#define RGBLIGHT_DEFAULT_SAT UINT8_MAX
#define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_DEFAULT_SPD 1
#define RGBLIGHT_DEFAULT_ON true




/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
