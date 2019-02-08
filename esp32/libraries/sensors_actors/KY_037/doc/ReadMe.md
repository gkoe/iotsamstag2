# Library KY-037

## Ziele

Der ESP soll mit Hilfe dieser Libary die Lautstärke von einen KY-037 Sensor lesen können dabei sollen die Analoge Werte in Decibel Werte umgewandelt werden.
Dieser Libary blockiert nicht den ESP dadurch gibt es keine Wartezeiten.

Diese Libary ist von der Libary Statemachine abhängig.

## Hardware

Es wird benötigt:
- ESP32 
- KY-037

Dabei muss KY-037 einen Analogen Wert zwischen 300 - 1000 ausgeben sonst sind die wert zu ungenau. Weiters sollte der KY-037 auf 3.3 Volt angeschlossen werden.

## Software

### Beispielaufrufe

```c
#include <Arduino.h>
#include <math.h>
#include <KY_037.h>

KY_037 *ky_037;
  
void setup ()
{
  Serial.begin (115200); 
	ky_037 = new KY_037(12, 13, 30, "test", "test", "db", 5.0);
}
  
void loop ()
{
	ky_037->getMeasure();
	delay(100);
}
```

### Erklärung

* ```KY_037(uint8_t dpin, uint8_t apin, uint8_t interval, const char* thingname,  const char* name, const char* unit, float threshold)``` 
Muss als erstes aufgerufen werden. Darin werden die Pins festlegen. 

### Library

##### Methoden

| ```KY_037::``` | Erklärung |
|-|-|
|```    KY_037(uint8_t dpin, uint8_t apin, uint8_t interval, const char* thingname,  const char* name, const char* unit, float hreshold)```| Setzt die Pins und den interval beim KY_037 Sensor. |
|```float getDB()``` | Gibt den letzten DB-Messwert zurück.  |
|```virtual float getMeasure()``` | Erhaltet den DB-Wert und gibt diesen zurück. |
