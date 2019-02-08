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
