//
// Created by Kaden Cassidy on 6/6/24.
//

#include <cstdint>
#include "subsystems/BluetoothController.h"
#include "subsystems/Motor.h"
#include "Competition.h"

namespace competition{

    Motor* weapon;
    Motor* driveR;
    Motor* driveL;
    uint16_t retrievedData[Bluetooth::retrievedDataLength];

    uint32_t time = 0;
    float data[] = {0,0,0};

    void setup(){
        Serial.begin(115200); //serial out to computer
//  while (!Serial){
//    delay(20);
//  }
        delay(200);
        Bluetooth::setup();
//        weapon = new Motor("Weapon", 6,1485, 2000, 1);
        driveL = new Motor("DriveL", 4,1515, 1000, 100000, 40);
        driveR = new Motor("DriveR", 3,1515, -1000, 100000, 40);

    }

    void loop(){
        time = millis();

        float* newData = Bluetooth::retrieve(time);
        if (newData != nullptr){
            for (size_t i = 0; i < Bluetooth::retrievedDataLength; i++){
//                retrievedData[i] = newData[i];
                data[i]= newData[i];
            }
        }



//        Serial.println(data[0]);

        free(newData);
//        weapon->setSpeed(data[0]);
        driveL->setSpeed(data[1] - data[2]);
        driveR->setSpeed(data[1] + data[2]);
        Bluetooth::addData((int16_t) (data[0]*32767));
        Bluetooth::addData((int16_t) (data[1]*32767));
        Bluetooth::addData((int16_t) (data[2]*32767));

        driveR->run(time);
        driveL->run(time);


//        weapon->run(time);
        Bluetooth::send(time);
    }
}