#ifndef COMMON_H
#define COMMON_H

///////////////////////////////////////////////////////////
// Defines
#define q	6		/* for 2^q points */
#define N	(1<<q)  /* N-point FFT, iFFT */
#ifndef PI
    #define PI	3.14159265358979323846264338327950288
#endif

///////////////////////////////////////////////////////////
// Structs
typedef double real;

typedef struct {
    real Re;
    real Im;
} complex;

#endif