#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "output.h"
#include "utils.h"
#include "accelerometer.h"
#include "findTheDot.h"

#include "shutdown.h" // temp

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
    printf("(X,Y) - Accel: (%0.3f, %0.3f)", Accelerometer_getX(), Accelerometer_getY());
    printf(" Dot: (%0.3f, %0.3f)\n", FindTheDot_getDotX(), FindTheDot_getDotY());
}

static void* Output_threadFunction(void* args)
{
    (void)args;
    (void)stopping; // temp
    //while (!stopping) {
    for (int i = 0; i < 10; i++) { // temp
        Output_printAccelerator();
        Utils_sleepForMs(threadSleepMs);
    }
    Shutdown_trigger();
    return NULL;
}