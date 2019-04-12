// File header
#include "dataCreator.h"

// Ssystem includes
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int protection = PROT_READ | PROT_WRITE;
int visibility = MAP_SHARED;

void* bufferAddress;
void* consumersCounterAddress;
void* producersCounterAddress;
void* globalStopFlagAddress;

int bufferFile;
int consumerCounterFile;
int producerCounterFile;
int globalStopFlagFile;

char* filesPreffix = "/tmp/";

// void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
void createBuffer (char * pName, size_t pSize) {
    printf("DEBUG | Creating shared buffer\n");
    
    char parsedName [1000]; 
    strcpy(parsedName, filesPreffix);
    strcat(parsedName, pName);

    printf("DEBUG | parsedName = %s\n", parsedName);
    
    bufferFile = open(parsedName, O_RDWR | O_CREAT);
    if (bufferFile < 0) printf("ERROR | Error while opening the buffer file %i\n", bufferFile);
    
    bufferAddress = mmap(NULL, pSize, protection, visibility, bufferFile, 0);
    if (bufferAddress == MAP_FAILED) printf("ERROR | Buffer address map failed\n");
}

void createCounters () {
    printf("DEBUG | Creating shared counters\n");

    char parsedName [1000]; 
    strcpy(parsedName, filesPreffix);
    strcat(parsedName, "consumers");

    printf("DEBUG | parsedName = %s\n", parsedName);
    
    consumerCounterFile = open(parsedName, O_RDWR | O_CREAT);
    if (consumerCounterFile < 0) printf("ERROR | Error while opening the consumers file %i\n", consumerCounterFile);

    //ftruncate(consumerCounterFile, sizeof(int));

    consumersCounterAddress = mmap(NULL, sizeof(int), protection, visibility, consumerCounterFile, 0);
    if (consumersCounterAddress == MAP_FAILED) printf("ERROR | Consumer address map failed\n");

    ssize_t s = write(STDOUT_FILENO, consumersCounterAddress, sizeof(int));

    producersCounterAddress = mmap(NULL, sizeof(int), protection, visibility, -1, 0);
    if (producersCounterAddress == MAP_FAILED) printf("ERROR | Producer address map failed\n");
}

void createGlobalFlags () {
    printf("DEBUG | Creating shared flags\n");
    globalStopFlagAddress = mmap(NULL, sizeof(int), protection, visibility, -1, 0);
    if (globalStopFlagAddress == MAP_FAILED) printf("ERROR | Global stop flag address map failed\n");
}

void createSharedVariables (char * pName, size_t pSize) {
    createBuffer (pName, pSize);
    createCounters ();
    createGlobalFlags ();
}

void deleteSharedVariables () {  
    printf("DEBUG | Deleting shared variables\n");

    close(bufferFile);
    close(consumerCounterFile);

    munmap(bufferAddress, 0);
    munmap(consumersCounterAddress, 0);
    munmap(producersCounterAddress, 0);
    munmap(globalStopFlagAddress, 0);
}
