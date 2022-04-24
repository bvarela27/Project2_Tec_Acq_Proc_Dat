#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C substring function definition
void substring(char* s, char* sub, int start, int len) {
    int counter = 0;

    while (counter < len) {
        sub[counter] = s[start+counter];
        counter++;
    }
    sub[counter] = '\0';
}

int string_get_idx(char* string, char c) {
    char *e = strchr(string, c);
    if (e == NULL) {
        return -1;
    }

    return (int)(e - string);
}

void string_bin_to_hex(char* code_block_hex, char* code_block_bin) {
    int i, num_bits_pad;
    char ch[20*BLOCK_SIZE_OPT*2] = "";

    num_bits_pad = strlen(code_block_bin) % NUM_BITS_IN_BYTE;

    // If the mod is different than 0, then 8 - num_bits_pad
    // number of zeros needs to be added.
    if (num_bits_pad != 0) {
        num_bits_pad = NUM_BITS_IN_BYTE - num_bits_pad;
    }

    // The first element of code_block_hex is the number
    // of zeros that were added
    sprintf(ch, "%d", num_bits_pad);
    strcat(code_block_hex, ch);

    // Bit to hex
    for (i=0; i<strlen(code_block_bin); i+=8) {
        if (i+NUM_BITS_IN_BYTE <= strlen(code_block_bin)) {
            substring(code_block_bin, ch, i, NUM_BITS_IN_BYTE);
        } else {
            substring(code_block_bin, ch, i, strlen(code_block_bin)-i);
        }
        sprintf(ch, "%02X", (int) strtol(ch, NULL, 2));
        strcat(code_block_hex, ch);
    }

    return;
}

void string_hex_to_bin(char* code_block_hex, char* code_block_bin) {
    int i, num_bits_pad;
    char ch[20*BLOCK_SIZE_OPT*2] = "";
    char tmp[10] = "";

    substring(code_block_hex, ch, 0, 1);
    num_bits_pad = atoi(ch);

    // Bit to hex
    for (i=1; i<strlen(code_block_hex); i+=2) {
        substring(code_block_hex, ch, i, 2);
        decToBinary((int) strtol(ch, NULL, 16), ch);
        if (i == strlen(code_block_hex)-2) {
            substring(ch, tmp, num_bits_pad, 8-num_bits_pad);
            strcat(code_block_bin, tmp);
        } else {
            strcat(code_block_bin, ch);
        }
    }

    return;
}

void decToBinary(int n, char* binaryNum) {

    int i;

    for (i=0; i<8; i++) {
        binaryNum[i] = '0';
    }

    i = 0;
    while (n > 0) {
        if (n%2) {
            binaryNum[7-i] = '1';
        } else {
            binaryNum[7-i] = '0';
        }
        n = n / 2;
        i++;
    }

    binaryNum[8] = '\0';

    return;
}