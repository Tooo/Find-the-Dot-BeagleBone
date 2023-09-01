# Find the Dot BeagleBone
Find the dot by orientating your BeagleBone.
Align the Neopixel LED lights and shoot your shot.

## Pre-requisite
1. Install NeoPixel

## Installation
1. Clone the repository
```bash
(host)$ git clone https://github.com/Tooo/Find-the-Dot-BeagleBone.git
```

2. Make executable file on the host
```bash
(host)$ make
```

3. Run executable on the BeagleBone
```bash
(bbg)$ ./find_the_dot
```

## How to Play?
Find the Dot is a game where the player orientates the BeagleBone to locate the "dot". 
The Neopixel Lights will change LEDs and colours, depending on the locations of the dot.
If all the LED lights are on and they are blue, then you found the dot.
Press the joystick down to shoot the shot and the buzzer will play a sound.

### Orientation
| Direction | Orientation |
| :------ | :------ |
| Up | Neopixel side tilting up |
| Down | Beaglebone side tilting up |
| Left | Audio connectors side tilting up |
| Right | USB connections side tilting up |

### LED Lights
Up/Down
| Point is .. | LED Lights | 
| :------ | :------ |
| Up | LED lights on top half |
| Down | LED lights on bottom half |
| Centred | All LED lights on |

Left/Right
| Point is .. | LED Colour | 
| :------ | :------ |
| Left | Red |
| Right | Green |
| Centred | Blue |

### Quitting Game
Press right on the joystick.

## Hardware Features
- NeoPixel changes colours and LED lights based on location of dot.
- Accelerometer used to detect orientation of board.
- Joystick used to shoot and quit the game.
- 14-Seg Display displays number of times you hit the dot.
- PWM Buzzer plays sequences of soudns when you hit or miss the dot.
- PRU lighs the Neopixel and reads the joysticks

## Threads
| Threads | Purpose | 
| :------ | :------ |
| Main | Start other threads and waits for shutdown to cleanup |
| Accelormeter | Reads accelormeter values every 10ms |
| Buzzer Player | Plays buzzer notes when called to play |
| Digit Display | Change the LED Digit display to the correct number with changing memory of I2C |
| Terminal Output | Display terminal output of stats |
| Find the Dot | Main logics for game |
| PRU | lighs the Neopixel and reads the joysticks |
