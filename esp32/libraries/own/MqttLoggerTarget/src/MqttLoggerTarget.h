#pragma once

#include <LoggerTarget.h>
#include <ArduinoJson.h>

class MqttLoggerTarget : public LoggerTarget
{
    public:
        MqttLoggerTarget(const char* name, int type, const char* topic);
        virtual void log(int type, const char* tag, const char* message);
        
    private:
		StaticJsonBuffer<200> _jsonBuffer;
		char _topic[128];
};
