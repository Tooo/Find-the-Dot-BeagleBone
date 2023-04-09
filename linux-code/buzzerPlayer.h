// buzzerPlayer.h
// Module to manage the Buzzer thread
#ifndef BUZZER_PLAYER_H_
#define BUZZER_PLAYER_H_

// Buzzer sounds
typedef enum {
    BUZZER_PLAYER_HIT = 0,
    BUZZER_PLAYER_MISS,
    BUZZER_PLAYER_COUNT,
} BuzzerPlayerEnum;

// Initialize/cleanup the module's data structures.
void BuzzerPlayer_init(void);
void BuzzerPlayer_cleanup(void);

void BuzzerPlayer_playSound(BuzzerPlayerEnum sound);

#endif