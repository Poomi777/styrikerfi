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
            return -1
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
    int success = 1;

    while (mutexv[i] != NULL && success) {
        int returner = pthread_mutex_trylock(mutexv[i]);

        if (returner != 0) {
            multi_mutex_unlock(mutexv);
            success = 0;
        }

        i++;
    }

    if (!success) {
        return -1;
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
    int number_of_mutexes = 0;
    int success = 1;

    while (mutexv[number_of_mutexes] != NULL) {
        number_of_mutexes++;
    }

    while (i < number_of_mutexes && success) {
        if (i > 0) {
            int j = i-1;

            while (j >= 0) {
                int returner = pthread_mutex_unlock(mutexv[j]);

                if (returner != 0) {
                    multi_mutex_unlock(mutexv);
                    success = 0;
                    break;
                }

                j--;
            }
        }

        if (!success) {
            break;
        }

        int returner = pthread_mutex_lock(mutexv[i]);

        if (returner != 0) {
            success = 0;
        }

        i++;
    }

    if (!success) {

        int j = i-1;

        while (j >= 0) {
            int returner = pthread_mutex_unlock(mutexv[j]);

            if (returner != 0) {
                return -1;
            }

            j--;
        }

        return -1;
    }
}

