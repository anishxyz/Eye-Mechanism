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
// orbi XX XX
// oscx XX XX
// oscy XX XX
// setx X
// sety X
// halt
// home

void cliLoop() {
    String str = "";

    while(Serial.available() > 0) {
        str = Serial.readStringUntil('\n');
    }

    if (str.substring(0,4).equals("cent")) {
        centerAll();
    } else if (str.substring(0,4).equals("orbi")) {
        int speed = str.substring(5,6).toInt();
        int rot = str.substring(7,12).toInt();
        setRotSpd(speed);
        setRot(rot);
        Serial.println("Orbiting... | Speed: " + getRotSpeedLvl() + " | Rotations: " + getRot());
        orbit(getRotSpd(), getRot());
    } else if (str.substring(0,4).equals("oscx")) {
        int speed = str.substring(5,6).toInt();
        int osc = str.substring(7,12).toInt();
        setOscDir(true);
        setOscSpd(speed);
        setOsc(osc);
        Serial.println("Oscillating... | Speed: " + getOscSpeedLvl() + " | Oscillations: " + getOsc()
            + " | Direction: " + getOscDirStr());
        oscillate(getOscSpd(), getOsc(), true);
    } else if (str.substring(0,4).equals("oscy")) {
        int speed = str.substring(5,6).toInt();
        int osc = str.substring(7,12).toInt();
        setOscDir(false);
        setOscSpd(speed);
        setOsc(osc);
        Serial.println("Oscillating... | Speed: " + getOscSpeedLvl() + " | Oscillations: " + getOsc()
            + " | Direction: " + getOscDirStr());
        oscillate(getOscSpd(), getOsc(), false);
    } else if (str.substring(0,4).equals("setx")) {
        float deg = str.substring(5,10).toFloat();
        setPosition(deg, true);
        Serial.print("Positioning....X Position set to ");
        Serial.print(deg);
        Serial.println(" degrees");
    } else if (str.substring(0,4).equals("sety")) {
        float deg = str.substring(5,10).toFloat();
        setPosition(deg, false);
        Serial.print("Positioning....Y Position set to ");
        Serial.print(deg);
        Serial.println(" degrees");
    } else if (str.substring(0,4).equals("movx")) {
        float deg = str.substring(5,10).toFloat();
        movePosition(deg, true);
        Serial.print("Positioning....X Position set to ");
        Serial.print(getPWMDeg(true));
        Serial.println(" degrees");
    } else if (str.substring(0,4).equals("movy")) {
        float deg = str.substring(5,10).toFloat();
        movePosition(deg, false);
        Serial.print("Positioning....Y Position set to ");
        Serial.print(getPWMDeg(false));
        Serial.println(" degrees");
    } else if (!str.equals("")) {
        Serial.print(str);
        Serial.println(" is not a valid command.");
        Serial.println("To see a valid list of commands, type -help")
    }
}
