#include <pthread.h>
#include <stdbool.h>

#include "buzzerPlayer.h"
#include "buzzer.h"

// Output Thread
static pthread_t buzzerThread;
static void* BuzzerPlayer_threadFunction(void* args);
static bool stopping;

void BuzzerPlayer_init(void)
{
    stopping = false;
    pthread_create(&buzzerThread, NULL, &BuzzerPlayer_threadFunction, NULL);
}

void BuzzerPlayer_cleanup(void)
{
    stopping = true;
    pthread_join(buzzerThread, NULL);
}

static void* BuzzerPlayer_threadFunction(void* args)
{
    (void)args;
    while (!stopping) {

    }
    return NULL;
}