// File header
#include "dataCreator.h"

// Ssystem includes
#include <sys/mman.h>
#include <stdio.h>
#include <stddef.h>

int protection = PROT_READ | PROT_WRITE;
int visibility = MAP_SHARED;

char* bufferAddress;
char* consumersCounterAddress;
char* producersCounterAddress;
char* globalStopFlagAddress;

// void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
void createBuffer (char * pName, size_t pSize) {
    printf("DEBUG | Creating shared buffer\n");
    bufferAddress = mmap(NULL, pSize, protection, visibility, -1, 0);
}

void createCounters () {
    printf("DEBUG | Creating shared counters\n");
    consumersCounterAddress = mmap(NULL, sizeof(int), protection, visibility, -1, 0);
    producersCounterAddress = mmap(NULL, sizeof(int), protection, visibility, -1, 0);
}

void createGlobalFlags () {
    printf("DEBUG | Creating shared flags\n");
    globalStopFlagAddress = mmap(NULL, sizeof(int), protection, visibility, -1, 0);
}

void createSharedVariables (char * pName, size_t pSize) {
    //createBuffer (pName, pSize);
    createCounters ();
    createGlobalFlags ();
}

void deleteSharedVariables () {  
    printf("DEBUG | Deleting shared variables\n");  
    munmap(bufferAddress, 0);
    munmap(consumersCounterAddress, 0);
    munmap(producersCounterAddress, 0);
    munmap(globalStopFlagAddress, 0);
}
