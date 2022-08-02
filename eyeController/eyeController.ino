#include "servoController.h"
#include "displayController.h"
#include "joystick.h"
#include "cli.h"

void setup() {
    Serial.begin(9600);
    servoInit();
    displayInit();
    jostickInit();
    //cliInit();

    welcome();
    homeScreen();
}



void loop() {
    //cliLoop();
}
