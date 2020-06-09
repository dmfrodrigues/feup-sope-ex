#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXN 256;

typedef struct {
    int a, b;
} send_me;

int main(){
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid == 0)/** Child */{
        close(fd[1]);
        send_me s;
        read(fd[0], &s, sizeof(send_me));
        printf("%d\n", s.a+s.b);
    } else /** Parent */{
        close(fd[0]);
        send_me s;
        scanf("%d %d", &s.a, &s.b);
        write(fd[1], &s, sizeof(send_me));
    }
    exit(0);
}
