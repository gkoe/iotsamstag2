# Library MAX4466

## Ziele

Der ESP soll mit Hilfe dieser Libary die Lautstärke von einen MAX4466 Sensor lesen können dabei sollen die Analoge Werte in Decibel Werte umgewandelt werden.
Dieser Libary blockiert nicht den ESP dadurch gibt es keine Wartezeiten.

Diese Libary ist von der Libary Statemachine abhängig.

## Hardware

Es wird benötigt:
- ESP32 
- MAX4466

Der MAX4466 sollte auf 3.3 Volt angeschlossen werden.

## Software

### Beispielaufrufe

```c
#include <Arduino.h>
#include <math.h>
#include <MAX4466.h>

MAX4466 *max4466;
  
void setup ()
{
  Serial.begin (115200); 
	max4466 = new MAX4466(32, 30, "test", "test", "db", 5.0);
}
  
// Das Programm liest die aktuellen Werte der Eingang-Pins
// und gibt diese auf der seriellen Ausgabe aus
void loop ()
{
	max4466->getMeasure();
	delay(10);
}
```

### Erklärung

* ```MAX4466(uint8_t apin, uint8_t interval, const char* thingname,  const char* name, const char* unit, float threshold)``` 
Konstruktor muss als Erstes aufgerufen werden, da dort der Pin festgelegt wird und der Sensor kalibriert wird.

### Library

##### Methoden

| ```MAX4466::``` | Erklärung |
|-|-|
|```    MAX4466(uint8_t apin, uint8_t interval, const char* thingname,  const char* name, const char* unit, float hreshold)```| Setzt den Pin und den interval beim MAX4466 Sensor. |
|```float getDB()``` | Gibt den letzten DB-Messwert zurück.  |
|```virtual float getMeasure()``` | Erhaltet den DB-Wert und gibt diesen zurück. |
|```void calibrate()``` | Kalibriert den Sensor. |
