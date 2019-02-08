#include <Arduino.h>

#define WEMOS

#ifdef WEMOS
	#define LED_BUILTIN_PIN 2  // WEMOS MINI32
#else 
	#ifdef TTGO
		#define LED_BUILTIN_PIN 16  // TTGO
	#endif
#endif	

#include <Arduino.h>
#include <HttpServer.h>
#include <ThingTime.h>
#include <ThingConfig.h>
#include <MqttClient.h>
#include <Logger.h>
#include <Sensor.h>
#include <Actor.h>
#include <Thing.h>
#include <UdpLoggerTarget.h>
#include <Logger.h>

//>>>>>>>>>>>>>>>>>>>> Thingspezifisch
#include <Dht22.h>				// allgemeine Dht22-Bibliothek
#include <Dht22_Temperature.h>	// Wrapper über den Dht22 zur Einbindung als Sensor
#include <Dht22_Humidity.h>
#include <Mhz14a.h>
#include <IrdaModule.h>
#include <PIR.h>


int Txpin = 19;
int Rxpin = 18;
//<<<<<<<<<<<<<<<<<<<<<<<

void setup() {
	Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
	Serial.println();
	Serial.println();
	Serial.println(F("*TT ThingTest fuer Sensoren und Aktoren"));
	Serial.println(F("*TT =================================="));
	ThingConfig.readConfig();			// Einlesen der Konfiguration in den JSON-Cache
	HttpServer.init();					// HttpServer initialisieren
	ThingTime.setNtpTimeSubscriber();   // Zeit über Internet synchronisieren	
	const char* thingName = ThingConfig.getValue("thingname");
	Thing.init(thingName, true);		// Thing initialisieren	mit JSON als Messageformat     
	
	// >>>>>>>>>>>>>>>>>>>>>>  Thingspezifischer Teil
  Sensor* pirPtr = new PIR(4,30,thingName,"PIR","",0);
  Thing.addSensor(pirPtr);
	//<<<<<<<<<<<<<<<<<<<<<<< Ende Thingspezifischer Teil
	UdpLoggerTarget* udpLoggerTarget = new UdpLoggerTarget("udplogger", 0);
  	Logger.addLoggerTarget(udpLoggerTarget);
	MqttClient.subscribeToBroker();
}

void loop() {
	HttpServer.handleClient();
	MqttClient.doLoop();					// Mqtt-Schnittstelle bedienen
	Thing.refreshSensorsAndActors();
	delay(1);
}
