import sys, os
import serial
import time
import traceback

speeds = {
        "fast": 3,
        "med": 2,
        "slow": 1,
        3: 3,
        2: 2,
        1: 1
    }

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
        time.sleep(1.7) # figure out constant

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
        str_out = self.serialPort.readlines()
        return str_out.decode()  # .split('\n\r')

    def orbit(self, speed, rotations):
        cmd = "orbi {} {}\n".format(speeds[speed], rotations)
        arduino.write_command(cmd, 0.5)

    def oscillate(self, speed, oscillations, axis):
        cmd = "osc{} {} {}".format(axis, speeds[speed], oscillations)
        arduino.write_command(cmd, 0.5)

    def center(self):
        arduino.write_command('cent', 0.5)

if __name__ == '__main__':
    #arduino = eye_mech('auto-detect')
    arduino = eye_mech('/dev/cu.usbmodem3134301')  # change port on re-plug
    arduino.connect()
    print("connect success!")
    arduino.orbit('fast', 1)
    # print(arduino.read_output())
    arduino.orbit('med', 2)
    # print(arduino.read_output())
    arduino.orbit(3, 3)
    arduino.flush()
    # print(arduino.read_output())
    arduino.oscillate('fast', 3, 'y')
    arduino.center()
    # print(arduino.read_output())
    arduino.disconnect()
    print("disconnect success!")
