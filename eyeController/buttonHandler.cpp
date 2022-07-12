//
// Created by Anish Agrawal on 7/12/22.
//

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "servoController.h"
#include "displayController.h"

void orbitButton(Adafruit_RGBLCDShield inp) {
    uint8_t buttons = inp.readButtons();
    boolean state = true;

    while (lcdb.readButtons() || state) {
        buttons = inp.readButtons();
        if (buttons & BUTTON_UP) {
            speedScreen();
            break;
        }
        if (buttons & BUTTON_DOWN) {
            rotScreen();
            break;
        }
        if (buttons & BUTTON_LEFT) {
            homeScreen();
            break;
        }
        if (buttons & BUTTON_RIGHT) {
            orbit(1, 2);
            break;
        }
    }
}
