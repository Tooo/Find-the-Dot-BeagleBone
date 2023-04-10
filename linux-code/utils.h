// utils.h
// Module to manage files and commands
#ifndef UTILS_H_
#define UTILS_H_

#define BUFFER_MAX_LENGTH 1024

// Run the given Command
void Utils_runCommand(char* command);

// Read/write a file, given the file path + name and buffer
void Utils_readFile(char* fileName, char* buffer);
void Utils_writeFile(char* fileName, char* buffer);

void Utils_sleepForMs(long long delayInMs);

// I2C functions
int Utils_initI2cBus(char* bus, int address);
void Utils_writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);
unsigned char Utils_readI2cReg(int i2cFileDesc, unsigned char regAddr);
void Utils_readMultipleI2cReg(int i2cFileDesc, unsigned char startAddr, unsigned char* buffer, int size);

// Random functions
void Utils_randomInit();
double Utils_randomDouble();

#endif