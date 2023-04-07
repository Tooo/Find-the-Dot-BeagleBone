// digitDisplay.h
// Module to manage LED Digit Display
// Thread looping to set digits on display
#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

// Initialize/cleanup the module's data structures.
void DigitDisplay_init(void);
void DigitDisplay_cleanup(void);

// Set display digit variable, used in display thread
void DigitDisplay_setDigit(int digit);

#endif