// System includes
#include <stdio.h>
#include <semaphore.h>

// App Includes
#include "semaphore/semaphore.h"
#include "data-creator/dataCreator.h"

// Main
int main(int argc, char *argv[])
{
    sem_t * semaphore = createSemaphore ();
    createSharedVariables ("test", 1000);
    
    getchar();

    removeSemaphore ();
    deleteSharedVariables ();

    return 0;
}
