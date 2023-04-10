#ifndef _SHARED_GAME_STRUCT_H_
#define _SHARED_GAME_STRUCT_H_

#include <stdbool.h>
#include <stdint.h>

#define NUM_OF_LEDS 8

typedef enum
{
    RED,
    RED_BRIGHT,
    GREEN,
    GREEN_BRIGHT,
    BLUE,
    BLUE_BRIGHT,
    OFF,
} neoColors;

// WARNING:
// Fields in the struct must be aligned to match ARM's alignment
//    bool/char, uint8_t:   byte aligned
//    int/long,  uint32_t:  word (4 byte) aligned
//    double,    uint64_t:  dword (8 byte) aligned
// Add padding fields (char _p1) to pad out to alignment.

// My Shared Memory Structure
// ----------------------------------------------------------------
typedef struct
{
    uint8_t neoLeds[NUM_OF_LEDS];
    bool joystickRightPressed;
    bool joystickDownPressed;
} sharedMemStruct_t;

#endif
