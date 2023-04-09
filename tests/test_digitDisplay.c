#include <stdio.h>

#include "../linux-code/utils.h"
#include "../linux-code/digitDisplay.h"


int main(void)
{
    DigitDisplay_init();

    for (int i = 0; i < 100; i++) {
        DigitDisplay_setDigit(i);
        Utils_sleepForMs(100);
    }
    
    DigitDisplay_cleanup();
}