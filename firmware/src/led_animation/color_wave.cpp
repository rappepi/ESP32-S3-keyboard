#include "color_wave.h"

void color_wave(CRGB* Leds) {
  const uint8_t WaveBPM = 30;
  const uint8_t HueBPM  = 10;
  const uint8_t Tilt    = 64;
  const bool Reverse    = 0;
  color_wave(WaveBPM, HueBPM, Tilt, Reverse, Leds);
}

void color_wave(uint8_t WaveBPM, uint8_t HueBPM, uint8_t Tilt, bool Reverse, CRGB* Leds) {
  // tMove : phase qui fait "avancer" la vague en X
  uint8_t tMove = beat8(WaveBPM);    // 0..255
  if (Reverse) tMove = 255 - tMove;

  // tHue : pour faire tourner le nuancier au fil du temps
  uint8_t tHue  = beat8(HueBPM);     // 0..255

  for (uint8_t y = 0; y < LED_ROWS_COUNT; ++y) {
    // Normalisation 0..255 sur la hauteur (évite division par 0 si RowsCount==1)
    uint8_t yNorm = (LED_ROWS_COUNT > 1) ? (uint8_t)((y * 255) / (LED_ROWS_COUNT - 1)) : 0;

    for (uint8_t x = 0; x < LED_COLUMNS_COUNT; ++x) {
      // Normalisation 0..255 sur la largeur
      uint8_t xNorm = (LED_COLUMNS_COUNT > 1) ? (uint8_t)((x * 255) / (LED_COLUMNS_COUNT - 1)) : 0;

      // Phase de la vague : avance en X + légère inclinaison selon Y
      // scale8(a, b) ≈ (a*b)/255, pratique pour doser l'influence du y
      uint8_t phase = xNorm + scale8(yNorm, Tilt) + tMove;

      // Luminosité suivant la sinusoïde ; min 40 pour éviter le noir total
      uint8_t bri = qadd8(40, scale8(sin8(phase), 215)); // 40..255

      // Teinte : un arc-en-ciel doux qui suit la phase/position
      uint8_t hue = tHue + x * 4;  // augmente légèrement avec x

      // Application de la couleur via ton mapping [ligne][colonne]
      Leds[LedMap[y][x]] = CHSV(hue, 255, bri);
    }
  }
}