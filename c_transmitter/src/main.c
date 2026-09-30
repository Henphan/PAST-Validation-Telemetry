#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "gnss_data.h"
#include "packet.h"
#include "utils.h"
#include "binary_conversion.h"
#include "crc_algorithm.h"

void read_data(char* data[][4]);

int main(void){
	int i, j;
	// Processing the raw GNSS data
	GNSS_row Row[52];
	char* endptr;
	for(i = 0; i < 52; i++){
		Row[i].time = strtod(raw_data[i][0], &endptr);
		Row[i].lat = strtod(raw_data[i][1], &endptr);
		Row[i].lon = strtod(raw_data[i][2], &endptr);
		Row[i].alt = strtod(raw_data[i][3], &endptr);
	}

	// Harcoding the final payload -- 51 x 32 bytes/lines = 1632 bytes
	u8 message1[1632];
	int idx = 0;
	// Starts at 1 to skip the headers
	for(i = 1; i < 52; i++){
		GNSS_row currRow = Row[i];
		double entry[] = {currRow.time, currRow.lat, currRow.lon, currRow.alt};
		int col_count = 4;
		u8 hex_entry[col_count][8];
		// hex_entry represents one row -- 4 doubles -- 4 x 8 bytes
		entry_to_hex(hex_entry, entry, col_count);
		for(j = 0; j < col_count; j++){
			for(int k = 0; k < 8; k++){
				u8 hex_value = hex_entry[j][k];
				message1[idx] = hex_value;
				idx += 1;
			}
		}
	}

	// Creating a payload
	int length = sizeof(message1)-1; // -1 for the null terminator
	// Getting the CRC of the payload
	uint16_t crc = crc16(message1, length);
	// Creating the packet
	
	u16 packet_num = (int)ceil(length / (double)PAYLOAD_MAX);
	u16 frag_length;
	u16 frag_id = 0;

	u8* ptr = message1;

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
		createPacket(&packet1, 0x01, ptr, frag_length, frag_id, i+1, packet_num);

		// Serialising the packet into a buffer
		u8 buffer[256];
		u16 blength;
		blength = serialisePacket(packet1, buffer);

		// Printing out the packet
		printf("Fragment %d\n", i);
		printf("Payload length: %d\n", frag_length);
		printf("Packet length: %d\n", blength);
		for(int k = 0; k < blength; k ++){
			printf("%02X ", buffer[k]);
		}
		printf("\n");

		// Moving along the packet
		ptr += frag_length;
	}

	return 0;
};

