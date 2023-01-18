#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

//gcc child.c -o child
// ./child

int main(){
    pid_t pid;

    switch( (pid = fork()) ){
        case -1:
        printf("Error. Fork failed\n");
        break;

        case 0:
        printf("I am the child.\n");

        default: //pid > 0
        printf("I am the parent. Child PID is %d\n", pid);
        wait(NULL);
        printf("Child terminated\n");
    }

    return 0;
}

// double foo (int *p)
// {
//     int x;
//     double y;
//     x = *p
//     //do something useful
//     return y
// }

// double bar ()
// {
//     double d;
//     int i = 42
//     d = foo( &i );
//     return d;
// }