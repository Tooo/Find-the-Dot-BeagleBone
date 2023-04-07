// shutdownManager.h
// Module to manage the shutdown of the application
#ifndef SHUTDOWN_H_
#define SHUTDOWN_H_

// Have main thread wait until trigger is called
void Shutdown_wait(void);

// Main thread continues once shutdown triggers
void Shutdown_trigger(void);

#endif