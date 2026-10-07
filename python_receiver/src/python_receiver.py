from crc_algorithm import crc16
import struct
import copy
import time
import os

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

data1 = bytes.fromhex("""
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

data2 = bytes.fromhex("""AA AA 01 F4 69 FA 5C 40 00 00 00 00 00 68 90 40 00 00 00 00 60 63 00 41 83 69 18 3E 22 02 40 C0 6A 18 3E 22 A6 FA 5C 40 00 00 00 00 00 C0 92 40 00 00 00 00 08 65 00 41 52 F2 EA 1C 03 02 40 C0 2D 43 1C EB E2 FA 5C 40 00 00 00 00 00 50 94 40 00 00 00 00 70 66 00 41 35 98 86 E1 23 02 40 C0 13 44 DD 07 20 FB 5C 40 00 00 00 00 00 E0 95 40 00 00 00 00 E8 66 00 41 2D 5B EB 8B 84 02 40 C0 E8 D9 AC FA 5C FB 5C 40 00 00 00 00 00 70 97 40 00 00 00 00 88 68 00 41 90 49 46 CE C2 02 40 C0 BD 6F 7C ED 99 FB 5C 40 00 00 00 00 00 00 99 40 00 00 00 00 50 69 00 41 98 17 60 1F 9D 02 40 C0 92 05 4C E0 D6 FB 5C 40 00 00 00 00 00 C8 99 40 00 00 00 00 90 6A 00 41 97 A8 DE 1A D8 02 40 C0 55 30 2A A9 13 FC 5C 40 00 00 00 00 00 90 9A 40 00 00 00 00 C0 6A 00 41 00 00 02 00 07 00 63 56""")

data3 = bytes.fromhex("""AA AA 01 F4 1F BF B7 E9 CF 02 40 C0 F5 84 25 1E 50 FC 5C 40 00 00 00 00 00 B0 9D 40 00 00 00 00 28 6C 00 41 D7 4C BE D9 E6 02 40 C0 94 D9 20 93 8C FC 5C 40 00 00 00 00 00 04 A0 40 00 00 00 00 28 6D 00 41 FB 05 BB 61 DB 02 40 C0 10 58 39 B4 C8 FC 5C 40 00 00 00 00 00 30 A1 40 00 00 00 00 A0 6E 00 41 6D 90 49 46 CE 02 40 C0 7B 6B 60 AB 04 FD 5C 40 00 00 00 00 00 5C A2 40 00 00 00 00 58 70 00 41 F4 37 A1 10 01 03 40 C0 D3 13 96 78 40 FD 5C 40 00 00 00 00 00 EC A3 40 00 00 00 00 C8 70 00 41 E5 0A EF 72 11 03 40 C0 08 E6 E8 F1 7B FD 5C 40 00 00 00 00 00 B4 A4 40 00 00 00 00 C8 71 00 41 42 09 33 6D FF 02 40 C0 2B 4D 4A 41 B7 FD 5C 40 00 00 00 00 00 E0 A5 40 00 00 00 00 40 73 00 41 B3 24 40 4D 2D 03 40 C0 3D 49 BA 66 F2 FD 5C 40 00 00 00 00 00 00 03 00 07 00 9A D4""")

data4 = bytes.fromhex("""AA AA 01 F4 00 0C A7 40 00 00 00 00 20 75 00 41 C9 1F 0C 3C F7 02 40 C0 3C DA 38 62 2D FE 5C 40 00 00 00 00 00 70 A7 40 00 00 00 00 C0 76 00 41 F4 37 A1 10 01 03 40 C0 18 95 D4 09 68 FE 5C 40 00 00 00 00 00 00 A9 40 00 00 00 00 E8 77 00 41 A6 D5 90 B8 C7 02 40 C0 F4 4F 70 B1 A2 FE 5C 40 00 00 00 00 00 C8 A9 40 00 00 00 00 68 78 00 41 89 EA AD 81 AD 02 40 C0 AD 34 29 05 DD FE 5C 40 00 00 00 00 00 58 AB 40 00 00 00 00 00 7A 00 41 9F 76 F8 6B B2 02 40 C0 42 43 FF 04 17 FF 5C 40 00 00 00 00 00 84 AC 40 00 00 00 00 68 7B 00 41 1F 2E 39 EE 94 02 40 C0 D7 51 D5 04 51 FF 5C 40 00 00 00 00 00 E8 AC 40 00 00 00 00 10 7D 00 41 ED B6 0B CD 75 02 40 C0 48 8A C8 B0 8A FF 5C 40 00 00 00 00 00 4C AD 40 00 00 00 00 C8 7E 00 41 0A 11 70 08 55 02 40 C0 00 00 04 00 07 00 47 AB""")

data5 = bytes.fromhex("""AA AA 01 F4 A8 57 CA 32 C4 FF 5C 40 00 00 00 00 00 B0 AD 40 00 00 00 00 B8 7F 00 41 3C 88 9D 29 74 02 40 C0 F5 B9 DA 8A FD FF 5C 40 00 00 00 00 00 DC AE 40 00 00 00 00 F0 80 00 41 BB D0 5C A7 91 02 40 C0 20 46 08 8F 36 00 5D 40 00 00 00 00 00 40 AF 40 00 00 00 00 90 81 00 41 A6 44 12 BD 8C 02 40 C0 26 FC 52 3F 6F 00 5D 40 00 00 00 00 00 04 B0 40 00 00 00 00 00 83 00 41 A6 D5 90 B8 C7 02 40 C0 0A DC BA 9B A7 00 5D 40 00 00 00 00 00 68 B0 40 00 00 00 00 98 83 00 41 4A 46 CE C2 9E 02 40 C0 C9 E5 3F A4 DF 00 5D 40 00 00 00 00 00 30 B1 40 00 00 00 00 80 84 00 41 3C 88 9D 29 74 02 40 C0 53 AE F0 2E 17 01 5D 40 00 00 00 00 00 62 B1 40 00 00 00 00 E0 85 00 41 99 F5 62 28 27 02 40 C0 CC 0B B0 8F 4E 01 5D 40 00 00 00 00 00 F8 B1 40 00 00 00 00 00 00 05 00 07 00 39 A3""")

data6 = bytes.fromhex("""AA AA 01 F4 D8 86 00 41 0A 80 F1 0C 1A 02 40 C0 FD BC A9 48 85 01 5D 40 00 00 00 00 00 5C B2 40 00 00 00 00 F8 87 00 41 CB DB 11 4E 0B 02 40 C0 F9 2C CF 83 BB 01 5D 40 00 00 00 00 00 F2 B2 40 00 00 00 00 58 89 00 41 12 BD 8C 62 B9 01 40 C0 D2 C6 11 6B F1 01 5D 40 00 00 00 00 00 56 B3 40 00 00 00 00 F8 8A 00 41 8C 15 35 98 86 01 40 C0 63 B4 8E AA 26 02 5D 40 00 00 00 00 00 1E B4 40 00 00 00 00 C8 8C 00 41 36 E5 0A EF 72 01 40 C0 AE F5 45 42 5B 02 5D 40 00 00 00 00 00 B4 B4 40 00 00 00 00 C8 8D 00 41 F6 D1 A9 2B 9F 01 40 C0 C3 F5 28 5C 8F 02 5D 40 00 00 00 00 00 E6 B4 40 00 00 00 00 78 8F 00 41 21 EA 3E 00 A9 01 40 C0 90 49 46 CE C2 02 5D 40 00 00 00 00 00 18 B5 40 00 00 00 00 D0 8F 00 41 D3 87 2E A8 6F 01 40 C0 17 F1 9D 98 F5 02 5D 40 00 00 06 00 07 00 0D B3""")

data7 = bytes.fromhex("""AA AA 01 A8 00 00 00 00 00 E0 B5 40 00 00 00 00 A8 91 00 41 7D E8 82 FA 96 01 40 C0 57 EC 2F BB 27 03 5D 40 00 00 00 00 00 76 B6 40 00 00 00 00 20 93 00 41 AF CE 31 20 7B 01 40 C0 61 A6 ED 5F 59 03 5D 40 00 00 00 00 00 3E B7 40 00 00 00 00 88 93 00 41 F6 D1 A9 2B 9F 01 40 C0 36 1F D7 86 8A 03 5D 40 00 00 00 00 00 70 B7 40 00 00 00 00 E8 93 00 41 A8 00 18 CF A0 01 40 C0 C4 EB FA 05 BB 03 5D 40 00 00 00 00 00 D4 B7 40 00 00 00 00 A8 94 00 41 E1 B4 E0 45 5F 01 40 C0 1D 77 4A 07 EB 03 5D 40 00 00 00 00 00 9C B8 40 00 00 07 00 07 00 50 DF""")

data = data1 + data2 + data3+ data4 + data5 + data6 + data7

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
    def get_frag_id(self):
        if len(self.frag_id) == 2:
            num = self.frag_id[0] << 8 | self.frag_id[1]
            return num
        else:
            raise Exception("Invalid field.")
    def get_frag_num(self):
        if len(self.frag_id) == 2:
            num = self.frag_num[0] << 8 | self.frag_num[1]
            return num
        else:
            raise Exception("Invalid field.")
    def get_frag_total(self):
        if len(self.frag_id) == 2:
            num = self.frag_total[0] << 8 | self.frag_total[1]
            return num
        else:
            raise Exception("Invalid field.")

packet = Packet()
packet_dict: dict[int, list[Packet]] = {}

clear_screen()
for byte in data:
    # time.sleep(0.05) # fake sleep
    print(hex(byte).upper().ljust(10), end=" ")
    if len(packet.start_marker) < 2: # checking for start marker
        if byte != 0xAA: # reset start marker
            print("GARBAGE")
            packet.start_marker = []
        else:
            packet.start_marker.append(byte)
            if len(packet.start_marker) == 1: # marker one found
                print("START MARKER 1/2")
            elif len(packet.start_marker) == 2: # marker two found
                print("START MARKER 2/2")

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
    if len(packet.crc) == 2: # checking for packet completion
        if packet.validate_crc(): # if crc's match then add to dict
            packet_dict.setdefault(packet.get_frag_id(), [])
            packet_dict[packet.get_frag_id()].append(copy.deepcopy(packet))
        # NOTE: Add packet drop notification
        packet = Packet() # create new packet

def sort_packet_dict(pdict): # sort fragments by frag_num
    for id in pdict:
        sorted_packet = sorted(packet_dict[id], key = lambda it: it.get_frag_num(), reverse = False)
        pdict[id] = sorted_packet

def join_payloads(frag_list: list[Packet]): # join the payloads of fragments together
    payload = []
    for frag in frag_list:
        payload += frag.payload
    return payload

clear_screen()

sort_packet_dict(packet_dict) # sorting the fragments
payload = bytes(join_payloads(packet_dict[0])) # joining the payloads
gnss_frame = []
i = 0
for i in range(0, len(payload), 8): # decoding the bytes into doubles
    chunk = payload[i:i+8]
    # print(chunk.hex(" ").upper()) # debugging code
    if len(chunk) == 8:
        double = struct.unpack('d', chunk)[0]
        # print(chunk.hex(" ").upper()) # debugging code
        gnss_frame.append(double)

j = 0
for i in range(0, len(gnss_frame), 4): # printing the doubles out in rows
    row = gnss_frame[i:i+4]
    print(j, row)
    j+=1
