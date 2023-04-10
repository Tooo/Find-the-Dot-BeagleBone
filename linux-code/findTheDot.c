#include <pthread.h>
#include <stdbool.h>

#include "findTheDot.h"
#include "shutdown.h"
#include "utils.h"
#include "accelerometer.h"
#include "buzzerPlayer.h"
#include "digitDisplay.h"
#include "linuxToPru.h"

#define RANDOM_MAX 1
#define RANDOM_RANGE 0.5
#define HIT_RANGE 0.1
static double dotX;
static double dotY;

static int hitCount;

// Output Thread
static pthread_t findTheDotThread;
static void* FindTheDot_threadFunction(void* args);
static bool stopping;
static int sleepInMs = 10;
static int pressedSleepInMs = 100;

static void FindTheDot_generateDot();

void FindTheDot_init(void)
{
    hitCount = 0;
    FindTheDot_generateDot();

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

static void FindTheDot_hit()
{
    hitCount++;
    DigitDisplay_setDigit(hitCount);
    BuzzerPlayer_playSound(BUZZER_PLAYER_HIT);
    FindTheDot_generateDot();
}

static void FindTheDot_miss()
{
    BuzzerPlayer_playSound(BUZZER_PLAYER_MISS);
}


static void* FindTheDot_threadFunction(void* args)
{
    (void)args;
    while (!stopping && !LinuxToPru_isJoystickRight()) {
        if (!LinuxToPru_isJoystickDown()) {
            Utils_sleepForMs(sleepInMs);
            continue;
        }

        double x = Accelerometer_getX();
        double y = Accelerometer_getY();

        if (x - dotX < HIT_RANGE && dotX - x < HIT_RANGE && 
            y - dotY < HIT_RANGE && dotY - y < HIT_RANGE ) {
            FindTheDot_hit();
        } else {
            FindTheDot_miss();
        }

        Utils_sleepForMs(pressedSleepInMs);
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