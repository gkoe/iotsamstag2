#include <Arduino.h>
#include <InternLed.h>
#include <HttpServer.h>
#include <ThingTime.h>
#include <ThingConfig.h>
#include <UdpLoggerTarget.h>
#include <Logger.h>
#include <Thing.h>
#include <tcpip_adapter.h> 

#define LED_BUILTIN_PIN 5

void setup() {
	Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
	Serial.println();
	Serial.println();
	Serial.println(F("*UTT Test fuer UDP-Loggertarget"));
	Serial.println(F("*UTT =========================="));
	ThingConfig.readConfig();			// Einlesen der Konfiguration in den JSON-Cache
	InternLed.init(LED_BUILTIN_PIN);
	HttpServer.init();					// HttpServer initialisieren
	ThingTime.setNtpTimeSubscriber();   // Zeit über Internet synchronisieren	
	const char* thingName = ThingConfig.getValue("thingname");
	Thing.init(thingName, true);		// Thing initialisieren	mit JSON als Messageformat     
	// >>>>>>>>>>>>>>>>>>>>>>  Thingspezifischer Teil
	//<<<<<<<<<<<<<<<<<<<<<<< Ende Thingspezifischer Teil
	UdpLoggerTarget* udpLoggerTarget=new UdpLoggerTarget("udplogger", 0);
    Logger.addLoggerTarget(udpLoggerTarget);
}

long lastUdpSentTime = millis();

void sendUdpLogMessages(){
  	LoggerTarget* udpLoggerTarget = Logger.getLoggerTarget("udplogger");
	int logLevel = udpLoggerTarget->getLogLevel();
  	Serial.printf("Actual minimum Loglevel set: %s\n", Logger.getLogLevelText(logLevel));
	Logger.info("Main-Loop", "Info");
	Logger.debug("Main-Loop", "Debug");
	Logger.exception("Main-Loop", "Exception");
	Logger.error("Main-Loop", "Error");
	Logger.fatalerror("Main-Loop", "FatalError");
	if(logLevel == LOG_LEVEL_NOLOG){
		logLevel = LOG_LEVEL_INFO;
		udpLoggerTarget->setLogLevel(logLevel);
		Serial.println("-----------------------------------------------------------------------");
	} else {
		logLevel++;
		udpLoggerTarget->setLogLevel(logLevel);
		Serial.println();
	}
}

void loop() {
	HttpServer.handleClient();
	if( millis() - lastUdpSentTime > 3000){
		sendUdpLogMessages();
		lastUdpSentTime = millis();
	}
	delay(1);
}