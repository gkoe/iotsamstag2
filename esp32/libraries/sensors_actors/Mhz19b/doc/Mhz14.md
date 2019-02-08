# Library Mhz14a

## Ziele

Der ESP soll mit Hilfe dieser Libary die Werte von einen Mhz14a Sensor lesen.
Dieser Libary blockiert nicht den ESP dadurch gibt es keine Wartezeiten.

Diese Libary ist von der Libary Sensor abhängig.

## Hardware

Es wird lediglich ein ESP32 und ein Mhz14a Sensor benötigt.

## Software

### Beispielaufrufe

```c
#include <Arduino.h> 
#include <SoftwareSerial.h>
#include <Mhz14a.h>


SoftwareSerial* _softwareSerialPtr;
int Txpin = 12;
int Rxpin = 13;
 

Mhz14a _mhz(Rxpin,Txpin,"Esp","Co2","ppm",5.0);


void setup() {
  Serial.begin(115200);
  Serial.println(F("MHZ14-Test"));
  Serial.println(F("=========="));  
  _mhz.calibrate();
  delay(500);
}

void loop() {
  float ppm = _mhz.getCo2();
  Serial.print("PPM: ");
  Serial.println(ppm);
  delay(1000);
}
```

### Erklärung

* ```Mhz14a(int rxPin, int txPin, const char *nodeName, const char *name, const char *unit, float threshold)``` Muss als erstes aufgerufen werden. Darin wird der Pin festlegen. 

### Library

##### Methoden

| ```Mhz14a::``` | Erklärung |
|-|-|
|```	Mhz14a(int rxPin, int txPin, const char* nodeName, const char* name, const char* unit, float threshold)```| Setzt die Pins beim Mhz14a Sensor. |
|```float getCo2()``` | Gibt den letzten CO2-Messwert zurück.  |
|```virtual void measure()``` | Ruft die Methoden getCo2 und setMeasurement (abhängig von Sensor) auf und setzt die Werte |
