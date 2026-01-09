#pragma once

/// current phase
/// DO NOT USE
//float g_phase = 0.0f;

#define MAX_KEYS 10

/// -1.0 -> 1.0 range.
float g_phases[MAX_KEYS] = {0};

/// end volume.
float g_volume_scale = 0.4f;

#define SAMPLE_RATE 44100
#define MONO 1

// audio streaming format
#define BITDEPTH float

#define NOTE_C4 261.63f

