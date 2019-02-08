#include <Arduino.h> // required before wiring_private.h
#define PIR_PIN 26

int lastChangeMs;
int lastState;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("PIR-Test"));
  Serial.println(F("========="));  
  pinMode(PIR_PIN, INPUT_PULLUP);
}



void loop() {
  delay(1);
}

