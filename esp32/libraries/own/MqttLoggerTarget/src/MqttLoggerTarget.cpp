#include "MqttLoggerTarget.h"
#include <Arduino.h>
#include <MqttClient.h>
#include <ThingConfig.h>
#include <ThingTime.h>

MqttLoggerTarget::MqttLoggerTarget(const char* name, int type, const char* topic)
    :LoggerTarget(name, type){
		strcpy(_topic, topic);
		strcat(_topic, "/log");
}

void MqttLoggerTarget::log(int type, const char* tag, const char* message){ 
	_jsonBuffer.clear();
	JsonObject& logEntry = _jsonBuffer.createObject();
	logEntry["type"] = type;
	logEntry["time"] = ThingTime.getDateTime();
	logEntry["message"] = message;
	char jsonText[128];
	logEntry.printTo(jsonText);
	MqttClient.publish(_topic ,jsonText);
    Serial.printf("*LG: %s => [ %i ] => %s \n", tag, type, message);
}
