#ifndef COMMON_H
#define COMMON_H

///////////////////////////////////////////////////////////
// Defines
#define q	                    6		/* for 2^q points */
#define N	                    (1<<q)  /* N-point FFT, iFFT */
#ifndef PI
    #define PI	                3.14159265358979323846264338327950288
#endif

#define NUM_BITS_IN_BYTE        8

#define NUM_BITS_SAMPLE         16

#define BLOCK_SIZE              64
#define BLOCK_SIZE_OPT          33
#define MAX_SINGLE_CODE_SIZE    30

#define Qb                      14
#define FACTOR                  (1<<Qb)

#define COEFF_QUANT_BITS        9
#define COEFF_QUANT_THRESH      680000
#define COEFF_QUANT_STEP        COEFF_QUANT_THRESH / (1<<COEFF_QUANT_BITS)

#include <stdlib.h>

///////////////////////////////////////////////////////////
// Structs
typedef __int64_t real;

typedef struct {
    real Re;
    real Im;
} complex;

///////////////////////////////////////////////////////////
// Functions
void substring(char* s, char* sub, int start, int len);
void string_bin_to_hex(char* code_block_hex, char* code_block_bin);
void string_hex_to_bin(char* code_block_hex, char* code_block_bin);
void decToBinary(int n, char* binaryNum);

#endif