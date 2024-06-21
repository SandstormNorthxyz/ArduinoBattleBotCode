//
// Created by Kaden Cassidy on 6/21/24.
//

#ifndef ARDUINOBATTLEBOTCODE_DRIVEBASE_H
#define ARDUINOBATTLEBOTCODE_DRIVEBASE_H

#include "Motor.h"
#include "utilities/IMU.h"
#include "BluetoothController.h"
#include "utilities/PID.h"

namespace drivebase {

    void init();

    void drive(float *data, uint32_t now);

    float limitTurnSpeed(float turnSpeed, float weaponSpeed);

    float holdHeading(float turnSpeed);

    float limitTurnAcceleration(float turnSpeed);
}

#endif //ARDUINOBATTLEBOTCODE_DRIVEBASE_H
