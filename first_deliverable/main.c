#include "fft_and_ifft.h"
#include "file_handler.h"
#include "compress_and_decompress.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    FILE* ptr;
    FILE* ptr_w;
    complex block[N], scratch[N];

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
        dequantify_coeff(block, N);
        ifft( block, N, scratch );
        for(i=0; i<N; i++) {
            block[i].Re = denormalize_sample(block[i].Re);
            fprintf(ptr_w, "%d\n", (int)block[i].Re);
        }
        //print_vector("iFFT", block, N);
    }

    fclose(ptr_w);

    //printf("max_real: %f, min_real: %f, max_im: %f, min_im: %f\n", max_real, min_real, max_im, min_im);

    /* FFT, iFFT of v[]: */
    //print_vector("Orig", block, N);

    //fft( block, N, scratch );
    //print_vector(" FFT", block, N);

    //ifft( block, N, scratch );
    //print_vector("iFFT", block, N);

    exit(EXIT_SUCCESS);
}