#include <Arduino.h>
#include <MqttClient.h>
#include <HttpServer.h>
#include <SPIFFS.h>
#include <ThingConfig.h>

struct MqttSubscription exampleSubsrition;
char example[50];

static void Print(const char *topic, const char *payload){
	Serial.println("Working!!");
	Serial.println(topic);
	Serial.println(payload);
}

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
  HttpServer.init();
  strcpy(example, "htlleonding");
	MqttClient.init("test");
  exampleSubsrition.topic = example;
	exampleSubsrition.subscriberCallback = Print;
  MqttClient.addSubscription(&exampleSubsrition);
  MqttClient.subscribeToBroker();
}

void loop() {
    // put your main code here, to run repeatedly:
		delay(500);
    HttpServer.handleClient();
		MqttClient.doLoop();
}
