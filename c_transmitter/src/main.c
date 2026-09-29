#include <stdint.h>
#include <stdio.h>
#include <math.h>
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
	uint8_t message[] = "AABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCBCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABCDEFGHIJKLMABC";
	int length = sizeof(message)-1; // -1 for the null terminator
	// Getting the CRC of the payload
	uint16_t crc = crc16(message, length);
	// Creating the packet
	
	int packet_num = (int)ceil(length / (double)PAYLOAD_MAX);
	int frag_length;
	int frag_id = 0;

	for(int i = 0; i < packet_num; i++){
		// Getting the length of each fragment
		if(length - PAYLOAD_MAX >= 0){
			length -= PAYLOAD_MAX;
			frag_length = PAYLOAD_MAX;
		}
		else{
			frag_length = length;
		}

		// Creating the fragment
		Packet packet1;
		createPacket(&packet1, 0x01, message, frag_length, frag_id, i, packet_num);

		// Serialising the packet into a buffer
		u8 buffer[256];
		u16 blength;
		blength = serialisePacket(packet1, buffer);

		// Printing out the packet
		printf("Fragment %d\n", i);
		printf("Payload length: %d\n", frag_length);
		for(int k = 0; k < blength; k ++){
			printf("%02X ", buffer[k]);
		}
		printf("\n");

		// Moving along the packet
		*message = message[PAYLOAD_MAX-1];
	}

	return 0;
};

