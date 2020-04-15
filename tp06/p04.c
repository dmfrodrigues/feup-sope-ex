#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

void *thread_func(void *threadnum) {
    sleep(1);
    printf("Hello from thread tid=%lu\n", pthread_self());
    pthread_exit(threadnum);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int num[NUM_THREADS];
    int t;
    for (t = 0; t < NUM_THREADS; t++) {
        num[t] = t;
        printf("Creating thread %d\n", t);
        pthread_create(&threads[t], NULL, thread_func, (void *)&num[t]);
    }

    void *ans = NULL;
    for(t = 0; t < NUM_THREADS; ++t){
        pthread_join(threads[t], &ans);
        printf("Thread no. %d exited\n", *(int *)ans);
    }

    exit(0);
}
