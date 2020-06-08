#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include <mqueue.h>

#define MAXN 8192

const int TMAX = 10;

const char MQ_NAME[] = "/messagequeue";

volatile sig_atomic_t timeup = false;
void sigalrm_handler(int n){
    timeup = true;
}

int main(){
    struct sigaction action;
    action.sa_handler = sigalrm_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGALRM, &action, NULL);
    alarm(TMAX);

    mqd_t mqd = mq_open(MQ_NAME, O_CREAT|O_RDONLY, 0600, NULL);
    if(mqd == -1) EXIT_ERROR("Could not create mq");

    printf("LISTENING\n");
    int cnt = 0;
    char buf[MAXN];
    while(!timeup){
        int r = mq_receive(mqd, buf, MAXN, NULL);
        if(r == -1 && errno == EINTR) break;
        buf[r] = '\0';
        printf("ARRIVED %s\n", buf); ++cnt;
    }
    printf("DONE LISTENING, REGISTERED %d USERS\n", cnt);

    mq_close(mqd);
    unlink(MQ_NAME);

    return 0;
}