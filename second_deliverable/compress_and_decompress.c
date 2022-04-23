#include "compress_and_decompress.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void quantify_coeff(complex* coeffs, int num_elements) {

    int i;

    for (i=0; i<num_elements; i++) {

        // Descale
        coeffs[i].Re = coeffs[i].Re >> Qb;
        coeffs[i].Im = coeffs[i].Im >> Qb;

        // Real part
        if (coeffs[i].Re >= (real) COEFF_QUANT_THRESH) {            // MAX value
            coeffs[i].Re = (real) (1 << COEFF_QUANT_BITS);
        } else if (coeffs[i].Re <= -(real) COEFF_QUANT_THRESH) {    // MIN value
            coeffs[i].Re = -(real) (1 << COEFF_QUANT_BITS);
        } else {                                                    // Middle value
            coeffs[i].Re =  round(coeffs[i].Re / ((real) COEFF_QUANT_STEP));
        }

        // Imaginary part
        if (coeffs[i].Im >= (real) COEFF_QUANT_THRESH) {            // MAX value
            coeffs[i].Im = (real) (1 << COEFF_QUANT_BITS);
        } else if (coeffs[i].Im <= -(real )COEFF_QUANT_THRESH) {    // MIN value
            coeffs[i].Im = -(real) (1 << COEFF_QUANT_BITS);
        } else {                                                    // Middle value
            coeffs[i].Im =  round(coeffs[i].Im / ((real) COEFF_QUANT_STEP));
        }
    }

    return;
}

void dequantify_coeff(complex* coeffs, int num_elements) {

    int i;

    for (i=0; i<num_elements; i++) {
        // Real part
        coeffs[i].Re =  coeffs[i].Re * ((real) COEFF_QUANT_STEP);

        // Imaginary part
        coeffs[i].Im =  coeffs[i].Im * ((real) COEFF_QUANT_STEP);

        // Scale
        coeffs[i].Re = coeffs[i].Re * FACTOR;
        coeffs[i].Im = coeffs[i].Im * FACTOR;
    }

    return;
}

void concatenate_huffman_codes_bit(char* dest, const char* code_Re, const char* code_Im) {
    strcat(dest, code_Re);
    strcat(dest, code_Im);

    return;
}