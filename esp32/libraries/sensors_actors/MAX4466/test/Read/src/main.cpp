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