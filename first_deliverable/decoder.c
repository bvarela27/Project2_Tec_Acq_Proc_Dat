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
    // Decoder
    int start, len, i, idx, num_codes_received;
    char code_encoder_hex[MAX_SINGLE_CODE_SIZE*BLOCK_SIZE_OPT*2] = "";
    char code_encoder_bin[MAX_SINGLE_CODE_SIZE*BLOCK_SIZE_OPT*2] = "";
    char single_code[MAX_SINGLE_CODE_SIZE];
    dict_string_t dict_huffman;
    FILE *ptr_encoder, *ptr_decoder, *ptr_mapping;
    complex block[N], scratch[N];

    // Set huffman dictionary
    ptr_mapping = get_file_pointer("mapping.txt", "r");
    dict_huffman = get_huffman_dict_from_file(ptr_mapping);

    // Opening files
    ptr_encoder = get_file_pointer("encoder_output.txt", "r");
    ptr_decoder = get_file_pointer("decoder_output.txt", "w");

    while(get_code_from_encoder(ptr_encoder, code_encoder_hex) == 0) {

        string_hex_to_bin(code_encoder_hex, code_encoder_bin);

        start = 0;
        len   = 1;
        num_codes_received = 0;

        // Get single codes from whole code
        for (i=0; i<strlen(code_encoder_bin); i++) {

            substring(code_encoder_bin, single_code, start, len);
            idx = dict_string_find_index_from_value(dict_huffman, single_code);

            // A single code was found
            if (idx != -1) {
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

        // Check if the number of codes received is the one that we were expecting
        if (num_codes_received != (int) BLOCK_SIZE_OPT*2) {
            printf("ERROR: The number of codes received: %d, The number of codes expected: %d\n", num_codes_received, (int) BLOCK_SIZE_OPT*2);
            exit(EXIT_FAILURE);
        }

        dequantify_coeff(block, BLOCK_SIZE_OPT);
        irfft( block, N, scratch );
        set_samples_from_block(ptr_decoder, block, N);

        strcpy(code_encoder_bin, "");
        strcpy(code_encoder_hex, "");
    }

    dict_string_free(dict_huffman);
    fclose(ptr_decoder);

    exit(EXIT_SUCCESS);
}