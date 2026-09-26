#include "fault_fsm.h"

static fault_state_t state;
static fault_code_t code;
static uint8_t warning_count;
static uint8_t fault_count;
static uint8_t recovery_count;

#define WARNING_SAMPLES 3U
#define FAULT_SAMPLES 5U
#define RECOVERY_SAMPLES 5U

void FAULT_Init(void)
{
    state = STATE_NORMAL;
    code = FAULT_NONE;
    warning_count = 0U;
    fault_count = 0U;
    recovery_count = 0U;
}

static fault_code_t detect_fault(const motor_sample_t *s)
{
    if (s == 0) return FAULT_SENSOR;
    if (!s->temp_valid || !s->vibration_valid || !s->current_valid) return FAULT_SENSOR;
    if (s->temperature_c >= 85.0f) return FAULT_OVERTEMP;
    if (s->vibration >= 0.80f) return FAULT_VIBRATION;
    if (s->current_a >= 7.0f) return FAULT_OVERCURRENT;
    return FAULT_NONE;
}

void FAULT_Update(const motor_sample_t *sample, const health_result_t *health)
{
    (void)health;
    const fault_code_t detected = detect_fault(sample);

    if (detected != FAULT_NONE) {
        recovery_count = 0U;
        code = detected;
        fault_count++;

        if (fault_count >= FAULT_SAMPLES) {
            state = STATE_FAULT;
        } else if (state == STATE_NORMAL) {
            warning_count++;
            if (warning_count >= WARNING_SAMPLES) state = STATE_WARNING;
        }
        return;
    }

    fault_count = 0U;
    warning_count = 0U;

    if (state == STATE_FAULT || state == STATE_WARNING) {
        state = STATE_RECOVERY;
        recovery_count = 0U;
    }

    if (state == STATE_RECOVERY) {
        recovery_count++;
        if (recovery_count >= RECOVERY_SAMPLES) {
            state = STATE_NORMAL;
            code = FAULT_NONE;
        }
    }
}

fault_state_t FAULT_GetState(void) { return state; }
fault_code_t FAULT_GetCode(void) { return code; }
