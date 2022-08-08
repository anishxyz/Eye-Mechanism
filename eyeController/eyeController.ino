#include "servoController.h"
#include "displayController.h"
#include "joystick.h"
#include "cli.h"

void setup() {
    Serial.begin(9600);
    servoInit();
    displayInit();
    jostickInit();
    welcome();
    //cliInit(); // mode to have constant readout for debugging and monitoring over serial


    homeScreen(); // enables screen UI and manual input
}



void loop() {
    //cliLoop(); // enables CLI mode to communicate over serial (required for python scripting)
}
