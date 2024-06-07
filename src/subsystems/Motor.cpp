//
// Created by Kaden Cassidy on 6/6/24.
//

#include "Motor.h"

#include <utility>

Motor::Motor(std::string name, int pin, double start, double maxS) : name(std::move(name)), pin(pin), zero(start), maxS(maxS), intSpeed(0), speed(start), interpolation((maxS-start)){
    esc.attach(pin);       // Attach the ESC to the pin
    esc.writeMicroseconds(zero);  // Set the initial position
}

void Motor::run() {
    esc.writeMicroseconds((int) speed); // update ESC speed
}
/**

**/
void Motor::setSpeed(double speed){


    speed = std::min(1, (int) speed);
    speed = std::max(-1, (int) speed);

    this->intSpeed = speed;
    this->speed = interpolation * this->intSpeed + zero;

//    Serial.print(name);
//    Serial.print(" speed set to: (");
//    Serial.print(this->intSpeed);
//    Serial.print(", ");
//    Serial.print(this->speed);
//    Serial.println(")");
}

void Motor::incSpeed(double inc){
    setSpeed(inc + this->intSpeed);
}

