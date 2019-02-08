#include <Arduino.h>

#define BUILTIN_LED 2

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Builtin Led blink");
  Serial.println("=================");
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
  Serial.println("Led ON");
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);
  Serial.println("Led OFF");
  digitalWrite(BUILTIN_LED, LOW);
  delay(2000);
}