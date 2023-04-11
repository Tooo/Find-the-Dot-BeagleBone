// main.c
// Main Thread of Find the Dot
#include <stdio.h>

#include "shutdown.h"
#include "utils.h"
#include "buzzer.h"
#include "buzzerPlayer.h"
#include "accelerometer.h"
#include "digitDisplay.h"
#include "output.h"
#include "utils.h"
#include "findTheDot.h"
#include "linuxToPru.h"

// Initialize/cleanup the module's data structures.
static void main_init(void);
static void main_cleanup(void);

int main(void)
{
    main_init();
    Shutdown_wait();
    main_cleanup();
    return 0;
}

static void main_init(void)
{
    LinuxToPru_init();
    Accelerometer_init();
    Utils_randomInit();
    Buzzer_init();
    BuzzerPlayer_init();
    DigitDisplay_init();
    Output_init();
    FindTheDot_init();
}

static void main_cleanup(void)
{
    FindTheDot_cleanup();
    Output_cleanup();
    DigitDisplay_cleanup();
    BuzzerPlayer_cleanup();
    Buzzer_cleanup();
    Accelerometer_cleanup();
    LinuxToPru_cleanup();
}