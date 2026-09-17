#include "crc_algorithm.h"
#include <stdint.h>

uint8_t crc_remainder(
	uint8_t entry[][8],
	uint8_t poly
){
	uint8_t crc;
	uint8_t message;
	int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 8; j++){
			message = entry[i][j];
			printf("%02X ", message);
		}
		printf("\n");
	}
	return crc;
}

uint8_t division_first(
	uint8_t message,
	uint8_t poly
){
	for (int i = 7; i >= 3; i--){
		if (message & (1U << i))
			message ^= poly << (i - 3);
	}
	return message;
}

uint8_t division_carry_over(
	uint8_t message,
	uint8_t poly,
	uint8_t remainder
){
	uint16_t working = (((uint16_t)remainder << 8) | message);
	for (int i = 15; i >= 3; i--){
		if (working & (1U << i))
			working ^= (uint16_t)poly << (i - 3);
	}
	return working;
}

uint8_t division_final(
	uint8_t message,
	uint8_t poly,
	uint8_t remainder
){
	uint16_t working = (((uint16_t)remainder << 8) | message) << 3;
	for (int i = 15; i >= 3; i--){
		if (working & (1U << i))
			working ^= (uint16_t)poly << (i - 3);
	}
	return working;
}
