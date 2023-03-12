#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alloca.h>

#include "multi_mutex.h"

int multi_mutex_unlock(pthread_mutex_t **mutexv)
{
    if (mutexv == NULL) {
        return -1;
    }

    int i = 0;

    while (mutexv[i] != NULL) {
        int returner = pthread_mutex_unlock(mutexv[i]);

        if (returner != 0) {
            return -1;
        }
        i++;
    }
}

int multi_mutex_trylock(pthread_mutex_t **mutexv)
{
    if (mutexv == NULL) {
        return -1;
    }

    int i = 0;
    int acquired = 0;

    while (mutexv[i] != NULL) {
        int returner = pthread_mutex_trylock(mutexv[i]);

        if (returner != 0) {
            multi_mutex_unlock(mutexv, i);
            return -1;
        }

        i++;
        acquired++;
    }
}

// Just for optional bonus points
// Blocks until all mutexes are available, making sure that no deadlocks can occur,
// i.e. no mutex may be held while blocking
int multi_mutex_lock(pthread_mutex_t **mutexv)
{
    if (mutexv == NULL) {
        return -1;
    }

    int i = 0;
    int acquired = 0;
    int backoff = 1;

    struct timespec ts;

    while (mutexv[i] != NULL) {
        int returner = pthread_mutex_trylock(mutexv[i]);

        if (returner != 0) {
            multi_mutex_unlock(mutexv, i);
            acquired = 0;


            ts.tv_sec = 0;
            ts.tv_nsec = (backoff * (rand() % MAX_BACKOFF_MS)) * 1000000;
            nanosleep(&ts, NULL);

            backoff = (backoff < MAX_BACKOFF_MS) ? (backoff * 2) : MAX_BACKOFF_MS;
        }

        else {
            i++;
            acquired++;
        }
    }
}

