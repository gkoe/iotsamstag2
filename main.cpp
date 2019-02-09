#include <Arduino.h>
#include <InternLed.h>
#include <HttpServer.h>
#include <ThingTime.h>
#include <ThingConfig.h>
#include <MqttClient.h>
#include <Sensor.h>
#include <Actor.h>
#include <Thing.h>
#include <UdpLoggerTarget.h>
#include <Logger.h>

//>>>>>>>>>>>>>>>>>>>> Thingspezifisch
#include <Beeper.h>
#include <RgbLed.h>
#include <Dht22.h>				// allgemeine Dht22-Bibliothek
#include <Dht22_Temperature.h>	// Wrapper über den Dht22 zur Einbindung als Temperatursensor
#include <Dht22_Humidity.h>
#include <PowerSwitch.h>

#define LED_BUILTIN_PIN 2 // NODEMCU D32

#define R 13 //  0
#define G 12 // 2
#define B 14 // 15

#define BEEPER_PIN 4
#define DHT22_PIN 27 // 17

#include <SimplePir.h>
#define PIR_PIN 26 // 16
//<<<<<<<<<<<<<<<<<<<<<<<

void setup() {
	Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
	Serial.println();
	Serial.println();
	Serial.println(F("*TT ThingTest fuer Seminar"));
	Serial.println(F("*TT ======================"));
	ThingConfig.readConfig();			// Einlesen der Konfiguration in den JSON-Cache
	InternLed.init(LED_BUILTIN_PIN);
	HttpServer.init();					// HttpServer initialisieren
	ThingTime.setNtpTimeSubscriber();   // Zeit über Internet synchronisieren	
	const char* thingName = ThingConfig.getValue("thingname");
	Thing.init(thingName, true);		// Thing initialisieren	mit JSON als Messageformat     
	// >>>>>>>>>>>>>>>>>>>>>>  Thingspezifischer Teil
	// Dht22* dhtSensorPtr = new Dht22(DHT22_PIN);
	// Sensor* temperatureSensorPtr =
	// 	 new Dht22_Temperature(dhtSensorPtr, thingName, "temperature", "Grad", 0.2);
	// Thing.addSensor(temperatureSensorPtr);
	// Sensor* humiditySensorPtr =
	// 	 new Dht22_Humidity(dhtSensorPtr, thingName, "humidity", "%", 0.5);
	// Thing.addSensor(humiditySensorPtr);
  	Sensor* pirPtr = new SimplePir(PIR_PIN,60,thingName,"pir","",0);
  	Thing.addSensor(pirPtr);
	Actor* rgbLed = new RgbLed(R, G, B, thingName, "rgbled");
	Thing.addActor(rgbLed);
	//<<<<<<<<<<<<<<<<<<<<<<< Ende Thingspezifischer Teil
	UdpLoggerTarget * udpLoggerTarget = new UdpLoggerTarget("udplogger", 0);
    Logger.addLoggerTarget(udpLoggerTarget);
	MqttClient.subscribeToBroker();
}

void loop() {
	HttpServer.handleClient();
	MqttClient.doLoop();					// Mqtt-Schnittstelle bedienen
	Thing.refreshSensorsAndActors();
	delay(1);
}
