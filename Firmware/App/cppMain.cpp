#include "cppMain.h"

#include "CanBus.h"
#include "EBrytecApp.h"
#include "Usb.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"
#include "usbd_cdc_if.h"

#include <stdint.h>

static uint64_t lastMillis = 0;

// static uint32_t tickDelay = 2000;

void cppMain()
{
    Brytec::EBrytecApp::initalize();

    // if (Brytec::EBrytecApp::isDeserializeOk())
    //     printf("Des succ");
    // else
    //     printf("Des fail");

    CanBus::start();

    while (1) {

        // static uint32_t tick = 0;
        // if (HAL_GetTick() != tick && HAL_GetTick() % tickDelay == 0) {
        //     tick = HAL_GetTick();
        //     HAL_GPIO_TogglePin(User_Led_GPIO_Port, User_Led_Pin);
        //     printf("toggle led\n");
        // }

        Usb::update();

        // HAL_Delay(1);

        // Brytec //////////////////////////////
        uint64_t difference = HAL_GetTick() - lastMillis;
        if (difference > 1) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            Brytec::EBrytecApp::update(timestep);
        }
        /////////////////////////////////////////
    }
}