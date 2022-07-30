#include "servoController.h"
#include "displayController.h"
#include "joystick.h"
#include "cli.h"

void setup() {
    Serial.begin(9600);
    servoInit();
    displayInit();
    jostickInit();
    //centerAll();
    //cliInit();

    //Serial.println("hello");

    //welcome();
    //homeScreen();
}



void loop() {
    cliLoop();
}
