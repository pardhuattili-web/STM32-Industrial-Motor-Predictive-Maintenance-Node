#ifndef HEALTH_MONITOR_H
#define HEALTH_MONITOR_H
#include <stdint.h>
#include "sensor_if.h"
typedef struct {
    float temp_penalty;
    float vibration_penalty;
    float current_penalty;
    uint8_t health_score;
} health_result_t;
void HEALTH_Init(void);
void HEALTH_Update(const motor_sample_t *sample, health_result_t *result);
#endif
