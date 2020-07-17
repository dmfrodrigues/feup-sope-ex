#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXN 256;

int main(){
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid == 0)/** Child */{
        close(fd[1]); FILE *f = fdopen(fd[0], "r");
        int a, b;
        fscanf(f, "%d %d", &a, &b);
        printf("%d\n", a+b);
    } else /** Parent */{
        close(fd[0]); FILE *f = fdopen(fd[1], "w");
        int a, b;
        scanf("%d %d", &a, &b);
        fprintf(f, "%d %d\n", a, b);
    }
    exit(0);
}
