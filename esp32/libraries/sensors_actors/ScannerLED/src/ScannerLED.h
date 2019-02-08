#pragma once
#include <Arduino.h>
#include <esp32_digital_led_lib.h>

class ScannerLED {
  private:
    strand_t * pStrand;
    pixelColor_t minColor;
    pixelColor_t maxColor;
    int prevIdx;
    int currIdx;
  public:
    ScannerLED(strand_t *, pixelColor_t);
    void drawNext();
};
