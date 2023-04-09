OUTDIR = $(HOME)/cmpt433/public/myApps/test

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -pthread
LINUX_CODE = ../linux-code

all: test_folder test

test_folder: 
	mkdir -p $(OUTDIR)

TESTS = test_buzzer
test: $(TESTS)

TEST_BUZZER_FILES = $(LINUX_CODE)/utils.c $(LINUX_CODE)/buzzer.c test_buzzer.c
test_buzzer:
	$(CC_C) $(CFLAGS) $(TEST_BUZZER_FILES) -o $(OUTDIR)/test_buzzer
