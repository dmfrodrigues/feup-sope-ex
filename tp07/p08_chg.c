#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>

#define MAXN 8196

const char MQ_NAME[] = "/messagequeue";

int main(int argc, char *argv[]){
    if(argc != 2) exit(EXIT_FAILURE);
    mqd_t mqd = mq_open(MQ_NAME, O_WRONLY);
    if(mqd == -1) return EXIT_FAILURE;

    mq_send(mqd, argv[1], strlen(argv[1]), 0);
    mq_close(mqd);

    exit(0);
}