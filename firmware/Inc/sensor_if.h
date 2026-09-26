#ifndef SENSOR_IF_H
#define SENSOR_IF_H
#include <stdint.h>
typedef struct {
    float temperature_c;
    float vibration;
    float current_a;
    uint8_t temp_valid;
    uint8_t vibration_valid;
    uint8_t current_valid;
} motor_sample_t;
void SENSOR_Init(void);
int SENSOR_Read(motor_sample_t *sample);
#endif
