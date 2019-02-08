#include <Arduino.h>
#include <Logger.h>
#include <DisplayLoggerTarget.h>
#include <Display.h>

void setup() {
    Serial.begin(115200);
    Display.init(ANIMATION_NONE, true, TO_LONG_BEHAVIOUR_NEWLINE);   // Am Beginn aufrufen
    LoggerTarget* loggerTarget = new DisplayLoggerTarget("displaylogger", 0);
    // Logger.init("test");
    Logger.addLoggerTarget(loggerTarget);
    Serial.println();
    Serial.println("=======================");
    Serial.println("DisplayLoggerTargetTest");
    Serial.println("=======================");
}

void loop() {
    LoggerTarget* loggerTarget = Logger.getLoggerTarget("displaylogger");
    int logLevel = loggerTarget->getLogLevel();
    Serial.printf("************ Setted LogLevel: %s *************\n", Logger.getLogLevelText(logLevel));
    Logger.info("Main-Loop", "Logtest: Info");
    Logger.debug("Main-Loop", "Logtest: Debug");
    Logger.exception("Main-Loop", "Logtest: Exception");
    Logger.error("Main-Loop", "Logtest: Error");
    Logger.fatalerror("Main-Loop", "Logtest: Fatalerror");
    if(logLevel == LOG_LEVEL_NOLOG){
        logLevel = LOG_LEVEL_INFO;
        loggerTarget->setLogLevel(logLevel);
        Serial.println("__________________________________________________");
    } else {
        logLevel++;
        loggerTarget->setLogLevel(logLevel);
    }
    delay(5000);
}