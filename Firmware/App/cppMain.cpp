#include "cppMain.h"

#include "BoardHardware.h"
#include "CanBus.h"
#include "EBrytecApp.h"
#include "L9966.h"
#include "PwmDriver.h"
#include "Usb.h"
#include "stm32g4xx_hal.h"
#include <stdint.h>

void cppMain()
{
    PwmDriver::init();

    Brytec::EBrytecApp::initalize();

    if (Brytec::EBrytecApp::isDeserializeOk())
        printf("Deserialize Ok\n");
    else
        printf("Deserialize FAIL\n");

    CanBus::start();

    BoardHardware::calibrateAdc();

    BoardHardware::setSpiL9966();
    L9966::init();

    while (1) {

        Usb::update();

        // Brytec //////////////////////////////
        static uint64_t lastMillis = 0;
        uint64_t difference = HAL_GetTick() - lastMillis;
        if (difference >= 10) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            Brytec::EBrytecApp::update(timestep);
        }
        /////////////////////////////////////////

        BoardHardware::readAllAdc();
    }
}