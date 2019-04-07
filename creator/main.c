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
    removeSemaphore ();
    
    createSharedVariables ("test", 1000);
    deleteSharedVariables ();

    return 0;
}
