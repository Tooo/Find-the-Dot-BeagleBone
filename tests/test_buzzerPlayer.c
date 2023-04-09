#include <stdio.h>

#include "../linux-code/utils.h"
#include "../linux-code/buzzer.h"
#include "../linux-code/buzzerPlayer.h"

int main(void)
{
    Buzzer_init();
    BuzzerPlayer_init();

    int input = -1;
    while (input != 2) {
        printf("Play Hit - 0, Miss - 1, Stop - 2: ");
        scanf("%d", &input);
        BuzzerPlayer_playSound(input);
    }

    BuzzerPlayer_cleanup();
    Buzzer_cleanup();
}