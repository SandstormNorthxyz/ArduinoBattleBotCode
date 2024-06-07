//
// Created by Kaden Cassidy on 6/7/24.
//

#ifndef ARDUINOBATTLEBOTCODE_BLUETOOTHCONTROLLER_H
#define ARDUINOBATTLEBOTCODE_BLUETOOTHCONTROLLER_H

#include <ArduinoBLE.h>

extern BLEService dataService;
extern BLECharacteristic writeCharacteristic;
extern BLECharacteristic readCharacteristic;

namespace Bluetooth{
    const size_t retrievedDataLength = 3;

    extern size_t transmitDataLength;
    extern uint32_t rTimer;
    extern uint32_t tTimer;
    const extern int transmissionDelay; // Delay between updates (in milliseconds)
    const extern int receptionDelay;

    extern uint16_t* transmitionData;

    void setup();

    void addData(uint16_t data);
    void resetData();
    void send(uint32_t now);
    uint16_t* retrieve(uint32_t now);
}

#endif //ARDUINOBATTLEBOTCODE_BLUETOOTHCONTROLLER_H
