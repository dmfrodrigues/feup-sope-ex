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
    assert(argc == 2);
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid == 0)/** Child */{
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("sort", "sort", NULL);
    } else /** Parent */{
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("cat", "cat", argv[1], NULL);
    }
    exit(0);
}
