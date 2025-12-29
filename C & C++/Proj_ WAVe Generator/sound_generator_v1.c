#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define FREQ 44100
#define DURATION 3
#define BITSPERSAMPLE 16
#define CHANNELS 1

#define DATASIZE (FREQ * DURATION * (BITSPERSAMPLE/8))


typedef struct WavHeader {
    unsigned int chunkId;
    unsigned int chunkSize;
    unsigned int format;
    unsigned int subchunk1Id;
    unsigned int subchunk1Size;
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned int sampleRate;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    unsigned int subchunk2Id;
    unsigned int subchunk2Size;
} WavHeader;

int main(int argc, char const *argv[])
{
    FILE* f2 = fopen("blebleble.wav", "wb");

    WavHeader wav2 = {
        chunkId: 0x46464952,
        chunkSize: 44 + DATASIZE - 8,
        format: 0x45564157,
        subchunk1Id: 0x20746D66,
        subchunk1Size: 16,
        audioFormat: 1,
        numChannels: CHANNELS,
        sampleRate: FREQ,
        byteRate: FREQ * CHANNELS * BITSPERSAMPLE/8,
        blockAlign: 1 * BITSPERSAMPLE/8,
        bitsPerSample: BITSPERSAMPLE,
        subchunk2Id: 0x61746164,
        subchunk2Size: DATASIZE
    };

    short data[DATASIZE] = {0};

    for (size_t i = 0; i < DATASIZE / (BITSPERSAMPLE/8); ++i) {
        float value = sinf((float)i / FREQ * 3.14159 * 2 * 440);
        data[i] = (short)(value * 32767);
        //printf("%d\n", data[i]);
    }
    
    wav2.chunkSize += DATASIZE;
    fwrite(&wav2, sizeof(WavHeader) + 8, 1, f2);
    fwrite(&data, sizeof(*data), DATASIZE/(BITSPERSAMPLE/8), f2);
    fclose(f2);

    return 0;
}
