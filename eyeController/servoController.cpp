//
// Created by Anish Agrawal on 7/11/22.
//

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "displayController.h"
#include "paramManager.h"
#include "cli.h"


//Servo Setup
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  220 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  440 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
int servoMid = (SERVOMAX+SERVOMIN)/2;
#define DEGMAX1  35 //max deg travel in x from origin
#define DEGMAX2  35 //max deg travel in y from origin
float degFactor1 = 110 / DEGMAX1;
float degFactor2 = 110 / DEGMAX2;
int steps = (SERVOMAX - SERVOMIN) * 2;

int pwmX = 330;
int pwmY = 330;

// our servo # counter
uint8_t servonum = 0;


void servoInit() {
    Serial.begin(9600);

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {
    double pulselength;

    pulselength = 1000000;   // 1,000,000 us per second
    pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
    //verbosityInt(pulselength, true); verbosity(" us per period", true);
    pulselength /= 4096;  // 12 bits of resolution
    //verbosity(pulselength, true); verbosity(" us per bit", true);
    pulse *= 1000000;  // convert input seconds to us
    pulse /= pulselength;
    //verbosityInt
    //(pulse, true);
    pwm.setPWM(n, 0, pulse);
}

void centerAll() {
    //iterates through 6 servos and positions them at their midpoint
    for(int i = 0; i < 6; i++) {
        pwm.setPWM(i, 0, servoMid);
    }
    verbosity("All axes centered.", true);
    pwmX = servoMid;
    pwmY = servoMid;
}

void orbit(int ms, int rotations) {
    // assign servo to axes
    int xServo = 0;
    int yServo = 1;

    //set eye position to middle top
    pwm.setPWM(xServo, 0, servoMid);
    pwm.setPWM(yServo, 0, SERVOMAX);
    int currX = servoMid;
    int currY = SERVOMAX;

    //phase controls increase/decrease of steps
    //true: increasing
    //false: decreasing
    boolean phaseX = true;
    boolean phaseY = false;

    //number of steps complete
    int currSteps = 0;

    //number of rotations completed
    int currRot = 0;

    //initialize screen to display orbit status
    initOrbitRuntime();

    //halt detection
    int haltCt = 0;

    // loop to keep adjusting position in steps until appropriate
    // number of steps for given rotations is complete

    for (int i = 1; i <= rotations; i++) {

        //runs a single rotation by running all 440 steps
        for (int j = 0; j < steps; j++) {

            //increase/decrease x axis in step
            if (phaseX) {
                pwm.setPWM(xServo, 0, currX++);
            } else {
                pwm.setPWM(xServo, 0, currX--);
            }

            //increase/decrease y axis in step
            if (phaseY) {
                pwm.setPWM(yServo, 0, currY++);
            } else {
                pwm.setPWM(yServo, 0, currY--);
            }

            //swaps direction when x axis limit hit
            if (currX == SERVOMAX || currX == SERVOMIN) {
                phaseX = !phaseX;
            }

            //swaps direction when y axis limit hit
            if (currY == SERVOMAX || currY == SERVOMIN) {
                phaseY = !phaseY;
            }

            if (haltCt == 350) {
                if (checkHalt()) {
                    verbosity("Halted.", true);
                    centerAll();
                    return;
                }
                if (serHalt()) {
                    verbosity("Halted.", true);
                    centerAll();
                    //homeScreen();
                    return;
                }
                haltCt = 0;
            } else {
                haltCt++;
            }

            pwmX = currX;
            pwmY = currY;

            //delay to maintain input speed
            delay(ms);
        }

        //used to update display for curr rotation number
        updateOrbitRuntime(i);
        verbosityInt(i, false);
        verbosity(" / ", false);
        verbosityInt(rotations, true);
    }
    verbosity("Orbit Complete.", true);
}

void oscillate(int ms, int oscillations, boolean input) {

    // assign servo to axes
    int xServo = 0;
    int yServo = 1;

    //select axis based on boolean input
    int axis = 0;
    if (input) {
        axis = xServo;
    } else {
        axis = yServo;
    }

    //current position of axis to be controlled
    int currPos = servoMid;

    //control if axis increasing/decreasing
    boolean phase = true;

    //initialize screen to display oscillate status
    initOscRuntime();

    //set both axes to center
    pwm.setPWM(xServo, 0, currPos);
    pwm.setPWM(yServo, 0, currPos);

    //number of steps complete
    int currSteps = 0;

    //halt detection
    int haltCt = 0;

    //number of oscillations completed
    int currOsc = 0;


    for (int i = 1; i <= oscillations; i++) {

        for (int j = 0; j < steps; j++) {

            //increase/decrease axis in step
            if (phase) {
                pwm.setPWM(axis, 0, currPos++);
            } else {
                pwm.setPWM(axis, 0, currPos--);
            }

            //swaps direction when axis limit hit
            if (currPos == SERVOMAX || currPos == SERVOMIN) {
                phase = !phase;
            }

            if (haltCt == 350) {
                if (checkHalt() || serHalt()) {
                    verbosity("Halted.", true);
                    centerAll();
                    return;
                }
                if (serHalt()) {
                    verbosity("Halted.", true);
                    centerAll();
                    //homeScreen();
                    return;
                }
                haltCt = 0;
            } else {
                haltCt++;
            }

            if (input) {
                pwmX = currPos;
            } else {
                pwmY = currPos;
            }

            //delay to maintain input speed
            delay(ms);

        }
        //used to update display for curr rotation number
        updateOscRuntime(i);
        verbosityInt(i, false);
        verbosity(" / ", false);
        verbosityInt(oscillations, true);
    }
    verbosity("Oscillate Complete.", true);
}

//deprecated in favor of oscillate
// void backAndForth(int startPulse, int endPulse, int ms, int servoNum) {
//    for(int curr = startPulse; curr < endPulse; curr++) {
//        pwm.setPWM(servoNum, 0, curr);
//        delay(ms);
//    }
//
//    for(int curr = endPulse; curr > startPulse; curr--) {
//        pwm.setPWM(servoNum, 0, curr);
//        delay(ms);
//    }
//}

int scaleDeg(float deg) {
  int temp = (deg * degFactor1) + 330;
  if (temp > SERVOMAX) {
    return SERVOMAX;
  }
  if (temp < SERVOMIN) {
    return SERVOMIN;
  }
  return temp;
}

void setPosition(float deg, bool xAxis) {
    if (xAxis) {
      pwm.setPWM(0, 0, scaleDeg(deg));
      pwmX = scaleDeg(deg);
    } else {
      pwm.setPWM(1, 0, scaleDeg(deg));
      pwmY = scaleDeg(deg);
    }
}

void movePosition(float deg, bool xAxis) {
    int tempPWM = scaleDeg(deg) - 330;

    if (xAxis) {
        tempPWM += pwmX;
    } else {
        tempPWM += pwmY;
    }

    if (tempPWM > SERVOMAX) {
        tempPWM = SERVOMAX;
    }
    if (tempPWM < SERVOMIN) {
        tempPWM = SERVOMIN;
    }

    if (xAxis) {
        pwmX = tempPWM;
        pwm.setPWM(0, 0, pwmX);
    } else {
        pwmY = tempPWM;
        pwm.setPWM(1, 0, pwmY);
    }
}

//void setPositionAcc(float deg, boolean xAxis) {
//    if (xAxis) {
//        pwm.setPWM(0, 0, scaleDeg(deg));
//        pwmX = scaleDeg(deg);
//    } else {
//        pwm.setPWM(1, 0, scaleDeg(deg));
//        pwmY = scaleDeg(deg);
//    }
//}

int scalePWM(bool xAxis) {
    if (xAxis) {
        return pwmX - 330;
    }
    return pwmY - 330;
}

void incrCoord(bool axis, int steps) {
    if (abs(scalePWM(axis) + steps) <= 110) {
        if (axis) {
            pwm.setPWM(0, 0, pwmX + steps);
            pwmX = pwmX + steps;
        } else {
            pwm.setPWM(1, 0, pwmY + steps);
            pwmY = pwmY + steps;
        }
    }
}

int getPWMX() {
    return pwmX;
}

int getPWMY() {
    return pwmY;
}

float scalePWM(int inp) {
    float temp = inp - 330;
    temp /= degFactor1;
    return temp;
}

float getPWMDeg(bool xAxis) {
    if (xAxis) {
        return scalePWM(pwmX);
    }
    return scalePWM(pwmY);
}
