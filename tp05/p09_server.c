#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 256
#define MAXR 65536

const double TMAX = 10;

const char fifo_s_path[] = "/tmp/fifo.s";
int fifo_s_des;

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

    mkfifo(fifo_s_path, 0660);
    fifo_s_des = open(fifo_s_path, O_RDONLY | O_NONBLOCK);

    printf("LISTENING\n");
    int cnt = 0;
    double Dt = 0.0;
    char buf[MAXN];
    while(Dt < TMAX){
        while(Dt < TMAX && readline(fifo_s_des, buf) == 0){
            clock_t now = clock();
            Dt = (double)(now - begin)/CLOCKS_PER_SEC;
        }
        if(Dt >= TMAX) break;
        pid_t pid; sscanf(buf, "%d", &pid);
        readline(fifo_s_des, buf);
        printf("ARRIVED: PID=%d, COMMAND=%s\n", pid, buf); ++cnt;

        
        char outbuf[MAXR]; strcpy(outbuf, "");
        FILE *fp = popen(buf, "r");
        if (fp == NULL) { printf("Failed to run command\n" ); exit(1); }
        char outbuf_tmp[MAXR];
        while (fgets(outbuf_tmp, MAXR-1, fp) != NULL) {
            strcat(outbuf, outbuf_tmp);
        }
        pclose(fp);
        char fifo_pid_path[MAXN]; sprintf(fifo_pid_path, "/tmp/fifo.%d", pid);
        int fifo_pid_des = open(fifo_pid_path, O_WRONLY);
        write(fifo_pid_des, outbuf, strlen(outbuf)+1);
        close(fifo_pid_des);
        
    }
    printf("DONE LISTENING, REGISTERED %d REQUESTS\n", cnt);

    close(fifo_s_des);
    unlink(fifo_s_path);

    return 0;
}
