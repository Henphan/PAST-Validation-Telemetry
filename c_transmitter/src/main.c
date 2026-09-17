#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "gnss_data.h"
#include "binary_conversion.h"
#include "crc_algorithm.h"


void read_data(char* data[][4]);

int main(void){
	int i, j;
	// processing the raw data into an array of structs
	// struct GNSS_Struct s_array[52];
	// struct GNSS_Struct s1;
	// char* endptr;
	// for(i = 0; i < 52; i++){
	// 	s1.time = strtod(raw_data[i][0], &endptr);
	// 	s1.lat = strtod(raw_data[i][1], &endptr);
	// 	s1.lon = strtod(raw_data[i][2], &endptr);
	// 	s1.alt = strtod(raw_data[i][3], &endptr);
	// 	s_array[i] = s1;
	// }

	// double attr;
	// double entry[] = {134713.00,-32.02342,115.96431,2800.00};
	// unsigned char hex_array[4][8];
	// entry_to_hex(hex_array, entry);
	//
	// uint8_t poly = 0xB;
	// crc_remainder(hex_array, poly);
	//
	// uint8_t a1 = 0xAA;
	// uint8_t a2 = 0xAA;
	// uint8_t b = 0xD;
	//
	// for (i = 7; i >= 3; i--) {
	//     if (a1 & (1U << i)) {
	// 	a1 ^= b << (i - 3);
	//     }
	// }
	//
	// printf("First remainder: %02X\n", a1);
	//
	// uint16_t working = (((uint16_t)a1 << 8) | a2) << 3;
	//
	// for (i = 15; i >= 3; i--) {
	//     if (working & (1U << i)) {
	// 	working ^= (uint16_t)b << (i - 3);
	//     }
	// }
	//
	// printf("Final CRC: %02X\n", working);


	uint8_t message1 = 0x34;
	uint8_t message2 = 0xEC;
	uint8_t poly = 0xB;
	uint8_t remainder;
	remainder = division_first(message1, poly);
	printf("Byte1 remainder: %02X\n", remainder);

	remainder = division_final(message2, poly, remainder);
	printf("Byte2 remainder: %02X\n", remainder);

	return 0;
};

