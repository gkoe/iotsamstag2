#include <Arduino.h>
#include <HttpServer.h>
#include <ThingTime.h>
#include <ThingConfig.h>
#include <UdpLoggerTarget.h>
#include <Logger.h>
#include <Thing.h>
#include <TSL2561.h>
#include <MqttClient.h>

TSL2561* tsl2561;

void setup() {
	Serial.begin(115200);
	ThingConfig.readConfig();			// Einlesen der Konfiguration in den JSON-Cache
	HttpServer.init();					// HttpServer initialisieren
	ThingTime.setNtpTimeSubscriber(); 
	const char* thingName = ThingConfig.getValue("thingname");
	Thing.init(thingName, true);
	tsl2561 = new TSL2561(1, thingName, "Light", "lux", 10.0);
	Thing.addSensor(tsl2561);
}

void loop() {
	HttpServer.handleClient();
	MqttClient.doLoop();					// Mqtt-Schnittstelle bedienen
	Thing.refreshSensorsAndActors();
	delay(1);
}
