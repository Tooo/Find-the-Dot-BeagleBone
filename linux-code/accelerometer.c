#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

#include "accelerometer.h"
#include "utils.h"

// I2c bus and address
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2C_ACCEL_ADDRESS 0x1C

// I2C values for accelerometer
#define REG_CTRL_REG1 0x2A

#define REG_STATUS    0x00
#define REG_XMSB      0x01
#define REG_XLSB      0x02
#define REG_YMSB      0x03
#define REG_YLSB      0x04
#define REG_ZMSB      0x05
#define REG_ZLSB      0x06

#define ACCEL_REG_COUNT 7
#define MAX_ACCEL_READ ((float)((1 << 15) - 1)/2)

// I2C file descriptor
static int i2cFileDesc;

// Accelerometer values
static double x;
static double y;
static double z;

// Accelerometer Thread
static pthread_t accelerometerThread;
static void* Accelerometer_threadFunction(void* args);
static bool stopping;
static int threadSleepMs = 10;

void Accelerometer_init(void)
{
    Utils_runCommand("config-pin P9_18 i2c");
    Utils_runCommand("config-pin P9_17 i2c");

    i2cFileDesc = Utils_initI2cBus(I2CDRV_LINUX_BUS1, I2C_ACCEL_ADDRESS);

    Utils_writeI2cReg(i2cFileDesc, REG_CTRL_REG1, 0x01);

    stopping = false;
    pthread_create(&accelerometerThread, NULL, &Accelerometer_threadFunction, NULL);
}

void Accelerometer_cleanup(void)
{
    stopping = true;
    pthread_join(accelerometerThread, NULL);

    Utils_writeI2cReg(i2cFileDesc, REG_CTRL_REG1, 0x00);
    close(i2cFileDesc);
}

void Accelerometer_readAndCalculateValues(void)
{
    unsigned char buffer[ACCEL_REG_COUNT] = {};
    Utils_readMultipleI2cReg(i2cFileDesc, REG_STATUS, buffer, ACCEL_REG_COUNT);
    int16_t x_int = (buffer[REG_XMSB] << 8) | (buffer[REG_XLSB]);
    int16_t y_int = (buffer[REG_YMSB] << 8) | (buffer[REG_YLSB]);
    int16_t z_int = (buffer[REG_ZMSB] << 8) | (buffer[REG_ZLSB]);

	x = x_int / MAX_ACCEL_READ;
	y = y_int / MAX_ACCEL_READ;
	z = z_int / MAX_ACCEL_READ;
}

double Accelerometer_getX(void)
{
    return x;
}

double Accelerometer_getY(void)
{
    return y;
}

double Accelerometer_getZ(void)
{
    return z;
}

static void* Accelerometer_threadFunction(void* args)
{
    (void)args;
    while (!stopping) {
        Accelerometer_readAndCalculateValues();
        Utils_sleepForMs(threadSleepMs);
    }
    return NULL;
}