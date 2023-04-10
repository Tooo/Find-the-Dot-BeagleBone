#ifndef _SHARED_DATA_STRUCT_H_
#define _SHARED_DATA_STRUCT_H_

#include <stdbool.h>
#include <stdint.h>


// WARNING:
// Fields in the struct must be aligned to match ARM's alignment
//    bool/char, uint8_t:   byte aligned
//    int/long,  uint32_t:  word (4 byte) aligned
//    double,    uint64_t:  dword (8 byte) aligned
// Add padding fields (char _p1) to pad out to alignment.

// My Shared Memory Structure
// ----------------------------------------------------------------
typedef struct {
    // 1 byte
    bool isLedOn;
    // 1 byte
    bool isButtonPressed;
    
    
    // 2 byte short (2 byte aligned)
    _Alignas(uint16_t) short smileCount;

    // // Padding
    // char _p0;
    // char _p1, _p2, _p3;

    // Must be dword aligned (multiple of 8)
    _Alignas(8) uint64_t numMsSinceBigBang;             // Works!
    // _Alignas(uint64_t) uint64_t numMsSinceBigBang;      // Fails!
    
} sharedMemStruct_t;

#endif
