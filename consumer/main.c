// System includes
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define SEMAPHORE_NAME "producer_consumer"

int* consumersCounterAddress;
int consumerCounterFile;

int protection = PROT_READ | PROT_WRITE;
int visibility = MAP_SHARED;


// Main
int main(int argc, char *argv[])
{
    // Open semaphore
    sem_t *sem = sem_open(SEMAPHORE_NAME, 0); /* Open a preexisting semaphore. */
    if (sem == SEM_FAILED) printf("ERROR | Couldn't open the semaphore\n");

    // mmap the files
    char name[1000] = "/tmp/consumers";
    consumerCounterFile = open(name, O_RDWR);
    if (consumerCounterFile < 0) printf("ERROR | Error while opening the consumers file %i\n", consumerCounterFile);

    consumersCounterAddress = mmap(NULL, sizeof(int), protection, visibility, consumerCounterFile, 0);
    if (consumersCounterAddress == MAP_FAILED) printf("DEBUG | consumer address\n");

    *consumersCounterAddress = 3;
    
    printf("DEBUG | Reading mmap position %i \n", *consumersCounterAddress);
    
    return 0;
}
