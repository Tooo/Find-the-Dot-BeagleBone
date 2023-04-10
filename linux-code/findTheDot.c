#include <pthread.h>
#include <stdbool.h>

#include "findTheDot.h"
#include "shutdown.h"

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

static void* FindTheDot_threadFunction(void* args)
{
    (void)args;
    while (!stopping) {

    }
    Shutdown_trigger();
    return NULL;
}