// File header
#include "semaphore.h"

// System includes
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>

#define SEMAPHORE_NAME "producer_consumer"

sem_t * semaphore;

sem_t * createSemaphore () {
    printf("DEBUG | Creating semaphore\n");
    if (NULL == semaphore) semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, S_IRWXO, 0);
    if (semaphore == SEM_FAILED) printf("Error | Error while creating the semaphore.\n");
    return semaphore;
}

void removeSemaphore () {
    printf("DEBUG | Removing semaphore\n");
    int result = sem_unlink(SEMAPHORE_NAME);
    if (result == -1) printf("Error | Error occurred while unlinking the semaphore\n");
}