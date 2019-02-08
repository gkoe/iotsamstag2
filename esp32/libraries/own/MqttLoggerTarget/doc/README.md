# Library MqttLoggerTarget

## Allgemeines

Diese Klasse ist dazu da über Mqtt die Log Nachrichten zu senden. Dabei wird die Zeit, der Type und die Nachricht übertragen. 
Dabei erbt MqttLoggerTarget von LoggerTarget.
Das der MqttLoggerTarget verwendet werden kann muss ein Logger erstellt werden,
danach muss diesen Logger die Instanz des MqttLoggerTarget mitbekommen da der Logger diesen verwaltet.

## Software

### Abhängigkeiten

- LoggerTarget
- ThingConfig

### Testanwendung am ESP32

Die Klasse MqttLoggerTarget wird mit einen Mqtt Broker getestet.
Dabei wrid empfohlen Mqtt.fx zu verwenden. (Dabei wird das Topic benötigt)


#### Library


#### Headerdatei MqttLoggerTarget.h

````c

#include <LoggerTarget.h>

class MqttLoggerTarget : public LoggerTarget
{
    public:
        MqttLoggerTarget(const char* name, int type, const char* topic);
        virtual void log(int type, const char* tag, const char* message);
        
    private:
			StaticJsonBuffer<200> _jsonBuffer;
			_topic[128];
};


````

### Beispiel für einen konkreten MqttLoggertarget

````
#include <Arduino.h>
#include <HttpServer.h>
#include <MqttClient.h>
#include <ThingTime.h>
#include <Logger.h>
#include <MqttLoggerTarget.h>

int logLevel = 0;
LoggerTarget* mlg;

void setup() {
	Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
	Serial.println();
	Serial.println();
	Serial.println("LoggerTest");
	Serial.println("==========");
	Serial.println();
	ThingTime.setNtpTimeSubscriber();
  HttpServer.init();
  MqttClient.init("test");
  MqttClient.subscribeToBroker();
	Logger.init("test");
  mlg = new MqttLoggerTarget("test", 0, "htlleonding/");
  Logger.addLoggerTarget(mlg);
}

int logType = 0;

void loop() {
	delay(1);
  HttpServer.handleClient();
	MqttClient.doLoop();
  Logger.info("Main-Loop", "Logtest Level: 0");
  Logger.debug("Main-Loop", "Logtest Level: 1");
  Logger.exception("Main-Loop", "Logtest Level: 2");
  Logger.error("Main-Loop", "Logtest Level: 3");
  Logger.fatalerror("Main-Loop", "Logtest Level: 4");
  Logger.nolog("Main-Loop", "Logtest Level: 5");
  if(logLevel == LOG_LEVEL_NOLOG){
      logLevel = LOG_LEVEL_INFO;
      mlg->setType(logLevel);
      Serial.println("");
  } else {
      logLevel++;
      mlg->setType(logLevel);
  }
	delay(10000);
}

````
