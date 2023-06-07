import serial
import time


serial_arduino = serial.Serial("COM6", baudrate=9600, timeout=1)


def test():

    if serial_arduino.isOpen():

        val = serial_arduino.readline()

        print(val)
    else:
        serial_arduino.close()
        print("kontol")


if __name__ == '__main__':
    while True:
        test()