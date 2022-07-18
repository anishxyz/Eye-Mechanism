//
// Created by Anish Agrawal on 7/18/22.
//

int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

int maxAccel = 5;
int deadZone = 2;

void jostickInit() {
    Serial.begin(9600);

    pinMode(VRx, INPUT);
    pinMode(VRy, INPUT);
    pinMode(SW, INPUT_PULLUP);
}

int joyX() {
    xPosition = analogRead(VRx);
    mapX = map(xPosition, 0, 2 * maxAccel, -maxAccel, maxAccel);
    return mapX;
}

int joyY() {
    yPosition = analogRead(VRy);
    mapX = map(yPosition, 0, 2 * maxAccel, -maxAccel, maxAccel);
    return mapY;
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