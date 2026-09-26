#include "sensor_if.h"
#include "health_monitor.h"
#include "fault_fsm.h"
#include "modbus_map.h"

static uint16_t sample_counter;

void APP_ReferenceStep(void)
{
    motor_sample_t sample;
    health_result_t health;

    if (SENSOR_Read(&sample) != 0) {
        return;
    }

    HEALTH_Update(&sample, &health);
    FAULT_Update(&sample, &health);

    modbus_registers_t regs = {
        .temperature_x10 = (uint16_t)(sample.temperature_c * 10.0f),
        .vibration_x100 = (uint16_t)(sample.vibration * 100.0f),
        .current_x10 = (uint16_t)(sample.current_a * 10.0f),
        .health_score = health.health_score,
        .fault_code = (uint16_t)FAULT_GetCode(),
        .state = (uint16_t)FAULT_GetState(),
        .sample_counter = sample_counter++,
        .status_bits = (uint16_t)(
            (sample.temp_valid ? 1U : 0U) |
            (sample.vibration_valid ? 2U : 0U) |
            (sample.current_valid ? 4U : 0U))
    };

    MODBUS_MAP_Update(&regs);
}

/*
 * The Modbus RTU transport/CRC layer should call MODBUS_MAP_Get()
 * when responding to function-code 0x03 requests.
 */
