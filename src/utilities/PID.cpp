//
// Created by Kaden Cassidy on 6/20/24.
//

#include "PID.h"

PID::PID(double kP, double kI, double kD) : kP(kP), kI(kI), kD(kD){
    this->reset();
}

void PID::setConstants(double kP, double kI, double kD){
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
}

void PID::setFeedForward(double constant){
    this->feedForwardConstant = constant;
}

void PID::setDeadZone(double deadZone){
    this->deadZone = deadZone;
}

void PID::setHomedThreshold(double homedThreshold){
    this->homedThreshold = homedThreshold;
}

void PID::setHomedConstant(double homedConstant){
    this->homedConstant = homedConstant;
}

void PID::setLowerLimit(double constant){
    this->lowerLimitConstant = constant;
}

void PID::reset(){
    prevErrorRingBuffer->fill(0.0);
    timeRingBuffer->fill(millis());
}

float PID::getCorrection(double current, double target){
    double error = target - current;

    if(target < homedThreshold && current < homedThreshold){
        return homedConstant;
    }

    double currentTime = millis();
    double prevTime = timeRingBuffer->getValue(currentTime);
    double deltaTime = currentTime - prevTime;

    if(deltaTime > 200){
        reset();
        deltaTime = 0.000000001;
    }

    double previousError = prevErrorRingBuffer->getValue(error);

    //Proportional component
    double pComponent = error * kP;

    //Integral component
    if(signum(previousError) != signum(error)){
        integralSum = 0;
    }

    integralSum += kI * error;

    double iComponent = integralSum * deltaTime;

    //Derivative Component
    double dComponent = (error - previousError) / deltaTime * kD;

    //FeedForward Component
    double lowerLimitComponent = (int8_t(signum(error))*2 -1) * lowerLimitConstant;

    if (error < 0){
        error *= -1;
    }
    if(error < deadZone){
        integralSum = 0;
        return feedForwardConstant + pComponent + iComponent + dComponent;
    }

//    Serial.print("P");
//    Serial.println(pComponent);
//    Serial.print("I");
//    Serial.println(iComponent);
//
//    Serial.print("D");
//    Serial.println(dComponent);
//
//    Serial.print("L");
//    Serial.println(lowerLimitComponent);
//
//    Serial.print("F");
//    Serial.println(feedForwardConstant);

    return pComponent + iComponent + dComponent + lowerLimitComponent + feedForwardConstant;
}

bool PID::signum(double number){
    return number <= 0;
}
