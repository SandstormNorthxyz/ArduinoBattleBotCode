////
//// Created by Kaden Cassidy on 6/6/24.
////
//
//#include "ArduinoBLE.h"
//#include "BluetoothTransmit.h"
//
//BLEService dataService("180C"); // Example UUID
//BLECharacteristic dataCharacteristic("2A56", BLERead | BLENotify, 50);
//
//namespace BluetoothTransmitter {
//
//    uint32_t timer = millis();
//    int updateDelay = 100;
//
//    void setup() {
//
//        if (!BLE.begin()) {
//            Serial.println("starting BLE failed!");
//            while (1);
//        }
//
//        BLE.setLocalName("Nano33BLE");
//        BLE.setAdvertisedService(dataService); // Add the service UUID
//        dataService.addCharacteristic(dataCharacteristic);
//        BLE.addService(dataService);
//
//        dataCharacteristic.writeValue("0"); // Initial value
//
//        BLE.advertise();
//        Serial.println("BLE device is now advertising");
//    }
//
//    void send(uint32_t now, const unsigned short* data, size_t length) {
//        // Listen for BLE peripherals to connect:
//        BLEDevice central = BLE.central();
//
////        // If a central is connected to the peripheral:
////        if (central) {
////            Serial.print("Connected to central: ");
////            Serial.println(central.address());
//
//            // While the central is connected:
//        if (central.connected() &&  (int) (now - timer) > updateDelay) {
//            timer = now;
//            // Collect and send data
//            uint8_t startBit = 0xFF;
//            uint8_t endBit = 0xFE;
//
//            size_t bufferLength = length*2 + 2;
//
//            uint8_t buffer[bufferLength];
//
//            buffer[0] = startBit;
//            buffer[1 + length*2] = endBit;
//
//            for (size_t i = 0; i < length; i++){
//                uint16_t value = data[i];
//                buffer[1 + i*2] = (value >> 8) & 0xFF;
//                buffer[2 + i*2] = value & 0xFF;
//            }
//
//            dataCharacteristic.writeValue(buffer, (int)bufferLength);
//
//
////            char buffer[50];
////            snprintf(buffer, 50, "Sensor Value: %d", 1);
////            dataCharacteristic.writeValue(buffer);
//
////            Serial.print("Disconnected from central: ");
////            Serial.println(central.address());
////        }
//        }
//    }
//}