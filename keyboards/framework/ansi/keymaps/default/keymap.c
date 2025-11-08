// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "framework.h"

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#    include "keyboards/framework/ansi/ansi.h"
#endif

enum _layers { _BASE, _FN, _FN_LOCK, _FM };

typedef enum {

    LED_FN  = 93,
    LED_WIN = 46,

    LED_F1    = 21,
    LED_F2    = 19,
    LED_F3    = 18,
    LED_F4    = 20,
    LED_F5    = 22,
    LED_F6    = 24,
    LED_F7    = 26,
    LED_F8    = 67,
    LED_F9    = 74,
    LED_F10   = 68,
    LED_F11   = 66,
    LED_F11_2 = 71,
    LED_F12   = 70,

    LED_TILDE      = 16,
    LED_1          = 15,
    LED_2          = 13,
    LED_3          = 12,
    LED_4          = 11,
    LED_5          = 9,
    LED_6          = 14,
    LED_7          = 10,
    LED_8          = 17,
    LED_9          = 69,
    LED_0          = 61,
    LED_MINUS      = 63,
    LED_EQUALS     = 62,
    LED_BACKSPACE  = 65,
    LED_BACKSPACE2 = 64,

    LED_DEL  = 72,
    LED_DEL2 = 73,

    LED_Q             = 5,
    LED_W             = 3,
    LED_E             = 2,
    LED_R             = 4,
    LED_T             = 7,
    LED_Y             = 8,
    LED_U             = 6,
    LED_I             = 58,
    LED_O             = 59,
    LED_P             = 60,
    LED_LEFT_BRACKET  = 57,
    LED_RIGHT_BRACKET = 54,
    LED_BACK_SLASH    = 55,
    LED_ENTER         = 56,
    LED_ENTER2        = 53,

    LED_A             = 36,
    LED_S             = 41,
    LED_D             = 37,
    LED_F             = 43,
    LED_G             = 39,
    LED_H             = 40,
    LED_J             = 49,
    LED_K             = 50,
    LED_L             = 51,
    LED_SEMI_COLON    = 48,
    LED_SINGLE_QUOTE  = 52,
    LED_FORWARD_SLASH = 79,

    LED_Z = 27,
    LED_X = 29,
    LED_C = 31,
    LED_V = 33,
    LED_B = 35,
    LED_N = 76,
    LED_M = 77,

    LED_COMMA = 78,
    LED_DOT   = 75,
    LED_ESC   = 25,
    LED_ESC2  = 23,

    LED_SPACE  = 85,
    LED_SPACE2 = 87,
    LED_SPACE3 = 86,
    LED_SPACE4 = 95,
    LED_SPACE5 = 96,
    LED_SPACE6 = 94,

    LED_RIGHT_SHIFT  = 92,
    LED_RIGHT_SHIFT2 = 80,
    LED_RIGHT_SHIFT3 = 82,
    LED_RIGHT_SHIFT4 = 83,

    LED_LEFT_SHIFT  = 28,
    LED_LEFT_SHIFT2 = 30,
    LED_LEFT_SHIFT3 = 32,

    LED_CAPS  = 38,
    LED_CAPS2 = 42,
    LED_CAPS3 = 44,

    LED_TAB  = 0,
    LED_TAB2 = 1,

    LED_CTRL  = 34,
    LED_CTRL2 = 45,
    LED_CTRL3 = 88,

    LED_ALT  = 47,
    LED_ALT2 = 84,

    LED_UP    = 81,
    LED_DOWN  = 90,
    LED_LEFT  = 89,
    LED_RIGHT = 91

} led_index;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │ESC  │Mut│vDn│vUp│Prv│Ply│Nxt│bDn│bUp│Scn│Air│Prt│App│Del │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backsp│
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \  │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  Shift  │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     *         │    │   │   │   │                   │   │   │    │↑  │    │
     * 11 keys │Ctrl│FN │GUI│Alt│                   │Alt│Ctl│ ←  ├───┤  → │
     *         │    │   │   │   │                   │   │   │    │  ↓│    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     * 78 total
     */
    [_BASE] = LAYOUT(KC_ESC, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, MO(_FN), KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RCTL, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT),
    /*
     * Function layer
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │FN lk│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Ins │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │   │   │   │   │   │   │   │   │   │   │   │   │   │      │
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │     │   │RGB│Nxt│Hue│Sat│Spd│Brt│   │   │Pau│   │   │    │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │      │   │   │Prv│Hue│Sat│Spd│Brt│ScL│   │   │   │       │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │        │   │   │   │   │   │Brk│   │   │   │   │         │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     *         │    │   │   │   │                   │   │   │    │PgU│    │
     * 11 keys │    │   │   │   │ Toggle Backlight  │   │   │Home├───┤End │
     *         │    │   │   │   │                   │   │   │    │PgD│    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     * 78 total
     */
    [_FN] = LAYOUT(FN_LOCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_SPI, RGB_VAI, _______, _______, KC_PAUS, _______, _______, _______, _______, _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_SPD, RGB_VAD, KC_SCRL, _______, _______, _______, _______, _______, _______, _______, BL_BRTG, _______, KC_BRK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_STEP, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END),
    // Function lock layer
    // Everything on F-row locked to function layer, except ESC and DEL
    [_FN_LOCK] = LAYOUT(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(_FM), _______, _______, _______, _______, _______, _______, _______, _______, _______),
    // Locked+temporary FN (back to base plus extra keys)
    [_FM] = LAYOUT(FN_LOCK, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_INS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_SPI, RGB_VAI, _______, _______, KC_PAUS, _______, _______, _______, _______, _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_SPD, RGB_VAD, KC_SCRL, _______, _______, _______, _______, _______, _______, _______, BL_BRTG, _______, KC_BRK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_STEP, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END),
};

