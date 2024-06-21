//
// Created by Kaden Cassidy on 6/6/24.
//

#ifndef ARDUINOBATTLEBOTCODE_MOTOR_H
#define ARDUINOBATTLEBOTCODE_MOTOR_H

#include "Servo.h"
#include <string>
#include <algorithm>

class Motor {
    public:
        // Constructor with parameters
        Motor(std::string name, int pin, float start, float interp, double maxAcceleration, int deadzone);

        // Method to run the motor
        void run(uint32_t time);
        void setSpeed(float speed);
        void incSpeed(float inc);
        float getIntSpeed();

    private:
        std::string name;   // Motor name
        int pin;       // Pin number
        float zero;     // Starting speed
        float interpolation;       // convert 0 to 1 to speeds
        float targetSpeed;      //target speed
        float speed;            // Current speed
        float intTargetSpeed;  //pre interpolated speed
        double maxAcceleration;
        int deadzone;
        uint32_t time;

        Servo esc;     // Servo object to control the ESC
};


#endif //ARDUINOBATTLEBOTCODE_MOTOR_H
