#include <Arduino.h> // required before wiring_private.h
#include <Mhz19b.h>


//SoftwareSerial* _softwareSerialPtr;
int Txpin = 12;
int Rxpin = 13;
 

Mhz19b _mhz(Rxpin,Txpin,"Esp","Co2","ppm",5.0);


// To request a new reading:
// FF=startbyte, 01=devicenum, 86=command, 00=5xnull bytes, 79=checksum
// byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
// Commands are: 86=gas concentration, 87=Calibrate zero, 88=Calibrate span
//const byte MHZ19_CMD_READ_CO2[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
//const byte MHZ19_CMD_CALIBRATE_ZERO[9] = {0xFF,0x01,0x87,0x00,0x00,0x00,0x00,0x00,0x78}; 

void setup() {
  Serial.begin(115200);
  Serial.println(F("MHZ19-Test"));
  Serial.println(F("=========="));  
  //_softwareSerialPtr = new SoftwareSerial(RxPin, TxPin);
  _mhz.calibrate();
  delay(500);
}

void loop() {
  float ppm = _mhz.getCo2();
  Serial.print("PPM: ");
  Serial.println(ppm);
  delay(2000);
}