void set_default_colors(void) {
    rgb_matrix_set_color((int)LED_F1, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F3, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F4, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F5, 100, 100, 100);
    rgb_matrix_set_color((int)LED_F6, 100, 100, 100);
    rgb_matrix_set_color((int)LED_F7, 100, 100, 100);
    rgb_matrix_set_color((int)LED_F8, 100, 100, 100);
    rgb_matrix_set_color((int)LED_F9, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F10, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F11, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F11_2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_F12, 100, 100, 100);

    rgb_matrix_set_color((int)LED_TILDE, 70, 70, 70);
    rgb_matrix_set_color((int)LED_1, 10, 10, 10);
    rgb_matrix_set_color((int)LED_2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_3, 10, 10, 10);
    rgb_matrix_set_color((int)LED_4, 100, 100, 100);
    rgb_matrix_set_color((int)LED_5, 100, 100, 100);
    rgb_matrix_set_color((int)LED_6, 100, 100, 100);
    rgb_matrix_set_color((int)LED_7, 10, 10, 10);
    rgb_matrix_set_color((int)LED_8, 10, 10, 10);
    rgb_matrix_set_color((int)LED_9, 10, 10, 10);
    rgb_matrix_set_color((int)LED_0, 200, 200, 200);
    rgb_matrix_set_color((int)LED_MINUS, 0, 0, 0);
    rgb_matrix_set_color((int)LED_EQUALS, 0, 0, 0);

    rgb_matrix_set_color((int)LED_Q, 64, 64, 64);
    rgb_matrix_set_color((int)LED_W, 100, 100, 100);
    rgb_matrix_set_color((int)LED_E, 64, 64, 64);
    rgb_matrix_set_color((int)LED_R, 64, 64, 64);
    rgb_matrix_set_color((int)LED_T, 64, 64, 64);
    rgb_matrix_set_color((int)LED_Y, 64, 64, 64);
    rgb_matrix_set_color((int)LED_U, 64, 64, 64);
    rgb_matrix_set_color((int)LED_I, 100, 100, 100);
    rgb_matrix_set_color((int)LED_O, 64, 64, 64);
    rgb_matrix_set_color((int)LED_P, 64, 64, 64);
    rgb_matrix_set_color((int)LED_LEFT_BRACKET, 0, 0, 0);
    rgb_matrix_set_color((int)LED_RIGHT_BRACKET, 0, 0, 0);
    rgb_matrix_set_color((int)LED_BACK_SLASH, 0, 0, 0);
    rgb_matrix_set_color((int)LED_BACKSPACE, 10, 10, 10);
    rgb_matrix_set_color((int)LED_BACKSPACE2, 10, 10, 10);

    rgb_matrix_set_color((int)LED_A, 100, 100, 100);
    rgb_matrix_set_color((int)LED_S, 100, 100, 100);
    rgb_matrix_set_color((int)LED_D, 100, 100, 100);
    rgb_matrix_set_color((int)LED_F, 64, 64, 64);
    rgb_matrix_set_color((int)LED_G, 64, 64, 64);
    rgb_matrix_set_color((int)LED_H, 64, 64, 64);
    rgb_matrix_set_color((int)LED_J, 64, 64, 64);
    rgb_matrix_set_color((int)LED_K, 64, 64, 64);
    rgb_matrix_set_color((int)LED_L, 64, 64, 64);
    rgb_matrix_set_color((int)LED_SEMI_COLON, 0, 0, 0);
    rgb_matrix_set_color((int)LED_SINGLE_QUOTE, 0, 0, 0);

    rgb_matrix_set_color((int)LED_Z, 64, 64, 64);
    rgb_matrix_set_color((int)LED_X, 64, 64, 64);
    rgb_matrix_set_color((int)LED_C, 64, 64, 64);
    rgb_matrix_set_color((int)LED_V, 64, 64, 64);
    rgb_matrix_set_color((int)LED_B, 100, 100, 100);
    rgb_matrix_set_color((int)LED_N, 64, 64, 64);
    rgb_matrix_set_color((int)LED_M, 64, 64, 64);
    rgb_matrix_set_color((int)LED_COMMA, 0, 0, 0);
    rgb_matrix_set_color((int)LED_DOT, 0, 0, 0);
    rgb_matrix_set_color((int)LED_FORWARD_SLASH, 0, 0, 0);

    rgb_matrix_set_color((int)LED_DEL, 10, 10, 10);
    rgb_matrix_set_color((int)LED_DEL2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_ESC, 10, 10, 10);
    rgb_matrix_set_color((int)LED_ESC2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_ENTER, 10, 10, 10);
    rgb_matrix_set_color((int)LED_ENTER2, 10, 10, 10);

    rgb_matrix_set_color((int)LED_SPACE, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE3, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE4, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE5, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE6, 10, 10, 10);

    rgb_matrix_set_color((int)LED_RIGHT_SHIFT, 10, 10, 10);
    rgb_matrix_set_color((int)LED_RIGHT_SHIFT2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_RIGHT_SHIFT3, 10, 10, 10);
    rgb_matrix_set_color((int)LED_RIGHT_SHIFT4, 10, 10, 10);

    rgb_matrix_set_color((int)LED_LEFT_SHIFT, 10, 10, 10);
    rgb_matrix_set_color((int)LED_LEFT_SHIFT2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_LEFT_SHIFT3, 10, 10, 10);
    rgb_matrix_set_color((int)LED_CAPS, 10, 10, 10);
    rgb_matrix_set_color((int)LED_CAPS2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_CAPS3, 10, 10, 10);
    rgb_matrix_set_color((int)LED_TAB, 10, 10, 10);
    rgb_matrix_set_color((int)LED_TAB2, 10, 10, 10);

    rgb_matrix_set_color((int)LED_CTRL, 10, 10, 10);
    rgb_matrix_set_color((int)LED_CTRL2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_CTRL3, 10, 10, 10);

    rgb_matrix_set_color((int)LED_ALT, 10, 10, 10);
    rgb_matrix_set_color((int)LED_ALT2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_FN, 10, 10, 10);
    rgb_matrix_set_color((int)LED_WIN, 100, 100, 100);

    rgb_matrix_set_color((int)LED_UP, 64, 64, 64);
    rgb_matrix_set_color((int)LED_DOWN, 64, 64, 64);
    rgb_matrix_set_color((int)LED_LEFT, 64, 64, 64);
    rgb_matrix_set_color((int)LED_RIGHT, 64, 64, 64);
}

