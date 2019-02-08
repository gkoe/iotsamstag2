#include <Arduino.h>
#include <HttpServer.h>
#include <OtaUpdater.h>

void setup() {
    Serial.begin(115200);
	Serial.println();
	Serial.println();
	Serial.println("OtaUpdaterTest");
	Serial.println("==============");
	HttpServer.init();
	OtaUpdater.init();
}

int delayToNextWrite = 1000;
void loop() {
	HttpServer.handleClient();
	OtaUpdater.checkForUpdate();
	delay(1);
	delayToNextWrite--;
	if(delayToNextWrite <= 0){
		delayToNextWrite=1000;
		Serial.print(".");
	}
}