# Library Beeper

## Ziele

Der ESP soll mit Hilfe dieser Library und einem Beeper-Actors Geräusche ausgeben können.
Diese Libary ist von der Libary Actor abhängig.

## Hardware

Es wird verwendet: 
* ESP32
* Beeper

### Anschluss

Der Anschluss ist sehr einfach ein PIN muss auf den GND der andere ist zum Anstecken des PIN welcher in Programm übergeben wird. 

## Software

### Test

```c
#include <Arduino.h>
#include <Beeper.h>

Beeper * beeper;

void setup() {
	Serial.begin(115200);
	Serial.println("test");
  beeper = new Beeper(0, true, "beeper", "switch");
	Serial.println("test");
}

void loop() {
	Serial.println("test");
  beeper->setActorTo(1);
	delay(5000);
	beeper->setActorTo(0);
	delay(5000);
}
```

### Erklärung

* ```Beeper(int pin, bool beep, const char* thingName, const char* name)``` Über Konstruktor wird der Pin und ob der Beeper gleich einen Sound von sich geben soll.

### Library

|Methode| Erklärung |
|-|-|
|```	`Beeper(int pin, bool beep, const char* thingName, const char* name)```| Setzt den Pin und ob er sofort einen Sound ausgeben soll. |
|```void setActorTo(float value)``` | Setzt den Actor auf ON or OFF |
|```float readStateFromActor()``` | Gibt den aktuellen Wert von Beeper zurück. |
