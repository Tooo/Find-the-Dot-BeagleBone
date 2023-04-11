#include <unistd.h>

#include "neoPixel.h"
#include "linuxToPru.h"
#include "sharedGameStruct.h"

// Colors used for LED
neoColors xColor[X_COUNT] = {
    RED,
    BLUE,
    GREEN
};

// Bright Colors used for LED
neoColors xColorBright[X_COUNT] = {
    RED_BRIGHT,
    BLUE_BRIGHT,
    GREEN_BRIGHT
};

// Enum for LED Brightness
typedef enum {
    LED_OFF,
    LED_BRIGHT,
    LED_DIM,
    LED_COUNT
} LedBrightnessEnum;

// Up 5 Array
LedBrightnessEnum up5Array[NUM_OF_LEDS] = {
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_DIM,
};

// Up 4 Array
LedBrightnessEnum up4Array[NUM_OF_LEDS] = {
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_DIM,
    LED_BRIGHT,
};

// Up 3 Array
LedBrightnessEnum up3Array[NUM_OF_LEDS] = {
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_DIM,
    LED_BRIGHT,
    LED_DIM,
};


// Up 2 Array
LedBrightnessEnum up2Array[NUM_OF_LEDS] = {
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_DIM,
    LED_BRIGHT,
    LED_DIM,
    LED_OFF,
};

// Up Array
LedBrightnessEnum upArray[NUM_OF_LEDS] = {
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_DIM,
    LED_BRIGHT,
    LED_DIM,
    LED_OFF,
    LED_OFF,
};

// Centre Array
LedBrightnessEnum centreArray[NUM_OF_LEDS] = {
    LED_DIM,
    LED_DIM,
    LED_DIM,
    LED_DIM,
    LED_DIM,
    LED_DIM,
    LED_DIM,
    LED_DIM,
};

// Down Array
LedBrightnessEnum downArray[NUM_OF_LEDS] = {
    LED_OFF,
    LED_OFF,
    LED_DIM,
    LED_BRIGHT,
    LED_DIM,
    LED_OFF,
    LED_OFF,
    LED_OFF,
};

// Down 2 Array
LedBrightnessEnum down2Array[NUM_OF_LEDS] = {
    LED_OFF,
    LED_DIM,
    LED_BRIGHT,
    LED_DIM,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
};

// Down 3 Array
LedBrightnessEnum down3Array[NUM_OF_LEDS] = {
    LED_DIM,
    LED_BRIGHT,
    LED_DIM,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
};

// Down 4 Array
LedBrightnessEnum down4Array[NUM_OF_LEDS] = {
    LED_BRIGHT,
    LED_DIM,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
};

// Down 5 Array
LedBrightnessEnum down5Array[NUM_OF_LEDS] = {
    LED_DIM,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
    LED_OFF,
};

// Led Arrays
LedBrightnessEnum* ledArrays[Y_COUNT] = {
    up5Array,
    up4Array,
    up3Array,
    up2Array,
    upArray,
    centreArray,
    downArray,
    down2Array,
    down3Array,
    down4Array,
    down5Array,
};

void NeoPixel_setLeds(XLedEnum xEnum, YLedEnum yEnum)
{
    LedBrightnessEnum* leds = ledArrays[yEnum];
    uint8_t colors[NUM_OF_LEDS];
    for (int i = 0; i < NUM_OF_LEDS; i++) {
        LedBrightnessEnum led = leds[i];
        if (led == LED_BRIGHT) {
            colors[i] = xColorBright[xEnum];
        } else if (led == LED_DIM) {
            colors[i] = xColor[xEnum];
        } else {
            colors[i] = OFF;
        }
    }
    LinuxToPru_setNeoPixel(colors);
}