#include "fft_and_ifft.h"
#include "file_handler.h"
#include "compress_and_decompress.h"
#include "dictionary.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    ////////////////////////////////////////////////////////////////
    // Encoder

    int i;
    char key[SIZE_CHAR];
    dict_int_t dict_coeffs;
    dict_string_t dict_huffman;
    list_t list_coeffs;
    FILE* ptr_r;
    FILE* ptr_w;
    complex block[N], scratch[N];

    dict_coeffs = dict_int_new();
    list_coeffs = list_new();

    // Opening file in reading mode
    ptr_r = get_file_pointer("samples.txt", "r");
    ptr_w = get_file_pointer("encoder.txt", "w");

    while(get_block_from_samples(ptr_r, block, BLOCK_SIZE) == 0) {
        fft( block, N, scratch );
        quantify_coeff(block, N);

        for(i=0; i<N; i++) {
            dict_int_add(dict_coeffs, block[i].Re, 1);
            dict_int_add(dict_coeffs, block[i].Im, 1);

            list_add(list_coeffs, block[i].Re, block[i].Im);
        }

        //dequantify_coeff(block, N);
        //ifft( block, N, scratch );
        //for(i=0; i<N; i++) {
        //    block[i].Re = denormalize_sample(block[i].Re);
        //    fprintf(ptr_w, "%d\n", (int)block[i].Re);
        //}
    }

    char keys[dict_coeffs->len][SIZE_CHAR];
    int* freqs = calloc(dict_coeffs->len, sizeof(int));

    if (keys == NULL || freqs == NULL) {
        printf("Unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    for (i=0; i<dict_coeffs->len; i++) {
        //printf("key: %d, value: %d\n", dict_coeffs->entry[i].key, dict_coeffs->entry[i].value);
        sprintf(key, "%d", (int) dict_coeffs->entry[i].key);
        strcpy(keys[i], key);
        freqs[i] = dict_coeffs->entry[i].value;
    }

    dict_int_free(dict_coeffs);

    int size = sizeof(keys) / sizeof(keys[0]);

    dict_huffman = HuffmanCodes(keys, freqs, size);

    //for (i=0; i<dict_huffman->len; i++) {
    //    printf("key: %s, value: %s\n", dict_huffman->entry[i].key, dict_huffman->entry[i].value);
    //}

    int idx_Re, idx_Im;
    char code_block_bit[20*BLOCK_SIZE*2] = "";

    // Concatenate codes
    for (i=0; i<list_coeffs->len; i++) {
        // When BLOCK_SIZE number of codes have been concatenated the code
        // should write that string into a file and restart the process again
        if (((i+1) % BLOCK_SIZE) == 0) {
            // Store string
            fprintf(ptr_w, "%s\n", code_block_bit);
            strcpy(code_block_bit, "");
        }

        // Real
        sprintf(key, "%d", (int) list_coeffs->entry[i].Re);
        idx_Re = dict_string_find_index(dict_huffman, key);

        // Imaginary
        sprintf(key, "%d", (int) list_coeffs->entry[i].Im);
        idx_Im = dict_string_find_index(dict_huffman, key);

        concatenate_huffman_codes_bit(code_block_bit, dict_huffman->entry[idx_Re].value, dict_huffman->entry[idx_Im].value);
    }

    list_free(list_coeffs);
    fclose(ptr_w);

    ////////////////////////////////////////////////////////////////
    // Decoder

    exit(EXIT_SUCCESS);
}