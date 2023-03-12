#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alloca.h>

#include "multi_mutex.h"

int multi_mutex_unlock(pthread_mutex_t **mutexv)
{
    (void) mutexv;
    return 0;
}

int multi_mutex_trylock(pthread_mutex_t **mutexv)
{
    (void) mutexv;
    return 0;
}

// Just for optional bonus points
// Blocks until all mutexes are available, making sure that no deadlocks can occur,
// i.e. no mutex may be held while blocking
int multi_mutex_lock(pthread_mutex_t **mutexv)
{
    (void) mutexv;
    return 0;
}

