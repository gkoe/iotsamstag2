#include <Hlw8012.h>

#define SEL 13
#define CF1 12
#define CF 	14


/****************************************** Statische Variablen **************************************/

Hlw8012 hlw8012(CF1, SEL,"Esp","Power","W",10);  // CF1-PIN

/****************************************** Setup **************************************/


void setup() {
	Serial.begin(115200);                 //Initialisierung der seriellen Schnittstelle
	Serial.println();
	Serial.println("Hlw8012Test");
	Serial.println("===========");
	Serial.println();
}

/****************************************** Loop **************************************/

void loop() {
	float power = hlw8012.getPower();
	Serial.print("Power: ");
	Serial.print(power);
	Serial.println("W");
	delay(1000);
}

