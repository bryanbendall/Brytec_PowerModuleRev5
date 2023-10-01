#include "cppMain.h"

#include "CanBus.h"
#include "EBrytecApp.h"
#include "PwmDriver.h"
#include "Usb.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"
#include "usbd_cdc_if.h"
#include <stdint.h>

static uint64_t lastMillis = 0;
GPIO_PinState powerState = GPIO_PIN_RESET;

void cppMain()
{
    PwmDriver::init();

    Brytec::EBrytecApp::initalize();

    if (Brytec::EBrytecApp::isDeserializeOk())
        printf("Deserialize Ok\n");
    else
        printf("Deserialize FAIL\n");

    CanBus::start();

    while (1) {

        {
            GPIO_PinState state = HAL_GPIO_ReadPin(PowerSwitchStatus_GPIO_Port, PowerSwitchStatus_Pin);
            if (powerState != state) {
                powerState = state;
                // true is power by 12v, false is usb
            }
        }

        Usb::update();

        // Brytec //////////////////////////////
        uint64_t difference = HAL_GetTick() - lastMillis;
        if (difference >= 1000) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            Brytec::EBrytecApp::update(timestep);
        }
        /////////////////////////////////////////
    }
}