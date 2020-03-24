#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXN 256

int main(){
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid == 0)/** Child */{
        close(fd[1]); FILE *f = fdopen(fd[0], "r");
        char a[MAXN], b[MAXN];
        fscanf(f, "%s %s", a, b);
        printf("%d\n", atoi(a)+atoi(b));
    } else /** Parent */{
        close(fd[0]);
        char a[MAXN], b[MAXN];
        scanf("%s %s", a, b);
        write(fd[1], a, strlen(a));
        write(fd[1], " ", 1);
        write(fd[1], b, strlen(b));
    }
    exit(0);
}
