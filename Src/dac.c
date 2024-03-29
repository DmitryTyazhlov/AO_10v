#include "dac.h"

#include "gpio.h"
#include "main.h"
#include "spi.h"

uint8_t dac_set_voltage(uint8_t channel, double voltage) {
    voltage *= 404.08;
    uint16_t size = (uint16_t)voltage;
    switch (channel) {
        case 0:
            HAL_GPIO_WritePin(CS_AO0_GPIO_Port, CS_AO0_Pin, GPIO_PIN_RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(CS_AO1_GPIO_Port, CS_AO1_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(CS_AO2_GPIO_Port, CS_AO2_Pin, GPIO_PIN_RESET);
            break;
    }

    HAL_SPI_Transmit(&hspi1, (uint8_t*)&size, 1, 1);
    HAL_GPIO_WritePin(CS_AO0_GPIO_Port, CS_AO0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CS_AO1_GPIO_Port, CS_AO1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CS_AO2_GPIO_Port, CS_AO2_Pin, GPIO_PIN_SET);

    return 0;
}
