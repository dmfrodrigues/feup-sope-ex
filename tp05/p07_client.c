#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXN 256

int readline(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}

int main() {
    int req, ans;
    do {
        req = open("/tmp/fifo_req", O_WRONLY);
        if (req == -1) sleep(1);
    } while (req == -1);
    do {
        ans = open("/tmp/fifo_ans", O_RDONLY);
        if (ans == -1) sleep(1);
    } while (ans == -1);
    int a, b;
    scanf("%d %d", &a, &b);
    char buf[256];
    sprintf(buf, "%d %d", a, b);
    write(req, buf, strlen(buf)+1);
    int sum, sub, mul;
    char c;
    float div;
    while(readline(ans, buf) == 0){}
    sscanf(buf, "%d %d %d %c %f", &sum, &sub, &mul, &c, &div);
    printf("sum=%d, sub=%d, mul=%d, div type=%c %f\n", sum, sub, mul, c, div);

    exit(0);
}
