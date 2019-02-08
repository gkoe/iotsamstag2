#include <Arduino.h>
#include <Logger.h>
#include <SerialLoggerTarget.h>

void setup() {
    Serial.begin(115200);
    Serial.println("======================");
    Serial.println("SerialLoggerTargetTest");
    Serial.println("======================");
    Logger.init("test");
    LoggerTarget* serialLoggerTarget = new SerialLoggerTarget("seriallogger", 0);
    Logger.addLoggerTarget(serialLoggerTarget);
}

void loop() {
    delay(1000);
    LoggerTarget* serialLoggerTarget = Logger.getLoggerTarget("seriallogger");
    int logLevel = serialLoggerTarget->getLogLevel();
    Serial.printf("************ Setted LogLevel: %s *************\n", Logger.getLogLevelText(logLevel));
    Logger.info("Main-Loop", "Logtest Level: Info");
    Logger.debug("Main-Loop", "Logtest Level: Debug");
    Logger.exception("Main-Loop", "Logtest Level: Exception");
    Logger.error("Main-Loop", "Logtest Level: Error");
    Logger.fatalerror("Main-Loop", "Logtest Level: Fatalerror");
    if(logLevel == LOG_LEVEL_NOLOG){
        logLevel = LOG_LEVEL_INFO;
        serialLoggerTarget->setLogLevel(logLevel);
        Serial.println("__________________________________________________");
    } else {
        logLevel++;
        serialLoggerTarget->setLogLevel(logLevel);
    }
}