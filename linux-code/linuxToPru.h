// linuxToPru.h
// Module to manage files and commands
#ifndef LINUX_TO_PRU_H_
#define LINUX_TO_PRU_H_

#include <stdbool.h>

// Initialize/cleanup the module's data structures.
void LinuxToPru_init(void);
void LinuxToPru_cleanup(void);

bool LinuxToPru_isJoystickDown(void);
bool LinuxToPru_isJoystickRight(void);

#endif