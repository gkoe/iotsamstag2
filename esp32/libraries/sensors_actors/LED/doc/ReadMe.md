# Library LED

## Ziele

Der ESP soll mit Hilfe dieser Library und einer LED. Die LED soll verschieden Farben anzeigen können. Weiters ist es möglich Animationen wie einen Regenbogen oder langsam die einzelnen Farben der LED erleuchten soll.
Diese Libary ist von der Libary Actor abhängig.

## Hardware

Es wird verwendet: 
* ESP32
* LED's

### Anschluss

Der Anschluss ist sehr einfach ein PIN muss auf den GND einer muss auf 5 Volt und der letzte muss mit eine PIN des ESP angesteckt werden. Dieser braucht auch das Programm zum übertragen des wird. 

## Software

### Test

```c
#include <Arduino.h>
#include <LED.h>

LED *led;

void setup() {
	Serial.begin(115200);
  led = new LED(16, 50, "LED", "LED");
}

void loop() {
  led->setActorTo(1);
	delay(1000);
	led->setActorTo(0);
	delay(1000);
}
```

### Erklärung

* ```LED(int pin, int pixels, const char* thingName, const char* name)``` Über Konstruktor wird der Pin die Anzahl der Led's.

### Library

|Methode| Erklärung |
|-|-|
|```LED(int pin, int pixels, const char* thingName, const char* name)```| Setzt den Pin und die Anzahl der Led's. |
|```void setActorTo(float value)``` | Setzt den Actor auf ON or OFF |
|```float readStateFromActor()``` | Gibt den aktuellen Wert von den Led's zurück. |
|```void rainbow(unsigned long delay_ms, unsigned long timeout_ms)```| Setzt die Leds auf einen Regenbogeneffekt dabei braucht man die Millisekunden bis sich die nächste LED ändern soll(delay_ms) und zum anderen wie lange diese Animation dauern soll(timeout_ms). |
|```void scanner(unsigned long delay_ms, unsigned long timeout_ms)```| Setzt die Leds auf einen Leuchturmeffekt dabei braucht man die ms bis sich die nächste LED ändern soll(delay_ms) und zum anderen wie lange diese Animation dauern soll.(timeout_ms) Standardmäßig wird hier weiß als Farbe genommen.|
|```void scanner(pixelColor_t scanColors, unsigned long delay_ms, unsigned long timeout_ms)```| Setzt die Leds auf einen Leuchturmeffekt dabei braucht man die ms bis sich die nächste LED ändern soll(delay_ms) und zum anderen wie lange diese Animation dauern soll.(timeout_ms). Die besonderheit hier ist das man die Farbe mitgeben kann(scanColors). ``` pixelFromRGBW(0, 255, 0, 255) ```(Grün)|
