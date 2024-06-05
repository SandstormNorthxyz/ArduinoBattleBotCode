#include "Arduino.h"
#include "SBUSRecieve.h"
//#include <mbed.h>

void setup() {
  Serial.begin(115200); //serial out to computer

  SBUS::init();

}

uint32_t serialTimer = millis();

void loop() {
  uint32_t now = micros();
  SBUS::update(now);

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