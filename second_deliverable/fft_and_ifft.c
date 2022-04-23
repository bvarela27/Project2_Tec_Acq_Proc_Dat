#include "fft_and_ifft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void rfft( complex *v, int n, complex *tmp ) {
    if(n>1) {			/* otherwise, do nothing and return */
        int k,m;
        complex z, w, *vo, *ve;

        ve = tmp; vo = tmp+n/2;
        for(k=0; k<n/2; k++) {
            ve[k] = v[2*k];
            vo[k] = v[2*k+1];
        }
        fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
        fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
        for(m=0; m<n/2; m++) {
            w.Re = cos(2*PI*m/(double)n);
            w.Im = -sin(2*PI*m/(double)n);
            z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
            z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
            v[  m  ].Re = ve[m].Re + z.Re;
            v[  m  ].Im = ve[m].Im + z.Im;
        }
        v[32].Re = ve[0].Re - vo[0].Re;
    }

    return;
}

void fft( complex *v, int n, complex *tmp ) {
    if(n>1) {			/* otherwise, do nothing and return */
        int k,m;
        complex z, w, *vo, *ve;

        ve = tmp; vo = tmp+n/2;
        for(k=0; k<n/2; k++) {
            ve[k] = v[2*k];
            vo[k] = v[2*k+1];
        }
        fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
        fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
        for(m=0; m<n/2; m++) {
            w.Re = cos(2*PI*m/(double)n);
            w.Im = -sin(2*PI*m/(double)n);
            z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
            z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
            v[  m  ].Re = ve[m].Re + z.Re;
            v[  m  ].Im = ve[m].Im + z.Im;
            v[m+n/2].Re = ve[m].Re - z.Re;
            v[m+n/2].Im = ve[m].Im - z.Im;
        }
    }

    return;
}

void _ifft( complex *v, int n, complex *tmp ) {
    if(n>1) {			/* otherwise, do nothing and return */
        int k,m;
        complex z, w, *vo, *ve;

        ve = tmp; vo = tmp+n/2;
        for(k=0; k<n/2; k++) {
            ve[k] = v[2*k];
            vo[k] = v[2*k+1];
        }
        _ifft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
        _ifft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
        for(m=0; m<n/2; m++) {
            w.Re = cos(2*PI*m/(double)n);
            w.Im = sin(2*PI*m/(double)n);
            z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
            z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
            v[  m  ].Re = ve[m].Re + z.Re;
            v[  m  ].Im = ve[m].Im + z.Im;
            v[m+n/2].Re = ve[m].Re - z.Re;
            v[m+n/2].Im = ve[m].Im - z.Im;
        }
    }
    return;
}

void ifft( complex *v, int n, complex *tmp ) {
    int i;

    _ifft(v, n, tmp);

    // This is needed because the _ifft returns the right
    // value, but it is mutiplied by n
    for (i=0; i< n; i++) {
        v[i].Re = v[i].Re / ((real) n);
        v[i].Im = v[i].Im / ((real) n);
    }

    return;
}

void irfft( complex *v, int n, complex *tmp ) {
    int i, cnt = 2;

    // Complete the coeffs that were not processed by the encoder
    for (i=33; i<n; i++) {
        v[i].Re = v[i-cnt].Re;
        v[i].Im = -v[i-cnt].Im;
        cnt += 2;
    }

    ifft(v, n, tmp);

    return;
}
