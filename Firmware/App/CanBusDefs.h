#pragma once

#include "PowerModuleRev5Defs.h"
#include "fdcan.h"
#include <stdint.h>

namespace CanBusDefs {

FDCAN_HandleTypeDef* getCanBus(uint8_t index)
{
    switch (index) {
    case BT_CAN_Pin_4_Pin_3:
        return &hfdcan2;
    }

    return nullptr;
}

uint8_t getCanBusIndex(FDCAN_HandleTypeDef* bus)
{
    if (bus == &hfdcan2)
        return BT_CAN_Pin_4_Pin_3;

    return UINT8_MAX;
}

}