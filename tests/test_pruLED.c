#include <stdio.h>
#include <unistd.h>

#include "../linux-code/linuxToPru.h"
#include "../linux-code/sharedGameStruct.h"

int main(void)
{
    uint8_t colors[8] = {
        RED,
        RED_BRIGHT,
        GREEN,
        GREEN_BRIGHT,
        BLUE,
        BLUE_BRIGHT,
        OFF,
        RED_BRIGHT,
    };
    uint8_t colorChange[8] = {
        BLUE,
        GREEN,
        RED,
        OFF,
        OFF,
        BLUE_BRIGHT,
        GREEN_BRIGHT,
        RED_BRIGHT,
    };
    LinuxToPru_init();
    LinuxToPru_setNeoPixel(colors);
    sleep(2);
    LinuxToPru_setNeoPixel(colorChange);

    LinuxToPru_cleanup();

}