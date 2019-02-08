#include <Arduino.h>
#include <Beeper.h>

#define BEEPER_PIN 4
Beeper * beeper;

void setup() {
	Serial.begin(115200);
	Serial.println("Beepertest");
  beeper = new Beeper(BEEPER_PIN,"BeeperThing", "beeper");
}

void loop() {
	Serial.println("Beeper ON");
  beeper->setActorTo(1.0);
	delay(2000);
	Serial.println("Beeper OFF");
	beeper->setActorTo(0);
	delay(5000);
}
