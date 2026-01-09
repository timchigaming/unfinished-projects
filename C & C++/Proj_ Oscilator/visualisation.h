#pragma once

// Neat
#include "headers.h"
#include "vars.h"

// LIBGDI!!! I love it, idk why
#include "windows.h"

// for VSM synchronization
#include "deltaTime.h"
double timePassed = 0;

// Where VSM should to draw a waveform.
typedef enum {
    console = 0,
    directly_to_screen = 1
} e_VSM_Surface;

////////// Structs //////////

typedef struct {
    HWND surface;
    /// In HZ
    double updateRate;
} VSM;

/// GLOBAL VSM VARIABLE(handle) ///
VSM vsm;

////////// Functions //////////
/// VSM - VisualiSation Module
void vsm_init(e_VSM_Surface surface) {
    vsm.surface = GetDesktopWindow(); // by default
    switch (surface)
    {
    case console: {
        vsm.surface = GetConsoleWindow();
        break;
        }
    default: {
        break;
        }
    }
    //vsm.surface.hdc = GetWindowDC(vsm.surface.hwnd);

    // Get the window size
    //GetClientRect(vsm.surface.hwnd, vsm.surface.rect );

    // Get monitore refresh rate
    HDC desktop = GetDC(NULL);
    vsm.updateRate = GetDeviceCaps(desktop, VREFRESH);
    ReleaseDC(NULL, desktop);
}

void vsm_drawWave_OLD(BITDEPTH* buffer, unsigned int frameCount) {
/////////////////////////////////////////////////
    RECT rect;
    GetClientRect(vsm.surface, &rect);

    int window_width = rect.right - rect.left;
    int window_heigth = rect.bottom - rect.top;
    float pixelStep = window_width / frameCount; // horisontal pixel offset
    int window_vertical_center = rect.top + (window_heigth/2);
    
    float amplitudeScale = 100;
/////////////////////////////////////////////////
    HDC hdc = GetDC(vsm.surface);

    // double buffered
    HDC v_hdc = CreateCompatibleDC(hdc);
    HBITMAP v_bitmap = CreateCompatibleBitmap(hdc, window_width, window_heigth);
    SelectObject(v_hdc, v_bitmap);

    FillRect(v_hdc, &rect, (HBRUSH)(COLOR_BACKGROUND + 1));

    // OLD METHOD - with no optimisation, works slow, but accuratly
    for (int i = 0; i < frameCount; i++)
    {
        float amplitude = ma_clamp(buffer[i], -1.0f, 1.0f) ;
        float pixelToDraw = i*pixelStep;

        SetPixel(v_hdc, rect.left + pixelToDraw, window_vertical_center - (amplitude * amplitudeScale), RGB(255, 255, 255));
    }

    BitBlt(hdc, rect.left, rect.top, window_width, window_heigth, v_hdc, rect.left, rect.top, SRCCOPY);

    DeleteObject(v_bitmap);
    DeleteDC(v_hdc);
    ReleaseDC(vsm.surface, hdc);
}

void vsm_drawWave(BITDEPTH* buffer, unsigned int frameCount) {
/////////////////////////////////////////////////
    RECT rect;
    GetClientRect(vsm.surface, &rect);

    int window_width = rect.right - rect.left;
    int window_heigth = rect.bottom - rect.top;
    float pixelStep = window_width / frameCount; // horisontal pixel offset
    int window_vertical_center = rect.top + (window_heigth/2);
    
    float amplitudeScale = 200;
/////////////////////////////////////////////////
    HDC hdc = GetDC(vsm.surface);

    // double buffered
    HDC v_hdc = CreateCompatibleDC(hdc);
    HBITMAP v_bitmap = CreateCompatibleBitmap(hdc, window_width, window_heigth);
    SelectObject(v_hdc, v_bitmap);

    HPEN hWhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(v_hdc, hWhitePen);

    FillRect(v_hdc, &rect, (HBRUSH)(COLOR_BACKGROUND + 1));

    POINT* points = (POINT*) malloc(sizeof(POINT) * frameCount);
    if (points) {
        for(int i = 0; i < frameCount; i++) {
            float amplitude = ma_clamp(buffer[i], -1.0f, 1.0f) ;
            float pixelToDraw = i*pixelStep;

            points[i].x = pixelToDraw;
            points[i].y = window_vertical_center - amplitude * amplitudeScale;
        }
        if (frameCount > 0) {
            Polyline(v_hdc, points, frameCount);
        }
        free(points);
    }
    

    /*
    for (int i = 0; i < frameCount; i++)
    {
        float amplitude = ma_clamp(buffer[i], -1.0f, 1.0f) ;
        float pixelToDraw = i*pixelStep;

        SetPixel(v_hdc, rect.left + pixelToDraw, window_vertical_center - (amplitude * amplitudeScale), RGB(255, 255, 255));
    }
    */
    BitBlt(hdc, rect.left, rect.top, window_width, window_heigth, v_hdc, rect.left, rect.top, SRCCOPY);

    DeleteObject(hWhitePen);
    DeleteObject(v_bitmap);
    DeleteDC(v_hdc);
    ReleaseDC(vsm.surface, hdc);
}

void vsm_drawWave_sync(BITDEPTH* buffer, unsigned int frameCount) {
    update_deltaTime();

    timePassed += deltaTime;
    if (timePassed >= 1.0/vsm.updateRate) { 
        vsm_drawWave(buffer, frameCount);
        timePassed -= (1.0 / vsm.updateRate);
    }
}