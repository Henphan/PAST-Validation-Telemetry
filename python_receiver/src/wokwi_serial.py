import serial

print("Connecting...")

ser = serial.serial_for_url(
    "rfc2217://localhost:4000",
    baudrate=115200,
    timeout=1
)

print("Connected")

while True:
    data = ser.read(1)

    if data:
        print(data.hex(" ").upper())
