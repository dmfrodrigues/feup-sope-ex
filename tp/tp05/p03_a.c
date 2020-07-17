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
        int des = open(argv[1], O_RDONLY);
        if(des == -1) kill(pid, SIGKILL);
        char buf[MAXN];
        int r;
        while((r = read(des, buf, MAXN)) != 0){
            write(fd[1], buf, r);
        }
    }
    exit(0);
}
