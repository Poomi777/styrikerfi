#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int run_program(char *file_path, char *argv[]) {
    if (file_path == NULL) return 127; // return special error value if file path is NULL
    if (argv == NULL) argv = (char*[]){file_path, NULL}; //run program without arguments if argv is NULL

    pid_t pid = fork(); // create new process
    if (pid == 0) { // child process
        if (execvp(file_path, argv) == -1) {
            perror("execvp failed");
            return 127;
        }
    } else if (pid > 0) { // parent process
        int status;
        waitpid(pid, &status, 0); // wait for child process to exit
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        else {
            return 127;
        }
    } else { // fork failed
        perror("fork failed");
        return 127;
    }
}
