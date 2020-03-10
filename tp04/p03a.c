#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int v = 0;
int delta = 1;

void sig_handler(int signo) {
    switch(signo){
        case SIGUSR1: delta = +1; break;
        case SIGUSR2: delta = -1; break;
        default: break;
    }
}

int main(void) {
    struct sigaction action;
    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGUSR1, &action, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGUSR1 handler\n");
        exit(1);
    }
    if (sigaction(SIGUSR2, &action, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGUSR2 handler\n");
        exit(1);
    }
    while(1){
        sleep(1);
        v += delta;
        printf("v=%d\n", v);
    }
    exit(0);
}
