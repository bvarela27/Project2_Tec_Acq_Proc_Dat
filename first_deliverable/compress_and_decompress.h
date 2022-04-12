#ifndef COMPRESS_AND_DECOMPRESS_H
#define COMPRESS_AND_DECOMPRESS_H

#include "common.h"

///////////////////////////////////////////////////////////
// Functions
void quantify_coeff(complex* coeffs, int num_elements);
void dequantify_coeff(complex* coeffs, int num_elements);

#endif