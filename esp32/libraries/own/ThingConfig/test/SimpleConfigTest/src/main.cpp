#include <Arduino.h>
#include <ThingConfig.h>
#include <Logger.h>
#include <SerialLoggerTarget.h>

/*************************************** Setup ******************************/
void setup() {
  char buffer[300];
  char line[300];
  Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
  LoggerTarget* serialLoggerTarget = new SerialLoggerTarget("seriallogger", 0);
  Logger.addLoggerTarget(serialLoggerTarget);
  Logger.info("Main-setup()","");
  Logger.info("Main-setup()","===============");
  Logger.info("Main-setup()","ThingConfigTest");
  Logger.info("Main-setup()","===============");
  ThingConfig.readConfig();  	// alte Config ausgeben
  ThingConfig.getConfigJson(buffer, 200);	// Gesamte Config als JSON-String auslesen
  sprintf(line,"Last saved config-json: %s",buffer);
  Logger.info("Main-setup()", line);
  Logger.info("Main-setup()","After clearConfig");
  ThingConfig.clearConfig();	// Config im Hauptspeicher löschen
  ThingConfig.readConfig();
  const char* value =ThingConfig.getValue("undefinedkey");
  sprintf(line,"read of undefined key, value: '%s'",value);
  Logger.info("Main-setup()", line);
  ThingConfig.setValue("key1", "value1");	// Config imHauptspeicher ändern und gleich persistieren
  ThingConfig.setValue("key2", "value2");
  sprintf(line,"Setted Config, Key1: %s", ThingConfig.getValue("key1"));
  Logger.info("Main-setup()", line);
  ThingConfig.getConfigJson(buffer, 200);	// Gesamte Config als JSON-String auslesen
  sprintf(line,"Values in config-json: %s",buffer);
  Logger.info("Main-setup()", line);
  ThingConfig.setValue("key1", "value999");	// Konfiguration ändern
  ThingConfig.getConfigJson(buffer, 200);	// Gesamte Config als JSON-String auslesen
  sprintf(line,"Values in config-json: %s",buffer);
  Logger.info("Main-setup()", line);
  sprintf(line,"Values in config-json: %s",buffer);
  Logger.info("Main-setup()", "Delete key: key1");
  ThingConfig.deleteKey("key1");
  ThingConfig.getConfigJson(buffer, 200);	// Gesamte Config als JSON-String auslesen
  sprintf(line,"Values in config-json: %s",buffer);
  Logger.info("Main-setup()", line);
}

/*************************************** Loop ******************************/
void loop() {
	delay(1);
}
