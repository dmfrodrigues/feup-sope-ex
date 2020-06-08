#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
    pid_t pid;
    int i, j;
    printf("I'm process %d. My parent is %d.\n", getpid(), getppid());
    int r = 0;
    for (i = 1; i <= 3; i++) {
        pid = fork();
        if (pid < 0) {
            printf("fork      error");
            exit(1);
        } else if (pid == 0) {
            printf(
                "I'm process %d. My parent is %d.                       I'm "
                "going to work for 1 second ...\n",
                getpid(), getppid());
            sleep(1);  // simulando o trabalho do filho
            printf(
                "I'm process %d. My parent is %d.                       I "
                "finished my work\n",
                getpid(), getppid());
            //exit(0);  // a eliminar na alinea c)
        } else        // simulando o trabalho do pai
            for (r = 0, j = 1; j <= 10; j++) {
                sleep(1);
                printf("father      working      ...\n");
                if (r == 0) r = waitpid(-1, NULL, WNOHANG);
            }
    }
    exit(0);
}