from crc_algorithm import crc16
import struct
import copy
import time

data = bytes.fromhex("""
AA AA 01 F4 00 00 00 00 00 5C 00 41 69 6F F0 85 C9 00 40 C0 
1B 2F DD 24 06 F9 5C 40 00 00 00 00 00 00 59 40 00 00 00 00 
F8 5C 00 41 38 32 8F FC C1 00 40 C0 9B 3D D0 0A 0C F9 5C 40 
00 00 00 00 00 00 69 40 00 00 00 00 20 5D 00 41 70 99 D3 65 
31 01 40 C0 13 9B 8F 6B 43 F9 5C 40 00 00 00 00 00 C0 72 40 
00 00 00 00 B8 5E 00 41 4C E0 D6 DD 3C 01 40 C0 3D 27 BD 6F 
7C F9 5C 40 00 00 00 00 00 20 7C 40 00 00 00 00 C0 5F 00 41 
3D 44 A3 3B 88 01 40 C0 D2 35 93 6F B6 F9 5C 40 00 00 00 00 
00 C0 82 40 00 00 00 00 70 61 00 41 7D 79 01 F6 D1 01 40 C0 
D2 C6 11 6B F1 F9 5C 40 00 00 00 00 00 70 87 40 00 00 00 00 
D0 61 00 41 61 8E 1E BF B7 01 40 C0 2A 6F 47 38 2D FA 5C 40 
00 00 00 00 00 B0 8D 40 00 00 00 00 88 62 00 41 59 C0 04 6E 
DD 01 40 C0 B8 58 51 83 00 00 01 00 07 00 3E 11""")

class Packet:
    def __init__(self) -> None:
        self.start_marker = []
        self.packet_type: int | None = None
        self.packet_length: int | None = None
        self.payload = []
        self.frag_id = []
        self.frag_num = []
        self.frag_total = []
        self.crc = []
    def validate_crc(self):
        remainder = crc16(self.payload)
        return (hex(remainder) == hex(self.crc[0]<<8 | self.crc[1]))
    def deconstruct_payload(self):
        # NOTE: This method currently ignores incomplete numbers
        payload = bytes(self.payload)
        if self.packet_type == 1: # GNSS data
            out = []
            for i in range(0, len(payload), 8):
                chunk = payload[i:i+8]
                # print(chunk.hex(" ").upper()) # debugging code
                if len(chunk) == 8:
                    double = struct.unpack('d', chunk)[0]
                    out.append(double)
            return out

packet = Packet()
my_packets: list[Packet] = []

for byte in data:
    # time.sleep(0.1)
    print(hex(byte).upper().ljust(10), end=" ")
    if len(packet.start_marker) != 2: # checking for start marker
        if byte == 0xAA:
            packet.start_marker.append(byte)
            print("START MARKER")
        else:
            print("GARBAGE")

    elif packet.packet_type is None: # checking for packet type
        # NOTE: No validation
        packet.packet_type = byte
        print("PACKET TYPE")

    elif packet.packet_length is None:
        # NOTE: No validation
        packet.packet_length = byte
        print("PACKET LENGTH")

    elif len(packet.payload) != packet.packet_length: # checking for payload
        packet.payload.append(byte)
        print(len(packet.payload),'/',packet.packet_length)

    elif len(packet.frag_id) != 2: # checking for frag id
        packet.frag_id.append(byte)
        print("FRAG ID")

    elif len(packet.frag_num) != 2: # checking for frag num
        packet.frag_num.append(byte)
        print("FRAG NUM")

    elif len(packet.frag_total) != 2: # checking for frag total
        packet.frag_total.append(byte)
        print("FRAG Total")

    elif len(packet.crc) != 2: # checking for crc
        packet.crc.append(byte)
        print("CRC")
    else:
        print("GARBAGE")
if packet.validate_crc(): # if crc's match
    my_packets.append(copy.deepcopy(packet))
