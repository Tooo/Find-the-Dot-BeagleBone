#include <stdint.h>
#include <stdbool.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "../logicAnalyzer-Linux/sharedDataStruct.h"

// Reference for shared RAM:
// https://markayoder.github.io/PRUCookbook/05blocks/blocks.html#_controlling_the_pwm_frequency

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

#define PROCESSOR_SPEED_MHZ 200000000
#define BUFFER_WINDOW_TIME_S 4
// Delay per sample is:
//  # instructions per second * seconds/window / samples / window
#define DELAY_PER_SAMPLE (PROCESSOR_SPEED_MHZ * BUFFER_WINDOW_TIME_S / NUM_SAMPLES)

#define DELAY_250_MS 50000000

void main(void)
{
    // Initialize:
    pSharedMemStruct->isFilledWithSamples = false;

    while (true) { 

        // // Drive LED from shared memory
        // if (pSharedMemStruct->isLedOn) {
        //     __R30 |= DIGIT_ON_OFF_MASK;
        // } else {
        //     __R30 &= ~DIGIT_ON_OFF_MASK;
        // }

        // Hoping to toggle the LED at period of 4s
        __R30 ^= DIGIT_ON_OFF_MASK;
        // __delay_cycles(DELAY_250_MS);

        // Sample button state to shared memory
        // Fill the sample buffer every 4s
        // 60 samples in the buffer
        for (int i = 0; i < NUM_SAMPLES; i++) {
            bool isButtonPressed = (__R31 & JOYSTICK_RIGHT_MASK) != 0;
            char ch = isButtonPressed ? 'X' : '_';
            pSharedMemStruct->data[i] = ch;
            __delay_cycles(DELAY_PER_SAMPLE);
        }
        
        // Signal Linux that data is ready
        pSharedMemStruct->isFilledWithSamples = true;

        // wait until linux has processed
        while (pSharedMemStruct->isFilledWithSamples) {
            // do nothing
        }

    }
}
