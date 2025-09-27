#include <stdio.h>
#include "file_lib.h"
#include "wav.h"

/**
 * The contents of the file are a char*, but that doesn't mean it is a "string".
 * When working with "strings" in C though, we normally NULL terminate.
 * This is not NULL terminated. Nor could it be, as we wouldn't be able to represent NULL in the file.
 * So, we need to print each character separately.
 * Here, we are printing as bytes (base 16).
 *
 * @parameters
 * char* file_contents - The file's bytes.
 * size_t num_bytes - The number of bytes to print.
 */

void print_file(char* file_contents, size_t num_bytes) {
    // Note this is printing the bytes in hex
    for (size_t i = 0; i<num_bytes; i++) {
        printf("%x", file_contents[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    char* contents;
    header* wav_h = malloc(sizeof(header));
    size_t num_bytes = read_file(argv[1], &contents);
    printf("%s\n", argv[1]);
    printf("%lu bytes read.\n", num_bytes);
    //print_file(contents, num_bytes);
    write_file(argv[2], contents, num_bytes);
    create_header(contents, &wav_h, num_bytes);

    // test riffArr 0-3 bytes
    printf("riffArr: ");
    for (size_t i=0; i<=3; i++) {
        printf("%c", wav_h->riffArr[i]);
    }
    printf("\n");

    // test file_size 4-7 bytes
    printf("file_size: ");
    printf("%d", wav_h->fileSize);
    printf("\n");

    // test 8-11 bytes
    printf("typeArr: ");
    for (size_t j=0; j<=3; j++) {
        printf("%c", wav_h->typeArr[j]);
    }
    printf("\n");

    // test format 20-21 bytes
    printf("format: ");
    printf("%u", wav_h->format);
    printf("\n");

    // test channels 22-23 bytes
    printf("channels: ");
    printf("%d", wav_h->channels);
    printf("\n");

    return 0;
}
