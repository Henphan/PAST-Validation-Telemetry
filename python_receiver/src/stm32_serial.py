import serial

print("Connecting...")

ser = serial.Serial(
    port="/dev/cu.usbmodem11303",
    baudrate=115200,
    timeout=2
)

print("Connected!")

output = ""

while True:
    data = ser.read(32)
    if data:
        print("Received:", data.hex(" ").upper())
        print(len(data))
