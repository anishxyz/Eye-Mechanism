//
// Created by Anish Agrawal on 7/13/22.
//

#include <Wire.h>


typedef void (*displayFunc)();

int rotations = 5;
int rotms = 1;
int rotSlow = 5;
int rotMed = 3;
int rotFast = 1;

int oscillations = 5;
int oscms = 1;
bool oscDir = true;
int oscSlow = 5;
int oscMed = 3;
int oscFast = 1;

void incrRot(int inp) {
    rotations = rotations + inp;
}

void incrOsc(int inp) {
    oscillations = oscillations + inp;
}

bool getOscDir() {
    return oscDir;
}

void togOscDir() {
    oscDir = !oscDir;
}

int getRot() {
    return rotations;
}

int getOsc() {
    return oscillations;
}

void setRotSpd(int inp) {
    if (inp == 1) {
        rotms = rotSlow;
    } else if (inp == 2) {
        rotms = rotMed;
    } else if (inp == 3) {
        rotms = rotFast;
    }
}

void setOscSpd(int inp) {
    if (inp == 1) {
        oscms = oscSlow;
    } else if (inp == 2) {
        oscms = oscMed;
    } else if (inp == 3) {
        oscms = oscFast;
    }
}

int getRotSpd() {
    return rotms;
}

int getOscSpd() {
    return oscms;
}

String getRotSpeedLvl() {
    if (rotms == rotFast) {
        return "FAST";
    }
    if (rotms == rotMed) {
        return "Med";
    }
    if (rotms == rotSlow) {
        return "Slow";
    }
}


String getOscSpeedLvl() {
    if (oscms == oscFast) {
        return "FAST";
    }
    if (oscms == oscMed) {
        return "Med";
    }
    if (oscms == oscSlow) {
        return "Slow";
    }
}
