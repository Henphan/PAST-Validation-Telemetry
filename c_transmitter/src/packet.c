#include "packet.h"
#include "utils.h"
#include <string.h>
#include "crc_algorithm.h"

void createPacket(Packet *packet, u8 type, u8* payload, int payload_length){
	packet->start_marker = 0xAAAA;
	packet->type = type;
	packet->length = payload_length;
	memcpy(packet->payload, payload, payload_length);
	packet->crc = crc16(payload, payload_length);
};

// takes in the Packet and a 256-byte buffer
// copies data into buffer 
// returns the number of bytes used
u16 serialisePacket(Packet packet, u8 buffer[256]){
	// 16-bit because we need to track up until 256
	u16 index = 0;

	// start marker
	buffer[index++] = packet.start_marker >> 8;
	buffer[index++] = packet.start_marker;

	// type and length
	buffer[index++] = packet.type;
	buffer[index++] = packet.length;

	// payload
	for(int i = 0; i < packet.length; i++){
		buffer[index++] = packet.payload[i];
	}

	// crc
	buffer[index++] = packet.crc >> 8;
	buffer[index++] = packet.crc;

	return index;
}
