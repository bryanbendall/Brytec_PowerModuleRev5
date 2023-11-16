#include "BrytecBoard.h"

#include "BoardHardware.h"
#include "BoardPinInput.h"
#include "BoardPinInputOutput.h"
#include "CanBus.h"
#include "Fram.h"
#include "FramDeserializer.h"
#include "L9966.h"
#include "L9966Input.h"
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
using out1 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<5>, PwmDriverOutput<4>>, L9966Input<11>>;
using out2 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<2>, Stm32Output<GPIOB_BASE, Den2_Pin>>, L9966Input<10>>;
using out3 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<9>, PwmDriverOutput<8>>, L9966Input<13>>;
using out4 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<11>, PwmDriverOutput<10>>, L9966Input<3>>;
using out5 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<3>, Stm32Output<GPIOA_BASE, Den5_Pin>>, L9966Input<12>>;
using out6 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<7>, PwmDriverOutput<6>>, L9966Input<4>>;

// Dual outputs
using out7 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<1>, Stm32Output<GPIOC_BASE, Den7_8_Pin>>, L9966Input<9>>;
using out8 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<0>, Stm32Output<GPIOC_BASE, Den7_8_Pin>>, L9966Input<8>>;
using out9 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<15>, PwmDriverOutput<14>>, L9966Input<1>>;
using out10 = BoardPinInputOutput<PowerOutput<PwmDriverOutput<12>, PwmDriverOutput<14>>, L9966Input<2>>;

// Inputs
using in1 = BoardPinInput<L9966Input<5>>;
using in2 = BoardPinInput<L9966Input<6>>;
using in3 = BoardPinInput<L9966Input<7>>;

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
    BoardHardware::setSpiL9966();

    switch (index) {

    // Inputs and Outputs
    case BT_PIN_Pin_1_and_8:
        out3::setupType(type);
        break;
    case BT_PIN_Pin_2_and_9:
        out6::setupType(type);
        break;
    case BT_PIN_Pin_6_and_12:
        out1::setupType(type);
        break;
    case BT_PIN_Pin_7_and_13:
        out5::setupType(type);
        break;
    case BT_PIN_Pin_14_and_15:
        out4::setupType(type);
        break;
    case BT_PIN_Pin_18_and_19:
        out2::setupType(type);
        break;
    case BT_PIN_Pin_20:
        out10::setupType(type);
        break;
    case BT_PIN_Pin_21:
        out9::setupType(type);
        break;
    case BT_PIN_Pin_25:
        out8::setupType(type);
        break;
    case BT_PIN_Pin_26:
        out7::setupType(type);
        break;

    // Inputs only
    case BT_PIN_Pin_22:
        in1::setupType(type);
        break;
    case BT_PIN_Pin_23:
        in2::setupType(type);
        break;
    case BT_PIN_Pin_24:
        in3::setupType(type);
        break;

    default:
        break;
    }
}

void BrytecBoard::shutdownAllPins()
{
    HAL_GPIO_WritePin(User_Led_GPIO_Port, User_Led_Pin, GPIO_PIN_RESET);
    out1::shutdown();
    out2::shutdown();
    out3::shutdown();
    out4::shutdown();
    out5::shutdown();
    out6::shutdown();
    out7::shutdown();
    out8::shutdown();
    out9::shutdown();
    out10::shutdown();

    BoardHardware::setSpiL9966();
    L9966::softwareReset();
    L9966::init();
}

float BrytecBoard::getPinValue(uint16_t index, IOTypes::Types type)
{
    BoardHardware::setSpiL9966();

    switch (index) {

    // Inputs and Outputs
    case BT_PIN_Pin_1_and_8:
        return out3::getValue(type);
    case BT_PIN_Pin_2_and_9:
        return out6::getValue(type);
    case BT_PIN_Pin_6_and_12:
        return out1::getValue(type);
    case BT_PIN_Pin_7_and_13:
        return out5::getValue(type);
    case BT_PIN_Pin_14_and_15:
        return out4::getValue(type);
    case BT_PIN_Pin_18_and_19:
        return out2::getValue(type);
    case BT_PIN_Pin_20:
        return out10::getValue(type);
    case BT_PIN_Pin_21:
        return out9::getValue(type);
    case BT_PIN_Pin_25:
        return out8::getValue(type);
    case BT_PIN_Pin_26:
        return out7::getValue(type);

        // Inputs
    case BT_PIN_Pin_22:
        return in1::getValue(type);
    case BT_PIN_Pin_23:
        return in2::getValue(type);
    case BT_PIN_Pin_24:
        return in3::getValue(type);

    default:
        break;
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
    BoardHardware::setSpiL9966();

    switch (index) {
    case BT_PIN_Pin_1_and_8:
        return out3::readVoltage();
    case BT_PIN_Pin_2_and_9:
        return out6::readVoltage();
    case BT_PIN_Pin_6_and_12:
        return out1::readVoltage();
    case BT_PIN_Pin_7_and_13:
        return out5::readVoltage();
    case BT_PIN_Pin_14_and_15:
        return out4::readVoltage();
    case BT_PIN_Pin_18_and_19:
        return out2::readVoltage();
    case BT_PIN_Pin_20:
        return out10::readVoltage();
    case BT_PIN_Pin_21:
        return out9::readVoltage();
    case BT_PIN_Pin_25:
        return out8::readVoltage();
    case BT_PIN_Pin_26:
        return out7::readVoltage();

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
            out3::setValue(value);
            break;
        case BT_PIN_Pin_2_and_9:
            out6::setValue(value);
            break;
        case BT_PIN_Pin_6_and_12:
            out1::setValue(value);
            break;
        case BT_PIN_Pin_7_and_13:
            out5::setValue(value);
            break;
        case BT_PIN_Pin_14_and_15:
            out4::setValue(value);
            break;
        case BT_PIN_Pin_18_and_19:
            out2::setValue(value);
            break;
        case BT_PIN_Pin_20:
            out10::setValue(value);
            break;
        case BT_PIN_Pin_21:
            out9::setValue(value);
            break;
        case BT_PIN_Pin_25:
            out8::setValue(value);
            break;
        case BT_PIN_Pin_26:
            out7::setValue(value);
            break;

        default:
            break;
        }
    }
}

void BrytecBoard::sendBrytecCan(const CanExtFrame& frame)
{
    CanBus::send(frame);
}

void BrytecBoard::sendBrytecCanUsb(const CanExtFrame& frame)
{
    Brytec::UsbPacket packet;
    packet.set<Brytec::CanExtFrame>(frame);
    Usb::send(packet);
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