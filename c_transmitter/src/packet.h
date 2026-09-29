#ifndef PACKET_H
#define PACKET_H

#include "utils.h"

typedef struct {
	u16 start_marker;
	u8 type;
	u8 length;
	u8 payload[251];
	u8 crc;
}Packet;

void createPacket(
	Packet* packet,
	u8 type,
	u8* payload,
	int payload_length
);

u16 serialisePacket(
	Packet packet, u8 buffer[256]
);

#endif
