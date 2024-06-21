//
// Created by Kaden Cassidy on 6/20/24.
//

#ifndef ARDUINOBATTLEBOTCODE_DRIVEBASE_H
#define ARDUINOBATTLEBOTCODE_DRIVEBASE_H

#include "Motor.h"
#include "utilities/PID.h"

namespace driveBase{

    Motor* driveR;
    Motor* driveL;

    PID* pid = new PID(0,0,0);

    float currentHeading = 0;
    float targetHeading = 0;


    void initialize(Motor* right, Motor* left){
        driveBase::driveL = left;
        driveBase::driveR = right;
    }

    float limitTurnSpeed(float turnSpeed, float weaponSpeed){
        return turnSpeed;
    }

    float holdHeading(float turnSpeed){

        if (turnSpeed == 0){
            //add time constraints
            return pid->getCorrection(currentHeading, targetHeading);
        }

        return turnSpeed;

    }

    float* drive(float * data){
        float weaponSpeed = data[0];
        float driveSpeed = data[1];
        float turnSpeed = data[2];

        turnSpeed = limitTurnSpeed(turnSpeed, weaponSpeed);

        turnSpeed = holdHeading(turnSpeed);

        driveL->setSpeed(driveSpeed - turnSpeed);
        driveR->setSpeed(driveSpeed + turnSpeed);

        data[2] = turnSpeed;

        return data;
    }




}

#endif //ARDUINOBATTLEBOTCODE_DRIVEBASE_H
