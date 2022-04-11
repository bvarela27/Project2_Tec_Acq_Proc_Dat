#include "fft_and_ifft.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/* Print a vector of complexes as ordered pairs. */
static void print_vector( const char *title, complex *x, int n) {
    int i;

    printf("%s (dim=%d):\n", title, n);
    for(i=0; i<n; i++ ) printf("[%d] [ %f, %f ]\n", i, x[i].Re,x[i].Im);
    printf("\n\n");
    return;
}

int main(void) {
    complex v[N], scratch[N];
    int k;

    /* Fill v[] with a function of known FFT: */
    for(k=0; k<N; k++) {

        v[k].Re = (real) ((__int16_t) (1000*cos(2*PI*k/(double)N))) + (real) ((__int16_t) (1000*sin(2*PI*(k*0.1)/(double)N)));
        v[k].Im = 0;

        //v[k].Re = 0.125*cos(2*PI*k/(double)N);
        //v[k].Im = 0.125*sin(2*PI*k/(double)N);

        //if(k < 4) {
        //    v[k].Re = 1.0;
        //    v[k].Im = 0.0;
        //} else {
        //    v[k].Re = 0.0;
        //    v[k].Im = 0.0;
        //}
    }

    /* FFT, iFFT of v[]: */
    print_vector("Orig", v, N);
    fft( v, N, scratch );
    print_vector(" FFT", v, N);
    ifft( v, N, scratch );
    print_vector("iFFT", v, N);

    exit(EXIT_SUCCESS);
}