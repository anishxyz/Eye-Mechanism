//
// Created by Anish Agrawal on 7/12/22.
//

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "servoController.h"
#include "displayController.h"

int clickDelay = 150;

void orbitButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            delay(clickDelay);
            rotSpdScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            delay(clickDelay);
            rotScreen();
            break;
        }
        if (buttons & BUTTON_LEFT) {
            delay(clickDelay);
            homeScreen();
            break;
        }
        if (buttons & BUTTON_RIGHT) {
            resetScreen();
            delay(350);
            orbit(getRotSpd(), getRot());
            orbitScreen();
            break;
        }
    }
}

void homeButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            delay(clickDelay);
            orbitScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            delay(clickDelay);
            oscScreen();
            break;
        }
        if (buttons & BUTTON_RIGHT) {
            delay(clickDelay);
            posScreen();
            break;
        }
    }
}

void rotButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            incrRot(1);
            delay(250);
            rotScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            incrRot(-1);
            delay(250);
            rotScreen();
            break;
        }
        if (buttons & BUTTON_LEFT) {
            delay(clickDelay);
            orbitScreen();
            break;
        }
        if (buttons & BUTTON_RIGHT) {
            resetScreen();
            delay(350);
            orbit(getRotSpd(), getRot());
            orbitScreen();
            break;
        }
    }
}

void rotSpdButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            setRotSpd(5);
            delay(clickDelay);
            orbitScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            setRotSpd(3);
            delay(clickDelay);
            orbitScreen();
            break;
        }
        if (buttons & BUTTON_LEFT) {
            delay(clickDelay);
            orbitScreen();
            break;
        }
        if (buttons & BUTTON_RIGHT) {
            setRotSpd(1);
            delay(clickDelay);
            orbitScreen();
            break;
        }
    }
}
