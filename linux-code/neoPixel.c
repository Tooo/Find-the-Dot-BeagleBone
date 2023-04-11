#include <unistd.h>

#include "neoPixel.h"
#include "linuxToPru.h"
#include "sharedGameStruct.h"

neoColors xColor[X_COUNT] = {
    RED,
    BLUE,
    GREEN
};

void NeoPixel_setLeds(XLedEnum xEnum, YLedEnum yEnum)
{
    uint8_t colors[NUM_OF_LEDS];
    for (int i = 0; i < NUM_OF_LEDS; i++) {
        colors[i] = xColor[xEnum];
    }
    LinuxToPru_setNeoPixel(colors);
}