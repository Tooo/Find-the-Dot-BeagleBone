// system.h
// Module to manage files and commands
#ifndef SYSTEM_H_
#define SYSTEM_H_

#define BUFFER_MAX_LENGTH 1024

// Run the given Command
void System_runCommand(char* command);

// Read/write a file, given the file path + name and buffer
void System_readFile(char* fileName, char* buffer);
void System_writeFile(char* fileName, char* buffer);

void System_sleepForMs(long long delayInMs);

// I2C functions
int System_initI2cBus(char* bus, int address);
void System_writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);
unsigned char System_readI2cReg(int i2cFileDesc, unsigned char regAddr);
void System_readMultipleI2cReg(int i2cFileDesc, unsigned char startAddr, unsigned char* buffer, int size);

#endif