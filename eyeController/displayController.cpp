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

int rotations = 10;
int rotms = 1;
int oscillations = 0;
int oscms = 0;


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

int getRot() {
    return rotations;
}

void setRotSpd(int ms) {
    rotms = ms;
}

int getRotSpd() {
    return rotms;
}

String getSpeedLvl() {
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

void initOrbitRuntime() {
    lcd.setCursor(0,0);
    lcd.print("Orbit Running...");
    lcd.setCursor(0,1);
    lcd.print("0 / ");
    lcd.print(rotations);
    lcd.setCursor(12,1);
    lcd.print(getSpeedLvl());
}

void updateOrbitRuntime(int r) {
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
    lcd.createChar(5, mline);
    lcd.createChar(6, rline);
    lcd.createChar(7, arrDub);
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
    resetScreen();
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.print(" Speed: ");
    lcd.print(getSpeedLvl());
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.print(" Rotat: ");
    lcd.print(rotations);

    //initButton();
    orbitButton(lcd);
}


void oscScreen() {
    resetScreen();
    lcd.print("oscillate!");
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
