// accelerometer.h
// Module to manage the accelerometer
#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

// Axis count
#define AXIS_COUNT 3

// Initialize/cleanup the module's data structures.
void Accelerometer_init(void);
void Accelerometer_cleanup(void);

// Read file and convert to X, Y, Z
void Accelerometer_readAndCalculateValues(void);

// Get values from accelerometer.
int Accelerometer_getX(void);
int Accelerometer_getY(void);
int Accelerometer_getZ(void);

#endif