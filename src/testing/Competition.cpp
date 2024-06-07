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
    uint16_t data[] = {0,0,0};

    void setup(){
        Bluetooth::setup();
        weapon = new Motor("Weapon", 6,1485, 2000);
        driveL = new Motor("DriveL", 4,1485, 2000);
        driveR = new Motor("DriveR", 3,1485, 2000);
    }

    void loop(){
        time = millis();

        uint16_t* newData = Bluetooth::retrieve(time);
        if (newData != nullptr){
            for (size_t i = 0; i < Bluetooth::retrievedDataLength; i++){
//                retrievedData[i] = newData[i];
                data[i]= newData[i];
            }
        }

        weapon->setSpeed(data[0]);
        driveL->setSpeed(data[1]);
        driveR->setSpeed(data[2]);

        weapon->run();
        driveL->run();
        driveR->run();
    }
}