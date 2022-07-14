//
// Created by Anish Agrawal on 7/12/22.
//

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "servoController.h"
#include "displayController.h"

// delay after button clicks so no accidental "double-click"
int clickDelay = 150;


void homeButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            delay(clickDelay); //delay so click does not hold onto next screen
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

        if (buttons & BUTTON_SELECT) {
            delay(clickDelay);
            centerAll();
            homeScreen();
            break;
        }
    }
}


void orbitButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            delay(clickDelay); //delay so click does not hold onto next screen
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
        if (buttons & (BUTTON_RIGHT || BUTTON_SELECT)) {
            resetScreen();
            delay(350);
            orbit(getRotSpd(), getRot());
            orbitScreen();
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
            delay(250); //delay so click does not hold onto next screen
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
        if (buttons & (BUTTON_RIGHT || BUTTON_SELECT)) {
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
            delay(clickDelay); //delay so click does not hold onto next screen
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

void oscButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            delay(clickDelay); //delay so click does not hold onto next screen
            oscSpdScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            delay(clickDelay);
            numOscScreen();
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
            oscillate(getOscSpd(), getOsc(), getOscDir());
            oscScreen();
            break;
        }
        if (buttons & BUTTON_SELECT) {
            togOscDir();
            delay(clickDelay);
            oscScreen();
            break;
        }
    }
}

void numOscButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            incrOsc(1);
            delay(250); //delay so click does not hold onto next screen
            numOscScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            incrOsc(-1);
            delay(250);
            numOscScreen();
            break;
        }
        if (buttons & BUTTON_LEFT) {
            delay(clickDelay);
            oscScreen();
            break;
        }
        if (buttons & BUTTON_RIGHT) {
            resetScreen();
            delay(350);
            oscillate(getOscSpd(), getOsc(), getOscDir());
            oscScreen();
            break;
        }
    }
}

void oscSpdButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (inp.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            setOscSpd(5);
            delay(clickDelay); //delay so click does not hold onto next screen
            oscScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            setOscSpd(3);
            delay(clickDelay);
            oscScreen();
            break;
        }
        if (buttons & BUTTON_LEFT) {
            delay(clickDelay);
            oscScreen();
            break;
        }
        if (buttons & BUTTON_RIGHT) {
            setOscSpd(1);
            delay(clickDelay);
            oscScreen();
            break;
        }
    }
}
