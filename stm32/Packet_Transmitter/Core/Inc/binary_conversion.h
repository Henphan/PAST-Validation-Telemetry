#ifndef BINARY_CONVERSION_H
#define BINARY_CONVERSION_H

#include <stdint.h>

void double_to_hex(uint8_t * hex_array, double val);
void entry_to_hex(uint8_t hex_array[][8], double* entry, int length);

#endif
