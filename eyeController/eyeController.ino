#include "servoController.h"
#include "displayController.h"
#include "joystick.h"

void setup() {
  servoInit();
  displayInit();
  jostickInit();
  Serial.print("hello");

  //setPosition(0, true);
  //orbit(1, 2);
  //oscillate(1, 5, true);
  //welcome();
  homeScreen();
}


void loop() {

}
