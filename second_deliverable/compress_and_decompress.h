#ifndef COMPRESS_AND_DECOMPRESS_H
#define COMPRESS_AND_DECOMPRESS_H

#include "common.h"
#include "huffman.h"

///////////////////////////////////////////////////////////
// Functions
void quantify_coeff(complex* coeffs, int num_elements);
void dequantify_coeff(complex* coeffs, int num_elements);

void concatenate_huffman_codes_bit(char* dest, const char* code_Re, const char* code_Im);

#endif