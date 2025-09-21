#ifndef keyboard_matrix_config_H
#define keyboard_matrix_config_H

#include <stdint.h>
#include <cstddef>
#include "usb_hid_keys.h"
#include "utils.h"

#define ROW_1_PIN 14
#define ROW_2_PIN 13
#define ROW_3_PIN 12
#define ROW_4_PIN 11
#define ROW_5_PIN 8
#define ROW_6_PIN 18
#define ROW_7_PIN 17

#define ROWS_COUNT      7
#define COLUMNS_COUNT   21

#define DEBOUNCE_TIME_MS 5

constexpr uint8_t rows_pin[] = {ROW_1_PIN, ROW_2_PIN, ROW_3_PIN, ROW_4_PIN, ROW_5_PIN, ROW_6_PIN, ROW_7_PIN};

//Create the mask to read the rows pins. Rows pin should be < 32
constexpr uint32_t make_rows_mask(const uint8_t* pins, size_t size) {
    uint32_t mask = 0;
    for (size_t i = 0; i < size; i++) {
        mask |= ((uint32_t)1 << pins[i]);
    }
    return mask;
}

constexpr uint32_t rows_mask = make_rows_mask(rows_pin, ARRAY_SIZE(rows_pin));

const uint8_t keyboard_map[ROWS_COUNT][COLUMNS_COUNT] = {
    //Row 1
    {KEY_NONE, KEY_NONE, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    //Row 2
    {KEY_ESC, KEY_NONE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_SYSRQ, KEY_SCROLLLOCK, KEY_PAUSE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    //Row 3
    {KEY_GRAVE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGEUP, KEY_NUMLOCK, KEY_KPSLASH, KEY_KPASTERISK, KEY_KPMINUS},
    //Row 4
    {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_ENTER, KEY_DELETE, KEY_END, KEY_PAGEDOWN, KEY_KP7, KEY_KP8, KEY_KP9, KEY_KPPLUS},
    //Row 5
    {KEY_CAPSLOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_HASHTILDE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_KP4, KEY_KP5, KEY_KP6, KEY_NONE},
    //Row 6
    {KEY_LEFTSHIFT, KEY_102ND, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHTSHIFT, KEY_NONE, KEY_NONE, KEY_UP, KEY_NONE, KEY_KP1, KEY_KP2, KEY_KP3, KEY_KPENTER},
    //Row 7
    {KEY_LEFTCTRL, KEY_LEFTMETA, KEY_LEFTALT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_SPACE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_RIGHTALT, KEY_RIGHTMETA, KEY_PROPS, KEY_RIGHTCTRL, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_KP0, KEY_NONE, KEY_KPDOT, KEY_NONE}
};

#endif