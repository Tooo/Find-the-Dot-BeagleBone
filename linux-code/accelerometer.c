#include <unistd.h>
#include <stdint.h>

#include "accelerometer.h"
#include "system.h"

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

// I2C file descriptor
static int i2cFileDesc;

// Accelerometer values
static int16_t x;
static int16_t y;
static int16_t z;

void Accelerometer_init(void)
{
    System_runCommand("config-pin P9_18 i2c");
    System_runCommand("config-pin P9_17 i2c");

    i2cFileDesc = System_initI2cBus(I2CDRV_LINUX_BUS1, I2C_ACCEL_ADDRESS);

    System_writeI2cReg(i2cFileDesc, REG_CTRL_REG1, 0x01);
}

void Accelerometer_cleanup(void)
{
    System_writeI2cReg(i2cFileDesc, REG_CTRL_REG1, 0x00);
    close(i2cFileDesc);
}

void Accelerometer_readAndCalculateValues(void)
{
    unsigned char buffer[ACCEL_REG_COUNT] = {};
    System_readMultipleI2cReg(i2cFileDesc, REG_STATUS, buffer, ACCEL_REG_COUNT);
    x = (buffer[REG_XMSB] << 8) | (buffer[REG_XLSB]);
    y = (buffer[REG_YMSB] << 8) | (buffer[REG_YLSB]);
    z = (buffer[REG_ZMSB] << 8) | (buffer[REG_ZLSB]);
}

int Accelerometer_getX(void)
{
    return x;
}

int Accelerometer_getY(void)
{
    return y;
}

int Accelerometer_getZ(void)
{
    return z;
}