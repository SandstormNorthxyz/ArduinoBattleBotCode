#include "Arduino.h"
#include "testing/Competition.h"
#include "testing/BluetoothTest.h"
#include "testing/imuTest.h"
#define program competition
//#define program bluetoothTest


void setup() {
//  Serial.begin(115200); //serial out to computer
//  while (!Serial){
//    delay(20);
//  }
//  delay(200);
  program::setup();
}


void loop(){
    program::loop();
}