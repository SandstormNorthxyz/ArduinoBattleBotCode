//
// Created by Kaden Cassidy on 6/6/24.
//

#ifndef ARDUINOBATTLEBOTCODE_BASICDRIVE_H
#define ARDUINOBATTLEBOTCODE_BASICDRIVE_H

#include "Arduino.h"
#include "Servo.h"
#include "subsystems/SBUSRecieve.h"
//#include <mbed.h>
#include "PwmOut.h"
#include "Servo.h"


namespace basicDrive {

    extern Servo leftMotor;
    extern Servo rightMotor;
    extern Servo weaponMotor;

    extern uint32_t serialTimer;

    void setup();
    void loop();
}


#endif //ARDUINOBATTLEBOTCODE_BASICDRIVE_H
