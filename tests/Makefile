OUTDIR = $(HOME)/cmpt433/public/myApps/test

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -pthread
LINUX_CODE = ../linux-code

all: test_folder test

test_folder: 
	mkdir -p $(OUTDIR)

TESTS = test_buzzer test_buzzerPlayer test_digitDisplay
test: $(TESTS)

TEST_BUZZER_FILES = $(LINUX_CODE)/utils.c $(LINUX_CODE)/buzzer.c test_buzzer.c
test_buzzer:
	$(CC_C) $(CFLAGS) $(TEST_BUZZER_FILES) -o $(OUTDIR)/test_buzzer

TEST_BUZZER_PLAYER_FILES = $(LINUX_CODE)/utils.c $(LINUX_CODE)/buzzer.c $(LINUX_CODE)/buzzerPlayer.c test_buzzerPlayer.c
test_buzzerPlayer:
	$(CC_C) $(CFLAGS) $(TEST_BUZZER_PLAYER_FILES) -o $(OUTDIR)/test_buzzerPlayer

TEST_DIGIT_DISPLAY_FILES = $(LINUX_CODE)/utils.c $(LINUX_CODE)/digitDisplay.c test_digitDisplay.c
test_digitDisplay:
	$(CC_C) $(CFLAGS) $(TEST_DIGIT_DISPLAY_FILES) -o $(OUTDIR)/test_digitDisplay