// PROGRAMA p01.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STDERR 2

typedef struct {
    char *text;
    int N;
} thread_args_t;

void *thrfunc(void *arg) {
    thread_args_t *args = arg;

    int i;
    fprintf(stderr, "Starting thread %s\n", args->text);
    for (i = 1; i <= args->N; i++) write(STDERR, args->text, 1);
    return NULL;
}
int main() {
    pthread_t ta, tb;
    
    thread_args_t *arg1 = malloc(sizeof(thread_args_t));
    arg1->text = "1";
    arg1->N = 10000;

    thread_args_t *arg2 = malloc(sizeof(thread_args_t));
    arg2->text = "2";
    arg2->N = 5000;

    pthread_create(&ta, NULL, thrfunc, arg1);
    pthread_create(&tb, NULL, thrfunc, arg2);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}
