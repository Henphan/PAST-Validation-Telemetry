#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "gnss_data.h"
// #include "binary_conversion.h"
#include "packet.h"
#include "utils.h"


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
	
	Packet packet1;

	// payload of containing 8 bytes of data
	u8 data[] = {
		0xAB,
		0xCD,
		0xEF,
		0xCD,
		0xEF,
		0x01,
		0x23,
		0x45,
		0x67,
		0x89,
		0xAB,
		0xCD,
		0xEF,
		0x01,
		0x45,
		0xAB
	};
	u8 length = sizeof(data);

	// buffer space for the final packet
	u8 buffer[256];
	u16 blength;

	createPacket(&packet1, 0x01, data, length);
	blength = serialisePacket(packet1, buffer);

	printf("%d\n",blength);

	for(i = 0; i < blength; i++){
		printf("%02X ", buffer[i]);
	}
	printf("\n");

	return 0;
};

