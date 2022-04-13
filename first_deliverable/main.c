#include "fft_and_ifft.h"
#include "file_handler.h"
#include "compress_and_decompress.h"
#include "dictionary.h"
#include "huffman.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

real max_real, min_real, max_im, min_im;


/* Print a vector of complexes as ordered pairs. */
static void print_vector( const char *title, complex *x, int n) {
    int i;

    //printf("%s (dim=%d):\n", title, n);
    for(i=0; i<n; i++ ) {
        printf("[%d] [ %.f, %.f ]\n", i+1, x[i].Re,x[i].Im);

        if (x[i].Re > max_real) max_real = x[i].Re;
        if (x[i].Re < min_real) min_real = x[i].Re;
        if (x[i].Im > max_im) max_im = x[i].Im;
        if (x[i].Im < min_im) min_im = x[i].Im;
    }
    printf("\n\n");
    return;
}

int main(void) {
    int i, count;
    char key[SIZE_CHAR];
    dict_int_t dict_coeffs;
    dict_string_t dict_huffman;
    list_t list_coeffs;
    FILE* ptr;
    FILE* ptr_w;
    complex block[N], scratch[N];

    dict_coeffs = dict_int_new();
    list_coeffs = list_new();

    count = 0;
    max_real, min_real, max_im, min_im = 0, 0, 0, 0;

    // Opening file in reading mode
    ptr = get_file_pointer("samples.txt");
    ptr_w = fopen("samples_get.txt", "w");

    while(get_block_from_samples(ptr, block, 64) == 0) {
        //print_vector("Orig", block, N);
        fft( block, N, scratch );
        //print_vector(" FFT", block, N);
        quantify_coeff(block, N);

        for(i=0; i<N; i++) {
            dict_int_add(dict_coeffs, block[i].Re, 1);
            dict_int_add(dict_coeffs, block[i].Im, 1);

            list_add(list_coeffs, block[i].Re, block[i].Im);
        }

        dequantify_coeff(block, N);
        ifft( block, N, scratch );
        for(i=0; i<N; i++) {
            block[i].Re = denormalize_sample(block[i].Re);
            fprintf(ptr_w, "%d\n", (int)block[i].Re);
        }
        //print_vector("iFFT", block, N);
    }

    fclose(ptr_w);

    printf("len_dict: %d\n", dict_coeffs->len);

    char keys[dict_coeffs->len][SIZE_CHAR];
    int* freqs = calloc(dict_coeffs->len, sizeof(int));

    if (keys == NULL || freqs == NULL) {
        printf("Unable to allocate memory\n");
        return -1;
    }

    for (i=0; i<dict_coeffs->len; i++) {
        //printf("key: %d, value: %d\n", dict_coeffs->entry[i].key, dict_coeffs->entry[i].value);
        sprintf(key, "%d", (int) dict_coeffs->entry[i].key);
        strcpy(keys[i], key);
        freqs[i] = dict_coeffs->entry[i].value;
    }

    printf("len_list: %d\n", list_coeffs->len);

    dict_int_free(dict_coeffs);
    list_free(list_coeffs);

    //char arr[][SIZE_CHAR] = {"11", "4", "-18", "102", "5", "256", "120", "6", "44", "-240"};
    //int freq[] =            {5,    1,   6,     3,     10,  11,    1,     1,   1,     10};

    int size = sizeof(keys) / sizeof(keys[0]);

    printf(" Char | Huffman code ");
    printf("\n--------------------\n");

    dict_huffman = HuffmanCodes(keys, freqs, size);

    for (i=0; i<dict_huffman->len; i++) {
        printf("key: %s, value: %s\n", dict_huffman->entry[i].key, dict_huffman->entry[i].value);
    }

    //printf("max_real: %f, min_real: %f, max_im: %f, min_im: %f\n", max_real, min_real, max_im, min_im);

    /* FFT, iFFT of v[]: */
    //print_vector("Orig", block, N);

    //fft( block, N, scratch );
    //print_vector(" FFT", block, N);

    //ifft( block, N, scratch );
    //print_vector("iFFT", block, N);

    exit(EXIT_SUCCESS);
}