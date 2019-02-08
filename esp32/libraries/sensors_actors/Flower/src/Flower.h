#pragma once 

#include <Arduino.h>
#include "BLEDevice.h"

    static BLEUUID serviceUUID("00001204-0000-1000-8000-00805f9b34fb");
    static BLEUUID uuid_version_battery("00001a02-0000-1000-8000-00805f9b34fb");
    static BLEUUID uuid_sensor_data("00001a01-0000-1000-8000-00805f9b34fb");
    static BLEUUID uuid_write_mode("00001a00-0000-1000-8000-00805f9b34fb");
    static BLERemoteCharacteristic* _pRemoteCharacteristic;

class Flower
{
    public:
        Flower(const char* macAddr, bool battery);
        bool getSensorData();
        float getTemperature();
        uint8_t getMoisture();
        uint8_t getLight();
        uint8_t getConductivity();
        uint8_t getBattery();

    private:
        bool _getBattery;
        char _macAddr[20];
        float _temperature;
        uint8_t _moisture;
        uint8_t _light;
        uint8_t _conductivity;
        uint8_t _battery;
};