void set_ctrl_colors(void) {
    rgb_matrix_set_color((int)LED_H, 0, 0, 255);

    rgb_matrix_set_color((int)LED_I, 255, 0, 255);
    rgb_matrix_set_color((int)LED_L, 255, 0, 255);

    rgb_matrix_set_color((int)LED_V, 255, 0, 0);
    rgb_matrix_set_color((int)LED_Z, 64, 64, 0);
    rgb_matrix_set_color((int)LED_Y, 64, 64, 0);
    rgb_matrix_set_color((int)LED_X, 100, 0, 0);
    rgb_matrix_set_color((int)LED_C, 255, 0, 0);
    rgb_matrix_set_color((int)LED_S, 255, 0, 0);

    rgb_matrix_set_color((int)LED_F, 0, 0, 255);

    rgb_matrix_set_color((int)LED_SPACE, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE2, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE3, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE4, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE5, 10, 10, 10);
    rgb_matrix_set_color((int)LED_SPACE6, 10, 10, 10);
}

void set_ctrl_shift_colors(void) {
    rgb_matrix_set_color((int)LED_Q, 0, 255, 0);
    rgb_matrix_set_color((int)LED_W, 0, 255, 0);
    rgb_matrix_set_color((int)LED_D, 0, 255, 0);
    rgb_matrix_set_color((int)LED_E, 0, 255, 0);

    rgb_matrix_set_color((int)LED_SPACE, 0, 255, 0);
    rgb_matrix_set_color((int)LED_SPACE2, 0, 255, 0);
    rgb_matrix_set_color((int)LED_SPACE3, 0, 255, 0);
    rgb_matrix_set_color((int)LED_SPACE4, 0, 255, 0);
    rgb_matrix_set_color((int)LED_SPACE5, 0, 255, 0);
    rgb_matrix_set_color((int)LED_SPACE6, 0, 255, 0);

    rgb_matrix_set_color((int)LED_H, 64, 64, 64);

    rgb_matrix_set_color((int)LED_I, 64, 64, 64);
    rgb_matrix_set_color((int)LED_L, 64, 64, 64);

    rgb_matrix_set_color((int)LED_V, 64, 64, 64);
    rgb_matrix_set_color((int)LED_Z, 64, 64, 64);
    rgb_matrix_set_color((int)LED_Y, 64, 64, 64);
    rgb_matrix_set_color((int)LED_X, 64, 64, 64);
    rgb_matrix_set_color((int)LED_C, 64, 64, 64);
    rgb_matrix_set_color((int)LED_S, 64, 64, 64);
    rgb_matrix_set_color((int)LED_F, 64, 64, 64);
}

