//
// Created by Kaden Cassidy on 6/20/24.
//

#ifndef ARDUINOBATTLEBOTCODE_PID_H
#define ARDUINOBATTLEBOTCODE_PID_H

#include "utilities/ringBuffer.h"

class PID{

    public:
        PID(double kP, double kI, double kD);

        void setConstants(double kP, double kI, double kD);

        void setFeedForward(double constant);

        void setDeadZone(double deadZone);

        void setHomedThreshold(double homedThreshold);

        void setHomedConstant(double homedConstant);

        void setLowerLimit(double constant);

        void reset();

        float getCorrection(double current, double target);
    private:
        double kP;
        double kI;
        double kD;
        double feedForwardConstant;
        double deadZone = deadZone;
        double homedThreshold;
        double homedConstant = homedConstant;
        double lowerLimitConstant;
        double integralSum;
        ringBuffer<double, 3>* prevErrorRingBuffer;
        ringBuffer<double, 3>* timeRingBuffer;

        bool signum(double number){
            return number <= 0;
        }
};

#endif //ARDUINOBATTLEBOTCODE_PID_H
