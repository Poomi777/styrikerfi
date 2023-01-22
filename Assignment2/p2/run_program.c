#include "run_program.h"
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*remember to check out https://man7.org/linux/man-pages/man3/exec.3.html*/

#define ERROR_CODE 127

int run_program(char *file_path, char *argv[])
{
    int command = fork();

    if (file_path == NULL) {
        return ERROR_CODE;
    }

    else {
        execvp(file_path, argv);
    }

    return ERROR_CODE;



    // remember to return ERROR_CODE on error.
}
