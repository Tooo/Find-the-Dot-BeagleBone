#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <time.h>

#include "utils.h"

void Utils_runCommand(char* command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");

    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[BUFFER_MAX_LENGTH];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL) {
            break;
        }
        // printf("--> %s", buffer); // Uncomment for debugging
    }

    // Get the exit code from pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command:  %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

void Utils_readFile(char* fileName, char* buffer)
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) {
        printf("ERROR: Unable to open %s.\n", fileName);
        exit(1);
    }

    fgets(buffer, BUFFER_MAX_LENGTH, pFile);

    fclose(pFile);
}

void Utils_writeFile(char* fileName, char* buffer)
{
    FILE *pFile = fopen(fileName, "w");
    if (pFile == NULL) {
        printf("ERROR: Unable to open %s.\n", fileName);
        exit(1);
    }

    int charWritten = fprintf(pFile, buffer);
    if (charWritten <= 0) {
        printf("ERROR: Cannot write %s.\n", fileName);
        exit(1);
    }

    fclose(pFile);
}

void Utils_sleepForMs(long long delayInMs)
{
	static const long long NS_PER_MS = 1000 * 1000;
	static const long long NS_PER_SECOND = 1000000000;

    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;

    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

int Utils_initI2cBus(char* bus, int address)
{
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(-1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("Unable to set I2C device to slave address.");
		exit(-1);
	}
	return i2cFileDesc;
}

void Utils_writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value)
{
	unsigned char buff[2];
	buff[0] = regAddr;
	buff[1] = value;
	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("Unable to write i2c register");
		exit(-1);
	}
}

unsigned char Utils_readI2cReg(int i2cFileDesc, unsigned char regAddr)
{
	// To read a register, must first write the address
	int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
	if (res != sizeof(regAddr)) {
		perror("Unable to write i2c register.");
		exit(-1);
	}

	// Now read the value and return it
	char value = 0;
	res = read(i2cFileDesc, &value, sizeof(value));
	if (res != sizeof(value)) {
		perror("Unable to read i2c register");
		exit(-1);
	}
	return value;
}

void Utils_readMultipleI2cReg(int i2cFileDesc, unsigned char startAddr, unsigned char* buffer, int size)
{
	// To read a register, must first write the address
	int res = write(i2cFileDesc, &startAddr, sizeof(startAddr));
	if (res != sizeof(startAddr)) {
		perror("Unable to write i2c register.");
		exit(-1);
	}

	// Now read the value and return it
	res = read(i2cFileDesc, buffer, sizeof(*buffer)*size);
	if (res != sizeof(*buffer)*size) {
		perror("Unable to read i2c register");
		exit(-1);
	}
}

void Utils_randomInit()
{
	time_t t;
	srand(time(&t));
}

double Utils_randomDouble()
{
	return (double) rand() / (double) RAND_MAX;
}