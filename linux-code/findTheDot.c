#include <pthread.h>
#include <stdbool.h>

#include "findTheDot.h"
#include "shutdown.h"
#include "utils.h"
#include "accelerometer.h"
#include "buzzerPlayer.h"
#include "digitDisplay.h"
#include "linuxToPru.h"
#include "neoPixel.h"

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
    dotX = Utils_randomDouble() * RANDOM_MAX - RANDOM_RANGE;
    dotY = Utils_randomDouble() * RANDOM_MAX - RANDOM_RANGE;
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

static void FindTheDot_updateNeo()
{
    XLedEnum xEnum = FindTheDot_getXLedEnum();
    YLedEnum yEnum = FindTheDot_getYLedEnum();
    NeoPixel_setLeds(xEnum, yEnum);
}

static void* FindTheDot_threadFunction(void* args)
{
    (void)args;
    while (!stopping && !LinuxToPru_isJoystickRight()) {
        FindTheDot_updateNeo();
        if (!LinuxToPru_isJoystickDown()) {
            Utils_sleepForMs(sleepInMs);
            continue;
        }

        XLedEnum xEnum = FindTheDot_getXLedEnum();
        YLedEnum yEnum = FindTheDot_getYLedEnum();

        if (xEnum == X_CENTRE && yEnum == Y_CENTRE) {
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

int FindTheDot_getHitCount()
{
    return hitCount;
}

XLedEnum FindTheDot_getXLedEnum()
{
    double x = Accelerometer_getX();

    if (x - dotX > HIT_RANGE) {
        return X_LEFT;
    } else if (dotX - x > HIT_RANGE) {
        return X_RIGHT;
    } else {
        return X_CENTRE;
    }
}

YLedEnum FindTheDot_getYLedEnum()
{
    double y = Accelerometer_getY();

    for (int i = 5; i >= 0; i--) {
        if (dotY - y > HIT_RANGE*i) {
            return Y_CENTRE - i;
        }

        if (y - dotY > HIT_RANGE*i) {
            return Y_CENTRE + i;
        }

    }

    return Y_CENTRE;
}