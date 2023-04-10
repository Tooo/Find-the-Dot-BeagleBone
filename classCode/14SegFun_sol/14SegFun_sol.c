/*
    PRU Demo app for Zen Cape:
    - Flashes the right 14-seg display digit on the Zen Cape.
    - Flashes slower when pressing RIGHT on the joystick.
    By TI; modified by Brian Fraser

    Setup (all commands on Target)
    ******************************************************
    1.  Set both GPIO pins to be controlled by PRU0
            config-pin p8_12 pruout
            config-pin p8_15 pruin

    Display something on 14-seg display:
    2a. Enable I2C:
            config-pin P9_18 i2c
            config-pin P9_17 i2c

    2b. Enable I2C chip & set pattern; Pick correct board
        ZEN CAPE GREEN:
            i2cset -y 1 0x20 0x00 0x00
            i2cset -y 1 0x20 0x01 0x00
            i2cset -y 1 0x20 0x14 0x1E
            i2cset -y 1 0x20 0x15 0x78
        ZEN CAPE RED
            i2cset -y 1 0x20 0x02 0x00
            i2cset -y 1 0x20 0x03 0x00
            i2cset -y 1 0x20 0x00 0x0f
            i2cset -y 1 0x20 0x01 0x5e

    3. On target, compile PRU code (after copying to target):
        make
        On target, load compiled code:
        make install_PRU0
*/

#include <stdint.h>
#include <stdbool.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

// Delay 250ms (# cycles 200Mhz / 4)
#define DELAY_250_MS 50000000

volatile register uint32_t __R30;   // Output GPIO register
volatile register uint32_t __R31;   // Input GPIO register

// GPIO Output: P8_12 = pru0_pru_r30_14 
//   = LEDDP2 (Turn on/off right 14-seg digit) on Zen cape
#define DIGIT_ON_OFF_MASK (1 << 14)
// GPIO Input: P8_15 = pru0_pru_r31_15 
//   = JSRT (Joystick Right) on Zen Cape
//   (Happens to be bit 15 and p8_15; just a coincidence; see P8 header info sheet)
#define JOYSTICK_RIGHT_MASK (1 << 15)


// 200 Mhz clock
#define DELAY_100_MS 20000000
void delay(unsigned int delayInMs)
{
    // __delay_cycles needs a constant
    for (int i = 0; i < delayInMs; i += 100) {
        __delay_cycles(DELAY_100_MS);
    }
}

void flashOn(unsigned int delayOnInMs, unsigned int delayOffInMs) 
{
    __R30 |= DIGIT_ON_OFF_MASK;
    delay(delayOnInMs);

    __R30 &= ~DIGIT_ON_OFF_MASK;
    delay(delayOffInMs);
}


void main(void)
{
    int delayInMs = 1000;

    // Toggle digit on/off GPIO; slow down when button pressed
    while (true) {
        // 0. Toggle
        // __R30 ^= DIGIT_ON_OFF_MASK;
        // __delay_cycles(DELAY_100_MS);

        // 1. Control timing
        // __R30 |= DIGIT_ON_OFF_MASK;
        // __delay_cycles(DELAY_100_MS * 5);

        // __R30 &= ~DIGIT_ON_OFF_MASK;
        // __delay_cycles(DELAY_100_MS);

        // 2. Using delay function
        // flashOn(500, 500);
        // flashOn(100, 100);
        // flashOn(100, 100);

        // 3. Speeding up
        flashOn(delayInMs, 500);
        delayInMs /= 2;
        if (delayInMs == 0) {
            delayInMs = 1000;
        }
    }
}
