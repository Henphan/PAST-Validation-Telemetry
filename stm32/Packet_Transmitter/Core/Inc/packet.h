#ifndef PACKET_H
#define PACKET_H

#include "utils.h"

#define PAYLOAD_MAX 244

typedef struct {
	u16 start_marker;
	u8 type;
	u8 length;
	u8 payload[244];
	u16 frag_id;
	u16 frag_no;
	u16 frag_total;
	u16 crc;
}Packet;

void createPacket(
	Packet* packet,
	u8 type,
	u8* payload,
	int payload_length,
	u16 frag_id,
	u16 frag_no,
	u16 frag_total
);

u16 serialisePacket(
	Packet packet, u8 buffer[256]
);

#endif
