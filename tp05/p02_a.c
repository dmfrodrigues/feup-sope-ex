#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXN 256

int main(){
    int to[2];
    int fr[2];
    pipe(to);
    pipe(fr);
    pid_t pid = fork();
    if(pid == 0)/** Child */{
        close(to[1]); close(fr[0]);
        FILE *fto = fdopen(to[0], "r");
        FILE *ffr = fdopen(fr[1], "w");
        int a, b;
        fscanf(fto, "%d %d", &a, &b);
        char c;
        if(b == 0) c = 'I';
        else if(a%b == 0) c = 'f';
        else c = 'd';
        fprintf(ffr, "%d %d %d %c %f\n", a+b, a-b, a*b, c, (double)a/b);
    } else /** Parent */{
        close(to[0]); close(fr[1]);
        FILE *fto = fdopen(to[1], "w");
        FILE *ffr = fdopen(fr[0], "r");
        int a, b;
        scanf("%d %d", &a, &b);
        fprintf(fto, "%d %d\n", a, b);
        fflush(fto);
        int sum, sub, mul; char c; float div;
        fscanf(ffr, "%d %d %d %c %f", &sum, &sub, &mul, &c, &div);
        printf("sum=%d, sub=%d, mul=%d, div type=%c %f\n", sum, sub, mul, c, div);
        waitpid(pid, NULL);
    }
    exit(0);
}
