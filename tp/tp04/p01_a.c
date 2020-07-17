#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signo) { printf("In SIGINT handler ...\n"); }

int main(void) {
    if (signal(SIGINT, sigint_handler) < 0) {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }
    printf("Sleeping for 10 seconds ...\n");
    sleep(10);
    printf("Waking up ...\n");
    exit(0);
}
