import serial
import time

arduino = serial.Serial(port='/dev/cu.usbmodem3134301', baudrate=115200, timeout=.1)


def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline().strip().decode("utf-8")
    return data
while True:
    command = input("Enter command ") # Taking input from user
    value = write_read(command)
    print(value) # printing the cenvalue