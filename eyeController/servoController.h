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

//void backAndForth(int startPulse, int endPulse, int ms, int servoNum); //deprecated in favor of oscillate

/**
 * Set axis to degree position
 *
 * @param deg degree to be set
 * @param servoNum axis to be controlled
 */
void setPosition(float deg, boolean servoNum);

/**
 * Increment axis by set amount of pulse-width steps
 *
 * @param axis axis of choice: true for x axis, false for y axis
 * @param steps steps to be incremented
 */
void incrCoord(bool axis, int steps);

/**
 * Get current PWM position of x-axis servo motor
 *
 * @return integer pulse-width value of x motor
 */
int getPWMX();

/**
 * Get current PWM position of y-axis servo motor
 *
 * @return integer pulse-width value of y motor
 */
int getPWMY();

/**
 * Get degree value of current PWM position of servo motor
 *
 * @param xAxis axis of choice: true for x axis, false for y axis
 * @return float value of curr position degrees
 */
float getPWMDeg(bool xAxis);

/**
 * Moves the selected axis by a certain number of degrees
 *
 * @param deg degrees to be moved
 * @param xAxis axis of choice: true for x axis, false for y axis
 */
void movePosition(float deg, bool xAxis);

#endif //EYE_MECHANISM_SERVOCONTROLLER_H
