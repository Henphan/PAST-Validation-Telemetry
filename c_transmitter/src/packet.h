#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

typedef struct {
	uint16_t start_marker;
	uint8_t type;
	uint8_t length;
	uint8_t payload[251];
	uint8_t crc;
}Packet;

void createPacket(
	Packet* packet,
	uint8_t type,
	uint8_t* payload
);

uint16_t serialisePacket(
	Packet packet, uint8_t buffer[256]
);

#endif
