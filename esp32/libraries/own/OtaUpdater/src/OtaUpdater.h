//OtaUpdater.h

#ifndef _OTAUPDATER_H
#define _OTAUPDATER_H

#include <arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define OTAUPDATER_DEBUG

class OtaUpdaterClass {

public:
    OtaUpdaterClass();
    void init();
    void checkForUpdate();

private: 
};

extern OtaUpdaterClass OtaUpdater;

#endif









