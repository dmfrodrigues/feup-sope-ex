#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAXN 256

const char fifo_path[] = "/tmp/fifo_chg";

int main(int argc, char *argv[]){
    if(argc != 2) exit(EXIT_FAILURE);
    int pdes;
    do{
        pdes = open(fifo_path, O_WRONLY);
        if(pdes == -1) sleep(1);
    } while(pdes == -1);

    char buf[MAXN];
    strcat(strcpy(buf, argv[1]), "\n");
    write(pdes, buf, strlen(buf));

    exit(0);
}