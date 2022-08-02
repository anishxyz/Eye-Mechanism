//
// Created by Anish Agrawal on 7/13/22.
//

#ifndef EYE_MECHANISM_PARAMMANAGER_H
#define EYE_MECHANISM_PARAMMANAGER_H

void incrRot(int inp);

void setRot(int inp);

void setOsc(int inp);

void incrOsc(int inp);

bool getOscDir();

void setOscDir(bool inp);

bool getVerbose();

void setVerbose(bool inp);

void verbosity(String inp, bool newLine);

void verbosityInt(int inp, bool newLine);

void verbosityFloat(float inp, bool newLine);

void togOscDir();

int getRot();

int getOsc();

void setHalt(bool inp);

bool getHalt();

void setRotSpd(int inp);

void setOscSpd(int inp);

int getRotSpd();

int getOscSpd();

String getRotSpeedLvl();

String getOscSpeedLvl();

int getStep(bool xAxis);

void incrStep(bool xAxis);

void decrStep(bool xAxis);

int getDeg(bool xAxis);

String getOscDirStr();

#endif //EYE_MECHANISM_PARAMMANAGER_H
