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
        Motor(std::string name, int pin, double start, double maxS);

        // Method to run the motor
        void run();
        void setSpeed(double speed);
        void incSpeed(double inc);

    private:
        std::string name;   // Motor name
        int pin;       // Pin number
        double zero;     // Starting speed
        double interpolation;       // convert 0 to 1 to speeds
        double maxS;       // Maximum speed
        double speed;     // Current speed
        double intSpeed;  //pre interpolated speed

        Servo esc;     // Servo object to control the ESC
};


#endif //ARDUINOBATTLEBOTCODE_MOTOR_H
