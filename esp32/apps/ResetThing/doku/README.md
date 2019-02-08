# ResetThing

## Ziele
Ein bereits eingesetzter ESP merkt sich sensible Daten in seiner ThingConfig und die Wifi-Credentials am System. Mit ResetThing wird der ESP wieder in den Auslieferungszustand versetz und kann bedenkenlos weitergegeben werden.
Dazu werden die Wifi-Credentials über den Wifi-Manager gelöscht und das Filesystem über SPIFFS formatiert.

## Abhängigkeiten
- WifiManager zum Löschen der Wifi-Credentials
- SPIFFS zum Formatieren des Filesystems
- InternLed für die Benutzerinteraktion (blinkt während des Reset)


## Programm
Das Rücksetzen startet nach einer Karenzzeit von 5 Sekunden.

````c
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

````

### UI der App

````
Reset Thing
===========
Factory-Reset in 5 Sekunden
Factory-Reset in 4 Sekunden
Factory-Reset in 3 Sekunden
Factory-Reset in 2 Sekunden
Factory-Reset in 1 Sekunden
*HS Format flash memory!
*HS Done!
*HS WifiManager resetSettings()
*WM: [1] SETTINGS ERASED
*WM: [3] WiFi station enable
*HS Done!
*WM: [3] unloading
````


