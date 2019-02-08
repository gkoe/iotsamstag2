#include "IrdaModule.h"
#include <ThingConfig.h>

#define  HARDWARESERIALNUMBER 2
char defaultirCode[] = "89,35,55,142,237,226,109,51,82,37,95,137,249,130,79,8,72,45,95,114,139,233,109,34,74,45,95,119,230,130,79,4,64,35,18,137,174,124,6,11,253,43,26,145,182,132,14,19,5,51,34,153,190,140,22,27,13,59,42,161,198,148,30,35,21,67,50,169,206,121,18,39,7,53,34,168,205,153,18,38,7,53,51,153,205,155,70,75,13";
 
IrdaModule::IrdaModule(int rxPin, int txPin, const char *thingName, const char *name) :Actor(thingName, name)
{
  _hardwareSerialPtr = new HardwareSerial(HARDWARESERIALNUMBER);
  _hardwareSerialPtr->begin(9600, SERIAL_8N1, rxPin, txPin);
}

void IrdaModule::setActorTo(float value)
{
    const char *configIrCode;
   // configIrCode = ThingConfig.getValue("IrCode");
    char *irCode;
  if(configIrCode == NULL){
    irCode = defaultirCode;
 }else{
   strcpy(irCode,configIrCode);
  }
	if (value > 0.5)
	{
    
		send_ir_signal(irCode);
        _beamerstate = 1;
	}
	else
	{
     
	    send_ir_signal(irCode);
      delay(2000);
      send_ir_signal(irCode);
        _beamerstate =0;
	}
}

float IrdaModule::readStateFromActor()
{
	return _beamerstate;
}


void IrdaModule::start_learning_mode() {

  Serial.println("Turnning on learning mode ..");

  uint8_t data[] = {0xe0};
  _hardwareSerialPtr->write((uint8_t*)data, sizeof(data));


  int len = 0;
  int r;
  unsigned long timeout = 700;
  unsigned long start = millis();
  int buffer[1];
  memset(buffer, 0, sizeof(buffer));
       
  while (millis() - start < timeout) {
    if (_hardwareSerialPtr->available()) {
      buffer[0] = _hardwareSerialPtr->read();
    }

    yield();
  }

  if(buffer[0] == 255) { 
    Serial.println("Error starting..");
  }
  else {
    Serial.println("Ready to record the remote. Press any button now..");
  }
}


void IrdaModule::read_ir_signal()
{
    int len = 0;
    int c;
    unsigned long timeout = 700;
    unsigned long start = millis();

    int buffer[512];
    memset(buffer, 0, sizeof(buffer));

    while ((millis() - start < timeout))
    {
        if (_hardwareSerialPtr->available())
        {
            c = _hardwareSerialPtr->read();
            buffer[len++] = c;
        }
        yield();
    }

    String ir_signal = "";
    unsigned int num = 0;

    for (int idx = 0; idx < len; idx++)
    {
        ir_signal += buffer[idx];

        if (idx + 1 != len)
        {
            ir_signal += ",";
        }

        if (idx != len - 1)
        {
            num += buffer[idx];
        }
    }

    byte received_checksum = (byte)num;
    int ir_signal_checksum = buffer[len - 1];

    if (received_checksum == ir_signal_checksum)
    {
        Serial.println("Your ir signal:");
        Serial.println(ir_signal);

       char irCode[250];
       ir_signal.toCharArray(irCode, ir_signal.length());
       ThingConfig.setValue("IrCode",irCode);
    }
    else
    {
        Serial.println("Invalid checksum:");
    }
}

void IrdaModule::send_ir_signal(char *irCodedefault){

 
  Serial.println("Send IR code ..");
  char irCode[] = "89,35,55,142,237,226,109,51,82,37,95,137,249,130,79,8,72,45,95,114,139,233,109,34,74,45,95,119,230,130,79,4,64,35,18,137,174,124,6,11,253,43,26,145,182,132,14,19,5,51,34,153,190,140,22,27,13,59,42,161,198,148,30,35,21,67,50,169,206,121,18,39,7,53,34,168,205,153,18,38,7,53,51,153,205,155,70,75,13";
  
    char* rest = irCode;

  uint8_t irArray[512];
  unsigned int idx = 1;
  char *str;

  irArray[0] = 227; 
  while ((str = strtok_r(rest, ",", &rest)) != NULL) {
    uint8_t ir = (uint8_t)atoi(str + '\0');
    irArray[idx++] = ir;
    yield();
  }
  
  delay(1000);
  _hardwareSerialPtr->write((uint8_t*)irArray, idx);
  int len = 0;
  int r;
  unsigned long timeout = 700;
  unsigned long start = millis();
  int buffer[1];
  memset(buffer, 0, sizeof(buffer));
  while (millis() - start < timeout) {
    if (_hardwareSerialPtr->available()) {
      buffer[0] = _hardwareSerialPtr->read();
    }

    yield();
  }
  if(buffer[0] == 255) {
    Serial.println("Error starting..");
  }
  else {
    Serial.println("Success!..");
  }
}