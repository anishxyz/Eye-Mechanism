//
// Created by Anish Agrawal on 7/11/22.
//

#ifndef EYE_MECHANISM_SERVOCONTROLLER_H
#define EYE_MECHANISM_SERVOCONTROLLER_H

//
// Created by Anish Agrawal on 7/11/22.
//

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

void servoInit();

void setServoPulse(uint8_t n, double pulse);

void backAndForth(int startPulse, int endPulse, int ms, int servoNum);

void oscillate(int ms, int oscillations, int axis);

void orbit(int ms, int rotations);

void centerAll();

#endif //EYE_MECHANISM_SERVOCONTROLLER_H
