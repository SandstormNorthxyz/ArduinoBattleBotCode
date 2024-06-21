//
// Created by Kaden Cassidy on 6/20/24.
//

#ifndef ARDUINOBATTLEBOTCODE_IMUTEST_H
#define ARDUINOBATTLEBOTCODE_IMUTEST_H

//#include <Arduino.h>
//#include <Arduino_LSM9DS1.h>

namespace imuTest{

//    Madgwick filter;
//    const float sampleFrequency = 100.0f;

    void setup() {

//        if (!IMU.begin()) {
//            Serial.println("Failed to initialize IMU!");
//            while (1){
//                Serial.println("Failed to initialize IMU!");
//                delay(1000);
//            }
//        }
//
//        filter.begin(sampleFrequency);
//        Serial.println("IMU initialized!");
    }

    void loop() {

    }
//        float ax, ay, az;
//        float gx, gy, gz;
//        float mx, my, mz;
//
//        if (IMU.accelerationAvailable()) {
//            IMU.readAcceleration(ax, ay, az);
//        }
//
//        if (IMU.gyroscopeAvailable()) {
//            IMU.readGyroscope(gx, gy, gz);
//        }
//
//        if (IMU.magneticFieldAvailable()) {
//            IMU.readMagneticField(mx, my, mz);
//        }
//
//        filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
//
//        float roll = filter.getRoll();
//        float pitch = filter.getPitch();
//        float yaw = filter.getYaw();
//
//        Serial.print("Roll: ");
//        Serial.print(roll);
//        Serial.print(", Pitch: ");
//        Serial.print(pitch);
//        Serial.print(", Yaw: ");
//        Serial.println(yaw);
//
//        delay(10);
//    }
}

#endif //ARDUINOBATTLEBOTCODE_IMUTEST_H
