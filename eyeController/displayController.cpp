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

typedef void (*displayFunc)();  

void displayInit() {
    lcd.begin(16, 2);
    lcd.setBacklight(WHITE);
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

void orbitScreen() {
    resetScreen();
    lcd.print("orbit!");
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
    delay(4000);
    lcd.clear();
}

displayFunc menuOptions[] = {
    orbitScreen,
    oscScreen,
    posScreen
  };

void homeScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("< Orbit");
    lcd.setCursor(0, 1);
    lcd.print("^ Oscillate");
    lcd.setCursor(11, 0);
    lcd.print("> Pos");

    uint8_t buttons = lcd.readButtons();
    boolean state = true;
    
    while (lcd.readButtons() || state) {
      buttons = lcd.readButtons();
      if (buttons & BUTTON_UP) {
        oscScreen();
      }
//      if (buttons & BUTTON_DOWN) {
//        lcd.print("DOWN ");
//        lcd.setBacklight(YELLOW);
//      }
      if (buttons & BUTTON_LEFT) {
        orbitScreen();
      }
      if (buttons & BUTTON_RIGHT) {
        posScreen();
      }
      if (buttons & BUTTON_SELECT) {
        
      }
    }
}
