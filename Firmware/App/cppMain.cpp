#include "cppMain.h"

#include "BoardHardware.h"
#include "CanBus.h"
#include "EBrytecApp.h"
#include "Fram.h"
#include "L9966.h"
#include "MsTimeout.h"
#include "PwmDriver.h"
#include "UsDelay.h"
#include "Usb.h"
#include "stm32g4xx_hal.h"
#include <stdint.h>

MsTimeout brytecMs(10);
MsTimeout adcTimeout(100);
MsTimeout adcPrintTimeout(1000);
bool lastIgntionPowerState = false;

void cppMain()
{
    DWT_Delay_Init();

    PwmDriver::init();

    BoardHardware::calibrateAdc();

    BoardHardware::setSpiMemory();
    Fram::init(&hspi1);

    BoardHardware::setSpiL9966();
    L9966::init(&hspi1);

    Brytec::EBrytecApp::initalize();

    if (Brytec::EBrytecApp::isDeserializeOk())
        printf("Deserialize Ok\n");
    else
        printf("Deserialize FAIL\n");

    while (1) {

        Usb::update();

        Brytec::EBrytecApp::processCanCommands();

        bool igntionPowerState = BoardHardware::getIgntionPowerState();
        if (igntionPowerState != lastIgntionPowerState) {
            PwmDriver::setEnableOutput(igntionPowerState);
            lastIgntionPowerState = igntionPowerState;
        }

        if (brytecMs.isTimeout())
            Brytec::EBrytecApp::update(brytecMs.getTimestepMs());

        if (adcTimeout.isTimeout())
            BoardHardware::readNextAdc();

        // if (adcPrintTimeout.isTimeout())
        //     BoardHardware::printAllAdc();
    }
}