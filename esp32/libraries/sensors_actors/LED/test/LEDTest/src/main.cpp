#include <Arduino.h>
#include <LED.h>

LED *led;

void setup() {
	Serial.begin(115200);
  led = new LED(25, 15, "LED", "LED");
}

void loop() {
	led->scanner(pixelFromRGBW(0, 255, 0, 255), 1000, 15000);
}
