#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "output.h"
#include "utils.h"
#include "accelerometer.h"

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
    printf("X: %f, Y: %f\n", Accelerometer_getX(), Accelerometer_getY());
}

static void* Output_threadFunction(void* args)
{
    (void)args;
    while (!stopping) {
        Output_printAccelerator();
        Utils_sleepForMs(threadSleepMs);
    }
    return NULL;
}