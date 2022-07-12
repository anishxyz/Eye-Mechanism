//
// Created by Anish Agrawal on 7/11/22.
//
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_PWMServoDriver.h>

//Display Setup
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define WHITE 0x7 //color constant for backlight

void displayInit() {
    lcd.begin(16, 2);
    lcd.setBacklight(WHITE);
}

void displayScroll(String text) {
    lcd.print(text);
    //delay(1000);
    for (int i = 0; i < text.length() - 16; i++) {
        lcd.scrollDisplayLeft();
        //delay(300);
    }
}

void homeScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("< Orbit");
    lcd.setCursor(0, 1);
    lcd.print("^ Oscillate");
    lcd.setCursor(11, 0);
    lcd.print("> Pos");
}

void orbitScreen() {
    lcd.clear();
    lcd.print("orbit!");
}

void oscScreen() {
    lcd.clear();
    lcd.print("oscillate!");
}

void posScreen() {
    lcd.clear();
    lcd.print("position!");
}

void welcome() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Eye Mechanism");
    lcd.setCursor(0, 1);
    lcd.print("by anish & kito");
    delay(4000);
    lcd.clear();
}
