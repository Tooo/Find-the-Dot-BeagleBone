#include <stdio.h>

#include "../linux-code/utils.h"
#include "../linux-code/buzzer.h"

int main(void)
{
    Buzzer_init();

    int noteTime = 500;

    Buzzer_playNote(BUZZER_NOTE_A, noteTime);
    Buzzer_playNote(BUZZER_NOTE_B, noteTime);
    Buzzer_playNote(BUZZER_NOTE_C, noteTime);
    Buzzer_playNote(BUZZER_NOTE_D, noteTime);
    Buzzer_playNote(BUZZER_NOTE_E, noteTime);
    Buzzer_playNote(BUZZER_NOTE_F, noteTime);
    Buzzer_playNote(BUZZER_NOTE_G, noteTime);

    Buzzer_cleanup();
}