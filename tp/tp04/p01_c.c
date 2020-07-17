#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signo) { printf("In SIGINT handler ...\n"); }

int main(void) {
    struct sigaction act;
    act.sa_handler = sigint_handler;
    if (sigaction(SIGINT, &act, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }
    printf("Sleeping for 10 seconds ...\n");
    int s = 10;
    while((s = sleep(s))){}
    printf("Waking up ...\n");
    exit(0);
}
