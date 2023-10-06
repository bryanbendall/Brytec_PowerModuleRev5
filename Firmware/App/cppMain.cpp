#include "cppMain.h"

#include "CanBus.h"
#include "EBrytecApp.h"
#include "PwmDriver.h"
#include "Usb.h"
#include "adc.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"
#include "usbd_cdc_if.h"
#include <stdint.h>

#define ADC_NUM 10
volatile uint16_t adcConv[ADC_NUM] = {};

static uint64_t lastMillis = 0;
static uint64_t lastAdc = 0;
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

    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

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
        if (difference >= 10) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            Brytec::EBrytecApp::update(timestep);
        }
        /////////////////////////////////////////

        uint64_t adcDifference = HAL_GetTick() - lastAdc;
        if (adcDifference >= 50) {
            lastAdc = HAL_GetTick();

            static uint8_t channel = 0;

            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
            adcConv[channel] = HAL_ADC_GetValue(&hadc1);
            channel++;
            channel = channel % ADC_NUM;
        }

    }
}