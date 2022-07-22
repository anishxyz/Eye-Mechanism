import serial
import time
arduino = serial.Serial(port='/dev/cu.usbmodem313101', baudrate=115200, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'ascii'))
    time.sleep(0.05)
    data = arduino.readline()
    return data
while True:
    command = input("Enter command ") # Taking input from user
    value = write_read(command)
    print(value) # printing the value