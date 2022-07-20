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