//
// Created by Anish Agrawal on 7/11/22.
//
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "buttonHandler.h"
#include "paramManager.h"
#include "servoController.h"

//Display Setup
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define WHITE 0x7 //color constant for backlight

typedef void (*displayFunc)();

//custom characters

//up arrow
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

//down arrow
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

//right arrow
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

//left arrow
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

//back button
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

//vertical line in middle
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

//vertical line right-justified
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

//arrows up and down
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

//vertical line with tabs
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

//horizontal line with tabs
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

void resetScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
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

void backAndLines() {
    resetScreen();
    lcd.write(byte(4));
    lcd.setCursor(1, 0);
    lcd.write(byte(6));
    lcd.setCursor(1, 1);
    lcd.write(byte(6));
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
    lcd.print(getRot());

    //initButton();
    orbitButton(lcd);
}


void rotScreen() {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(7));
    lcd.print(" Rotat: ");
    lcd.print(getRot());

    delay(10);
    rotButton(lcd);
}

void initOrbitRuntime() {
    lcd.setCursor(0,0);
    lcd.print("Orbit Running...");
    lcd.setCursor(0,1);
    lcd.print("0 / ");
    lcd.print(getRot());
    lcd.setCursor(12,1);
    lcd.print(getRotSpeedLvl());
}

void updateOrbitRuntime(int r) {
    lcd.setCursor(0,1);
    lcd.print(r);
}

byte getDirByte() {
    if (getOscDir()) {
        return byte(5);
    } else {
        return byte(7);
    }
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
    lcd.print(getOsc());
    lcd.setCursor(15, 1);
    lcd.write(getDirByte());

    oscButton(lcd);
}

void initOscRuntime() {
    lcd.setCursor(0,0);
    lcd.print("Oscil Running...");
    lcd.setCursor(0,1);
    lcd.print("0 / ");
    lcd.print(getOsc());
    lcd.setCursor(10,1);
    lcd.write(getDirByte());
    lcd.setCursor(12,1);
    lcd.print(getOscSpeedLvl());
}

void updateOscRuntime(int r) {
    lcd.setCursor(0,1);
    lcd.print(r);
}

bool checkHalt() {
    uint8_t buttons = lcd.readButtons();

    if (buttons) {
//        if (buttons & BUTTON_SELECT) {
//            return true;
//        }
        return true;
    }
    return false;
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
    lcd.print(getOsc());

    delay(10);
    numOscButton(lcd);
}


void setPosScreen(boolean xAxis) {
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(7));
    if (xAxis) {
     lcd.print(" X-Deg: ");
    } else {
      lcd.print(" Y-Deg: ");
    }
    
    lcd.print(getDeg(xAxis)); 
    delay(10);
    
    setPosButton(lcd, xAxis); 
}


void posScreen() {
    resetScreen();
    backAndLines();
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.print(" X-Deg: ");
    lcd.print(getDeg(true)); 

    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.print(" Y-Deg: ");
    lcd.print(getDeg(false)); 

    //posButton(lcd);
    posButton(lcd);
}

void posPrint() {
    lcd.setCursor(12, 0);
    lcd.print(getPWMDeg(true), 1);
    lcd.setCursor(12, 1);
    lcd.print(getPWMDeg(false), 1);
}