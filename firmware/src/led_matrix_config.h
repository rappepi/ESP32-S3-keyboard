#ifndef ledMatrixConfig_H
#define ledMatrixConfig_H

#include <stdint.h>

#define LED_PIN_1       42
#define LED_PIN_2       41
#define LED_COUNT_1     52
#define LED_COUNT_2     68
#define LED_COUNT       (LED_COUNT_1 + LED_COUNT_2)
#define LED_TYPE        SK6812

#define LED_ROWS_COUNT      7
#define LED_COLUMNS_COUNT   21

#define DEFAULT_BRIGHTNESS      50
#define LED_FRAME_RATE          30
#define LED_FRAME_INTERVAL_MS   (1000/LED_FRAME_RATE)

const uint8_t LedMap[LED_ROWS_COUNT][LED_COLUMNS_COUNT] = {        //255 means no led (spacing)
    //Row 1
    {255, 255, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 255, 255, 255, 255},
    //Row 2
    {21, 255, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 255, 255, 255, 255},
    //Row 3
    {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
    //Row 4
    {72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52},
    //Row 5
    {73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 255, 255, 255, 255, 86, 87, 88, 255},
    //Row 6
    {106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 255, 255, 93, 255, 92, 91, 90, 89},
    //Row 7
    {107, 108, 109, 255, 255, 255, 110, 255, 255, 255, 111, 112, 113, 114, 115, 116, 117, 118, 255, 119, 255}
};

#endif