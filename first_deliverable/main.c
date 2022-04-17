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

    int i, j;
    char key[SIZE_CHAR];
    dict_int_t dict_coeffs;
    dict_string_t dict_huffman;
    list_t list_coeffs;
    FILE* ptr_r;
    FILE* ptr_w;
    complex block[N], scratch[N];

    dict_coeffs = dict_int_new();
    list_coeffs = list_new();

    // Opening files
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

    int idx_Re, idx_Im;
    char code_block_bit[20*BLOCK_SIZE*2] = "";

    // Concatenate codes
    for (i=0; i<list_coeffs->len; i++) {
        // Real
        sprintf(key, "%d", (int) list_coeffs->entry[i].Re);
        idx_Re = dict_string_find_index_from_key(dict_huffman, key);

        // Imaginary
        sprintf(key, "%d", (int) list_coeffs->entry[i].Im);
        idx_Im = dict_string_find_index_from_key(dict_huffman, key);

        concatenate_huffman_codes_bit(code_block_bit, dict_huffman->entry[idx_Re].value, dict_huffman->entry[idx_Im].value);

        // When BLOCK_SIZE number of codes have been concatenated the code
        // should write that string into a file and restart the process again
        if (((i+1) % BLOCK_SIZE) == 0) {
            // Store string
            fprintf(ptr_w, "%s\n", code_block_bit);
            strcpy(code_block_bit, "");
        }
    }

    list_free(list_coeffs);
    //dict_string_free(dict_huffman);
    fclose(ptr_w);

    ////////////////////////////////////////////////////////////////
    // Decoder
    int start, len, idx, num_codes_received;

    // Opening files
    char code_encoder[MAX_SINGLE_CODE_SIZE*BLOCK_SIZE*2];
    char single_code[MAX_SINGLE_CODE_SIZE];

    ptr_r = get_file_pointer("encoder.txt", "r");
    ptr_w = get_file_pointer("samples_get.txt", "w");

    while(get_code_from_encoder(ptr_r, code_encoder) == 0) {
        //printf("code: %s, len: %ld\n", code_encoder, strlen(code_encoder));

        start = 0;
        len   = 1;
        num_codes_received = 0;

        // Get single codes from whole code
        for (i=0; i<strlen(code_encoder); i++) {

            substring(code_encoder, single_code, start, len);
            //printf("i: %d, single_code: %s, start: %d, len: %d\n", i, single_code, start, len);
            idx = dict_string_find_index_from_value(dict_huffman, single_code);

            // A single code was found
            if (idx != -1) {
                //printf("i: %d, idx: %d, single_code: %s, start: %d, len: %d\n", i, idx, single_code, start, len);

                // Set array of complex numbers
                if (num_codes_received%2 == 0) { // Set real part of the complex number
                    block[num_codes_received/2].Re = atoi(dict_huffman->entry[idx].key);
                } else {                    // Set imaginary part of the complex number
                    block[num_codes_received/2].Im = atoi(dict_huffman->entry[idx].key);
                }

                start = start + len;
                len = 1;
                num_codes_received++;
            } else {
                len++;
                if (len > (int) MAX_SINGLE_CODE_SIZE) {
                    printf("The code received does not match with any of the codes expected\n");
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Check if the number of codes reveiced is the one that we were expecting
        if (num_codes_received != (int) BLOCK_SIZE*2) {
            printf("The number of codes received is not the one that we were expecting\n");
            printf("The number of codes received: %d, The number of codes expected: %d\n", num_codes_received, (int) BLOCK_SIZE*2);
            exit(EXIT_FAILURE);
        }

        dequantify_coeff(block, N);
        ifft( block, N, scratch );

        for(i=0; i<N; i++) {
            block[i].Re = denormalize_sample(block[i].Re);
            fprintf(ptr_w, "%d\n", (int)block[i].Re);
        }
    }

    //dict_string_free(dict_huffman);
    fclose(ptr_w);

    exit(EXIT_SUCCESS);
}