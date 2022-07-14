//
// Created by Anish Agrawal on 7/11/22.
//
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "buttonHandler.h"

//Display Setup
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define WHITE 0x7 //color constant for backlight

typedef void (*displayFunc)();

int rotations = 5;
int rotms = 1;
int oscillations = 5;
int oscms = 1;
boolean oscDir = true;


//custom characters
byte arrUp[8] =
        {
                0b00000,
                0b00100,
                0b01110,
                0b10101,
                0b00100,
                0b00100,
                0b00000,
                0b00000
        };


byte arrDown[8] =
        {
                0b00000,
                0b00000,
                0b00100,
                0b00100,
                0b10101,
                0b01110,
                0b00100,
                0b00000
        };

byte arrRight[8] =
        {
                0b00000,
                0b00000,
                0b00100,
                0b00010,
                0b11111,
                0b00010,
                0b00100,
                0b00000
        };

byte arrLeft[8] =
        {
                0b00000,
                0b00000,
                0b00100,
                0b01000,
                0b11111,
                0b01000,
                0b00100,
                0b00000
        };


byte back[8] =
        {
                0b00000,
                0b00100,
                0b01000,
                0b11111,
                0b01001,
                0b00101,
                0b00001,
                0b00000
        };


byte mline[8] =
        {
                0b00100,
                0b00100,
                0b00100,
                0b00100,
                0b00100,
                0b00100,
                0b00100,
                0b00100
        };

byte rline[8] =
        {
                0b00001,
                0b00001,
                0b00001,
                0b00001,
                0b00001,
                0b00001,
                0b00001,
                0b00001
        };


byte arrDub[8] =
        {
                0b00100,
                0b01110,
                0b10101,
                0b00100,
                0b00100,
                0b10101,
                0b01110,
                0b00100
        };


byte oscDirY[8] =
        {
                0b01110,
                0b00100,
                0b00100,
                0b00100,
                0b00100,
                0b00100,
                0b00100,
                0b01110
        };


byte oscDirX[8] =
        {
                0b00000,
                0b00000,
                0b00000,
                0b10001,
                0b11111,
                0b10001,
                0b00000,
                0b00000
        };

void resetScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
}

void backAndLines() {
    resetScreen();
    lcd.write(byte(4));
    lcd.setCursor(1, 0);
    lcd.write(byte(6));
    lcd.setCursor(1, 1);
    lcd.write(byte(6));
}

void incrRot(int inp) {
    rotations = rotations + inp;
}

void incrOsc(int inp) {
    oscillations = oscillations + inp;
}

boolean getOscDir() {
    return oscDir;
}

void togOscDir() {
    oscDir = !oscDir;
}

int getRot() {
    return rotations;
}

int getOsc() {
    return oscillations;
}

void setRotSpd(int ms) {
    rotms = ms;
}

void setOscSpd(int ms) {
    oscms = ms;
}

int getRotSpd() {
    return rotms;
}

int getOscSpd() {
    return oscms;
}

byte getDirByte() {
    if (oscDir) {
        return byte(5);
    } else {
        return byte(7);
    }
}

String getRotSpeedLvl() {
    if (rotms == 1) {
        return "FAST";
    }
    if (rotms == 3) {
        return "Med";
    }
    if (rotms == 5) {
        return "Slow";
    }
}

String getOscSpeedLvl() {
    if (oscms == 1) {
        return "FAST";
    }
    if (oscms == 3) {
        return "Med";
    }
    if (oscms == 5) {
        return "Slow";
    }
}

void initOrbitRuntime() {
    lcd.setCursor(0,0);
    lcd.print("Orbit Running...");
    lcd.setCursor(0,1);
    lcd.print("0 / ");
    lcd.print(rotations);
    lcd.setCursor(12,1);
    lcd.print(getRotSpeedLvl());
}

void updateOrbitRuntime(int r) {
    lcd.setCursor(0,1);
    lcd.print(r);
}

void initOscRuntime() {
    lcd.setCursor(0,0);
    lcd.print("Oscil Running...");
    lcd.setCursor(0,1);
    lcd.print("0 / ");
    lcd.print(oscillations);
    lcd.setCursor(12,1);
    lcd.print(getOscSpeedLvl());
}

void updateOscRuntime(int r) {
    lcd.setCursor(0,1);
    lcd.print(r);
}

boolean checkHalt() {
    uint8_t buttons = lcd.readButtons();

    if (buttons) {
//        if (buttons & BUTTON_SELECT) {
//            return true;
//        }
        return true;
    }
    return false;
}


void displayInit() {
    lcd.begin(16, 2);
    lcd.setBacklight(WHITE);
    lcd.createChar(0, arrUp);
    lcd.createChar(1, arrDown);
    lcd.createChar(2, arrRight);
    lcd.createChar(3, arrLeft);
    lcd.createChar(4, back);
    //lcd.createChar(5, mline);
    lcd.createChar(6, rline);
    lcd.createChar(7, arrDub);
    //lcd.createChar(8, oscDirY);
    lcd.createChar(5, oscDirX);
}


void displayScroll(String text) {
    lcd.print(text);
    //delay(1000);
    for (int i = 0; i < text.length() - 16; i++) {
        lcd.scrollDisplayLeft();
        //delay(300);
    }
}

void rotSpdScreen() {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.print(" Slow");
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.print(" Med");
    lcd.setCursor(10, 0);
    lcd.write(byte(2));
    lcd.print(" FAST");

    delay(10);
    rotSpdButton(lcd);
}

void rotScreen() {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(7));
    lcd.print(" Rotat: ");
    lcd.print(rotations);

    delay(10);
    rotButton(lcd);
}

void orbitScreen() {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.print(" Speed: ");
    lcd.print(getRotSpeedLvl());
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.print(" Rotat: ");
    lcd.print(rotations);

    //initButton();
    orbitButton(lcd);
}


void oscScreen() {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.print(" Speed: ");
    lcd.print(getOscSpeedLvl());
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.print(" Oscil: ");
    lcd.print(oscillations);
    lcd.setCursor(15, 1);
    lcd.write(getDirByte());

    oscButton(lcd);
}

void oscSpdScreen() {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.print(" Slow");
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.print(" Med");
    lcd.setCursor(10, 0);
    lcd.write(byte(2));
    lcd.print(" FAST");

    delay(10);
    oscSpdButton(lcd);
}

void numOscScreen() {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(7));
    lcd.print(" Oscil: ");
    lcd.print(oscillations);

    delay(10);
    numOscButton(lcd);
}

void posScreen() {
    resetScreen();
    lcd.print("position!");
}

void welcome() {
    resetScreen();
    lcd.print("Eye Mechanism");
    lcd.setCursor(0, 1);
    lcd.print("by anish & kito");
    delay(2000);
    lcd.clear();
}


void homeScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.print(" Orbit");
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.print(" Oscillate");
    lcd.setCursor(11, 0);
    lcd.write(byte(2));
    lcd.print(" Pos");

    homeButton(lcd);
}
