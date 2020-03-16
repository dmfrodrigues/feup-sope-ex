#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t pid;
int delay;

void childhandler(int signo) /* Executed if child dies before parent */ {
    int status;
    pid = wait(&status);
    printf("Child %d terminated within %d seconds.\n", pid, delay);
    exit(0);
}

void alarmhandler(int signo){
    printf("Program PID=%d exceeded limit of %d seconds!\n", pid, delay);
    kill(pid, SIGKILL);
    exit(1);
}

int main(int argc, char *argv[]) {
    sscanf(argv[1], "%d", &delay); /* read delay from command line */
    signal(SIGCHLD, childhandler);
    signal(SIGALRM, alarmhandler);
    pid = fork();
    if (pid == 0) /* child */
        execvp(argv[2], &argv[2]);
    alarm(delay);
    pause();
    return 0;
}
