#include <Arduino.h>
#include <Wire.h>
#include <TSL2561.h>

TSL2561* tsl2561;

void setup() {
	Serial.begin(115200);
  tsl2561 = new TSL2561(2, 4, 30, "Light", "test", "Lux", 30);
}

void loop() {
  tsl2561->getMeasure();
}
