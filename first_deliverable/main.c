#include "fft_and_ifft.h"
#include "file_handler.h"

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
        //printf("[%d] [ %f, %f ]\n", i, x[i].Re,x[i].Im);

        if (x[i].Re > max_real) max_real = x[i].Re;
        if (x[i].Re < min_real) min_real = x[i].Re;
        if (x[i].Im > max_im) max_im = x[i].Im;
        if (x[i].Im < min_im) min_im = x[i].Im;
    }
    //printf("\n\n");
    return;
}

int main(void) {
    int i, count;
    FILE* ptr;
    complex block[N], scratch[N];

    count = 0;
    max_real, min_real, max_im, min_im = 0, 0, 0, 0;

    // Opening file in reading mode
    ptr = get_file_pointer("samples.txt");

    while(get_block_from_samples(ptr, block, 64) == 0) {
        fft( block, N, scratch );
        print_vector(" FFT", block, N);
    }

    printf("max_real: %f, min_real: %f, max_im: %f, min_im: %f\n", max_real, min_real, max_im, min_im);

    /* FFT, iFFT of v[]: */
    //print_vector("Orig", block, N);

    //fft( block, N, scratch );
    //print_vector(" FFT", block, N);

    //ifft( block, N, scratch );
    //print_vector("iFFT", block, N);

    exit(EXIT_SUCCESS);
}