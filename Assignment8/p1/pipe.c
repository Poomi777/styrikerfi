// This changes the way some includes behave.
// This should stay before any include.
#define _GNU_SOURCE

#include "pipe.h"
#include <sys/wait.h> /* For waitpid */
#include <unistd.h> /* For fork, pipe */
#include <stdlib.h> /* For exit */
#include <fcntl.h>
#include <errno.h>

int run_program(char *argv[])
{

    if (argv == NULL) {
        return -1;
    }

    // -------------------------
    // TODO: Open a pipe
    // -------------------------
    int pipe_fileDescript[2];
    
    if (pipe2(pipe_fileDescript, O_CLOEXEC) == -1) {
        return -1;
    }

    int child_pid = fork();
    if (child_pid == -1) {
        close(pipe_fileDescript[0]);
        close(pipe_fileDescript[1]);
        return -1;
    } 
    
    else if (child_pid == 0) {
        close(pipe_fileDescript[0]);

        // Replace program
        execvp(argv[0], argv);

        // -------------------------
        // TODO: Write the error on the pipe
        // -------------------------
        int exec_errno = errno;
        write(pipe_fileDescript[1], &exec_errno, sizeof(exec_errno));


        exit(0);
    } 
    
    else {
        close(pipe_fds[1]);

        int status, hadError = 0;

        int waitError = waitpid(child_pid, &status, 0);
        if (waitError == -1) {
            // Error while waiting for child.
            hadError = 1;
        } 
        
        else if (!WIFEXITED(status)) {
            // Our child exited with another problem (e.g., a segmentation fault)
            // We use the error code ECANCELED to signal this.
            hadError = 1;
            errno = ECANCELED;
        } 
        
        else {
            // -------------------------
            // TODO: If there was an execvp error in the child, set errno
            //       to the value execvp set it to.
            // -------------------------

            int child_errno;
            
            if (read(pipe_fileDescript[0], &child_errno, sizeof(child_errno)) == sizeof(child_errno)) {
                errno = child_errno;
                hadError = 1;
            }
        }
        close(pipe_fileDescript[0]);


        return hadError ? -1 : WEXITSTATUS(status);
    }
}
