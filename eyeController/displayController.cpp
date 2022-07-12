//
// Created by Anish Agrawal on 7/11/22.
//
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>
#include "servoController.h"

//Display Setup
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define WHITE 0x7 //color constant for backlight

typedef void (*displayFunc)();

int rotations = 0;
int rotms = 0;
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
}

void resetScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

void displayScroll(String text) {
    lcd.print(text);
    //delay(1000);
    for (int i = 0; i < text.length() - 16; i++) {
        lcd.scrollDisplayLeft();
        //delay(300);
    }
}

void speedScreen() {
  resetScreen();
  lcd.print("I AM SPEED!");
}

void rotScreen() {
  resetScreen();
  lcd.print("I AM SPINNY!");
}

void orbitScreen() {
    resetScreen();
    lcd.write(byte(4));
    lcd.setCursor(1, 0);
    lcd.write(byte(6));
    lcd.setCursor(1, 1);
    lcd.write(byte(6));
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.print(" Speed: Slow");
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.print(" Rotat: 5");

    uint8_t buttons = lcd.readButtons();
    boolean state = true;
    
    while (lcd.readButtons() || state) {
      buttons = lcd.readButtons();
      if (buttons & BUTTON_UP) {
        speedScreen();
        break;
      }
      if (buttons & BUTTON_DOWN) {
        rotScreen();
        break;
      }
      if (buttons & BUTTON_LEFT) {
        //homeScreen();
        break;
      }
      if (buttons & BUTTON_RIGHT) {
        orbit(1, 2);
        break;
      }
    }
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

    uint8_t buttons = lcd.readButtons();
    boolean state = true;
    
    while (lcd.readButtons() || state) {
      buttons = lcd.readButtons();
      if (buttons & BUTTON_UP) {
        orbitScreen();
        break;
      }
      if (buttons & BUTTON_DOWN) {
        oscScreen();
        break;
      }
      if (buttons & BUTTON_RIGHT) {
        posScreen();
        break;
      }
    }
}
