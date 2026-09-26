#include "sensor_if.h"

void SENSOR_Init(void)
{
    /* Replace with ADC/I2C/SPI initialization for the selected STM32 board. */
}

int SENSOR_Read(motor_sample_t *sample)
{
    if (sample == 0) return -1;

    /*
     * Safe reference values for firmware development.
     * Replace with calibrated sensor drivers during hardware integration.
     */
    sample->temperature_c = 48.0f;
    sample->vibration = 0.18f;
    sample->current_a = 2.4f;
    sample->temp_valid = 1U;
    sample->vibration_valid = 1U;
    sample->current_valid = 1U;
    return 0;
}
