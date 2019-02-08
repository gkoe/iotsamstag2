#include <Arduino.h> // required before wiring_private.h
#define PIR_PIN 16

int lastChangeMs;
int lastState;

void setup() {
  Serial.begin(115200);
  Serial.println(F("PIR-Test"));
  Serial.println(F("========="));  
  pinMode(PIR_PIN, INPUT_PULLUP);
  lastChangeMs = millis();
  lastState = digitalRead(PIR_PIN);
}



void loop() {
  int state = digitalRead(PIR_PIN);
  if(state != lastState){
    int duration = millis() - lastChangeMs;
    Serial.printf("State changed from %d to %d after %dms\n", lastState, state, duration);
    lastChangeMs=millis();
    lastState = state;
  }
  delay(1);
}

