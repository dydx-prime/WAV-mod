#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sub1(char *filename);

int main() {
    char filename[200]; //allowing room for long directories or file names
    int validity = 0; // flag used to check file opening status

    // Opening File
    FILE *fp;
    while(validity == 0){
        validity = sub1(filename);

        if(validity = 1) {
        fp = fopen(filename, "rb+"); // rb can only read not write so I used rb+
        if(fp == NULL){
        printf("File does not exist.\n");
        validity = 0;
    }

    }
    }

    // header 
    char ChunkID[4];
    unsigned int ChunkSize, Subchunk1Size, SampleRate, ByteRate, Subchunk2Size;
    char Format[4], Subchunk1ID[4], Subchunk2ID[4];
    unsigned short AudioFormat, NumChannels, BlockAlign, BitsPerSample;

    // header reading
    fread(ChunkID, sizeof(char), 4, fp);
    fread(&ChunkSize, sizeof(unsigned int), 1, fp);
    fread(Format, sizeof(char), 4, fp);
    fread(Subchunk1ID, sizeof(char), 4, fp);
    fread(&Subchunk1Size, sizeof(unsigned int), 1, fp);
    fread(&AudioFormat, sizeof(unsigned short), 1, fp);
    fread(&NumChannels, sizeof(unsigned short), 1, fp);
    fread(&SampleRate, sizeof(unsigned int), 1, fp);
    fread(&ByteRate, sizeof(unsigned int), 1, fp);
    fread(&BlockAlign, sizeof(unsigned short), 1, fp);
    fread(&BitsPerSample, sizeof(unsigned short), 1, fp);
    fread(Subchunk2ID, sizeof(char), 4, fp);
    fread(&Subchunk2Size, sizeof(unsigned int), 1, fp);

    //header print
    printf("Chunk ID: %.4s\n", ChunkID);
    printf("Chunk Size: %u\n", ChunkSize);
    printf("Format: %.4s\n", Format);
    printf("Subchunk1 ID: %.4s\n", Subchunk1ID);
    printf("Subchunk1 Size: %u\n", Subchunk1Size);
    printf("Audio Format: %u\n", AudioFormat);
    printf("Num Channels: %u\n", NumChannels);
    printf("Sample Rate: %u\n", SampleRate);
    printf("Byte Rate: %u\n", ByteRate);
    printf("Block Align: %u\n", BlockAlign);
    printf("Bits Per Sample: %u\n", BitsPerSample);
    printf("Subchunk2 ID: %.4s\n", Subchunk2ID);
    printf("Subchunk2 Size: %u\n", Subchunk2Size);

    SampleRate /= 2;
    ByteRate /= 2;

    fseek(fp, 24, SEEK_SET); // changing position of pointer
    // New SampleRate and ByteRate is placed onto the updated file
    fwrite(&SampleRate, sizeof(unsigned int), 1, fp); 
    fwrite(&ByteRate, sizeof(unsigned int), 1, fp);

    fclose(fp);

    return 0;
}

int sub1(char *filename){
    printf("Enter path/filename: ");
    fgets(filename, 200, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // remove newline

    //allowing the use of lowercase and upercase inputs
    char *ptr1 = strstr(filename + strlen(filename)-4, ".wav");
    char *ptr2 = strstr(filename + strlen(filename)-4, ".WAV");
    
    //ensuring it's a wave file
    if(ptr1 != NULL || ptr2 !=NULL){
        return 1;
    }

    else{
    printf("File name is not in .WAV or .wav format!\n");
    return 0;
    }

}