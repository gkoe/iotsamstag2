#include <Arduino.h>
#include <math.h>
#include <KY_037.h>

KY_037 *ky_037;
  
void setup ()
{
  	Serial.begin (115200); 
	ky_037 = new KY_037(4, 2, 30, "test", "test", "db", 5.0);
}
  
// Das Programm liest die aktuellen Werte der Eingang-Pins
// und gibt diese auf der seriellen Ausgabe aus
void loop ()
{
	ky_037->getMeasure();
	delay(10);
}
