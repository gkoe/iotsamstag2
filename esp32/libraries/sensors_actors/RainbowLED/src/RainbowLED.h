#pragma once
#include <Arduino.h>
#include <esp32_digital_led_lib.h>

class RainbowLED {
  private:
    strand_t * pStrand;
    const uint8_t color_div = 4;
    const uint8_t anim_step = 1;
    uint8_t anim_max;
    uint8_t stepVal1;
    uint8_t stepVal2;
    pixelColor_t color1;
    pixelColor_t color2;
  public:
    RainbowLED(strand_t *);
    void drawNext();
};
