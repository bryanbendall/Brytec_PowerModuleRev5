#include "BrytecBoard.h"

#include "CanBus.h"
#include "Fram.h"
#include "FramDeserializer.h"
#include "PowerModuleRev5Defs.h"
#include "PowerOutput.h"
#include "PwmDriverOutput.h"
#include "Stm32Output.h"
#include "Usb.h"
#include "gpio.h"
#include <stdio.h>

namespace Brytec {

using output1 = PowerOutput<PwmDriverOutput<5>, PwmDriverOutput<4>>;
using output2 = PowerOutput<PwmDriverOutput<2>, Stm32Output<GPIOB_BASE, Den2_Pin>>;
using output3 = PowerOutput<PwmDriverOutput<9>, PwmDriverOutput<8>>;
using output4 = PowerOutput<PwmDriverOutput<11>, PwmDriverOutput<10>>;
using output5 = PowerOutput<PwmDriverOutput<3>, Stm32Output<GPIOA_BASE, Den5_Pin>>;
using output6 = PowerOutput<PwmDriverOutput<7>, PwmDriverOutput<6>>;

FramDeserializer deserializer;

BinaryDeserializer* BrytecBoard::getDeserializer()
{
    FramDeserializer des;
    deserializer = des;
    return &deserializer;
}

void BrytecBoard::error(EBrytecErrors error)
{
    switch (error) {
    case EBrytecErrors::ModuleHeader:
        printf("Module header is wrong\n");
        break;
    case EBrytecErrors::NodeGroupHeader:
        printf("Node Group header is wrong\n");
        break;
    case EBrytecErrors::ModuleNotEnabled:
        printf("This module is not enabled\n");
        break;
    case EBrytecErrors::AddNodeFailed:
        printf("Failed to add node\n");
        break;
    case EBrytecErrors::NodeVectorOutOfSpace:
        printf("Node Vector out of space\n");
        break;
    case EBrytecErrors::FailedToCreateNode:
        printf("Failed to create node\n");
        break;
    case EBrytecErrors::NodeIndexOutOfBounds:
        printf("Node index out of bounds\n");
        break;
    case EBrytecErrors::BadAlloc:
        printf("Node group allocation failed\n");
        break;
    case EBrytecErrors::CanBufferFull:
        printf("Can Buffer Full\n");
        break;

    default:
        printf("Unknown Error\n");
        break;
    }
}

void BrytecBoard::setupBrytecCan(uint32_t mask, uint32_t filter)
{
}

void BrytecBoard::setupPin(uint16_t index, IOTypes::Types type)
{
}

void BrytecBoard::shutdownAllPins()
{
    // BT_PIN_Onboard_LED
    HAL_GPIO_WritePin(User_Led_GPIO_Port, User_Led_Pin, GPIO_PIN_RESET);
    output1::setValue(0.0f);
}

float BrytecBoard::getPinValue(uint16_t index)
{
    return 0.0f;
}

float BrytecBoard::getPinVoltage(uint16_t index)
{
    return 0.0f;
}

float BrytecBoard::getPinCurrent(uint16_t index)
{
    return 0.0f;
}

void BrytecBoard::setPinValue(uint16_t index, IOTypes::Types type, float value)
{
    bool state = value > 0.001f;

    switch (index) {
    case BT_PIN_Onboard_LED:
        HAL_GPIO_WritePin(User_Led_GPIO_Port, User_Led_Pin, (GPIO_PinState)state);
        // printf("turning led %i\n", state);

        output1::setValue(value);

        // printf("setting value to - %f\n", value);

        break;

    default:
        break;
    }
}

void BrytecBoard::sendBrytecCan(CanExtFrame frame)
{
    Usb::send(frame);
    CanBus::send(frame);
}

void BrytecBoard::ReserveConfigSize(uint16_t size)
{
    Fram::write(0, (uint8_t*)&size, 2);
}

void BrytecBoard::updateConfig(uint8_t* data, uint32_t size, uint32_t offset)
{
    // Add room for storing the size
    Fram::write(offset + 2, data, size);
}

uint32_t BrytecBoard::getTemplateSize()
{
    return sizeof(moduleTemplate);
}

void BrytecBoard::getTemplateData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    if (offset > sizeof(moduleTemplate))
        return;

    memcpy(dest, &moduleTemplate[offset], length);
}

uint32_t BrytecBoard::getConfigSize()
{
    uint16_t dataSize;
    Fram::read(0, (uint8_t*)&dataSize, 2);
    return dataSize;
}

void BrytecBoard::getConfigData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    Fram::read(offset + 2, dest, length);
}
}