#pragma once

#include <stdint.h>

class BoardHardware {

public:
    static void setSpiMemory();
    static void setSpiL9966();

    static void calibrateAdc();
    static void readAllAdc();
    static void printAllAdc();
    static uint16_t getAdcData(uint8_t index);

    static bool getIgntionPowerState();
};