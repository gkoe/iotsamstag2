#include <Arduino.h>
#include "BLEDevice.h"
#include "Flower.h"

Flower::Flower(const char* macAddr, bool battery) {
  _getBattery = battery;
  strcpy(_macAddr, macAddr);
}

float Flower::getTemperature(){
  return _temperature;
}

uint8_t Flower::getMoisture(){
  return _moisture;
}

uint8_t Flower::getLight(){
  return _light;
}

uint8_t Flower::getConductivity(){
  return _conductivity;
}

uint8_t Flower::getBattery(){
  return _battery;
}

bool Flower::getSensorData() {
  BLEAddress _pAddress(_macAddr);
  Serial.print(F("Forming a connection to Flora device at "));
  Serial.println(_pAddress.toString().c_str());
  BLEClient*  pClient  = BLEDevice::createClient();
  // Connect to the remove BLE Server.
  if (!pClient->connect(_pAddress)) {
      return false;
  }
  Serial.println(" - Connected to Flora");
  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    return false;
  }
  Serial.println(" - Found our service");
  _pRemoteCharacteristic = pRemoteService->getCharacteristic(uuid_write_mode);
  uint8_t buf[2] = {0xA0, 0x1F};
  _pRemoteCharacteristic->writeValue(buf, 2, true);
  delay(500);
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  _pRemoteCharacteristic = pRemoteService->getCharacteristic(uuid_sensor_data);
  Serial.println(pRemoteService->toString().c_str());
  if (_pRemoteCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(uuid_sensor_data.toString().c_str());
    return false;
  }
  // Read the value of the characteristic.
  std::string value = _pRemoteCharacteristic->readValue();
  const char *val = value.c_str();
  _temperature = (val[0] + val[1] * 256) / ((float)10.0);
  _moisture = val[7];
  _light = val[3] + val[4] * 256;
  _conductivity = val[8] + val[9] * 256;
  if (_getBattery) {
    _pRemoteCharacteristic = pRemoteService->getCharacteristic(uuid_version_battery);
    if (_pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(uuid_sensor_data.toString().c_str()); 
      return false;
    }
    // Read the value of the characteristic...
    value = _pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    const char *val2 = value.c_str();
    _battery = val2[0];
  }

  pClient->disconnect();
}