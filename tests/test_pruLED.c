#include <stdio.h>
#include <unistd.h>

#include "../linux-code/linuxToPru.h"
#include "../linux-code/sharedGameStruct.h"

// Pins the need to be configed
// config-pin p8_15 pruin for joystick right
// config-pin p8_16 pruin for joystick down
// config-pin p8_11 pruout for neo

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
    uint8_t colorElse[8] = {
        RED,
        GREEN,
        RED,
        GREEN,
        RED,
        GREEN,
        RED,
        GREEN,
    };
    LinuxToPru_init();
    while (true)
    {
        if (LinuxToPru_isJoystickDown())
        {
            LinuxToPru_setNeoPixel(colors);
        }
        else if (LinuxToPru_isJoystickRight())
        {
            LinuxToPru_setNeoPixel(colorChange);
        } 
        else 
        {
            LinuxToPru_setNeoPixel(colorElse);
        }
    }
    sleep(2);

    LinuxToPru_cleanup();

}