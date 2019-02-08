#include <RgbLed.h>

#define R 13
#define G 12
#define B 14

/****************************************** Statische Variablen **************************************/

RgbLed rgbLed(R, G, B, "RgbThing", "Test");

/****************************************** Setup **************************************/

void setup()
{
	Serial.begin(115200); //Initialisierung der seriellen Schnittstelle
	Serial.println();
	Serial.println("RgbLedTest");
	Serial.println("==========");
	Serial.println();
}

/****************************************** Loop **************************************/

void loop()
{
	float color = RGB_RED;
	Serial.println("Rot");
	rgbLed.setActorTo(color);
	delay(2000);
	color = RGB_GREEN;
	Serial.println("Grün");
	rgbLed.setActorTo(color);
	delay(2000);
	color = RGB_BLUE;
	Serial.println("Blau");
	rgbLed.setActorTo(color);
	delay(2000);
	color = 0;
	Serial.println("Aus");
	rgbLed.setActorTo(color);
	delay(2000);
	color = 10 * 10 * 100 + 10 * 100 + 10;
	Serial.println("Rot/Grün/Blau dunkel");
	rgbLed.setActorTo(color);
	delay(2000);
	color = 99 * 100 * 100 + 99 * 100;
	Serial.println("Rot/Grün");
	rgbLed.setActorTo(color);
	delay(2000);
}
