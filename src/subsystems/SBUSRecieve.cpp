#include "SBUSRecieve.h"

namespace SBUS {

  bool sbusRecieveData = false;
  SBUSData sbusData = {{0}, {0}, 0};
  uint32_t sbusHeaderTimer = micros();

  void init() {
    //https://infocenter.nordicsemi.com/index.jsp?topic=%2Fps_nrf52840%2Fuart.html
    //https://github.com/Reefwing-Software/Reefwing-SBUS
//    *((uint32_t *) 0x40002508) = 0x80000000; //RTS disconnect
//    *((uint32_t *) 0x4000250C) = 0x80000000; //TXD disconnect
//    *((uint32_t *) 0x40002510) = 0x80000000; //CTS disconnect

    Serial1.begin(115200);//, (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_8)); , SERIAL_8E1

    *((uint32_t *) 0x40002524) = 0x19114A7; //baud rate register
    *((uint32_t *) 0x4000256C) = 0x000000F; //config register - not setting stop bit???
    delay(10);
  }

  void update(uint32_t now) {
    uint8_t sbusRecieved = 0;
    if (!sbusRecieveData && Serial1.available()) {
      sbusRecieved = Serial1.read();
      if (sbusRecieved == 0x0F && (now - sbusHeaderTimer) > 2000) {
        sbusRecieveData = true;
      } else {
        sbusHeaderTimer = now;
      }
    } else if (Serial1.available() >= 23) {
      digitalWrite(2, !digitalRead(2));
      uint8_t rxData[23];
      Serial1.readBytes(rxData, 23);
      //https://github.com/bolderflight/sbus
      sbusData.analogData[0] = static_cast<int16_t>((rxData[0] | rxData[1] << 8) & 0x07FF);
      sbusData.analogData[1] = static_cast<int16_t>((rxData[1] >> 3 | rxData[2] << 5) & 0x07FF);
      sbusData.analogData[2] = static_cast<int16_t>((rxData[2] >> 6 | rxData[3] << 2 | rxData[4] << 10) & 0x07FF);
      sbusData.analogData[3] = static_cast<int16_t>((rxData[4] >> 1 | rxData[5] << 7) & 0x07FF);
      sbusData.analogData[4] = static_cast<int16_t>((rxData[5] >> 4 | rxData[6] << 4) & 0x07FF);
      sbusData.analogData[5] = static_cast<int16_t>((rxData[6] >> 7 | rxData[7] << 1 | rxData[8] << 9) & 0x07FF);
      sbusData.analogData[6] = static_cast<int16_t>((rxData[8] >> 2 | rxData[9] << 6) & 0x07FF);
      sbusData.analogData[7] = static_cast<int16_t>((rxData[9] >> 5 | rxData[10] << 3) & 0x07FF);
      sbusData.analogData[8] = static_cast<int16_t>((rxData[11] | rxData[12] << 8) & 0x07FF);
      sbusData.analogData[9] = static_cast<int16_t>((rxData[12] >> 3 | rxData[13] << 5) & 0x07FF);
      sbusData.analogData[10] = static_cast<int16_t>((rxData[13] >> 6 | rxData[14] << 2 | rxData[15] << 10) & 0x07FF);
      sbusData.analogData[11] = static_cast<int16_t>((rxData[15] >> 1 | rxData[16] << 7) & 0x07FF);
      sbusData.analogData[12] = static_cast<int16_t>((rxData[16] >> 4 | rxData[17] << 4) & 0x07FF);
      sbusData.analogData[13] = static_cast<int16_t>((rxData[17] >> 7 | rxData[18] << 1 | rxData[19] << 9) & 0x07FF);
      sbusData.analogData[14] = static_cast<int16_t>((rxData[19] >> 2 | rxData[20] << 6) & 0x07FF);
      sbusData.analogData[15] = static_cast<int16_t>((rxData[20] >> 5 | rxData[21] << 3) & 0x07FF);

      sbusData.digitalData[0] = rxData[22] & 0x01;
      sbusData.digitalData[1] = rxData[22] & 0x02;

      sbusData.frameLost = rxData[22] & 0x04;
      sbusData.frameLost = rxData[22] & 0x08;

      sbusHeaderTimer = now;
      sbusRecieveData = false;
    }
  }

}
