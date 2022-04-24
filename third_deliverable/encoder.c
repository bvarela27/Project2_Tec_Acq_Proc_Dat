#include "fft_and_ifft.h"
#include "file_handler.h"
#include "compress_and_decompress.h"
#include "dictionary.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(void) {
    ////////////////////////////////////////////////////////////////
    // Encoder
    clock_t start_time, end_time;
    double encoder_time;
    int i, size, idx_Re, idx_Im;
    char key[SIZE_CHAR];
    char code_block_bin[20*BLOCK_SIZE_OPT*2] = "";
    char code_block_hex[20*BLOCK_SIZE_OPT*2] = "";
    dict_int_t dict_coeffs;
    dict_string_t dict_huffman;
    list_t list_coeffs;
    FILE *ptr_samples, *ptr_encoder, *ptr_mapping;
    complex block[N], scratch[N];

    // Start time measure
    start_time = clock();

    dict_coeffs = dict_int_new();
    list_coeffs = list_new();

    // Opening files
    ptr_samples = get_file_pointer("samples.txt", "r");
    ptr_encoder = get_file_pointer("encoder_output.txt", "w");

    while(get_block_from_samples(ptr_samples, block, BLOCK_SIZE) == 0) {
        rfft( block, N, scratch );
        quantify_coeff(block, BLOCK_SIZE_OPT);

        for(i=0; i<BLOCK_SIZE_OPT; i++) {
            dict_int_add(dict_coeffs, block[i].Re, 1);
            dict_int_add(dict_coeffs, block[i].Im, 1);

            list_add(list_coeffs, block[i].Re, block[i].Im);
        }
    }

    // Logic needed for huffman
    char keys[dict_coeffs->len][SIZE_CHAR];
    int  freqs[dict_coeffs->len];

    for (i=0; i<dict_coeffs->len; i++) {
        sprintf(key, "%d", (int) dict_coeffs->entry[i].key);
        strcpy(keys[i], key);
        freqs[i] = dict_coeffs->entry[i].value;
    }

    dict_int_free(dict_coeffs);

    size = sizeof(keys) / sizeof(keys[0]);
    dict_huffman = HuffmanCodes(keys, freqs, size);

    // Store huffman mapping
    ptr_mapping = get_file_pointer("mapping.txt", "w");
    store_huffman_codes(ptr_mapping, dict_huffman);

    // Concatenate codes
    for (i=0; i<list_coeffs->len; i++) {
        // Real
        sprintf(key, "%d", (int) list_coeffs->entry[i].Re);
        idx_Re = dict_string_find_index_from_key(dict_huffman, key);

        // Imaginary
        sprintf(key, "%d", (int) list_coeffs->entry[i].Im);
        idx_Im = dict_string_find_index_from_key(dict_huffman, key);

        concatenate_huffman_codes_bit(code_block_bin, dict_huffman->entry[idx_Re].value, dict_huffman->entry[idx_Im].value);

        // When BLOCK_SIZE_OPT number of codes have been concatenated the code
        // should write that string into a file and restart the process again
        if (((i+1) % BLOCK_SIZE_OPT) == 0) {
            // Store string
            string_bin_to_hex(code_block_hex, code_block_bin);
            fprintf(ptr_encoder, "%s\n", code_block_hex);
            strcpy(code_block_bin, "");
            strcpy(code_block_hex, "");
        }
    }

    list_free(list_coeffs);
    dict_string_free(dict_huffman);
    fclose(ptr_encoder);

    // End time measuare
    end_time = clock();
    encoder_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Encoder time: %fs\n", encoder_time);

    exit(EXIT_SUCCESS);
}