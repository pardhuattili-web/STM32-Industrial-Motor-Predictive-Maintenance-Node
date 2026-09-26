#include "modbus_map.h"

static modbus_registers_t registers_image;

void MODBUS_MAP_Update(const modbus_registers_t *image)
{
    if (image == 0) return;
    registers_image = *image;
}

const modbus_registers_t *MODBUS_MAP_Get(void)
{
    return &registers_image;
}
