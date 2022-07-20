#include "servoController.h"
#include "displayController.h"
#include "joystick.h"
#include "cli.h"

void setup() {
    Serial.begin(9600);
    servoInit();
    displayInit();
    jostickInit();
    cliInit();

    //Serial.println("hello");

    //setPosition(0, true);
    //orbit(1, 2);
    //oscillate(1, 5, true);
    //welcome();
    homeScreen();
}



void loop() {
    if (Serial.available() > 0) {
       Serial.println(Serial.read());
    }
}
