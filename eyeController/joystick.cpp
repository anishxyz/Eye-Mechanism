//
// Created by Anish Agrawal on 7/18/22.
//
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

int maxAccel = 3;
int scalar = 512 / maxAccel;
int deadZone = 0;

void jostickInit() {
    Serial.begin(9600);

    pinMode(VRx, INPUT);
    pinMode(VRy, INPUT);
    pinMode(SW, INPUT_PULLUP);
}

int joyX() {
    xPosition = analogRead(VRx);
    mapX = map(xPosition, 0, 1023, -512, 512);
    if (abs(mapX) <= deadZone) {
        return 0;
    }
    return mapX / scalar;
}

int joyY() {
    yPosition = analogRead(VRy);
    mapY = map(yPosition, 0, 1023, -512, 512);
    if (abs(mapY) <= deadZone) {
        return 0;
    }
    return mapY / scalar;
}

bool joySW() {
    if (digitalRead(SW) == 0) {
        return true;
    }
    return false;
}

//void joyDebug() {
//    xPosition = analogRead(VRx);
//    yPosition = analogRead(VRy);
//    SW_state = digitalRead(SW);
//    mapX = map(xPosition, 0, 1023, -512, 512);
//    mapY = map(yPosition, 0, 1023, -512, 512);
//
//    Serial.print("X: ");
//    Serial.print(mapX);
//    Serial.print(" | Y: ");
//    Serial.print(mapY);
//    Serial.print(" | Button: ");
//    Serial.println(SW_state);
//
//    delay(100);
//}
