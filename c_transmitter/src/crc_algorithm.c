#include "crc_algorithm.h"
#include <stdint.h>

uint8_t crc_remainder(
	// entry: an array of eight 8-bit values (one double)
	uint8_t entry[8],
	// poly: an 8-bit polynomial value
	uint8_t poly,
	// n: the degree of the polynomial
	int n
){
	// TODO: Validate that the poly and the n match 
	// TODO: Replace the hardcoded array length
	uint8_t crc, message, remainder;
	for(int i = 0; i < 8; i++){
		message = entry[i];
		// no remainder to add on
		if(i == 0)
			remainder = division_first(message, poly, n);
		// append n-amount of zeros at the end
		else if(i == 7)
			crc = division_final(message, poly, n, remainder);
		// add on the remainder but dont append any zero
		else
			remainder = division_carry_over(message, poly, n, remainder);
	}
	return crc;
}

uint8_t division_first(
	uint8_t message,
	uint8_t poly,
	int n
){
	// NOTE: Hardcoded i = 7
	for (int i = 7; i >= n; i--){
		if (message & (1U << i))
			message ^= poly << (i - n);
	}
	return message;
}

uint8_t division_carry_over(
	uint8_t message,
	uint8_t poly,
	int n,
	uint8_t remainder
){
	uint16_t working = (((uint16_t)remainder << 8) | message);
	// NOTE: Hardcoded i = 15
	for (int i = 15; i >= n; i--){
		if (working & (1U << i))
			working ^= (uint16_t)poly << (i - n);
	}
	return working;
}

uint8_t division_final(
	uint8_t message,
	uint8_t poly,
	int n,
	uint8_t remainder
){
	uint16_t working = (((uint16_t)remainder << 8) | message) << n;
	// NOTE: Hardcoded i = 15
	for (int i = 15; i >= n; i--){
		if (working & (1U << i))
			working ^= (uint16_t)poly << (i - n);
	}
	return working;
}
