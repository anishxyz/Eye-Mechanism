//
// Created by Anish Agrawal on 7/11/22.
//

#ifndef EYE_MECHANISM_DISPLAYCONTROLLER_H
#define EYE_MECHANISM_DISPLAYCONTROLLER_H


void rotSpdScreen();

void backAndLines();

void rotScreen();

void updateOrbitRuntime(int r);

void initOrbitRuntime();

bool checkHalt();

void displayInit();

void resetScreen();

void displayScroll(String text);

void homeScreen();

void orbitScreen();

void oscScreen();

void oscSpdScreen();

void numOscScreen();

void posScreen();

void welcome();

void setPosScreen(boolean xAxis);

void initOscRuntime();

void updateOscRuntime(int r);

void posPrint();

#endif //EYE_MECHANISM_DISPLAYCONTROLLER_H
