//
// Created by Anish Agrawal and Kito Pang on 7/19/22.
//

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "servoController.h"
#include "displayController.h"
#include "paramManager.h"
#include "joystick.h"

const unsigned int MAX_MESSAGE_LENGTH = 5;
String line = "--------------------------------------------------";

void cliInit() {
    verbosity("", true);
    verbosity(line, true);
    verbosity("Eye Mechanism CLI", true);
    verbosity(line, true);
    verbosity("--Orbit", true);
    verbosity("\t Speed: ", false);
    verbosity(getRotSpeedLvl(), true);
    verbosity("\t Rotations: ", false);
    verbosityInt(getRot(), true);
    verbosity("--Oscillate", true);
    verbosity("\t Speed: ", false);
    verbosity(getOscSpeedLvl(), true);
    verbosity("\t Oscillations: ", false);
    verbosityInt(getOsc(), true);
    verbosity("\t Direction: ", false);
    verbosity(getOscDirStr(), true);
    verbosity("--Position", true);
    verbosity("\t X-Degrees: ", false);
    verbosityFloat(getPWMDeg(true), true);
    verbosity("\t Y-Degrees: ", false);
    verbosityFloat(getPWMDeg(false), true);
    verbosity(line, true);
    verbosity("", true);
}

void cliLoop() {
    String str = "";

    while(Serial.available() > 0) {
        str = Serial.readStringUntil('\n');
    }

    if (!str.equals("")) {
        if (str.substring(0, 4).equals("cent")) {
            centerAll();
        } else if (str.substring(0, 5).equals("orbi ")) {
            int speed = str.substring(5, 6).toInt();
            int rot = str.substring(7, 12).toInt();
            setRotSpd(speed);
            setRot(rot);
            verbosity("Orbiting... | Speed: " + getRotSpeedLvl() + " | Rotations: " + getRot(), true);
            orbit(getRotSpd(), getRot());
        } else if (str.substring(0, 5).equals("oscx ")) {
            int speed = str.substring(5, 6).toInt();
            int osc = str.substring(7, 12).toInt();
            setOscDir(true);
            setOscSpd(speed);
            setOsc(osc);
            verbosity("Oscillating... | Speed: " + getOscSpeedLvl() + " | Oscillations: " + getOsc()
                           + " | Direction: " + getOscDirStr(), true);
            oscillate(getOscSpd(), getOsc(), true);
        } else if (str.substring(0, 5).equals("oscy ")) {
            int speed = str.substring(5, 6).toInt();
            int osc = str.substring(7, 12).toInt();
            setOscDir(false);
            setOscSpd(speed);
            setOsc(osc);
            verbosity("Oscillating... | Speed: " + getOscSpeedLvl() + " | Oscillations: " + getOsc()
                           + " | Direction: " + getOscDirStr(), true);
            oscillate(getOscSpd(), getOsc(), false);
        } else if (str.substring(0, 5).equals("setx ")) {
            float deg = str.substring(5, 10).toFloat();
            setPosition(deg, true);
            verbosity("Positioning....X Position set to ", false);
            verbosityFloat(getPWMDeg(true), false);
            verbosity(" degrees", true);
        } else if (str.substring(0, 5).equals("sety ")) {
            float deg = str.substring(5, 10).toFloat();
            setPosition(deg, false);
            verbosity("Positioning....Y Position set to ", false);
            verbosityFloat(getPWMDeg(false), false);
            verbosity(" degrees", true);
        } else if (str.substring(0, 5).equals("movx ")) {
            float deg = str.substring(5, 10).toFloat();
            movePosition(deg, true);
            verbosity("Positioning....X Position set to ", false);
            verbosityFloat(getPWMDeg(true), false);
            verbosity(" degrees", true);
        } else if (str.substring(0, 5).equals("movy ")) {
            float deg = str.substring(5, 10).toFloat();
            movePosition(deg, false);
            verbosity("Positioning....Y Position set to ", false);
            verbosityFloat(getPWMDeg(false), false);
            verbosity(" degrees", true);
        } else if (str.substring(0, 3).equals("joy")) {
            verbosity("Joystick Active", true);
            while(true) {
                incrCoord(true, joyX());
                incrCoord(false, joyY());
                if (joySW()) {
                    verbosity("Joystick Deactivated", true);
                    verbosity("X: ", false);
                    verbosityFloat(getPWMDeg(true), false);
                    verbosity(", Y: ", false);
                    verbosityFloat(getPWMDeg(false), true);
                    break;
                }
            }
        } else if (str.substring(0, 5).equals("anish")) {
            verbosity("Made with <3 by Anish Agrawal", true);
            verbosity("Dancing...", true);
            orbit(0, 2);
            oscillate(0, 2, true);
            oscillate(0, 2, false);
        } else if (str.substring(0, 6).equals("status")) {
            cliInit();
        } else if (str.substring(0, 5).equals("verb ")) {
            int tog = str.substring(5, 6).toInt();
            if (tog == 1) {
                setVerbose(true);
                Serial.println("verbosity activated.");
            }
            if (tog == 0) {
                setVerbose(false);
                //Serial.println("verbosity deactivated.");
            }
        } else if (str.substring(0, 9).equals("commands")) {
            verbosity("", true);
            verbosity(F("Here are available commands for the Eye-Mechanism:"), true);
            verbosity(line, true);
            verbosity("", true);
            verbosity("Operation Commands", true);
            verbosity("--", true);
            verbosity(F("\tcent\t\t: centers eyes"), true);
            verbosity(F("\torbi S #####\t: rotates eyes, S = 1,2,3 for speeds slow, med, fast and ##### is number of rotations (max of 2^15 - 1)"), true);
            verbosity(F("\toscx S #####\t: oscillates eyes right-left, S = 1,2,3 for speeds slow, med, fast and ##### is number of oscillations (max of 2^15 - 1)"), true);
            verbosity(F("\toscy S #####\t: oscillates eyes up-down, S = 1,2,3 for speeds slow, med, fast and ##### is number of oscillations (max of 2^15 - 1)"), true);
            verbosity(F("\thalt\t\t: stop and terminate oscillate/orbit command"), true);
            verbosity("", true);
            verbosity("Position Commands", true);
            verbosity("Note: axes range from -36.67 degrees to +36.67 degrees", true);
            verbosity("--", true);
            verbosity(F("\tsetx #####\t: set x position to desired angle, ##### is decimal, degree of desired position"), true);
            verbosity(F("\tsety #####\t: set y position to desired angle, ##### is decimal, degree of desired position"), true);
            verbosity(F("\tmovx #####\t: move x position by a desired amount (in degrees), ##### is decimal, degree of desired movement"), true);
            verbosity(F("\tmovy #####\t: move y position by a desired amount (in degrees),  ##### is decimal, degree of desired movement"), true);
            verbosity("", true);
            verbosity("Other Commands", true);
            verbosity("--", true);
            verbosity(F("\tcommands\t: revisit this menu!"), true);
            verbosity("", true);
            verbosity(F("In trouble? Bug? email anish.agrawal@mojo.vision, phone 650 653 1313"), true);
            verbosity("try the secret command ;) -anish", true);
        } else {
            verbosity(str, false);
            verbosity(" is not a valid command.", true);
            verbosity(F("To see a valid list of commands, type 'commands'"), true);
        }
        //homeScreen();
    }
}

bool serHalt() {
    if (Serial.peek() == 'h') {
        String curr;
        while(Serial.available() > 0) {
            curr = Serial.readStringUntil('\n');
        }
        if (curr.equals("halt")) {
            return true;
        }
    }
    return false;
}

