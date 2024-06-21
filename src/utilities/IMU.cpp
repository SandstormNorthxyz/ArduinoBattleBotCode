//
// Created by Kaden Cassidy on 6/20/24.
//

#include "IMU.h"

namespace imu {

    float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
//    float vx = 0.0f, vy = 0.0f, vz = 0.0f; // Velocities
//    float prev_ax = 0.0f, prev_ay = 0.0f, prev_az = 0.0f; // Previous accelerations
    const float alpha = 0.98f; // Complementary filter coefficient
    uint32_t previousTime;

    void setup() {

        if (!IMU.begin()) {
            Serial.println("Failed to initialize IMU!");
            while (1);
        }

        Serial.println("IMU initialized!");
        previousTime = millis();
    }

    void getData(float * array) {
        float ax = 0, ay = 0, az = 0;
        float gx = 0, gy = 0, gz = 0;
        float global_ax = 0, global_ay = 0, global_az = 0;

        // Read gyroscope
        if (IMU.gyroscopeAvailable() && IMU.accelerationAvailable()) {
            IMU.readGyroscope(gx, gy, gz);
            // Integrate gyroscope data -> angular velocity to get angle
            uint32_t currentTime = millis();
            auto dt = (float) (currentTime - previousTime);
            previousTime = currentTime;
            dt /= 1000.0f;
            roll += gx * dt;
            pitch += gy * dt;
            yaw += gz * dt;
            //        }
            //        if (){
            IMU.readAcceleration(ax, ay, az);

            // Use accelerometer data for tilt estimation
            float rollAcc = atan2(ay, az);
            float pitchAcc = atan2(-ax, sqrt(ay * ay + az * az));

            // Complementary filter to combine gyroscope and accelerometer data
            roll = alpha * roll + (1 - alpha) * rollAcc;
            pitch = alpha * pitch + (1 - alpha) * pitchAcc;



            // Calculate the rotation matrix
            float cosRoll = cos(roll);
            float sinRoll = sin(roll);
            float cosPitch = cos(pitch);
            float sinPitch = sin(pitch);
            float cosYaw = cos(yaw);
            float sinYaw = sin(yaw);

            // Rotation matrix from IMU frame to global frame
            float R[3][3] = {
                    {cosYaw * cosPitch, cosYaw * sinPitch * sinRoll - sinYaw * cosRoll, cosYaw * sinPitch * cosRoll + sinYaw * sinRoll},
                    {sinYaw * cosPitch, sinYaw * sinPitch * sinRoll + cosYaw * cosRoll, sinYaw * sinPitch * cosRoll - cosYaw * sinRoll},
                    {-sinPitch, cosPitch * sinRoll, cosPitch * cosRoll}
            };

            // Transform IMU accelerations to global frame
            global_ax = R[0][0] * ax + R[0][1] * ay + R[0][2] * az;
            global_ay = R[1][0] * ax + R[1][1] * ay + R[1][2] * az;
            global_az = R[2][0] * ax + R[2][1] * ay + R[2][2] * az;

//            // Integrate acceleration to get velocity (trapezoidal integration)
//            vx += (ax_global + prev_ax) / 2.0f * dt;
//            vy += (ay_global + prev_ay) / 2.0f * dt;
//            vz += (az_global + prev_az) / 2.0f * dt;
//
//            // Update previous accelerations
//            prev_ax = ax_global;
//            prev_ay = ay_global;
//            prev_az = az_global;

//            // Integrate acceleration to get velocity (trapezoidal integration)
//            vx += (ax + prev_ax) / 2.0f * dt;
//            vy += (ay + prev_ay) / 2.0f * dt;
//            vz += (az + prev_az) / 2.0f * dt;
//
//            // Update previous accelerations
//            prev_ax = ax;
//            prev_ay = ay;
//            prev_az = az;

//            Serial.print("X: ");
//            Serial.print(ax);
//            Serial.print(", Y: ");
//            Serial.print(ay);
//            Serial.print(", Z: ");
//            Serial.println(az);
        }




        array[0] = roll;
        array[1] = pitch;
        array[2] = yaw;

        array[3] = global_ax;
        array[4] = global_ay;
        array[5] = global_az;
    }
}
