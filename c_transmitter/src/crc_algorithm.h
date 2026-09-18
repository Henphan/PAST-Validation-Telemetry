#ifndef CRC_ALGORITHM_H
#define CRC_ALGORITHM_H

#include <stdio.h>
#include <stdint.h>

uint8_t crc_remainder(uint8_t entry[8],uint8_t poly, int n);
uint8_t division_first(uint8_t message, uint8_t poly, int n);
uint8_t division_carry_over(uint8_t message, uint8_t poly, int n, uint8_t remainder);
uint8_t division_final(uint8_t message, uint8_t poly, int n, uint8_t remainder);


#endif
