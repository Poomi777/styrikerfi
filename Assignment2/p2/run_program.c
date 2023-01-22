#include "run_program.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*remember to check out https://man7.org/linux/man-pages/man3/exec.3.html*/

#define ERROR_CODE 127

int run_program(char *file_path, char *argv[])
{
    pid_t pid = fork();

    if (file_path == NULL) {
        return ERROR_CODE;
    }

    if (pid == 0) {
        if (argv == NULL) {
            execlp(file_path, file_path, NULL);
        }
        
        else {
            execvp(file_path, argv);
        }
        exit(ERROR_CODE);
    }

    // remember to return ERROR_CODE on error.
    else {
        return ERROR_CODE;
    }
    /*return ERROR_CODE;*/




}
