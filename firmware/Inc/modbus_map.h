#ifndef MODBUS_MAP_H
#define MODBUS_MAP_H
#include <stdint.h>
typedef struct {
    uint16_t temperature_x10;
    uint16_t vibration_x100;
    uint16_t current_x10;
    uint16_t health_score;
    uint16_t fault_code;
    uint16_t state;
    uint16_t sample_counter;
    uint16_t status_bits;
} modbus_registers_t;
void MODBUS_MAP_Update(const modbus_registers_t *image);
const modbus_registers_t *MODBUS_MAP_Get(void);
#endif
