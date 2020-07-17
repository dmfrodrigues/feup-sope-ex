#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

size_t pid_arr_sz = 0;
pid_t *pid_arr = NULL;

void childhandler(int signo) /* Executed if child dies before parent */ {
    int status;
    pid_t pid;
    pid = wait(&status);
    printf("Child %d terminated with status %d\n", pid, status);
    for(size_t i = 0; i < pid_arr_sz; ++i){
            if(pid_arr[i] == pid){
                pid_arr[i] = 0;
                break;
            }
        }
    if(status != 0){
        for(size_t i = 0; i < pid_arr_sz; ++i){
            if(pid_arr[i] != 0){
                kill(pid_arr[i], SIGKILL);
            }
        }
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    pid_arr_sz = argc-1;
    pid_arr = malloc(pid_arr_sz*sizeof(pid_t));
    signal(SIGCHLD, childhandler);
    for(int i = 0; i < argc-1; ++i){
        pid_arr[i] = fork();
        if (pid_arr[i] == 0) /* child */
            execlp(argv[i+1], argv[i+1], NULL);
    }
    pause();
    return 0;
}
