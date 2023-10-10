#include "cppMain.h"

#include "CanBus.h"
#include "EBrytecApp.h"
#include "PwmDriver.h"
#include "PwmDriverOutput.h"
#include "Stm32Output.h"
#include "Usb.h"
#include "adc.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"
#include "usbd_cdc_if.h"
#include <stdint.h>

#define ADC_NUM 10
volatile uint16_t adcConv[ADC_NUM] = {};

GPIO_PinState powerState = GPIO_PIN_RESET;

using dsel7_8 = Stm32Output<GPIOC_BASE, Dsel7_8_Pin>;
using dsel9_10 = PwmDriverOutput<13>;

void readAdc()
{
    static uint64_t lastAdc = 0;
    uint64_t adcDifference = HAL_GetTick() - lastAdc;
    if (adcDifference >= 50) {
        lastAdc = HAL_GetTick();

        static uint8_t channel = 0;

        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        adcConv[channel] = HAL_ADC_GetValue(&hadc1);
        channel++;
        channel = channel % ADC_NUM;

        if (channel == 0) {
            // Select output 0
            dsel7_8::setState(false);
            dsel9_10::setState(false);
        } else if (channel == 5) {
            // Select output 1
            dsel7_8::setState(true);
            dsel9_10::setState(true);
        }
    }
}

void printAdc()
{
    static uint64_t lastMillisPrint = 0;
    uint64_t difference = HAL_GetTick() - lastMillisPrint;
    if (difference >= 1000) {
        lastMillisPrint = HAL_GetTick();
        for (int i = 0; i < ADC_NUM; i++) {
            printf("%d, ", adcConv[i]);
        }
        printf("\n");
    }
}

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
        static uint64_t lastMillis = 0;
        uint64_t difference = HAL_GetTick() - lastMillis;
        if (difference >= 10) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            Brytec::EBrytecApp::update(timestep);
        }
        /////////////////////////////////////////

        readAdc();
    }
}