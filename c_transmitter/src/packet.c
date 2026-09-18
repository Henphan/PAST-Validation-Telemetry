#include "packet.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void createPacket(Packet *packet, uint8_t type, uint8_t* payload){
	packet->start_marker = 0xAAAA;
	packet->type = type;
	packet->length = sizeof(payload);
	memcpy(packet->payload, payload, packet->length);
	// TODO: Replace placeholder with CRC code
	packet->crc = 0x1;
};

// takes in the Packet and a 256-byte buffer
// copies data into buffer 
// returns the number of bytes used
uint16_t serialisePacket(Packet packet, uint8_t buffer[256]){
	// 16-bit because we need to track up until 256
	uint16_t index = 0;

	// assigning default fields
	// TODO: Yo this part could be cooked later on
	// start_marker is uint16_t being assigned to uint8_t
	buffer[index++] = packet.start_marker;
	buffer[index++] = packet.start_marker;
	buffer[index++] = packet.type;
	buffer[index++] = packet.length;

	for(int i = 0; i < packet.length; i++){
		buffer[index++] = packet.payload[i];
	}

	buffer[index++] = packet.crc;

	return index;
}
