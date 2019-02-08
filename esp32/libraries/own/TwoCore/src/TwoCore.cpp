#include "TwoCore.h"
#include <Arduino.h>

void TwoCore::init(){

}

void TwoCore::Task(TaskFunction_t function) {
	//TaskHandle_t task;
	xTaskCreatePinnedToCore(
                    function,   /* Function to implement the task */
                    "coreTask", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    1,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    1);  /* Core where the task should run */
	//_tasks.push_back(task);
}