void print_all_led_indexes_for_keycode(uint16_t keycode) {
    for (uint8_t layer = 0; layer < sizeof(keymaps) / sizeof(keymaps[0]); ++layer) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                if (pgm_read_word(&keymaps[layer][row][col]) == keycode) {
                    int led_idx = g_led_config.matrix_co[row][col];
                    uprintf("Layer %d, Row %d, Col %d: LED Indexxxx %d keycode: %d\n", layer, row, col, led_idx, keycode);
                }
            }
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    set_default_colors();

    // Red when Left Control is held
    if (get_mods() & MOD_LCTL) {
        set_ctrl_colors();
    } else {
        set_default_colors();
    }

    if ((get_mods() & MOD_LCTL) && (get_mods() & MOD_LSFT)) {
        // Set breathing effect for Q, W, D, E if animation is supported
        set_ctrl_shift_colors();
    } else if (get_mods() & MOD_LCTL) {
        set_ctrl_colors();
    } else {
        set_default_colors();
    }

    return true;
}

// Make sure to keep FN Lock even after reset
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    print_all_led_indexes_for_keycode(keycode);

    switch (keycode) {
        case FN_LOCK:
            if (record->event.pressed) {
                if (layer_state_is(_FN)) {
                    set_single_persistent_default_layer(_FN_LOCK);
                }
                if (layer_state_is(_FM)) {
                    set_single_persistent_default_layer(_BASE);
                }
            }
            return false;
            break;
        default:
            break;
    }
    return true;
}