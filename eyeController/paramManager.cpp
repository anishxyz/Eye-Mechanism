//
// Created by Anish Agrawal on 7/13/22.
//

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

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

int xStep = 4;
int yStep = 4;
int degreeArr[9] = {-9,-35,-25,-15,0, 15,25,35,45};

bool halt = false;
bool verbose = true;

void setVerbose(bool inp) {
    verbose = inp;
}

bool getVerbose() {
    return verbose;
}

void verbosity(String inp, bool newLine) {
    if (getVerbose()) {
        if (newLine) {
            Serial.println(inp);
        } else {
            Serial.print(inp);
        }
    }
}

void verbosityInt(int inp, bool newLine) {
    if (getVerbose()) {
        if (newLine) {
            Serial.println(inp);
        } else {
            Serial.print(inp);
        }
    }
}

void verbosityFloat(float inp, bool newLine) {
    if (getVerbose()) {
        if (newLine) {
            Serial.println(inp);
        } else {
            Serial.print(inp);
        }
    }
}

void incrRot(int inp) {
    rotations = rotations + inp;
}

void incrOsc(int inp) {
    oscillations = oscillations + inp;
}

bool getOscDir() {
    return oscDir;
}

void setOscDir(bool inp) {
    oscDir = inp;
}

String getOscDirStr() {
    if (oscDir) {
        return "x-axis";
    } else {
        return "y-axis";
    }
}

void togOscDir() {
    oscDir = !oscDir;
}

void setHalt(bool inp) {
    halt = inp;
}

bool getHalt() {
    return halt;
}

void setRot(int inp) {
    rotations = inp;
}

void setOsc(int inp) {
    oscillations = inp;
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

int getStep(bool xAxis) {
    if(xAxis) {
        return xStep;
    } else {
        return yStep;
    }
}


void incrStep(bool xAxis) {
    if(xAxis && xStep < 8) {
        xStep++;
    } else if (!xAxis && yStep < 8) {
        yStep++;
    }
}

void decrStep(bool xAxis) {
    if(xAxis && xStep > 0) {
        xStep--;
    } else if(!xAxis && yStep > 0) {
        yStep--;
    }
}

int getDeg(bool xAxis) {
    if(xAxis) {
        return degreeArr[xStep];
    } else {
        return degreeArr[yStep];
    }
}
