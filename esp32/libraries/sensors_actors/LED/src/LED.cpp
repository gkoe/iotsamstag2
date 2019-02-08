#include "LED.h"
#include <Actor.h>
#include <esp32_digital_led_lib.h>
#include <RainbowLED.h>
#include <ScannerLED.h>


LED::LED(int pin, int pixels, const char* thingName, const char* name )
	:Actor(thingName, name)
{
	_pStrand = {.rmtChannel = 0, .gpioNum = pin, .ledType = LED_WS2812B_V3, .brightLimit = 32, .numPixels = pixels, .pixels = nullptr, ._stateVars = nullptr};
	pinMode (16, OUTPUT);
  digitalWrite (16, LOW);
	_pixels = pixels;
	if (digitalLeds_initStrands(&_pStrand, 1)) {
    Serial.println("Init FAILURE: halting");
    while (true) {};
  }
	Serial.println("LED started.");
	digitalLeds_resetPixels(&_pStrand);
}

void LED::setActorTo(float value)
{
	if (value > 0.5)
	{
		Serial.println(F("*PS: set pin high!"));
		pixelColor_t pixel = pixelFromRGBW(0, 0, 100, 0);
		scanner(pixel, 50, pixels*10*50);
	}
	else
	{
		Serial.println(F("*PS: set pin low!"));
		pixelColor_t pixel = pixelFromRGBW(0, 0, 0, 0);
		scanner(pixel, 50, pixels*10*50);
	}
}

float LED::readStateFromActor()
{
	if (digitalRead(_pin) == HIGH)
	{
		return 1;
	}
	else{
		return 0;
	}
}

void LED::scanners(strand_t * strands[], pixelColor_t scanColors, int numStrands, unsigned long delay_ms, unsigned long timeout_ms)
{
  ScannerLED * pScanner[numStrands];
  int i;
  Serial.print("DEMO: scanners(");
  for (i = 0; i < numStrands; i++) {
    pScanner[i] = new ScannerLED(strands[i], scanColors);
    if (i > 0) {
      Serial.print(", ");
    }
    Serial.print("ch");
    Serial.print(strands[i]->rmtChannel);
    Serial.print(" (0x");
    Serial.print((uint32_t)pScanner[i], HEX);
    Serial.print(")");
    Serial.print(" #");
    Serial.print((uint32_t)scanColors.num, HEX);
  }
  Serial.print(")");
  Serial.println();
  unsigned long start_ms = millis();
  while (timeout_ms == 0 || (millis() - start_ms < timeout_ms)) {
    for (i = 0; i < numStrands; i++) {
      pScanner[i]->drawNext();
    }
    delay(delay_ms);
  }
  for (i = 0; i < numStrands; i++) {
    delete pScanner[i];
    digitalLeds_resetPixels(strands[i]);
  }
}

void LED::scanner(pixelColor_t scanColors, unsigned long delay_ms, unsigned long timeout_ms)
{
  strand_t * strands [] = { &_pStrand };
  scanners(strands, scanColors, 1, delay_ms, timeout_ms);
}

void LED::scanner(unsigned long delay_ms, unsigned long timeout_ms)
{
  strand_t * strands [] = { &_pStrand };
  uint8_t c = strands[0]->brightLimit; // TODO: improve
  scanners(strands, pixelFromRGBW(c, c, c, c), 1, delay_ms, timeout_ms);
}

void LED::rainbows(strand_t * strands[], int numStrands, unsigned long delay_ms, unsigned long timeout_ms)
{
  //Rainbower rbow(pStrand); Rainbower * pRbow = &rbow;
  RainbowLED * pRbow[numStrands];
  int i;
  Serial.print("DEMO: rainbows(");
  for (i = 0; i < numStrands; i++) {
    pRbow[i] = new RainbowLED(strands[i]);
    if (i > 0) {
      Serial.print(", ");
    }
    Serial.print("ch");
    Serial.print(strands[i]->rmtChannel);
    Serial.print(" (0x");
    Serial.print((uint32_t)pRbow[i], HEX);
    Serial.print(")");
  }
  Serial.print(")");
  Serial.println();
  unsigned long start_ms = millis();
  while (timeout_ms == 0 || (millis() - start_ms < timeout_ms)) {
    for (i = 0; i < numStrands; i++) {
      pRbow[i]->drawNext();
    }
    delay(delay_ms);
  }
  for (i = 0; i < numStrands; i++) {
    delete pRbow[i];
    digitalLeds_resetPixels(strands[i]);
  }
}

void LED::rainbow(unsigned long delay_ms, unsigned long timeout_ms)
{
  strand_t * strands [] = { &_pStrand };
  rainbows(strands, 1, delay_ms, timeout_ms);
}

void LED::staticLight(pixelColor_t color) {
	for(int a = 0; a < _pixels; a++) {
    _pStrand.pixels[a] = color; 
  }
	digitalLeds_updatePixels(&_pStrand);
}
