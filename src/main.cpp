#include "Arduino.h"
#include "testing/BasicDrive.h"
#include "testing/Competition.h"
#define program competition



void setup() {
  Serial.begin(115200); //serial out to computer
//  while (!Serial){
//    delay(20);
//  }
  delay(200);
  program::setup();
}


void loop(){
    program::loop();
}