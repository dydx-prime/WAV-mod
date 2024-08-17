#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979

//declaration of subroutines
void writeWAVHeader(FILE *fp, int sampleRate, int numSamples);
void SinWave(short *audioData, float user_Freq, int numSamples, int sampleRate);

int main() {
    float time, user_freq;
    printf("Enter duration of .wav file in seconds: ");
    scanf("%f", &time);
    printf("Enter frequency of sin wave in Hertz: ");
    scanf("%f", &user_freq);

    int sampleRate = 44100;
    int numSamples = time * sampleRate;
    
    //dynamic allocation of memory
    short *audioData = malloc(numSamples * sizeof(short));

    if (audioData == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    FILE *fp = fopen("tone1.wav", "wb");
    if (fp == NULL) {
        printf("Could not open file for writing\n");
        free(audioData);
        return 1;
    }

    SinWave(audioData, user_freq, numSamples, sampleRate);
    writeWAVHeader(fp, sampleRate, numSamples);
    fwrite(audioData, sizeof(short), numSamples, fp);

    fclose(fp);
    free(audioData);

    return 0;
}

//WAV header 
void writeWAVHeader(FILE *fp, int sampleRate, int numSamples) {
    char chunkID[4];
    char format[4];
    char subchunk1ID[4];
    char subchunk2ID[4];

    strncpy(chunkID, "RIFF", 4);
    strncpy(format, "WAVE", 4);
    strncpy(subchunk1ID, "fmt ", 4);
    strncpy(subchunk2ID, "data", 4);

    int byteRate = sampleRate * 2;
    int blockAlign = 2;
    int bitsPerSample = 16;
    int subchunk2Size = numSamples * 2;
    int chunkSize = 36 + subchunk2Size;
    
    fwrite(chunkID, 1, 4, fp);
    fwrite(&chunkSize, 4, 1, fp);
    fwrite(format, 1, 4, fp);

    fwrite(subchunk1ID, 1, 4, fp);
    int subchunk1Size = 16;
    short audioFormat = 1;
    short numChannels = 1;
    fwrite(&subchunk1Size, 4, 1, fp);
    fwrite(&audioFormat, 2, 1, fp);
    fwrite(&numChannels, 2, 1, fp);
    fwrite(&sampleRate, 4, 1, fp);
    fwrite(&byteRate, 4, 1, fp);
    fwrite(&blockAlign, 2, 1, fp);
    fwrite(&bitsPerSample, 2, 1, fp);

    fwrite(subchunk2ID, 1, 4, fp);
    fwrite(&subchunk2Size, 4, 1, fp);
}

// sin wave calculation
void SinWave(short *audioData, float user_Freq, int numSamples, int sampleRate) {
    for (int i = 0; i < numSamples; i++) {
        audioData[i] = (short)(32700.0 * sin(2.0 * PI * user_Freq * ((float)i / sampleRate)));
    }
}
