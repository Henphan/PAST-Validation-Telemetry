#include "crc_algorithm.h"
#include <stdint.h>


u16 crc16(const u8* message, int length){
	u16 poly = 0x1021;
	u16 crc = 0xFFFF;
	for(int i = 0; i < length; i++){
		crc ^= (u16)message[i] << 8;

		for (int bit = 0; bit < 8; bit++)
		{
		    if (crc & 0x8000)
			crc = (u16)((crc << 1) ^ poly);
		    else
			crc = (u16)(crc << 1);
		}
	}
	return crc;
}
