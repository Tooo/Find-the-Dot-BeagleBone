#include "buzzer.h"
#include "utils.h"
#include <stdio.h>

// Buzzer files
static char* periodFile = "/dev/bone/pwm/0/a/period";
static char* dutyCycleFile = "/dev/bone/pwm/0/a/duty_cycle";
static char* enableFile = "/dev/bone/pwm/0/a/enable";

// Obtain values in pages.mtu.edu/~suits/notefreqs.html
static double notes[BUZZER_NOTE_COUNT] = {220, 246.94, 261.63, 293.66, 329.63, 349.23, 392};

void Buzzer_init(void)
{
    Utils_runCommand("config-pin P9_22 pwm");
}

void Buzzer_cleanup(void)
{
    // To confirm the buzzer is not playing
    Utils_writeFile(enableFile, "0");
}

void Buzzer_play(int period, int dutyCycle, int timeInMs)
{
    char periodStr[BUFFER_MAX_LENGTH];
    snprintf(periodStr, BUFFER_MAX_LENGTH, "%d", period);
    Utils_writeFile(periodFile, periodStr);

    char dutyCycleStr[BUFFER_MAX_LENGTH];
    snprintf(dutyCycleStr, BUFFER_MAX_LENGTH, "%d", dutyCycle);
    Utils_writeFile(dutyCycleFile, dutyCycleStr);
    Utils_writeFile(enableFile, "1");

    Utils_sleepForMs(timeInMs);

    Utils_writeFile(enableFile, "0");
}

void Buzzer_playNote(BuzzerNoteId noteId, int timeInMs)
{
    int nsPerS = 1000000000;
    double hz = notes[noteId];
    int period = nsPerS*(1/hz);
    int dutyCycle = period/2;

    Buzzer_play(period, dutyCycle, timeInMs);
}