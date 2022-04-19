#ifndef FFT_AND_IFFT_H
#define FFT_AND_IFFT_H

#include "common.h"

///////////////////////////////////////////////////////////
// Functions
void fft( complex *v, int n, complex *tmp );
void ifft( complex *v, int n, complex *tmp );
void _ifft( complex *v, int n, complex *tmp );

void rfft( complex *v, int n, complex *tmp );
void irfft( complex *v, int n, complex *tmp );

#endif