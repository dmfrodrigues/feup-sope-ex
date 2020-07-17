#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>

#define MAXN 256

int main(int argc, char *argv[]){
    assert(argc == 3);
    int pipe1[2];
    pipe(pipe1);
    pid_t pid = fork();
    if(pid == 0)/** 1st Child */{
        close(pipe1[1]);
        dup2(pipe1[0], STDIN_FILENO);
        int pipe2[2];
        pipe(pipe2);
        pid = fork();
        if(pid == 0)/** 2nd child */{
            close(pipe2[1]);
            dup2(pipe2[0], STDIN_FILENO);
            execlp("sort", "sort", NULL);
        } else{
            dup2(pipe1[0], STDIN_FILENO);
            dup2(pipe2[1], STDOUT_FILENO);
            execlp("grep", "grep", argv[2], NULL);
        }
    } else {
        close(pipe1[0]);
        dup2(pipe1[1], STDOUT_FILENO);
        execlp("ls", "ls", argv[1], "-laR", NULL);
    }
    exit(0);
}
