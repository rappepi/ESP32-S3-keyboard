#ifndef colorWave_H
#define colorWave_H

#include "../led_matrix_config.h"
#include <stdint.h>
#include <stdbool.h>
#include <FastLED.h>

void color_wave(uint8_t WaveBPM, uint8_t HueBPM, uint8_t Tilt, bool Reverse, CRGB* Leds);

void color_wave(CRGB* Leds);

#endif