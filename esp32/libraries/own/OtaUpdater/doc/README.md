# Library OtaUpdater (OverTheAir-Updater)

## Ziele

Diese Bibliothek kapselt die Möglichkeit, die Programmierung des ESP statt über die serielle Schnittstelle über das WLAN durchführen zu können.
Das bietet folgende Vorteile:
- Keine kabelgebundene Verbindung zum ESP notwendig
	- ESP ist in Gerät verbaut und nicht direkt zugänglich
	- ESP ist im Nahbereich gefährlicher Spannungen (z.B. Powerswicht für 230V) im Einsatz und soll deshalb nicht zugänglich sein

Es gibt aber auch einige Einschränkungen:
-	Flashspeicher muss mindestens doppelt so groß sein, wie das Programm
-	Erste Programmierung muss über serielle Verbindung erfolgen

### Abhängigkeiten

- WifiHttpServer zur Verbindung mit dem WLAN


## Hardware

Es wird lediglich ein NodeMCU benötigt.

## UserInterface

Der Benutzer verbindet sich über den WifiHttpServer mit dem ESP und trägt diese Adresse in platformio.ini als Portadresse ein
````
upload_port = 10.0.0.142
````

## Software

### Testanwendung am ESP

Ein kleines Testprogramm überprüft die Funktion der Bibliothek. Der ESP verbindet sich über den WifiHttpServer mit dem WLAN, initialisiert den OTA-Updater und wartet in der loop() auf Updateanforderungen.

Die beiden OTA-Zeilen sind bei Bedarf in die eigenen Programme zu übernehmen. Den Rest erledigt die OtaUpdater-Bibliothek.


````c
#include <WifiHttpServer.h>
#include <OtaUpdater.h>

void setup() {
    Serial.begin(115200);
	Serial.println();
	Serial.println();
	Serial.println("OtaUpdaterTest");
	Serial.println("==============");
	WifiHttpServer.init();
	OtaUpdater.init();
}

int delayToNextWrite = 1000;
void loop() {
	WifiHttpServer.handleClient();
	OtaUpdater.checkForUpdate();
	delay(1);
	delayToNextWrite--;
	if(delayToNextWrite <= 0){
		delayToNextWrite=1000;
		Serial.print(".");
	}
}````

### Bibliothek OtaUpdater

Die Bibliothek kapselt die entsprechenden Methoden der Klasse ArduinoOTA.

````c
//OtaUpdater.cpp
#include "OtaUpdater.h"


OtaUpdaterClass::OtaUpdaterClass() {
}

void OtaUpdaterClass::init() {
	// OTA config
	// Port defaults to 8266
    ArduinoOTA.setPort(8266);
    // Hostname defaults to esp8266-[ChipID]
    // ArduinoOTA.setHostname("myesp8266");
    // No authentication by default
    // ArduinoOTA.setPassword((const char *)"123");
    ArduinoOTA.onStart([]() {
		Serial.println("Start");
	  });
	  ArduinoOTA.onEnd([]() {
		Serial.println("\nEnd");
	  });
	  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	  });
	  ArduinoOTA.onError([](ota_error_t error) {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed");
	  });
	  ArduinoOTA.begin();
}

void OtaUpdaterClass::checkForUpdate() {
    ArduinoOTA.handle();
}

// Quasi Singleton
OtaUpdaterClass OtaUpdater;
````

## UI des OTA-Uploads

Die Binärdatei des erstellten Programms wird an den OTA-Client am ESP über die angegebene IP-Adresse und den Standardport 8266 übermittelt.

````
Building .pioenvs\d1_mini\firmware.bin
Looking for upload port...
Use manually specified: 10.0.0.142
Uploading .pioenvs\d1_mini\firmware.bin
18:52:03 [DEBUG]: Options: {'esp_ip': '10.0.0.142', 'host_port': 37927, 'image': '.pioenvs\\d1_mini\\firmware.bin', 'host_ip': '0.0.0.0', 'auth': '', 'esp_port': 8266, 'spiffs': False, 'debug':
 True, 'progress': True}
18:52:03 [INFO]: Starting on 0.0.0.0:37927
18:52:03 [INFO]: Upload size: 263376
18:52:03 [INFO]: Sending invitation to: 10.0.0.142
18:52:04 [INFO]: Waiting for device...
Uploading: [============================================================] 100% Done...

18:52:11 [INFO]: Waiting for result...
18:52:11 [INFO]: Result: OK
````

## Absichern des Uploads mit Kennwort und Portnummer
Damit nicht jeder Angreifer, der Zugriff zum WLAN hat, die Firmware der Geräte überspielen kann, wird die Verbindung, wenn schon nicht verschlüsselt, so doch mit einem Kennwort abgesichert.
Ausserdem wird der Standardport 8266 abgeändert.
Ideal wäre ein eigener Upload-Server mit fixer IP-Adresse, die dann beim ESP als einzig gültige Quelle eingetragen wird.

### Datei OtaUpdater.cpp
Hier wird die Portnummer und das Passwort eingetragen. 
Vorsicht: Über das Hochladen in Git-Repositories gelangen die Daten in die Öffentlichkeit.

````c
void OtaUpdaterClass::init() {
	// Port defaults to 8266
    ArduinoOTA.setPort(PORTNUMMER);
    // Hostname defaults to esp8266-[ChipID]
    // ArduinoOTA.setHostname("myesp8266");
    // No authentication by default
    ArduinoOTA.setPassword("PASSWORD");
    ArduinoOTA.onStart([]() {
		Serial.println("Start");

````

### platformio.ini
Bei jedem ESP muss zumindest die IP-Adresse angepasst werden.

````
upload_port = 192.168.0.2 --auth=avgp4eaoh2 --port=8265 --host_port=47986
````

### UI des Uploads
````
Looking for upload port...
Use manually specified: 192.168.0.2 --auth=PASSWORD --port=PORT --host_port=47986
Uploading .pioenvs\d1_mini\firmware.bin
19:31:45 [DEBUG]: Options: {'esp_ip': '192.168.0.2', 'host_port': PORT, 'image': '.pioenvs\\d1_mini\\firmware.bin', 'host_ip': '0.0.0.0', 'auth': 'PASSWORD', 'esp_port': 8265, 'spiffs': False, 'debug': True, 'progress': True}
19:31:45 [INFO]: Starting on 0.0.0.0:47986
19:31:45 [INFO]: Upload size: 386656
Sending invitation to 192.168.0.2
Authenticating...OK
19:31:48 [INFO]: Waiting for device...
Uploading: [============================================================] 100% Done...

19:31:55 [INFO]: Waiting for result...
19:31:55 [INFO]: Result: OK
````

