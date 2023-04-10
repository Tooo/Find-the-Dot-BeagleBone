#include <stdint.h>
#include <stdbool.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "../sharedMem-Linux/sharedDataStruct.h"

// Reference for shared RAM:
// https://markayoder.github.io/PRUCookbook/05blocks/blocks.html#_controlling_the_pwm_frequency

/*
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
*/

// GPIO Configuration
// ----------------------------------------------------------
volatile register uint32_t __R30;   // output GPIO register
volatile register uint32_t __R31;   // input GPIO register

// GPIO Output: P8_12 = pru0_pru_r30_14 
//   = LEDDP2 (Turn on/off right 14-seg digit) on Zen cape
#define DIGIT_ON_OFF_MASK (1 << 14)
// GPIO Input: P8_15 = pru0_pru_r31_15 
//   = JSRT (Joystick Right) on Zen Cape
//   (Happens to be bit 15 and p8_15; just a coincidence; see P8 header info sheet)
#define JOYSTICK_RIGHT_MASK (1 << 15)


// Shared Memory Configuration
// -----------------------------------------------------------
#define THIS_PRU_DRAM       0x00000         // Address of DRAM
#define OFFSET              0x200           // Skip 0x100 for Stack, 0x100 for Heap (from makefile)
#define THIS_PRU_DRAM_USABLE (THIS_PRU_DRAM + OFFSET)

// This works for both PRU0 and PRU1 as both map their own memory to 0x0000000
volatile sharedMemStruct_t *pSharedMemStruct = (volatile void *)THIS_PRU_DRAM_USABLE;

void main(void)
{
    // Initialize:
    pSharedMemStruct->isLedOn = true;
    pSharedMemStruct->isButtonPressed = false;
    pSharedMemStruct->smileCount = 0x5566;
    pSharedMemStruct->numMsSinceBigBang = 0x0000111122223333;

    while (true) { 

        // Drive LED from shared memory
        if (pSharedMemStruct->isLedOn) {
            __R30 |= DIGIT_ON_OFF_MASK;
        } else {
            __R30 &= ~DIGIT_ON_OFF_MASK;
        }

        // Sample button state to shared memory
        pSharedMemStruct->isButtonPressed = (__R31 & JOYSTICK_RIGHT_MASK) != 0;
    }
}
