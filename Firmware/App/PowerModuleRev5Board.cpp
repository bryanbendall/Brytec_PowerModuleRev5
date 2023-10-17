#include "BrytecBoard.h"

#include "BoardHardware.h"
#include "CanBus.h"
#include "Fram.h"
#include "FramDeserializer.h"
#include "L9966.h"
#include "PowerModuleRev5Defs.h"
#include "PowerOutput.h"
#include "PwmDriverOutput.h"
#include "Stm32Output.h"
#include "Usb.h"
#include "adc.h"
#include "gpio.h"

#define ADCIN_2 BoardHardware::getAdcData(0)
#define ADCIN_3 BoardHardware::getAdcData(1)
#define ADCIN_4 BoardHardware::getAdcData(2)
#define ADCIN_1 BoardHardware::getAdcData(3)
#define ADCIN_12 BoardHardware::getAdcData(4)
#define ADCIN_5 BoardHardware::getAdcData(5)
#define ADCIN_11 BoardHardware::getAdcData(6)
#define ADCIN_14 BoardHardware::getAdcData(7)
#define ADCIN_1x2 BoardHardware::getAdcData(8)
#define ADCIN_12x2 BoardHardware::getAdcData(9)

namespace Brytec {

// Single outputs
using output1 = PowerOutput<PwmDriverOutput<5>, PwmDriverOutput<4>>;
using output2 = PowerOutput<PwmDriverOutput<2>, Stm32Output<GPIOB_BASE, Den2_Pin>>;
using output3 = PowerOutput<PwmDriverOutput<9>, PwmDriverOutput<8>>;
using output4 = PowerOutput<PwmDriverOutput<11>, PwmDriverOutput<10>>;
using output5 = PowerOutput<PwmDriverOutput<3>, Stm32Output<GPIOA_BASE, Den5_Pin>>;
using output6 = PowerOutput<PwmDriverOutput<7>, PwmDriverOutput<6>>;

// Dual outputs
using output7 = PowerOutput<PwmDriverOutput<1>, Stm32Output<GPIOC_BASE, Den7_8_Pin>>;
using output8 = PowerOutput<PwmDriverOutput<0>, Stm32Output<GPIOC_BASE, Den7_8_Pin>>;
using output9 = PowerOutput<PwmDriverOutput<15>, PwmDriverOutput<14>>;
using output10 = PowerOutput<PwmDriverOutput<12>, PwmDriverOutput<14>>;

FramDeserializer deserializer;

BinaryDeserializer* BrytecBoard::getDeserializer()
{
    BoardHardware::setSpiMemory();

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
    if (type == IOTypes::Types::Output_Batt) {
        switch (index) {
        case BT_PIN_Pin_1_and_8:
            output3::setDiagnostics(true);
            break;
        case BT_PIN_Pin_2_and_9:
            output6::setDiagnostics(true);
            break;
        case BT_PIN_Pin_6_and_12:
            output1::setDiagnostics(true);
            break;
        case BT_PIN_Pin_7_and_13:
            output5::setDiagnostics(true);
            break;
        case BT_PIN_Pin_14_and_15:
            output4::setDiagnostics(true);
            break;
        case BT_PIN_Pin_18_and_19:
            output2::setDiagnostics(true);
            break;
        case BT_PIN_Pin_20:
            output10::setDiagnostics(true);
            break;
        case BT_PIN_Pin_21:
            output9::setDiagnostics(true);
            break;
        case BT_PIN_Pin_25:
            output8::setDiagnostics(true);
            break;
        case BT_PIN_Pin_26:
            output7::setDiagnostics(true);
            break;

        default:
            break;
        }
    }
}

void BrytecBoard::shutdownAllPins()
{
    HAL_GPIO_WritePin(User_Led_GPIO_Port, User_Led_Pin, GPIO_PIN_RESET);
    output1::setValue(0.0f);
    output2::setValue(0.0f);
    output3::setValue(0.0f);
    output4::setValue(0.0f);
    output5::setValue(0.0f);
    output6::setValue(0.0f);
    output7::setValue(0.0f);
    output8::setValue(0.0f);
    output9::setValue(0.0f);
    output10::setValue(0.0f);
    output1::setDiagnostics(false);
    output2::setDiagnostics(false);
    output3::setDiagnostics(false);
    output4::setDiagnostics(false);
    output5::setDiagnostics(false);
    output6::setDiagnostics(false);
    output7::setDiagnostics(false);
    output8::setDiagnostics(false);
    output9::setDiagnostics(false);
    output10::setDiagnostics(false);
}

float BrytecBoard::getPinValue(uint16_t index, IOTypes::Types type)
{
    return 0.0f;

    BoardHardware::setSpiL9966();

    if (type == IOTypes::Types::Input_20V_Variable || type == IOTypes::Types::Input_5V_Variable) {
        switch (index) {
        case BT_PIN_Pin_22: // Input 1
            return L9966::readIoVoltage(5);
        case BT_PIN_Pin_23: // Input 2
            return L9966::readIoVoltage(6);
        case BT_PIN_Pin_24: // Input 3
            return L9966::readIoVoltage(7);

        default:
            break;
        }
    }

    return 0.0f;
}

float getAdcVoltage(uint16_t index)
{
    uint32_t conversion = 0;

    switch (index) {
    case BT_PIN_Pin_1_and_8:
        conversion = ADCIN_3;
        break;
    case BT_PIN_Pin_2_and_9:
        conversion = ADCIN_4;
        break;
    case BT_PIN_Pin_6_and_12:
        conversion = ADCIN_5;
        break;
    case BT_PIN_Pin_7_and_13:
        conversion = ADCIN_11;
        break;
    case BT_PIN_Pin_14_and_15:
        conversion = ADCIN_2;
        break;
    case BT_PIN_Pin_18_and_19:
        conversion = ADCIN_14;
        break;
    case BT_PIN_Pin_20:
        conversion = ADCIN_1x2;
        break;
    case BT_PIN_Pin_21:
        conversion = ADCIN_1;
        break;
    case BT_PIN_Pin_25:
        conversion = ADCIN_12x2;
        break;
    case BT_PIN_Pin_26:
        conversion = ADCIN_12;
        break;

    default:
        return 0.0f;
    }

    return (float)conversion / 4095.0f * 3.3f;
}

float BrytecBoard::getPinVoltage(uint16_t index)
{
    // return getAdcVoltage(index);

    BoardHardware::setSpiL9966();

    switch (index) {
    case BT_PIN_Pin_1_and_8: // Output 3
        return L9966::readIoVoltage(13);
    case BT_PIN_Pin_2_and_9: // Output 6
        return L9966::readIoVoltage(4);
    case BT_PIN_Pin_6_and_12: // Output 1
        return L9966::readIoVoltage(11);
    case BT_PIN_Pin_7_and_13: // Output 5
        return L9966::readIoVoltage(12);
    case BT_PIN_Pin_14_and_15: // Output 4
        return L9966::readIoVoltage(3);
    case BT_PIN_Pin_18_and_19: // Output 2
        return L9966::readIoVoltage(10);
    case BT_PIN_Pin_20: // Output 10
        return L9966::readIoVoltage(2);
    case BT_PIN_Pin_21: // Output 9
        return L9966::readIoVoltage(1);
    case BT_PIN_Pin_25: // Output 8
        return L9966::readIoVoltage(8);
    case BT_PIN_Pin_26: // Output 7
        return L9966::readIoVoltage(9);

    case BT_PIN_Pin_22: // Input 1
        return L9966::readIoVoltage(5);
    case BT_PIN_Pin_23: // Input 2
        return L9966::readIoVoltage(6);
    case BT_PIN_Pin_24: // Input 3
        return L9966::readIoVoltage(7);

    default:
        break;
    }

    return 0.0f;
}

float BrytecBoard::getPinCurrent(uint16_t index)
{
    float kilis = 22700.0f; // typical kilis for the BTS7002

    if (index == BT_PIN_Pin_20 || index == BT_PIN_Pin_21 || index == BT_PIN_Pin_25 || index == BT_PIN_Pin_26)
        kilis = 5400.0f; // typical kilis for the BTS7008-2

    float calcAmps = (getAdcVoltage(index) * kilis) / 1200.0f;
    return calcAmps;
}

void BrytecBoard::setPinValue(uint16_t index, IOTypes::Types type, float value)
{
    if (index == BT_PIN_Onboard_LED) {
        HAL_GPIO_WritePin(User_Led_GPIO_Port, User_Led_Pin, (GPIO_PinState)(value > 0.001f));
        return;
    }

    if (type == IOTypes::Types::Output_Batt) {
        switch (index) {
        case BT_PIN_Pin_1_and_8:
            output3::setValue(value);
            break;
        case BT_PIN_Pin_2_and_9:
            output6::setValue(value);
            break;
        case BT_PIN_Pin_6_and_12:
            output1::setValue(value);
            break;
        case BT_PIN_Pin_7_and_13:
            output5::setValue(value);
            break;
        case BT_PIN_Pin_14_and_15:
            output4::setValue(value);
            break;
        case BT_PIN_Pin_18_and_19:
            output2::setValue(value);
            break;
        case BT_PIN_Pin_20:
            output10::setValue(value);
            break;
        case BT_PIN_Pin_21:
            output9::setValue(value);
            break;
        case BT_PIN_Pin_25:
            output8::setValue(value);
            break;
        case BT_PIN_Pin_26:
            output7::setValue(value);
            break;

        default:
            break;
        }
    }
}

void BrytecBoard::sendBrytecCan(CanExtFrame frame)
{
    Usb::send(frame);
    CanBus::send(frame);
}

void BrytecBoard::ReserveConfigSize(uint16_t size)
{
    BoardHardware::setSpiMemory();

    Fram::write(0, (uint8_t*)&size, 2);
}

void BrytecBoard::updateConfig(uint8_t* data, uint32_t size, uint32_t offset)
{
    BoardHardware::setSpiMemory();

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
    BoardHardware::setSpiMemory();

    uint16_t dataSize;
    Fram::read(0, (uint8_t*)&dataSize, 2);
    return dataSize;
}

void BrytecBoard::getConfigData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    BoardHardware::setSpiMemory();

    Fram::read(offset + 2, dest, length);
}
}