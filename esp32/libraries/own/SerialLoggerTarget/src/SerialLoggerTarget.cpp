#include "SerialLoggerTarget.h"
#include <Arduino.h>
#include <Thing.h>
#include <ThingConfig.h>
#include <ThingTime.h>


SerialLoggerTarget::SerialLoggerTarget(const char* name, int logLevel)
    :LoggerTarget(name, logLevel){
}

void SerialLoggerTarget::log(const char* logLevelText, const char* tag, const char* message){
    char logMessage[256];
    const char* thingName = Thing.getName();
    sprintf(logMessage, "*LG: %ld;%s;%s;%s;%s\n", ThingTime.getDateTime(),thingName, logLevelText,tag, message);
    Serial.printf(logMessage);
}
