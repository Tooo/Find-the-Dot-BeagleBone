// main.c
// Main Thread of BeatBox program
#include <stdio.h>

#include "shutdown.h"
#include "system.h"

// Initialize/cleanup the module's data structures.
static void main_init(void);
static void main_cleanup(void);

int main(void)
{
    main_init();
    Shutdown_wait();
    main_cleanup();
    return 0;
}

static void main_init(void)
{

}

static void main_cleanup(void)
{

}