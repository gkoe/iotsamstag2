#include "Mhz14a.h"


Mhz14a::Mhz14a(int rxPin, int txPin, const char *nodeName, const char *name, const char *unit, float threshold) 
      : Sensor(nodeName, name, unit, threshold)
{
  _hardwareSerialPtr = new HardwareSerial(HARDWARESERIALNUMBER);
  _hardwareSerialPtr->begin(9600, SERIAL_8N1, rxPin, txPin);
  calibrate();
}

void Mhz14a::calibrate()
{
  Serial.println("*MHZ: Calibrating!");
  _hardwareSerialPtr->write(_calibrate,9);
  while(_hardwareSerialPtr->available()>0)
  {
    _hardwareSerialPtr->read();
  }
}

/*
  Liest maximal alle Sekunden den CO2-Gehalt ein, speichert
  ihn für Abfragen in einem privaten Feld und liefert ihn zurück.
  Im Fehlerfall wird -1 zurückgegeben.
*/
float Mhz14a::getCo2()
{
  uint16_t co2=0;
  uint8_t response[9];
  uint8_t index = 0;
  if (millis() - _lastMeasurementMilliSeconds > 1000)
  {         // nur alle Sekunden messen
    _lastMeasurementMilliSeconds = millis();
    bool responseReceived = false;
    _hardwareSerialPtr->flush();
    _hardwareSerialPtr->write(_cmd_measure_co2,9);
    while(_hardwareSerialPtr->available()>0)
    {
      uint8_t readByte = _hardwareSerialPtr->read();
      if(index < 9){
        response[index++]=readByte;
        responseReceived=true;
      }
    }
    if(responseReceived)
    {
      if(index==9){
        co2 += (uint16_t)response[2] <<8;
        co2 += response[3];
        // Serial.printf("*MHZ: Co2-Gehalt: %d\n",co2);
        _ppmCo2=co2;
      }
      else{
        Serial.printf("!MHZ: Statt 9 Zeichen nur %d Zeichen empfangen\n",index);   
        _ppmCo2=-1;   
      }
    }
    else{
      Serial.printf("!MHZ: Kein Empfang von CO2-Sensor\n"); 
      _ppmCo2=-1;     
    }
  }
  return _ppmCo2;
}

void Mhz14a::measure()
{
  float co2 = getCo2();
  setMeasurement(co2);
}
