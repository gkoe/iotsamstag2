#include <FS.h>
#include <SPIFFS.h>
#include "ThingConfig.h"
#include <Logger.h>

#define FORMAT_SPIFFS_IF_FAILED true  // beim ersten Start auf dem ESP wird das Filesystem angelegt

/*
 * Die Konfiguration im Speicher wird gelöscht.
 * Es wird ein leeres Json-Objekt erzeugt.
 */
void ThingConfigClass::initJsonConfig(){
	_jsonBuffer.clear();
	JsonObject &root = _jsonBuffer.createObject();
	_jsonConfig = &root;
	char buffer[300];
    char line[300];
	_jsonConfig->printTo(buffer, 300);
    sprintf(line,"json config initialized: %s",buffer);
	Logger.info("ThingConfig-initJsonConfig()",line);
}

/*
 * Die Konfiguration im Speicher und die Konfigurationsdatei 
 * werden gelöscht.
 */
void ThingConfigClass::clearConfig(){
	initJsonConfig(); // Cache ebenfalls löschen
	if (SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
		Logger.info("ThingConfig-clearConfig()","mounted file system");
		if (SPIFFS.exists("/config.json")) {
			//file exists, reading and loading
			Logger.info("ThingConfig-clearConfig()","deleting config file");
			SPIFFS.remove("/config.json");
			} else{
				Logger.error("ThingConfig-clearConfig()","json config does not exist");
			}
    } else {
		Logger.error("ThingConfig-clearConfig()","failed to mount FS");
  	}
}

/*
 * Die Konfiguration wird als JSON-String zurückgegeben
 */
void ThingConfigClass::getConfigJson(char* buffer, size_t size){
	_jsonConfig->printTo(buffer, size);
}

/**
 * Konfiguration aus Datei in JSON-Objekt lesen
 */
void ThingConfigClass::readConfig(){
	initJsonConfig();  // damit nicht die alte Config erhalten bleibt
	bool isConfigRead = false;
	if (SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
		if (SPIFFS.exists("/config.json")) {
			//file exists, reading and loading
			File configFile = SPIFFS.open("/config.json", FILE_READ);
			if (configFile) {
				JsonObject &root = _jsonBuffer.parseObject(configFile);
				_jsonConfig = &root;
				if (_jsonConfig->success()) {	
					isConfigRead=true;
				} else {
					Logger.error("ThingConfig-readConfig()","failed to read from json file");
				}	
				configFile.close();
			} else {
				Logger.error("ThingConfig-readConfig()","failed to open json file");
			}		
		} else{
			Logger.error("ThingConfig-readConfig()","json file does not exist");
		}
    } else {
		Logger.error("ThingConfig-readConfig()","failed to mount filesystem");
  	}
	if(!isConfigRead){  // leere Config abspeichern
		initJsonConfig();
		saveConfig();
		delay(1000);
		Logger.info("ThingConfig-readConfig()","finished");
	}
}

/**
 * In JSON-Objekt gechachte Konfiguration in Datei schreiben
 */
void ThingConfigClass::saveConfig(){
	if (SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
		char buffer[300];
		char line[300];
		_jsonConfig->printTo(buffer, 300);
		sprintf(line,"json config to save: %s",buffer);
		Logger.info("ThingConfig-saveConfig()",line);
		File configFile = SPIFFS.open("/config.json", FILE_WRITE);
		if (!configFile) {
			Logger.error("ThingConfig-saveConfig()","failed to open json file");
		}
		else{
			_jsonConfig->printTo(configFile);
			configFile.close();
			readConfig();
		}
	} else {
		Logger.error("ThingConfig-saveConfig()","failed to mount filesystem");
	}
}

/**
 * Wert aus der Konfiguration auslesen (Key ist case-sensitiv)
 */
const char* ThingConfigClass::getValue(const char* key){
	const char* value = _jsonConfig->get<char*>(key);
	if(value == nullptr){
		return "";
	}
	return value;
}


/**
 * Wert in Konfiguration anlegen oder überschreiben
 */
void ThingConfigClass::setValue(const char* key, const char* value){
	_jsonConfig->set(key, value);
	char line[300];
	sprintf(line,"Setted value: %s for key: %s",value,key);
	Logger.info("ThingConfig-setValue()",line);
	saveConfig();
}

/**
 * Key wird aus der Konfiguration entfernt
 */
void ThingConfigClass::deleteKey(const char* key){
	char line[300];
	sprintf(line,"Removed key: %s",key);
	Logger.info("ThingConfig-deleteKey()",line);
	_jsonConfig->remove(key);
	saveConfig();
}

ThingConfigClass ThingConfig;

