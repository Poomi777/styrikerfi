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
    int status;

    if (file_path == NULL) {
        return ERROR_CODE;
    }

    if (pid == 0) {
        if (execvp(file_path, argv) == -1) {
            return ERROR_CODE;
        }
    }
/* WIFEXITED https://www.ibm.com/docs/en/ztpf/1.1.0.15?topic=zca-wifexitedquery-status-see-if-child-process-ended-normally*/
/* WEXITSTATUS https://www.ibm.com/docs/en/ztpf/1.1.0.15?topic=apis-wexitstatusobtain-exit-status-child-process*/
/* waitpid https://www.ibm.com/docs/en/ztpf/1.1.0.15?topic=apis-waitpidobtain-status-information-from-child-process*/


    else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        else {
            return ERROR_CODE;
        }

    }

    // remember to return ERROR_CODE on error.
    else {
        return ERROR_CODE;
    }
    /*return ERROR_CODE;*/




}
