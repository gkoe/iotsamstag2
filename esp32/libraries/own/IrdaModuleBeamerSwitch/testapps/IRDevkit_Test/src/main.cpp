#include <Arduino.h>
#include <IrdaModule.h>

#define  HARDWARESERIALNUMBER 2

int txPin= 19;
int rxPin= 18;

IrdaModule irdaModule(rxPin,txPin,"esp","irdaModule");

void setup() {
  Serial.begin(115200);
  
  Serial.println("IrdaModule-Test");
  Serial.println("===============");

}
 
void loop() {
   delay(5000);
    irdaModule.setActorTo(1);
    delay(10000);
    Serial.println(irdaModule.readStateFromActor());
    irdaModule.setActorTo(0);
    Serial.println(irdaModule.readStateFromActor());
    delay(10000);
}

