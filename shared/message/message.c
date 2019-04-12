// File header
#include "message.h"

// System includes
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct message {
    int producerId;
    time_t createdAt;
    int key;
};