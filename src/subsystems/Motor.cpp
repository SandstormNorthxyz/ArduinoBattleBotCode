//
// Created by Kaden Cassidy on 6/6/24.
//

#include "Motor.h"

#include <utility>
#include "BluetoothController.h"


Motor::Motor(std::string name, int pin, float start, float maxS, double maxAcceleration, int deadzone) : name(std::move(name)), pin(pin), zero(start), maxAcceleration(maxAcceleration), intTargetSpeed(0), targetSpeed(start), speed(start), time(0), interpolation((maxS)), deadzone(deadzone){
    esc.attach(pin);       // Attach the ESC to the pin
    esc.writeMicroseconds((int) zero);  // Set the initial position
}

float absl(float a){
    if (a < 0){
        return -a;
    }
    return a;
}

void Motor::run(uint32_t now) {
    auto dt = (double) (now - time);
    time = now;

    auto ds = (double) absl(targetSpeed - speed);

    double acceleration = ds/dt;

    if(acceleration < 0){
        acceleration = -acceleration;
    }

    if(maxAcceleration < acceleration){
        if(targetSpeed > speed){
            speed += (float) (maxAcceleration * dt);
        }else{
            speed -= (float) (maxAcceleration * dt);
        }

    }else{
        speed = targetSpeed;
    }

    if ((float)deadzone > absl(speed - zero)){
        if(targetSpeed > zero){
            float kick = (float)deadzone*2 + zero;
            if(targetSpeed > kick){
                speed = kick;
            }
            //speed = (float) std::min((int)targetSpeed, (int)zero + deadzone);
        }else{
            float kick = zero - (float)deadzone*2;
            if(targetSpeed < kick){
                speed = kick;
            }
//            speed = (float) std::max((int) targetSpeed, (int)zero - deadzone);
        }
    }

//    Bluetooth::addData((int16_t)speed);
    esc.writeMicroseconds((int) speed); // update ESC speed
}

/**

**/
void Motor::setSpeed(float power){

    if(power > 1){
        power = 1;
    }
    else if (power < -1){
        power = -1;
    }

    this->intTargetSpeed = power;
    this->targetSpeed = interpolation * this->intTargetSpeed + zero;

//    Serial.print(name);
//    Serial.print(" speed set to: (");
//    Serial.print(this->intSpeed);
//    Serial.print(", ");
//    Serial.print(this->speed);
//    Serial.println(")");
}

float Motor::getIntSpeed(){
    return (speed-zero) / interpolation;
}

void Motor::incSpeed(float inc){
    setSpeed(inc + this->intTargetSpeed);
}

