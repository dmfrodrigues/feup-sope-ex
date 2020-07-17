#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define MAXN 256

const double TMAX = 10;

int readline(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\n');
    *(--str) = '\0';
    return (n > 0);
}

int main(){
    clock_t begin = clock();

    mkfifo("/tmp/fifo_chg", 0660);
    int pdes = open("/tmp/fifo_chg", O_RDONLY | O_NONBLOCK);

    printf("LISTENING\n");
    int cnt = 0;
    double Dt = 0.0;
    char buf[MAXN];
    while(Dt < TMAX){
        while(Dt < TMAX && readline(pdes, buf) == 0){
            clock_t now = clock();
            Dt = (double)(now - begin)/CLOCKS_PER_SEC;
        }
        if(Dt >= TMAX) break;
        printf("ARRIVED %s\n", buf); ++cnt;
    }
    printf("DONE LISTENING, REGISTERED %d USERS\n", cnt);

    close(pdes);
    unlink("/tmp/fifo_chg");

    return 0;
}