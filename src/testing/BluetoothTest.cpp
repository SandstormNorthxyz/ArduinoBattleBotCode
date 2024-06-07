//
// Created by Kaden Cassidy on 6/6/24.
//

#include "BluetoothTest.h"
#include "subsystems/BluetoothTransmit.h"

namespace bluetoothTest{

    void setup(){
        Bluetooth::setup();
    }

    void loop(){
        uint32_t time = millis();
        uint16_t data[] = {155, 655};
        Bluetooth::loop(time, data, 2);
    }
}
