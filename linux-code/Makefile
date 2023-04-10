OUTFILE = find_the_dot
OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -pthread
CFILES = main.c findTheDot.c accelerometer.c buzzer.c buzzerPlayer.c shutdown.c utils.c digitDisplay.c output.c

all: find_the_dot

find_the_dot:
	$(CC_C) $(CFLAGS) $(CFILES) -o $(OUTDIR)/$(OUTFILE)
