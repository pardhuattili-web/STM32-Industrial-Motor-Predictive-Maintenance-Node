#ifndef FAULT_FSM_H
#define FAULT_FSM_H
#include <stdint.h>
#include "sensor_if.h"
#include "health_monitor.h"
typedef enum { STATE_NORMAL=0, STATE_WARNING=1, STATE_FAULT=2, STATE_RECOVERY=3 } fault_state_t;
typedef enum { FAULT_NONE=0, FAULT_OVERTEMP=1, FAULT_VIBRATION=2, FAULT_OVERCURRENT=3, FAULT_SENSOR=4 } fault_code_t;
void FAULT_Init(void);
void FAULT_Update(const motor_sample_t *sample, const health_result_t *health);
fault_state_t FAULT_GetState(void);
fault_code_t FAULT_GetCode(void);
#endif
