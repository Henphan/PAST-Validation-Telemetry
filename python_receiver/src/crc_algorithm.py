def crc16(message):
    POLY = 0x1021
    crc = 0xFFFF
    for byte in message:
        crc ^= byte<<8
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ POLY) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
    return crc


if __name__ == "__main__":
    raw_message = "123456789"
    message = raw_message.encode("ascii")
    message = []
    for c in raw_message:
        message.append(ord(c))

    print(hex(crc16(message)))
