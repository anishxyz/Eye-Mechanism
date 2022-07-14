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

String getRotSpeedLvl();

void welcome();

int getDeg(boolean xAxis); 

int getStep(boolean xAxis); 

void incrStep(boolean xAxis); 

void decrStep(boolean xAxis);

void setPosScreen(boolean xAxis);

void initOscRuntime();

void updateOscRuntime(int r);

#endif //EYE_MECHANISM_DISPLAYCONTROLLER_H
