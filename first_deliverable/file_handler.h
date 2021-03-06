#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "common.h"
#include "dictionary.h"
#include <stdio.h>

///////////////////////////////////////////////////////////
// Functions
FILE* get_file_pointer(char* file_name, char* mode);
int get_block_from_samples(FILE* ptr, complex* block, int block_size);
int get_code_from_encoder(FILE* ptr, char* code);
void set_samples_from_block(FILE* ptr, complex* block, int block_size);
real normalize_sample(real sample);
real denormalize_sample(real sample);
void store_huffman_codes(FILE* ptr, dict_string_t dict_huffman);
dict_string_t get_huffman_dict_from_file(FILE* ptr);

#endif