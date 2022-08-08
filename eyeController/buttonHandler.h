/**
 * @file buttonHeader.h
 * @author Anish Agrawal
 */


#ifndef EYE_MECHANISM_BUTTONHANDLER_H
#define EYE_MECHANISM_BUTTONHANDLER_H

/**
 * Controls button input on the home screen. Navigates
 * the menu system from the home screen which is as follows
 * Up: Orbit
 * Down: Oscillate
 * Right: Position
 *
 * @param inp lcd panel with buttons to be read and used for controls
 */
void homeButton(Adafruit_RGBLCDShield inp);

/**
 * Controls button input on the orbit config screen.
 * Navigates the menu system as follows
 * Up: Configure speed
 * Down: Configure number of rotations
 * Left: Back to home
 * Right: Run the eye-mech with current inputs
 *
 * @param inp lcd panel with buttons to be read and used for controls
 */
void orbitButton(Adafruit_RGBLCDShield inp);

/**
 * Controls button input on the rotation config screen.
 * Navigates the menu system which is as follows
 * Up: Increment rotations
 * Down: Decrement rotations
 * Left: Back to orbit config screen
 * Right: Run with current params
 *
 * @param inp lcd panel with buttons to be read and used for controls
 */
void rotButton(Adafruit_RGBLCDShield inp);

/**
 * Controls button input on the rotation speed config screen.
 * Navigates the menu system which is as follows
 * Up: Slow speed
 * Down: Med speed
 * Left: Back to orbit config screen
 * Right: FAST speed
 *
 * @param inp lcd panel with buttons to be read and used for controls
 */
void rotSpdButton(Adafruit_RGBLCDShield inp);

/**
 * Controls button input for position screen
 * @param inp lcd panel with buttons to be read and used for controls
 */
void posButton(Adafruit_RGBLCDShield inp);

/**
 * Controls button input for setting x and y position screens
 * @param inp lcd panel with buttons to be read and used for controls
 * @param xAxis true for x, false for y axis positioning
 */
void setPosButton(Adafruit_RGBLCDShield inp, boolean xAxis);

/**
 * Controls button input on the oscillation config screen.
 * Navigates the menu system as follows
 * Up: Configure speed
 * Down: Configure number of oscillations
 * Left: Back to home
 * Right: Run the eye-mech with current inputs
 * Select: toggle axis of oscillation
 *
 * @param inp lcd panel with buttons to be read and used for controls
 */
void oscButton(Adafruit_RGBLCDShield inp);

/**
 * Controls button input on the oscillation config screen.
 * Navigates the menu system which is as follows
 * Up: Increment oscillations
 * Down: Decrement oscillations
 * Left: Back to oscillation config screen
 * Right: Run with current params
 *
 * @param inp lcd panel with buttons to be read and used for controls
 */
void numOscButton(Adafruit_RGBLCDShield inp);


/**
 * Controls button input on the oscilation speed config screen.
 * Navigates the menu system which is as follows
 * Up: Slow speed
 * Down: Med speed
 * Left: Back to orbit config screen
 * Right: FAST speed
 *
 * @param inp lcd panel with buttons to be read and used for controls
 */
void oscSpdButton(Adafruit_RGBLCDShield inp);

#endif //EYE_MECHANISM_BUTTONHANDLER_H
