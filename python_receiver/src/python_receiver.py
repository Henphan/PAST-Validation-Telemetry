from crc_algorithm import crc16

packet = bytes.fromhex("""
AA AA 01 F4 00 00 00 00 00 5C 00 41 69 6F F0 85 C9 00 40 C0 1B 2F DD 24 06 F9 5C 40 00 00 00 00 00 00 59 40 00 00 00 00 F8 5C 00 41 38 32 8F FC C1 00 40 C0 9B 3D D0 0A 0C F9 5C 40 00 00 00 00 00 00 69 40 00 00 00 00 20 5D 00 41 70 99 D3 65 31 01 40 C0 13 9B 8F 6B 43 F9 5C 40 00 00 00 00 00 C0 72 40 00 00 00 00 B8 5E 00 41 4C E0 D6 DD 3C 01 40 C0 3D 27 BD 6F 7C F9 5C 40 00 00 00 00 00 20 7C 40 00 00 00 00 C0 5F 00 41 3D 44 A3 3B 88 01 40 C0 D2 35 93 6F B6 F9 5C 40 00 00 00 00 00 C0 82 40 00 00 00 00 70 61 00 41 7D 79 01 F6 D1 01 40 C0 D2 C6 11 6B F1 F9 5C 40 00 00 00 00 00 70 87 40 00 00 00 00 D0 61 00 41 61 8E 1E BF B7 01 40 C0 2A 6F 47 38 2D FA 5C 40 00 00 00 00 00 B0 8D 40 00 00 00 00 88 62 00 41 59 C0 04 6E DD 01 40 C0 B8 58 51 83 00 00 01 00 07 00 3E 11""")

class Packet:
    def __init__(self) -> None:
        self.start_marker = []
        self.type = None
        self.length = None
        self.payload = []
        self.frag_id = []
        self.frag_num = []
        self.frag_total = []
        self.crc = []

start_count = 0
start_found = False
packet_type = None
packet_length = None
payload = []
frag_id = []
frag_num = []
frag_total = []
crc = []

for byte in packet:
    print(hex(byte).upper(), end=" ")
    if not start_found: # checking for start marker
        if byte == 0xAA and start_count == 1:
            start_found = True
            print("START MARKER")
        elif byte == 0xAA:
            start_count += 1
    else:
        if packet_type is None: # checking for packet type
            packet_type = byte
            print("PACKET TYPE")
        elif packet_length is None: # checking for packet length
            packet_length = byte
            print("PACKET LENGTH")
        else: # checking for payload
            if len(payload) != packet_length:
                payload.append(byte)
                print(len(payload))
            else:
                if len(frag_id) != 2: # checking for frag id
                    frag_id.append(byte)
                    print("FRAG ID")
                elif len(frag_num) != 2: # checking for frag num
                    frag_num.append(byte)
                    print("FRAG NUM")
                elif len(frag_total) != 2: # checking for frag total
                    frag_total.append(byte)
                    print("FRAG Total")
                elif len(crc) != 2: # checking for crc
                    crc.append(byte)
                    print("CRC")
remainder = hex(crc16(payload))
print(remainder == hex(crc[0]<<8 | crc[1])) # comparing the two crc's
if remainder == hex(crc[0]<<8 | crc[1]): # construct packet object
    pass
