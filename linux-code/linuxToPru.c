#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "linuxToPru.h"
#include "utils.h"
#include "sharedGameStruct.h"

// General PRU Memomry Sharing Routine
// ----------------------------------------------------------------
#define PRU_ADDR      0x4A300000   // Start of PRU memory Page 184 am335x TRM
#define PRU_LEN       0x80000      // Length of PRU memory
#define PRU0_DRAM     0x00000      // Offset to DRAM
#define PRU1_DRAM     0x02000
#define PRU_SHAREDMEM 0x10000      // Offset to shared memory
#define PRU_MEM_RESERVED 0x200     // Amount used by stack and heap

// Convert base address to each memory section
#define PRU0_MEM_FROM_BASE(base) ( (base) + PRU0_DRAM + PRU_MEM_RESERVED)
#define PRU1_MEM_FROM_BASE(base) ( (base) + PRU1_DRAM + PRU_MEM_RESERVED)
#define PRUSHARED_MEM_FROM_BASE(base) ( (base) + PRU_SHAREDMEM)

static volatile void *pPruBase;
static volatile sharedMemStruct_t *pSharedPru0;


// Return the address of the PRU's base memory
volatile void* getPruMmapAddr(void)
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        perror("ERROR: could not open /dev/mem");
        exit(EXIT_FAILURE);
    }

    // Points to start of PRU memory.
    volatile void* pPruBaseLocal = mmap(0, PRU_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, PRU_ADDR);
    if (pPruBase == MAP_FAILED) {
        perror("ERROR: could not map memory");
        exit(EXIT_FAILURE);
    }
    close(fd);

    return pPruBaseLocal;
}

void freePruMmapAddr(volatile void* pPruBaseLocal)
{
    if (munmap((void*) pPruBaseLocal, PRU_LEN)) {
        perror("PRU munmap failed");
        exit(EXIT_FAILURE);
    }
}

void LinuxToPru_init(void)
{
    Utils_runCommand("config-pin p8_15 pruin");
    Utils_runCommand("config-pin p8_16 pruin");
    Utils_runCommand("config-pin p8_11 pruout");
    pPruBase = getPruMmapAddr();
    pSharedPru0 = PRU0_MEM_FROM_BASE(pPruBase);
}

void LinuxToPru_cleanup(void)
{
    freePruMmapAddr(pPruBase);
}

void LinuxToPru_setNeoPixel(uint8_t *colors)
{
    for (int i = 0; i < NUM_OF_LEDS; i++)
    {
        pSharedPru0->neoLeds[i] = colors[i];
    }
}

bool LinuxToPru_isJoystickDown(void)
{
    return !pSharedPru0->joystickDownPressed;
}

bool LinuxToPru_isJoystickRight(void)
{
    return !pSharedPru0->joystickRightPressed;
}
