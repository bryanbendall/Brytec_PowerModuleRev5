#include "BoardHardware.h"

#include "PwmDriverOutput.h"
#include "Stm32Output.h"
#include "adc.h"
#include "spi.h"
#include <stdio.h>

#define ADC_NUM 10

using dsel7_8 = Stm32Output<GPIOC_BASE, Dsel7_8_Pin>;
using dsel9_10 = PwmDriverOutput<13>;

enum class SpiState {
    Memory,
    L9966
};

struct BoardHardwareData {
    volatile uint16_t adcConv[ADC_NUM] = {};
    SpiState spiState = SpiState::Memory;
};
static BoardHardwareData s_data;

void BoardHardware::setSpiMemory()
{
    if (s_data.spiState == SpiState::Memory)
        return;

    HAL_SPI_DeInit(&hspi1);

    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        Error_Handler();
    }

    s_data.spiState = SpiState::Memory;
}

void BoardHardware::setSpiL9966()
{
    if (s_data.spiState == SpiState::L9966)
        return;

    HAL_SPI_DeInit(&hspi1);

    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        Error_Handler();
    }

    s_data.spiState = SpiState::L9966;
}

void BoardHardware::calibrateAdc()
{
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
}

void BoardHardware::readAllAdc()
{
    static uint64_t lastAdc = 0;
    uint64_t adcDifference = HAL_GetTick() - lastAdc;
    if (adcDifference >= 50) {
        lastAdc = HAL_GetTick();

        static uint8_t channel = 0;

        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        s_data.adcConv[channel] = HAL_ADC_GetValue(&hadc1);
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

void BoardHardware::printAllAdc()
{
    static uint64_t lastMillisPrint = 0;
    uint64_t difference = HAL_GetTick() - lastMillisPrint;
    if (difference >= 1000) {
        lastMillisPrint = HAL_GetTick();
        printf("Adc readings - ");
        for (int i = 0; i < ADC_NUM; i++) {
            printf("%d, ", s_data.adcConv[i]);
        }
        printf("\n");
    }
}

uint16_t BoardHardware::getAdcData(uint8_t index)
{
    if (index >= ADC_NUM)
        return 0;

    return s_data.adcConv[index];
}

bool BoardHardware::getIgntionPowerState()
{
    return HAL_GPIO_ReadPin(PowerSwitchStatus_GPIO_Port, PowerSwitchStatus_Pin);
}