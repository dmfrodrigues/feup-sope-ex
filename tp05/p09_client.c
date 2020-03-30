#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

#define MAXN 256
#define MAXR 65536

const char fifo_s_path[] = "/tmp/fifo.s";
int fifo_s_des;

int readall(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}

int main(int argc, char *argv[]){
    if(argc < 2) exit(0);

    do{
        fifo_s_des = open(fifo_s_path, O_WRONLY);
        if(fifo_s_des == -1) sleep(1);
    } while(fifo_s_des == -1);

    
    char fifo_pid_path[MAXN];
    sprintf(fifo_pid_path, "/tmp/fifo.%d", getpid());
    mkfifo(fifo_pid_path, 0660);
    int fifo_pid_des = open(fifo_pid_path, O_RDONLY | O_NONBLOCK);
    

    char buf[PIPE_BUF];
    sprintf(buf, "%d\n", getpid());
    strcat(buf, argv[1]);
    for(int i = 2; i < argc; ++i){
        strcat(buf, " ");
        strcat(buf, argv[i]);
    }
    strcat(buf, "\n");

    write(fifo_s_des, buf, strlen(buf));
    close(fifo_s_des);

    
    char getbuf[MAXR];
    while(!readall(fifo_pid_des, getbuf)){}
    printf("%s", getbuf);

    close(fifo_pid_des);
    unlink(fifo_pid_path);
    

    exit(0);
}
