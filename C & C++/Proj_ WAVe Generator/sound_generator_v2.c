#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define FREQ 44100
#define BITSPERSAMPLE 16
#define CHANNELS 1

#define DATASIZE (FREQ * (BITSPERSAMPLE/8))

#define ARR_LEN(arr) (sizeof(arr) / sizeof(*arr))

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

    unsigned short notes[] = {
        440,
        440*2,
        440*3,
        440*4,
    };

    WavHeader wav2 = {
        chunkId: 0x46464952,
        chunkSize: 44 + DATASIZE * ARR_LEN(notes) - 8,
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
        subchunk2Size: DATASIZE * ARR_LEN(notes)
    };

    short data[DATASIZE * ARR_LEN(notes)] = {0};

    wav2.chunkSize = wav2.chunkSize * ARR_LEN(notes);
    wav2.subchunk2Size = wav2.subchunk2Size * ARR_LEN(notes);

    for (size_t i = 0; i < ARR_LEN(notes); i++)
    {
        int noteDataStart = (DATASIZE / ARR_LEN(notes)) * i;
        int noteDataEnd = (DATASIZE / ARR_LEN(notes)) * (i+1);
        for (size_t j = noteDataStart; j < noteDataEnd; ++j) {
            float value = sinf((float)j / FREQ * 3.14159 * 2 * notes[i]);
            data[j] = (short)(value * 32767);
            //printf("%d\n", data[i]);
        }
    }
    

    
    //wav2.chunkSize += DATASIZE;
    fwrite(&wav2, sizeof(WavHeader) + 8, 1, f2);
    fwrite(&data, sizeof(*data), DATASIZE/(BITSPERSAMPLE/8) * ARR_LEN(notes), f2);
    fclose(f2);

    return 0;
}
