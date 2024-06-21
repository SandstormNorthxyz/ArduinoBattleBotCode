#ifndef ARDUINOBATTLEBOTCODE_DRIVEBASE_H
#define ARDUINOBATTLEBOTCODE_DRIVEBASE_H

#include "Motor.h"
#include "utilities/PID.h"

namespace driveBase {
    extern Motor* driveR;
    extern Motor* driveL;

    extern PID* pid;

    extern float currentHeading;
    extern float targetHeading;

    void initialize(Motor* right, Motor* left);

    float limitTurnSpeed(float turnSpeed, float weaponSpeed);

    float holdHeading(float turnSpeed);

    float* drive(float* data);
}

#endif //ARDUINOBATTLEBOTCODE_DRIVEBASE_H
