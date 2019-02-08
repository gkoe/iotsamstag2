#include <Arduino.h>
#include <TwoCore.h>

void Test(void * parameter){
	for(;;) {
		delay(1000);
		Serial.printf("Test %d\n", xPortGetCoreID());
	}
}

void Test2(void * parameter) {
	delay(1000);
	Serial.printf("Test %d\n", xPortGetCoreID());
}

TwoCore tw;


void setup() {
	Serial.begin(115200);
	tw.Task(Test);
}

void loop() {
}
