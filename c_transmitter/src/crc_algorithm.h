#ifndef CRC_ALGORITHM_H
#define CRC_ALGORITHM_H

#include <stdio.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;

u16 crc16(const u8* message, int length);

#endif
