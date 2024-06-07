//
// Created by Kaden Cassidy on 6/6/24.
//

#include "BluetoothTest.h"
#include "subsystems/BluetoothController.h"

namespace bluetoothTest{

    uint16_t data[] = {155, 655};
    uint16_t retrievedData[Bluetooth::retrievedDataLength];

    void setup(){
        Bluetooth::setup();
    }

    void loop(){
        uint32_t time = millis();
        Bluetooth::send(time, data, 2);
        uint16_t* newData = Bluetooth::retrieve(time);
        if (newData != nullptr){
//            size_t size = sizeof(newData) / sizeof(uint16_t);
//            for (size_t i = 0; i < size; i++){
//
//            }

            for (size_t i = 0; i < Bluetooth::retrievedDataLength; i++){
//                Serial.print(newData[i]);
                retrievedData[i] = newData[i];
                data[i]= newData[i];
            }



        }
    }
}
