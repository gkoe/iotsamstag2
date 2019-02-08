# Library TSL2561

## Ziele

Der ESP soll mit Hilfe dieser Libary die Lux von einen TSL2561 Sensor lesen.
Dieser Libary blockiert nicht den ESP dadurch gibt es keine Wartezeiten.

Diese Libary ist von der Libary StateMachine und der Adafruit Libary TSL2561_U abhängig.

## Hardware

Es wird benötigt:
- ESP32 
- TSL2561

## Software

### Beispielaufrufe

```c
#include <Arduino.h>
#include <Wire.h>
#include <TSL2561.h>

TSL2561* tsl2561;

void setup() {
	Serial.begin(115200);
  tsl2561 = new TSL2561(4, 5, 30, "Light", "test", "Lux", 30);
}

void loop() {
  tsl2561->getMeasure();
}
```

### Erklärung

* ```TSL2561(uint8_t SDA, uint8_t SCL, const int interval, const char* thingname, const char * name, const char* unit, float threshold)``` 
Muss als erstes aufgerufen werden. Darin wird der interval festgelegt so wie die Pins wo der TLS angeschlossen wird.

### Library

##### Methoden

| ```TSL2561:``` | Erklärung |
|-|-|
|```TSL2561(uint8_t SDA, uint8_t SCL, const int interval, const char* thingname, const char * name, const char* unit, float threshold)```| Setzt die Pins und den interval beim TLS2561 Sensor. |
|```float getLux()``` | Gibt den letzten Lux-Messwert zurück.  |
|```virtual float getMeasure()``` | Erhaltet den Lux-Wert und gibt diesen zurück. |
