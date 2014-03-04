#include "filter.h"

static float alpha = 0.15f;

/*
float alpha_func(int rc, int sample_rate)
{
    float dt = 1.0 / sample_rate;

    return dt / (rc + dt);
}
*/
void low_pass(float input[3], float filtered[3])
{
    int i;

    for (i = 0; i < 3; i++)
        filtered[i] = filtered[i] + alpha * (input[i] - filtered[i]);
}

void high_pass(float input[3], float filtered[3])
{
    static tmp[3] = { 0 };
    int i;

    for (i = 0; i < 3; i++) {
        filtered[i] = alpha * (filtered[i] + input[i] - tmp[i]);
        tmp[i] = input[i];
    }
}
