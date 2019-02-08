#define WEMOS

#ifdef WEMOS
	#define LED_BUILTIN_PIN 2  // WEMOS MINI32
#else 
	#ifdef TTGO
		#define LED_BUILTIN_PIN 16  // TTGO
	#endif
#endif	

#include <Arduino.h>
#include <FS.h> //this needs to be first, or it all crashes and burns...
#include <WiFiManager.h>
#include <InternLed.h>
#include <SPIFFS.h>

/*************************************** Setup ******************************/
void setup() {
	Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
	Serial.println();
	Serial.println();
	Serial.println(F("Reset Thing"));
	Serial.println(F("==========="));
	InternLed.init(LED_BUILTIN_PIN);
	for(int i=5; i>0; i--){
		Serial.print("Factory-Reset in ");
		Serial.print(i);
		Serial.println(" Sekunden");
		delay(1000);
	}
	InternLed.blinkSlow();
	delay(1000);
	Serial.println(F("*HS Format flash memory!"));
	SPIFFS.format();
	Serial.println(F("*HS Done!"));
	WiFi.disconnect(true);
	WiFiManager wifiManager;
	Serial.println(F("*HS WifiManager resetSettings()"));
	wifiManager.resetSettings();
	Serial.println(F("*HS Done!"));
	InternLed.blinkOff();

}

/*************************************** Loop ******************************/
void loop() {
	delay(1);
}

