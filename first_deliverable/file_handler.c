#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* get_file_pointer(char* file_name) {

    FILE* ptr;

    // Open file in reading mode
    ptr = fopen(file_name, "r");

    // Make sure the file was opened successfully
    if (NULL == ptr) {
        printf("file can't be opened \n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

int get_block_from_samples(FILE* ptr, complex* block, __int8_t BLOCK_SIZE) {
    char ch[10];
    int count;

    for (count = 0; count<BLOCK_SIZE; count++) {
        if (fgets(ch, sizeof(ch), ptr) != NULL) {
            block[count].Re = atoi(strtok(ch,"\n"));
            block[count].Im = 0;
        } else {
            // Close the file when the whole file was read
            fclose(ptr);
            return 1;
        }
    }

    return 0;
}