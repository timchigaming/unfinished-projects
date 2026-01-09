#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

// Neat
#include "headers.h"
#include "vars.h"
#include "generators.h"

// VISUALISATION MODULE!!
#include "visualisation.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    // In playback mode copy data to pOutput. In capture mode read data from pInput. In full-duplex mode, both
    // pOutput and pInput will be valid and you can move data from pInput into pOutput. Never process more than
    // frameCount frames.
    BITDEPTH* pOut = (BITDEPTH*)pOutput;

    memset(pOutput, 0, sizeof(BITDEPTH) * frameCount);

    for (int i = 0; i <= 10; i++)
    {
        if (GetAsyncKeyState('0' + i) & 0x8000) {
            float freq = NOTE_C4 * powf(2.0f, i / 12.0f);
            generate_sine_wave(freq, frameCount, pOut, i);
        }
    }

    vsm_drawWave_sync(pOut, frameCount);
}

int main(int argc, char const *argv[]) {
    // Basic MiniAudio initialization
        ma_device_config config = ma_device_config_init(ma_device_type_playback);
        config.playback.format   = ma_format_f32;   // Set to ma_format_unknown to use the device's native format.
        config.playback.channels = MONO;               // Set to 0 to use the device's native channel count.
        config.sampleRate        = SAMPLE_RATE;           // Set to 0 to use the device's native sample rate.
        config.dataCallback      = data_callback;   // This function will be called when miniaudio needs more data.
        config.pUserData         = NULL;   // Can be accessed from the device object (device.pUserData).
    
        ma_device device;
        if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
            return -1;  // Failed to initialize the device.
        }
    
    // Starting data_callback to work
        ma_device_start(&device);     // The device is sleeping by default so you'll need to start it manually.
    
    // ======= VISUALISATION MODULE =======
        vsm_init(console);

    // Init deltaTime counter
        initialize_timer();

    // Get process alive
        // Do something here. Probably your program's main loop.
        getchar();

    //Uninit
        ma_device_uninit(&device);
    return 0;
}
