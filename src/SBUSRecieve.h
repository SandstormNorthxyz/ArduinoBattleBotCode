#include "Arduino.h"

namespace SBUS {
  struct SBUSData {
    uint16_t analogData[16]; //11 bit, just stored in a 16-bit container
    bool digitalData[2];
    bool frameLost;
    bool failsafeActive;
  };

  extern bool sbusRecieveData;
  extern SBUSData sbusData;
  extern uint32_t sbusHeaderTimer;

  void init();

  void update(uint32_t now);
}