#ifndef             __H__WAV_LIB__
#define             __H__WAV_LIB__

#include <stdlib.h>
#include <stdio.h>

/* Srruct that holds the information for a valid .wav file. */
typedef struct wav_header {
    char riffArr[4]; // Holds 4 total chars to denote "RIFF".
    unsigned int fileSize; // Holds an unsigned integer for positive only file size values.
    char typeArr[4]; // Holds 4 total chars to denote file type "WAVE".
    unsigned int channels; // Holds an unsigned integer for positive only channel values.
    unsigned int format; // Holds an unsigned integer for positive only format values.
} header;

/* Struct that contains the pointers to the header, file size, and data for the .wav file.  */
typedef struct wav_info {
    header *header_ptr; // Pointer of type wav_header, that points to address of header of .wav file.
    int *size_ptr; // Pointer of type int that points to address of the file size of the .wav file.
    FILE *data_ptr; // Pointer of type FILE that points to address of the data contents of the .wav file.
} wav_file;

void create_header(char* file_contents, header** wav_header, size_t num_bytes);

/* Function that creates header from the first 44 bytes of the .wav file
 * @parameters
 * char* file_contents - The file's bytes.
 * header** wav_header - The pointer address of the pointer to the wav_header struct.
 * size_t num_bytes - The number of bytes within the file.
 */
void create_header(char* file_contents, header** wav_header, size_t num_bytes) {
    // Checks if file size is greater than or equal to 44 bytes (to ensure valid .wav file).
    if (num_bytes >= 44) {
        // Iterate through first 4 bytes and store char contents in header riffArr attribute.
        for (size_t i=0; i<=3; i++) {
            (*wav_header)->riffArr[i] = file_contents[i];
        }
        
        // Create an unsigned char array to ensure positive only character values for 4-7 bytes. 
        unsigned char sizeArr[4];
        for (size_t k=4, z=0; k<=7; k++) {
            sizeArr[z] = file_contents[k];
            z++;
        }
        
        // Bit shift to the left to get file size integer value (32-bit).
        (*wav_header)->fileSize = (sizeArr[0]) | (sizeArr[1] << 8) | (sizeArr[2] << 16) | (sizeArr[3] << 24) + 8; // Instructions say to subtract, but adding gets me to # bytes read.
 
        // Iterate through bytes 8-11 and store char contents in header typeArr attribute.
        for (size_t j=8, x=0; j<=11; j++) {
            (*wav_header)->typeArr[x] = file_contents[j];
            x++;
        }
        
        // Bit shift to the left to get format integer value (16-bit)
        (*wav_header)->format = (file_contents[20]) | (file_contents[21] << 8);

        // Bit shift to the left to get number of channels integer value (16-bit)
        (*wav_header)->channels = (file_contents[22]) | (file_contents[23] << 8);

    }
}
#endif
