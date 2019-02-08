#include <InternLed.h>
#include <Logger.h>
#include <SerialLoggerTarget.h>

#define LED_BUILTIN_PIN 2  // WEMOS MINI32 2, TTGO 16, Lolin 5, LOLIN D32 5, sonst 21

void setup() {
    Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
    LoggerTarget* serialLoggerTarget = new SerialLoggerTarget("seriallogger", 0);
    Logger.addLoggerTarget(serialLoggerTarget);
	Logger.debug("loop()","");
	Logger.debug("loop()","");
	Logger.debug("loop()","LedBlinkingTest");
	Logger.debug("loop()","===============");
	InternLed.init(LED_BUILTIN_PIN);
}

void loop() {
	Logger.debug("loop()","Schnelles blinken");
	InternLed.blinkFast();
	delay(4000);
	Logger.debug("loop()","Langsames blinken");
	InternLed.blinkOff();
	InternLed.blinkSlow();
	delay(4000);
	Logger.debug("loop()","Stop blinken");
	InternLed.blinkOff();
	delay(4000);
	Logger.debug("loop()","Zehn mal schnell blinken");
	InternLed.blinkFast(10);
	delay(8000);
	Logger.debug("loop()","Fünf mal langsam blinken");
	InternLed.blinkSlow(5);
	delay(8000);
}