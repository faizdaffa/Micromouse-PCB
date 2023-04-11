import serial,time

a = "asu"
serial_arduino = serial.Serial("COM7", baudrate="9600", timeout=5)
try:
    while True:
        serial_arduino.write(f"memek {a}".encode('utf-8'))
except serial.serialutil.SerialException:
    print('kontol')