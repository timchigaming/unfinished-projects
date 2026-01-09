#pragma once

// Neat
#include "headers.h"
#include "vars.h"

#define PI 3.14159265f

void generate_sine_wave(float freq, unsigned int frameCount, BITDEPTH* pOut, int key) {
    float phaseIncrement = freq / SAMPLE_RATE;

    for (int i = 0; i < frameCount; i++) {
        float sample = sinf((PI * 2) * g_phases[key]);
        pOut[i] += sample * g_volume_scale;

        g_phases[key] = fmodf(g_phases[key] + phaseIncrement, 1.0f);
    }
}