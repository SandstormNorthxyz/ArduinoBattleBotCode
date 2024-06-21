//
// Created by Kaden Cassidy on 6/21/24.
//

#include "Drivebase.h"

namespace drivebase{

    Motor* driveR;
    Motor* driveL;
    Motor* weapon;

    float maxDriveAcceleration = 1;

    float maxTurnSpeed = 16000.0f/32767.0f;
    float minTurnSpeed = 12000.0f/32767.0f;
    float fullSpeedTurnRequiredVelocity = 0;

    float turnSpeedInterpolation;

    PID* pid;

    float currentHeading = 0;
    float targetHeading = 0;

    void init(){
        weapon = new Motor("Weapon", 6,1485, 500, 100000, 10);
        driveL = new Motor("DriveL", 4,1515, 500, maxDriveAcceleration, 40);
        driveR = new Motor("DriveR", 3,1515, -500, maxDriveAcceleration, 40);

        imu::setup();
        pid = new PID(0, 0, 0);

        turnSpeedInterpolation = maxTurnSpeed - minTurnSpeed;
    }

    float limitTurnSpeed(float turnSpeed, float weaponSpeed) {
        return turnSpeed;
    }

    float holdHeading(float turnSpeed) {
        if (turnSpeed == 0) {
            //add time constraints
            float correction = pid->getCorrection(currentHeading, targetHeading);
//            Serial.println("Correction");
//            Serial.println(correction);
            return correction;
        }
        return turnSpeed;
    }

    float limitTurnAcceleration(float turnSpeed){
        float leftSpeed = driveL->getIntSpeed();
        float rightSpeed = driveR->getIntSpeed();

        if(leftSpeed < 0){
            leftSpeed *= -1;
        }

        if(rightSpeed < 0){
            rightSpeed *= -1;
        }

        float max;
        if (rightSpeed > leftSpeed){
            max = rightSpeed;
        }else{
            max = leftSpeed;
        }

        if (max < .7){
            if(turnSpeed != 0){
                if (turnSpeed < -minTurnSpeed){
                    turnSpeed = -minTurnSpeed/2;
                }else if (turnSpeed > minTurnSpeed){
                    turnSpeed = minTurnSpeed/2;
                }
            }

        }

//        float turnInterpolationScalar = imuData[3]*imuData[3] + imuData[4]*imuData[4];
////        turnInterpolationScalar *= 1.5;
//
//        if (turnInterpolationScalar > 1){
//            turnInterpolationScalar = 1;
//        }
//
//        if (turnInterpolationScalar >.5){
//            turnInterpolationScalar = 1;
//        }
//
//        float maxControllableTurn = maxTurnSpeed + (-turnInterpolationScalar) * turnSpeedInterpolation;
//
//        if (turnSpeed < -maxControllableTurn){
//            turnSpeed = -maxControllableTurn;
//        }else if (turnSpeed > maxControllableTurn){
//            turnSpeed = maxControllableTurn;
//        }

        return  turnSpeed;
    }

    void drive(float* data, uint32_t time){

        float weaponSpeed = data[0];
        float driveSpeed = data[1];
        float turnSpeed = data[2];

        float imuData[6];
        imu::getData(imuData);
//        Serial.print("InitialTurn");
//        Serial.println(turnSpeed);
        turnSpeed = limitTurnAcceleration(turnSpeed);
//

//        Serial.print("maxControllable");
//        Serial.println(turnSpeed);

        turnSpeed = limitTurnSpeed(turnSpeed, weaponSpeed);
//        Serial.print("Limit turn");
//        Serial.println(turnSpeed);
        turnSpeed = holdHeading(turnSpeed);
//        Serial.print("HoldHeading");
//        Serial.println(turnSpeed);

//        Serial.print("weapon");
//        Serial.println(weaponSpeed);
//        Serial.print("drive");
//        Serial.println(driveSpeed);
//        Serial.print("turn");
//        Serial.println(turnSpeed);


        weapon->setSpeed(weaponSpeed);
        driveL->setSpeed(driveSpeed - turnSpeed);
        driveR->setSpeed(driveSpeed + turnSpeed);

//
//        Bluetooth::addData((int16_t) (() *3000));
//        Bluetooth::addData((int16_t) (imuData[4]*3000));
//        Bluetooth::addData((int16_t) (imuData[5]*3000));

        driveR->run(time);
        driveL->run(time);
        weapon->run(time);

        data[0] = weaponSpeed;
        data[1] = driveSpeed;
        data[2] = turnSpeed;
    }

}
