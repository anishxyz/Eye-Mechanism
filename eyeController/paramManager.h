//
// Created by Anish Agrawal on 7/13/22.
//

#ifndef EYE_MECHANISM_PARAMMANAGER_H
#define EYE_MECHANISM_PARAMMANAGER_H

void incrRot(int inp);

void incrOsc(int inp);

bool getOscDir();

void togOscDir();

int getRot();

int getOsc();

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
