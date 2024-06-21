//
// Created by Kaden Cassidy on 6/6/24.
//

#include <cstdint>
#include "subsystems/BluetoothController.h"
#include "subsystems/Motor.h"
#include "Competition.h"
#include "subsystems/Drivebase.h"
#include "utilities/IMU.h"

namespace competition{

    uint32_t time = 0;
    float data[] = {0,0,0};

    void setup(){
        Serial.begin(115200); //serial out to computer
        //DO NOT WAIT FOR SERIAL
        delay(200);
        Bluetooth::setup();

        drivebase::init();

    }

    void loop(){
        time = millis();

        float* newData = Bluetooth::retrieve(time);
        if (newData != nullptr){
            for (size_t i = 0; i < Bluetooth::retrievedDataLength; i++){
                data[i]= newData[i];
            }
        }

        free(newData);

        Bluetooth::addData((int16_t) (data[0]*32767));
        Bluetooth::addData((int16_t) (data[1]*32767));
        Bluetooth::addData((int16_t) (data[2]*32767));

        drivebase::drive(data, time);

        Bluetooth::send(time);
    }
}