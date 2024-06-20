//
// Created by Kaden Cassidy on 6/6/24.
//

#include "BluetoothTest.h"
#include "subsystems/BluetoothController.h"

namespace bluetoothTest{

    float data[] = {1, 1, 1, 88};
    uint16_t retrievedData[Bluetooth::retrievedDataLength];

    void setup(){
        Bluetooth::setup();
    }

    void loop(){
        uint32_t time = millis();
        Bluetooth::addData((int16_t)(data[0] * 200));
        Bluetooth::addData((int16_t)(data[1] * 200));
        Bluetooth::addData((int16_t)(data[2] * 200));
        Bluetooth::addData((int16_t)(data[3] * 200));

        Bluetooth::send(time);
        float* newData = Bluetooth::retrieve(time);


        if (newData != nullptr){
            for (size_t i = 0; i < Bluetooth::retrievedDataLength; i++){
                data[i]= newData[i];
            }
        }

        free(newData);
    }
}
