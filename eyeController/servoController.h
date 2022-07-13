/**
 * @file servoController.h
 * @author Anish Agrawal
 */

#ifndef EYE_MECHANISM_SERVOCONTROLLER_H
#define EYE_MECHANISM_SERVOCONTROLLER_H

/**
 * initializes the servo motors to be used
 */
void servoInit();

/**
 * Adjust pulse length and units
 *
 * @param n
 * @param pulse pulse-width in seconds
 */
void setServoPulse(uint8_t n, double pulse);

/**
 * Centers all servo motors
 */
void centerAll();

/**
 * Controls the eye-mech to move eyeballs in a circular motion
 *
 * @param ms delay per step that dictates speed
 * @param rotations number of complete rotations or orbits
 */
void orbit(int ms, int rotations);

/**
 * Controls the eye-mech to oscillate the eyeballs in a given direction
 *
 * @param ms delay per step that dictates speed
 * @param oscillations number of complete rotations or orbits
 * @param input direction of oscillation (true is horizontal, false is vertical)
 */
void oscillate(int ms, int oscillations, boolean input);

void backAndForth(int startPulse, int endPulse, int ms, int servoNum);

#endif //EYE_MECHANISM_SERVOCONTROLLER_H
