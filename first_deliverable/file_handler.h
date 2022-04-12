#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "common.h"
#include <stdio.h>

///////////////////////////////////////////////////////////
// Functions
FILE* get_file_pointer(char* file_name);
int get_block_from_samples(FILE* ptr, complex* block, __int8_t BLOCK_SIZE);

#endif