#include <pthread.h>
#include <stdbool.h>

#include "findTheDot.h"
#include "shutdown.h"
#include "utils.h"
#include "accelerometer.h"

#define RANDOM_MAX 1
#define RANDOM_RANGE 0.5
double dotX;
double dotY;

// Output Thread
static pthread_t findTheDotThread;
static void* FindTheDot_threadFunction(void* args);
static bool stopping;

void FindTheDot_init(void)
{
    stopping = false;
    pthread_create(&findTheDotThread, NULL, &FindTheDot_threadFunction, NULL);
}

void FindTheDot_cleanup(void)
{
    stopping = true;
    pthread_join(findTheDotThread, NULL);
}

static void FindTheDot_generateDot()
{
    double x = Accelerometer_getX();
    double y = Accelerometer_getY();

    dotX = x + Utils_randomDouble() * RANDOM_MAX - RANDOM_RANGE;
    dotY = y + Utils_randomDouble() * RANDOM_MAX - RANDOM_RANGE;
}

static void* FindTheDot_threadFunction(void* args)
{
    (void)args;
    while (!stopping) {
        FindTheDot_generateDot();
        Utils_sleepForMs(1000);
    }
    Shutdown_trigger();
    return NULL;
}

double FindTheDot_getDotX()
{
    return dotX;
}

double FindTheDot_getDotY()
{
    return dotY;
}