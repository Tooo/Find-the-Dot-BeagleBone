#include <pthread.h>
#include <stdbool.h>

#include "buzzerPlayer.h"
#include "buzzer.h"

// Output Thread
static pthread_t buzzerThread;
static void* BuzzerPlayer_threadFunction(void* args);
static bool stopping;

#define SOUND_LENGTH 5
#define SOUND_ARG_LENGTH 2

static int (*currentSound)[SOUND_ARG_LENGTH];
static int playIndex;
static bool newSound;

// Pattern for hit
static int hitSound[SOUND_LENGTH][SOUND_ARG_LENGTH] = {
    {(int)BUZZER_NOTE_A, 500}, 
    {(int)BUZZER_NOTE_B, 500}, 
    {(int)BUZZER_NOTE_C, 500}, 
    {(int)BUZZER_NOTE_D, 500},
    {(int)BUZZER_NOTE_D, 500}
};

// Pattern for miss
static int missSound[SOUND_LENGTH][SOUND_ARG_LENGTH] = {
    {(int)BUZZER_NOTE_D, 500}, 
    {(int)BUZZER_NOTE_A, 500}, 
    {(int)BUZZER_NOTE_D, 500}, 
    {(int)BUZZER_NOTE_A, 500},
    {(int)BUZZER_NOTE_D, 500}
};

void BuzzerPlayer_init(void)
{
    stopping = false;
    playIndex = SOUND_LENGTH;
    newSound = false;
    pthread_create(&buzzerThread, NULL, &BuzzerPlayer_threadFunction, NULL);
}

void BuzzerPlayer_cleanup(void)
{
    stopping = true;
    pthread_join(buzzerThread, NULL);
}

void BuzzerPlayer_playSound(BuzzerPlayerEnum sound)
{
    if (sound == BUZZER_PLAYER_HIT) {
        currentSound = hitSound;
    } else if (sound == BUZZER_PLAYER_MISS) {
        currentSound = missSound;
    }
    newSound = true;
    playIndex = 0;
}

static void* BuzzerPlayer_threadFunction(void* args)
{
    (void)args;
    while (!stopping) {
        while (playIndex < SOUND_LENGTH) {
            Buzzer_playNote(currentSound[playIndex][0], currentSound[playIndex][1]);
            
            if (!newSound) {
                playIndex++;
            } else {
                newSound = false;
            }
        }
    }
    return NULL;
}