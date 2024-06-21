//
// Created by Kaden Cassidy on 6/20/24.
//

#ifndef ARDUINOBATTLEBOTCODE_IMU_H
#define ARDUINOBATTLEBOTCODE_IMU_H

#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

namespace imu {
    void setup();
    void getData(float * array);
}

#endif //ARDUINOBATTLEBOTCODE_IMU_H
