#include "packet.h"
#include "utils.h"
#include <string.h>

void createPacket(Packet *packet, u8 type, u8* payload, int payload_length){
	packet->start_marker = 0xAAAA;
	packet->type = type;
	packet->length = payload_length;
	memcpy(packet->payload, payload, payload_length);
	// TODO: Replace placeholder with CRC code
	packet->crc = 0x1;
};

// takes in the Packet and a 256-byte buffer
// copies data into buffer 
// returns the number of bytes used
u16 serialisePacket(Packet packet, u8 buffer[256]){
	// 16-bit because we need to track up until 256
	u16 index = 0;

	// assigning default fields
	// TODO: Yo this part could be cooked later on
	// start_marker is u16 being assigned to u8
	for(int i = 0; i < 2; i++){
		buffer[index++] = packet.start_marker;
	}
	buffer[index++] = packet.type;
	buffer[index++] = packet.length;

	for(int i = 0; i < packet.length; i++){
		buffer[index++] = packet.payload[i];
	}

	buffer[index++] = packet.crc;

	return index;
}
