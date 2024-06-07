//
// Created by Kaden Cassidy on 6/7/24.
//

#include "BluetoothController.h"

// Define the BLE service and characteristics
BLEService dataService("180C"); // Example UUID for the service
BLECharacteristic writeCharacteristic("2A56", BLEWrite | BLERead, 20); // Characteristic for receiving data
BLECharacteristic readCharacteristic("2A57", BLERead | BLENotify, 20); // Characteristic for sending data

namespace Bluetooth {

    uint16_t zeros[retrievedDataLength];
    uint16_t* transmitionData = {0};

    size_t transmitDataLength = 0;

    uint32_t tTimer = 0;
    uint32_t rTimer = 0;
    int transmissionDelay = 50; // Delay between updates (in milliseconds)
    int receptionDelay = 20;

    void setup() {
        if (!BLE.begin()) {
            Serial.println("starting BLE failed!");
            while (1);
        }

        BLE.setLocalName("Nano33BLE");
        BLE.setAdvertisedService(dataService);
        dataService.addCharacteristic(writeCharacteristic);
        dataService.addCharacteristic(readCharacteristic);
        BLE.addService(dataService);
        BLE.advertise();

        for (size_t i = 0; i < retrievedDataLength; i++){
            zeros[i] = 0;
        }

        Serial.println("BLE device is now advertising, waiting for connections...");
    }

    void resetData(){
        transmitDataLength = 0;
        delete transmitionData;
    }

    void addData(uint16_t data){
        transmitDataLength++;
        uint16_t* currentData = transmitionData;
        transmitionData = new uint16_t[transmitDataLength];
        for (size_t i = 0; i < transmitDataLength-1; i++){
            transmitionData[i] = currentData[i];
        }
        transmitionData[transmitDataLength-1] = data;
        delete currentData;
    }

    void send(uint32_t now) {
        BLEDevice central = BLE.central();

        size_t length = transmitDataLength;
        uint16_t* data = transmitionData;
        transmitDataLength = 0;
        delete transmitionData;

//       //&&
        if  (central.connected() && (int) (now - tTimer) > transmissionDelay) {
            //sending data
            tTimer = now;
            // Collect and send data
            uint8_t startBit = 0xFF;
            uint8_t endBit = 0xFE;

            size_t bufferLength = length*2 + 2;

            auto* buffer = (uint8_t*)malloc(bufferLength);

            buffer[0] = startBit;
            buffer[1 + length*2] = endBit;

            for (size_t i = 0; i < length; i++){
                uint16_t value = data[i];
                buffer[1 + i*2] = (value >> 8) & 0xFF;
                buffer[2 + i*2] = value & 0xFF;
            }

            writeCharacteristic.writeValue(buffer, (int)bufferLength);
        }

    }

    uint16_t* retrieve(uint32_t now) {
        BLEDevice central = BLE.central();

//       //
        if (central.connected()){
            if (writeCharacteristic.written() && (int) (now - rTimer) > receptionDelay) {
                // Handle data reception
                rTimer = now;

                int receivedLength = writeCharacteristic.valueLength();
                size_t dataLength = (receivedLength - 2) / 2;

                if (dataLength != retrievedDataLength) {
                    return zeros;
                }

                auto *receivedData = (uint8_t *) malloc(receivedLength);
                writeCharacteristic.readValue(receivedData, receivedLength);

                //                Serial.print("Received data: ");
                //                for (int i = 0; i < receivedLength; i++) {
                //                    Serial.print(receivedData[i], HEX);
                //                    Serial.print(" ");
                //                }
                //                Serial.println();


                // Parse the received data
                if (receivedData[0] == 0xFF && receivedData[receivedLength - 1] == 0xFE) {
                    auto *parsedData = (uint16_t *) malloc(dataLength);

                    for (size_t i = 0; i < dataLength; i++) {
                        uint8_t high_byte = receivedData[1 + i * 2];
                        uint8_t low_byte = receivedData[2 + i * 2];
                        parsedData[i] = (high_byte << 8) | low_byte;
                        //                        Serial.print("Parsed value ");
                        //                        Serial.print(i);
                        //                        Serial.print(": ");
                        //                        Serial.println(value);
                    }
                    return parsedData;
                } else {
                    Serial.println("Received data format is incorrect.");
                    return zeros;
                }
            }else{
                return nullptr;
            }
        }

        return zeros;
    }
}