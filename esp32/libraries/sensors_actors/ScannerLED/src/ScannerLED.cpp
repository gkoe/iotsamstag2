#include <Arduino.h>
#include <ScannerLED.h>
#include <esp32_digital_led_lib.h>

ScannerLED::ScannerLED(strand_t * pStrandIn, pixelColor_t maxColorIn)
{
  pStrand = pStrandIn;
  minColor = pixelFromRGBW(0, 0, 0, 0);
  maxColor = maxColorIn;
  prevIdx = 0;
  currIdx = 0;
}

void ScannerLED::drawNext()
{
  pStrand->pixels[prevIdx] = minColor;
  pStrand->pixels[currIdx] = maxColor;
  digitalLeds_updatePixels(pStrand);
  prevIdx = currIdx;
  currIdx++;
  if (currIdx >= pStrand->numPixels) {
    currIdx = 0;
  }
}
