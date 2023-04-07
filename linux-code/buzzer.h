// buzzer.h
// Module to manage the Buzzer
#ifndef BUZZER_H_
#define BUZZER_H_

typedef enum {
    BUZZER_NOTE_A = 0,
    BUZZER_NOTE_B,
    BUZZER_NOTE_C,
    BUZZER_NOTE_D,
    BUZZER_NOTE_E,
    BUZZER_NOTE_F,
    BUZZER_NOTE_G,
    BUZZER_NOTE_COUNT
} BuzzerNoteId;

// Initialize/cleanup the module's data structures.
void Buzzer_init(void);
void Buzzer_cleanup(void);

void Buzzer_play(int period, int dutyCycle, int timeInMs);
void Buzzer_playNote(BuzzerNoteId noteId, int timeInMs);

#endif