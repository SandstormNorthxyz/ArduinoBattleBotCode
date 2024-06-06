#include "Arduino.h"
#include "SBUSRecieve.h"
//#include <mbed.h>
#include "PwmOut.h"
#include "Servo.h"

Servo leftMotor;
Servo rightMotor;
Servo weaponMotor;

void setup() {
  Serial.begin(115200); //serial out to computer
//  while (!Serial){
//    delay(20);
//  }
  delay(200);
  SBUS::init();
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  leftMotor.attach(4);
  rightMotor.attach(3);
  weaponMotor.attach(6);
//  leftMotor.resume();
}

uint32_t serialTimer = millis();

void loop() {
  uint32_t now = micros();

  SBUS::update(now);

  double drive = (SBUS::sbusData.analogData[2] - 992) / 819.0; //-1 to 1
  double steer = (SBUS::sbusData.analogData[1] - 992) / 819.0; //-1 to 1
  double weapon = (SBUS::sbusData.analogData[0] - 172) / 1639.0; //0 to 1

  weaponMotor.writeMicroseconds((1485.0 * weapon) + 1485);

  leftMotor.writeMicroseconds((constrain(drive + steer, -1.0, 1.0) * 1485.0) + 1485);
  rightMotor.writeMicroseconds((constrain(-drive + steer, -1.0, 1.0) * 1485.0) + 1485);

//  weaponMotor.writeMicroseconds(1485);
//  leftMotor.writeMicroseconds(1485);
//  rightMotor.writeMicroseconds(1485);


  if((millis() - serialTimer) > 20) {
    serialTimer = millis();
    Serial.print("CH0:");
    Serial.print(SBUS::sbusData.analogData[0], DEC);
    Serial.print(",");

    Serial.print("CH1:");
    Serial.print(SBUS::sbusData.analogData[1], DEC);
    Serial.print(",");

    Serial.print("CH2:");
    Serial.print(SBUS::sbusData.analogData[2], DEC);
    Serial.print(",");

    Serial.print("CH3:");
    Serial.print(SBUS::sbusData.analogData[3], DEC);
    Serial.print(",");

    Serial.print("CH4:");
    Serial.print(SBUS::sbusData.analogData[4], DEC);
    Serial.print(",");

    Serial.print("CH5:");
    Serial.print(SBUS::sbusData.analogData[5], DEC);
    Serial.print(",");

    Serial.println();
  }

}