#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "gnss_data.h"
#include "packet.h"
#include "utils.h"
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
  
	// Creating a payload
	uint8_t message[] = "123456789";
	int length = sizeof(message)-1; // -1 for the null terminator
	// Getting the CRC of the payload
	uint16_t crc = crc16(message, length);
	// Creating the packet
	Packet packet1;
	createPacket(&packet1, 0x01, message, length);
	// Serialising the packet into a buffer
	u8 buffer[256];
	u16 blength;
	blength = serialisePacket(packet1, buffer);
	// Printing out the packet
	for(i = 0; i < blength; i++){
		printf("%02X ", buffer[i]);
	}
	printf("\n");

	return 0;
};

