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
        printf("ABOUT TO READ from %d to %ld\n", fd, (long)str);
        n = read(fd, str, 1);
        printf("JUST READ %c (%d) with code %d\n", *str, *str, n);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}

int main() {
    mkfifo("/tmp/fifo_req", 0660);
    mkfifo("/tmp/fifo_ans", 0660);
    int req = open("/tmp/fifo_req", O_RDONLY);
    int ans = open("/tmp/fifo_ans", O_WRONLY);

    printf("L18\n");
    int a, b;
    char buf[256];
    while(readline(req, buf) == 0){}
    printf("L30\n");
    sscanf(buf, "%d %d", &a, &b);
    printf("JUST READ %d %d\n", a, b);
    char c;
    if (b == 0)
        c = 'I';
    else if (a % b == 0)
        c = 'f';
    else
        c = 'd';
    sprintf(buf, "%d %d %d %c %f\n", a + b, a - b, a * b, c, (double)a / b);
    write(ans, buf, strlen(buf));
    exit(0);
}
