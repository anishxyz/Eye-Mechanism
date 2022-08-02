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

verbosity = {
        "on": 1,
        "off": 0,
        0: 0,
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
        time.sleep(3) # figure out constant
        self.verbosity("off")

    def disconnect(self):
        self.serialPort.close()

    def off(self):
        self.set_attenuation(255)

    def flush(self):
        self.serialPort.flushOutput()
        self.serialPort.flushInput()

    def write_command(self, cmd):
        cmd += "\n"
        for char in cmd:
            self.serialPort.write(char.encode('utf-8'))
            time.sleep(0.5)

    def read_output(self):
        str_out = self.serialPort.readall()
        return str_out.decode()  # .split('\n\r')


    def orbit(self, speed, rotations):
        """
        Rotate eye-mech in circular motion clock-wise
        :param speed: 'fast', 'med', or 'slow' or 3, 2, 1, respectively
        :param rotations: number of rotations
        """
        cmd = "orbi {} {}".format(speeds[speed], rotations)
        arduino.write_command(cmd)

    def oscillate(self, axis, speed, oscillations):
        """
        Oscillates eye-mech along given axis
        :param axis: 'x' for horizontal or 'y' for vertical
        :param speed: 'fast', 'med', or 'slow' or 3, 2, 1, respectively
        :param oscillations: number of oscillations
        """
        cmd = "osc{} {} {}".format(axis, speeds[speed], oscillations)
        arduino.write_command(cmd)

    def center(self):
        """
        Center eye-mech
        """
        arduino.write_command('cent')

    def verbosity(self, tog):
        """
        Enable/Disable serial output from eye-mech
        Enabling verbosity enables serial output
        Disabling verbosity disables serial output
        :param tog: 'on' or 'off', 1 or 0 respectively
        """
        cmd = "verb {}".format(verbosity[tog])
        arduino.write_command(cmd)

    def setPosition(self, axis, position):
        """
        Set the eye-mech to a specific position
        :param axis: 'x' for horizontal or 'y' for vertical
        :param position: coordinate from -36 to +36 degrees
        """
        cmd = "set{} {}".format(axis, position)
        arduino.write_command(cmd)

    def move(self, axis, position):
        """
        Move the eye-mech relative to current position position
        :param axis: 'x' for horizontal or 'y' for vertical
        :param position: coordinate from -36 to +36 degrees
        """
        cmd = "mov{} {}".format(axis, position)
        arduino.write_command(cmd)


if __name__ == '__main__':
    #arduino = eye_mech('auto-detect')
    arduino = eye_mech('/dev/cu.usbmodem3134301')  # change port on re-plug
    arduino.connect()
    print("connect success!")
    arduino.orbit('fast', 1)
    arduino.orbit('med', 2)
    arduino.orbit(3, 3)
    arduino.oscillate('y', 'fast', 3)
    arduino.center()
    arduino.write_command("anish")
    print(arduino.read_output())
    arduino.disconnect()
    print("disconnect success!")
