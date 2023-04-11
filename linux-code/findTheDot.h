// findTheDot.h
// Module to manage the find the dot game
#ifndef FIND_THE_DOT_H_
#define FIND_THE_DOT_H_

// X Enum
typedef enum {
    X_LEFT = 0,
    X_CENTRE,
    X_RIGHT,
    X_COUNT
} XLedEnum;

// Y Enum
typedef enum {
    Y_UP5 = 0,
    Y_UP4,
    Y_UP3,
    Y_UP2,
    Y_UP1,
    Y_CENTRE,
    Y_DOWN1,
    Y_DOWN2,
    Y_DOWN3,
    Y_DOWN4,
    Y_DOWN5,
    Y_COUNT,
} YLedEnum;

// Initialize/cleanup the module's data structures.
void FindTheDot_init(void);
void FindTheDot_cleanup(void);

double FindTheDot_getDotX();
double FindTheDot_getDotY();

XLedEnum FindTheDot_getXLedEnum();
YLedEnum FindTheDot_getYLedEnum();


#endif