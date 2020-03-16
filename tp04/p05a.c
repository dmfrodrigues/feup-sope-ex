#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    signal(SIGCHLD, SIG_IGN);
    pid_t pid;
    for (int i = 1; i <= 3; i++) {
        pid = fork();
        if (pid == 0) {
            printf("CHILD no. %d (PID=%d) working ... \n", i, getpid());
            sleep(i * 7);  // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n", i, getpid());
            exit(0);
        }
    }
    for (int i = 1; i <= 4; i++) {
        printf("PARENT: working hard (task no. %d) ...\n", i);
        int n = 20;
        while ((n = sleep(n)) != 0)
            ;
        printf("PARENT: end of task no. %d\n", i);
        printf("PARENT: waiting for child no. %d ...\n", i);
    }
    exit(0);
}
