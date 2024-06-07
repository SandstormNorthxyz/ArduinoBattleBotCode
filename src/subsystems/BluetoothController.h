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
    const size_t retrievedDataLength = 2;

    extern uint32_t rTimer;
    extern uint32_t tTimer;
    extern int transmissionDelay; // Delay between updates (in milliseconds)
    extern int receptionDelay;

    void setup();
    void send(uint32_t now, const unsigned short* data, size_t length);
    uint16_t* retrieve(uint32_t now);
}

#endif //ARDUINOBATTLEBOTCODE_BLUETOOTHCONTROLLER_H
