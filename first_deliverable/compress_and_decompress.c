#include "compress_and_decompress.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void quantify_coeff(complex* coeffs, int num_elements) {

    int i;

    for (i=0; i<num_elements; i++) {
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
    }

    return;
}
