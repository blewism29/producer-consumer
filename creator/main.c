// System includes
#include <stdio.h>
#include <semaphore.h>

// App Includes
#include "semaphore/semaphore.c"

// Main
int main(int argc, char *argv[])
{
    sem_t * semaphore = createSemaphore ();
    removeSemaphore ();
    return 0;
}
