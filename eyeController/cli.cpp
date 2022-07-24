//
// Created by Anish Agrawal on 7/19/22.
//

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "servoController.h"
#include "displayController.h"
#include "paramManager.h"

const unsigned int MAX_MESSAGE_LENGTH = 5;

void cliInit() {
    Serial.println();
    Serial.println("---------------------------------------------");
    Serial.println("Eye Mechanism CLI");
    Serial.println("---------------------------------------------");
    Serial.println("--Orbit");
    Serial.print("\t Speed: ");
    Serial.println(getRotSpeedLvl());
    Serial.print("\t Rotations: ");
    Serial.println(getRot());
    Serial.println("--Oscillate");
    Serial.print("\t Speed: ");
    Serial.println(getOscSpeedLvl());
    Serial.print("\t Oscillations: ");
    Serial.println(getOsc());
    Serial.print("\t Direction: ");
    Serial.println(getOscDirStr());
    Serial.println("--Position");
    Serial.print("\t X-Degrees: ");
    Serial.println(getPWMDeg(true));
    Serial.print("\t Y-Degrees: ");
    Serial.println(getPWMDeg(false));
    Serial.println("---------------------------------------------");
    Serial.println();
}

//needed commands
// orbi XX XX done
// oscx XX XX done
// oscy XX XX done
// setx X done
// sety X done
// halt
// cent done
//--help

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
            Serial.println("Orbiting... | Speed: " + getRotSpeedLvl() + " | Rotations: " + getRot());
            orbit(getRotSpd(), getRot());
        } else if (str.substring(0, 5).equals("oscx ")) {
            int speed = str.substring(5, 6).toInt();
            int osc = str.substring(7, 12).toInt();
            setOscDir(true);
            setOscSpd(speed);
            setOsc(osc);
            Serial.println("Oscillating... | Speed: " + getOscSpeedLvl() + " | Oscillations: " + getOsc()
                           + " | Direction: " + getOscDirStr());
            oscillate(getOscSpd(), getOsc(), true);
        } else if (str.substring(0, 5).equals("oscy ")) {
            int speed = str.substring(5, 6).toInt();
            int osc = str.substring(7, 12).toInt();
            setOscDir(false);
            setOscSpd(speed);
            setOsc(osc);
            Serial.println("Oscillating... | Speed: " + getOscSpeedLvl() + " | Oscillations: " + getOsc()
                           + " | Direction: " + getOscDirStr());
            oscillate(getOscSpd(), getOsc(), false);
        } else if (str.substring(0, 5).equals("setx ")) {
            float deg = str.substring(5, 10).toFloat();
            setPosition(deg, true);
            Serial.print("Positioning....X Position set to ");
            Serial.print(getPWMDeg(true));
            Serial.println(" degrees");
        } else if (str.substring(0, 5).equals("sety ")) {
            float deg = str.substring(5, 10).toFloat();
            setPosition(deg, false);
            Serial.print("Positioning....Y Position set to ");
            Serial.print(getPWMDeg(false));
            Serial.println(" degrees");
        } else if (str.substring(0, 5).equals("movx ")) {
            float deg = str.substring(5, 10).toFloat();
            movePosition(deg, true);
            Serial.print("Positioning....X Position set to ");
            Serial.print(getPWMDeg(true));
            Serial.println(" degrees");
        } else if (str.substring(0, 5).equals("movy ")) {
            float deg = str.substring(5, 10).toFloat();
            movePosition(deg, false);
            Serial.print("Positioning....Y Position set to ");
            Serial.print(getPWMDeg(false));
            Serial.println(" degrees");
        } else if (str.substring(0, 5).equals("anish")) {
            Serial.println("Made with <3 by Anish Agrawal");
            Serial.println("Dancing...");
            orbit(0, 2);
            oscillate(0, 2, true);
            oscillate(0, 2, false);
        } else if (str.substring(0, 9).equals("commands")) {
            Serial.println("Here are available commands for the Eye-Mechanism:");
            Serial.println("---------------------------------------------------");
            Serial.println("Operation Commands");
            Serial.println("--");
            Serial.println("\tcent\t\t: centers eyes");
            Serial.println("\torbi S #####\t: rotates eyes, S = 1,2,3 for speeds slow, med, fast and ##### is number of rotations (max of 2^15 - 1)");
            Serial.println("\toscx S #####\t: oscillates eyes right-left, S = 1,2,3 for speeds slow, med, fast and ##### is number of oscillations (max of 2^15 - 1)");
            Serial.println("\toscy S #####\t: oscillates eyes up-down, S = 1,2,3 for speeds slow, med, fast and ##### is number of oscillations (max of 2^15 - 1)");
            Serial.println("\thalt\t\t: stop and terminate oscillate/orbit command");
            Serial.println("Position Commands");
            Serial.println("Note: axes range from -36.67 degrees to +36.67 degrees");
            Serial.println("--");
            Serial.println("\tsetx #####\t: set x position to desired angle, ##### is decimal, degree of desired position");
            Serial.println("\tsety #####\t: set y position to desired angle, ##### is decimal, degree of desired position");
            Serial.println("\tmovx #####\t: move x position by a desired amount (in degrees), ##### is decimal, degree of desired movement");
            Serial.println("\tmovy #####\t: move y position by a desired amount (in degrees),  ##### is decimal, degree of desired movement");
            Serial.println("--");
            Serial.println("\tcommands\t\t: revisit this menu!");
            Serial.println("In trouble? Bug? email anish.agrawal@mojo.vision, phone 650 653 1313");
            Serial.println("try the secret command ;) -anish");
        } else {
            Serial.print(str);
            Serial.println(" is not a valid command.");
            Serial.println("To see a valid list of commands, type 'commands'");
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