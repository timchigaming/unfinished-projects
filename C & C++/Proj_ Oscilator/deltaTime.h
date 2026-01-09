#pragma once

#include "windows.h"

LARGE_INTEGER frequency;
LARGE_INTEGER lastFrameTime;
double deltaTime;

void initialize_timer() {
    QueryPerformanceFrequency(&frequency); // Get counter frequency
    QueryPerformanceCounter(&lastFrameTime); // Time of first count
}

void update_deltaTime() {
    LARGE_INTEGER currentFrameTime;
    QueryPerformanceCounter(&currentFrameTime);

    // Difference between ticks
    ULONGLONG deltaTicks = currentFrameTime.QuadPart - lastFrameTime.QuadPart;

    // DeltaTime in seconds
    deltaTime = (double)deltaTicks / frequency.QuadPart;

    // Update last frame time
    lastFrameTime = currentFrameTime;
}