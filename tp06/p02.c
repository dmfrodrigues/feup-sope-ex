#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define STDERR 2

int N = 50000;
int n =     0;

void *thrfunc(void *arg) {
    int i = 0;
    fprintf(stderr, "Starting thread %s\n", (char *)arg);
    while(n < N){
        write(STDERR, (char *)arg, 1);
        ++i; ++n;
    }
    char buf[1024];
    sprintf(buf, "Exiting thread, printed %d times, n=%d\n", i, n);
    write(STDERR, buf, strlen(buf));
    return NULL;
}
int main() {
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}
