import sys, os
import serial
import time
import traceback

class eye_mech:
    def __init__(self, port, baudrate=9600, bytesize=8, parity=serial.PARITY_NONE,
                 timeout=2, stopbits=serial.STOPBITS_TWO, writeTimeout=2, inter_byte_timeout=2 ):
        if port.lower() == "auto-detect":
            self.port = get_port_name("USB Serial Port")['port']
        else:
            self.port = port
        self.baudrate = baudrate
        self.bytesize = bytesize
        self.parity = parity
        self.timeout = timeout
        self.stopbits = stopbits
        self.writeTimeout = writeTimeout
        self.inter_byte_timeout = inter_byte_timeout

    def connect(self):
        self.serialPort = serial.Serial(
            port=self.port, baudrate=self.baudrate, bytesize=self.bytesize, parity=self.parity, timeout=self.timeout,
            stopbits=self.stopbits, writeTimeout=self.writeTimeout, inter_byte_timeout=self.inter_byte_timeout)

    def disconnect(self):
        self.serialPort.close()

    def off(self):
        self.set_attenuation(255)

    def flush(self):
        self.serialPort.flushOutput()
        self.serialPort.flushInput()

    def write_command(self, cmd, delay):
        for char in cmd:
            self.serialPort.write(char.encode('utf-8'))
            time.sleep(delay)

    def read_output(self):
        str_out = self.serialPort.readall()
        return str_out.decode()  #.split('\n\r') formally present



if __name__ == '__main__':
    #arduino = eye_mech('auto-detect')
    arduino = eye_mech('/dev/cu.usbmodem13301')
    arduino.connect()
    print("connect success!")
    arduino.write_command('ooorbi 3 2', 0.5)
    print("write success!")
    print(arduino.read_output())
    arduino.write_command('orbi 3 2', 0.5)
    print("write 2success!")
    print(arduino.read_output())
    print("read success!")
    arduino.disconnect()
