#include "health_monitor.h"

static float penalty(float x, float warning, float critical)
{
    if (x <= warning) return 0.0f;
    if (x >= critical) return 100.0f;
    return 50.0f * (x - warning) / (critical - warning);
}

void HEALTH_Init(void) {}

void HEALTH_Update(const motor_sample_t *sample, health_result_t *result)
{
    if (sample == 0 || result == 0) return;

    result->temp_penalty = penalty(sample->temperature_c, 65.0f, 85.0f);
    result->vibration_penalty = penalty(sample->vibration, 0.35f, 0.80f);
    result->current_penalty = penalty(sample->current_a, 4.0f, 7.0f);

    float health =
        100.0f
        - 0.35f * result->temp_penalty
        - 0.40f * result->vibration_penalty
        - 0.25f * result->current_penalty;

    if (health < 0.0f) health = 0.0f;
    if (health > 100.0f) health = 100.0f;
    result->health_score = (uint8_t)health;
}
