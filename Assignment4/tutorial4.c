#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>

// gcc pthread.c -lpthread -o pthread

void* greet(void *id) {
    printf("Hello I am %ld\n", (intptr_t)id);
    pthread_exit((void*)0);
}

int main() {
    #define NUM 5
    int i;

    pthread_t threads[NUM];
    for (i=0; i<NUM; i++) {
        int status = pthread_create(threads + i, NULL, greet, (void*)((intptr_t)i));

        if (status != 0) {
            printf("Error creating thread");
            exit(1);
        }
    }

    for(i=0; i<NUM; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}