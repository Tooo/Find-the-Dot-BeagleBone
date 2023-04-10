#!/bin/bash
# 1. Config in/out pins for PRU 
config-pin p8_12 pruout     # Control right-digit on 14-seg display
config-pin p8_15 pruin      # 

# Display something on 14-seg display:
# 2a. Enable I2C:
config-pin P9_18 i2c
config-pin P9_17 i2c

# 2b. Enable I2C chip & set pattern; Pick correct board
# ZEN CAPE GREEN:
#    i2cset -y 1 0x20 0x00 0x00
#    i2cset -y 1 0x20 0x01 0x00
#    i2cset -y 1 0x20 0x14 0x1E
#    i2cset -y 1 0x20 0x15 0x78
# ZEN CAPE RED
     i2cset -y 1 0x20 0x02 0x00
     i2cset -y 1 0x20 0x03 0x00
     i2cset -y 1 0x20 0x00 0x0f
     i2cset -y 1 0x20 0x01 0x5e

# 3. On target, compile PRU code (after copying to target):
#     make
#     On target, load compiled code:
#     make install_PRU0
