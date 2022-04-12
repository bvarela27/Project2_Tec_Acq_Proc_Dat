#ifndef COMMON_H
#define COMMON_H

///////////////////////////////////////////////////////////
// Defines
#define q	                    6		/* for 2^q points */
#define N	                    (1<<q)  /* N-point FFT, iFFT */
#ifndef PI
    #define PI	                3.14159265358979323846264338327950288
#endif

#define NUM_BITS_SAMPLE         16

#define COEFF_QUANT_BITS        8
#define COEFF_QUANT_THRESH      700
#define COEFF_QUANT_STEP        COEFF_QUANT_THRESH / (1<<COEFF_QUANT_BITS)

///////////////////////////////////////////////////////////
// Structs
typedef double real;

typedef struct {
    real Re;
    real Im;
} complex;

#endif