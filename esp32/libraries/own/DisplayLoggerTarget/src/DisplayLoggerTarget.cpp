#include "DisplayLoggerTarget.h"
#include <Arduino.h>
#include <Display.h>


DisplayLoggerTarget::DisplayLoggerTarget(const char* loggerName, int logLevel)
    :LoggerTarget(loggerName, logLevel){
}

/**
 * Ausgabe der Logmeldung auf das OLED-Display
 * Kürzen der Texte
 */
void DisplayLoggerTarget::log(const char* logLevelText, const char* tag, const char* message){
    char logMessage[256];
    char shortTag[10];
    char shortMessage[20];
    strncpy(shortTag, tag,5);
    shortTag[5]=0;
    strncpy(shortMessage, message,13);
    shortMessage[13]=0;
    sprintf(logMessage, "%c: %s, %s",logLevelText[0], shortTag, shortMessage);
    Display.println(logMessage);
    // Serial.printf("*DL: %s\n",logMessage);
}
