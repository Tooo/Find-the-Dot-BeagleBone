#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "output.h"
#include "utils.h"
#include "accelerometer.h"
#include "findTheDot.h"
#include "linuxToPru.h"

// Output Thread
static pthread_t outputThread;
static void* Output_threadFunction(void* args);
static bool stopping;
static int threadSleepMs = 1000;

void Output_init(void)
{
    stopping = false;
    pthread_create(&outputThread, NULL, &Output_threadFunction, NULL);
}

void Output_cleanup(void)
{
    stopping = true;
    pthread_join(outputThread, NULL);
}

static void Output_printAccelerator()
{
    printf("(X,Y) - Accel: (%0.2f, %0.2f)", Accelerometer_getX(), Accelerometer_getY());
    printf(" Dot: (%0.2f, %0.2f)", FindTheDot_getDotX(), FindTheDot_getDotY());
}
static void Output_printJoystick()
{
    printf(" Joystick: D:%d, R:%d", LinuxToPru_isJoystickDown(), LinuxToPru_isJoystickRight());
}

static void Output_printLed()
{
    printf(" LED: (%d, %d)", FindTheDot_getXLedEnum(), FindTheDot_getYLedEnum());
}

static void* Output_threadFunction(void* args)
{
    (void)args;
    while (!stopping) {
        Output_printAccelerator();
        Output_printJoystick();
        Output_printLed();
        printf("\n");
        Utils_sleepForMs(threadSleepMs);
    }
    return NULL;
}