#include "BluetoothController.h"

// Define the BLE service and characteristics
BLEService dataService("180C"); // Example UUID for the service
BLECharacteristic writeCharacteristic("2A56", BLEWrite | BLERead, 20); // Characteristic for receiving data
BLECharacteristic readCharacteristic("2A57", BLERead | BLENotify, 20); // Characteristic for sending data

namespace Bluetooth {

    float zeros[retrievedDataLength] = {0};
    int16_t* transmitionData = nullptr;
    size_t transmitDataLength = 0;
    uint32_t tTimer = 0;
    uint32_t rTimer = 0;
    const int transmissionDelay = 50; // Delay between updates (in milliseconds)
    const int receptionDelay = 20;

    void setup() {
        if (!BLE.begin()) {
            Serial.println("Starting BLE failed!");
            while (1);
        }

        BLE.setLocalName("Nano33BLE");
        BLE.setAdvertisedService(dataService);
        dataService.addCharacteristic(writeCharacteristic);
        dataService.addCharacteristic(readCharacteristic);
        BLE.addService(dataService);
        BLE.advertise();

        Serial.println("BLE device is now advertising, waiting for connections...");
    }

    void resetData() {
        transmitDataLength = 0;
        if (transmitionData) {
            delete[] transmitionData;
            transmitionData = nullptr;
        }
    }

    void addData(int16_t data) {
        auto* newData = new int16_t[transmitDataLength + 1];
        for (size_t i = 0; i < transmitDataLength; i++) {
            newData[i] = transmitionData[i];
        }
        newData[transmitDataLength] = data;
        delete[] transmitionData;
        transmitionData = newData;
        transmitDataLength++;
    }

    void send(uint32_t now) {
        BLEDevice central = BLE.central();
        if (central && central.connected() && (now - tTimer) > transmissionDelay) {
            tTimer = now;

            uint8_t startBit = 0xFF;
            uint8_t endBit = 0xFE;
            size_t bufferLength = transmitDataLength * 2 + 3;
            uint8_t* buffer = (uint8_t*)malloc(bufferLength);

            if (!buffer) {
                Serial.println("Memory allocation failed!");
                resetData();
                return;
            }

            buffer[0] = startBit;
            buffer[bufferLength - 2] = endBit;
            buffer[bufferLength - 1] = endBit;

            for (size_t i = 0; i < transmitDataLength; i++) {
                buffer[1 + i * 2] = (transmitionData[i] >> 8) & 0xFF;
                buffer[2 + i * 2] = transmitionData[i] & 0xFF;
            }

            writeCharacteristic.writeValue(buffer, bufferLength);
            free(buffer);
        }
        resetData();
    }

    float int16_to_proportion(int16_t value) {
        // Maximum positive value for int16_t
        const int16_t max_int16 = 32767;
        // Minimum negative value for int16_t
        const int16_t min_int16 = -32768;

        // Convert the int16_t value to a float
        float float_value = (float)value;

        // Normalize the float value to the range -1 to 1
        if (value >= 0) {
            return float_value / max_int16;
        } else {
            return float_value / -min_int16;
        }
    }

    float* retrieve(uint32_t now) {
        BLEDevice central = BLE.central();
        if (central && central.connected() && writeCharacteristic.written() && (now - rTimer) > receptionDelay) {
            rTimer = now;

            int receivedLength = writeCharacteristic.valueLength();
            size_t dataLength = (receivedLength - 3) / 2;

            if (dataLength != retrievedDataLength) {
                return zeros;
            }

            auto* receivedData = (uint8_t*)malloc(receivedLength);
            if (!receivedData) {
                Serial.println("Memory allocation failed!");
                return zeros;
            }

            writeCharacteristic.readValue(receivedData, receivedLength);

            if (receivedData[0] == 0xFF && receivedData[receivedLength - 1] == 0xFE && receivedData[receivedLength - 2] == 0xFE) {
                auto* parsedData = (float*)malloc(dataLength * sizeof(float));
                if (!parsedData) {
                    free(receivedData);
                    Serial.println("Memory allocation failed!");
                    return zeros;
                }

                for (size_t i = 0; i < dataLength; i++) {
                    parsedData[i] = int16_to_proportion((int16_t)((receivedData[1 + i * 2] << 8) | receivedData[2 + i * 2]));
                }

                free(receivedData);
                return parsedData;
            } else {
                Serial.println("Received data format is incorrect.");
                free(receivedData);
                return zeros;
            }
        }
        return nullptr;
    }


}
