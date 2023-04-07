// main.c
// Main Thread of Find the Dot
#include <stdio.h>

#include "shutdown.h"
#include "system.h"
#include "buzzer.h"
#include "accelerometer.h"
#include "digitDisplay.h"

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
    Accelerometer_init();
    Buzzer_init();
    DigitDisplay_init();
    
    
}

static void main_cleanup(void)
{
    DigitDisplay_cleanup();
    Buzzer_cleanup();
    Accelerometer_cleanup();
}