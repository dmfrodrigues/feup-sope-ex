#include "../shared_memory.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SHARED 0

shared_memory_t *mem = NULL;

void create_shared_memory(void){
    mem = malloc(sizeof(shared_memory_t));
    shared_memory_init(mem);
}

void free_shared_memory(void){
    free(mem); mem = NULL;
}

int total_produced = 0;
int produce(int i){
    struct timespec req = {
        .tv_sec = 0,
        .tv_nsec = 10000000
    };
    nanosleep(&req, NULL);
    int item = i+1;
    total_produced += item;
    return item;
}

int total_consumed = 0;
void consume(int item){
    struct timespec req = {
        .tv_sec = 0,
        .tv_nsec = 20000000
    };
    nanosleep(&req, NULL);
    total_consumed += item;
}

void* produce_thread_func(void *args){
    const int num_items = *(int *)args;
    printf("Going to produce %d items\n", num_items);
    for(int i = 0; i < num_items; ++i){
        int item = produce(i);
        sem_wait(&mem->slots);
        sem_wait(&mem->mutex);
        queue_push(&mem->buffer, item);
        if(num_items <= 20) printf("+ Produced %d, now have %lu items\n", item, mem->buffer.size);
        sem_post(&mem->mutex);
        sem_post(&mem->items);
    }
    printf("Produced %d items, with a total value of %d\n", num_items, total_produced);
    return NULL;
}

void* consume_thread_func(void *args){
    const int num_items = *(int *)args;
    printf("Going to consume %d items\n", num_items);
    for(int i = 0; i < num_items; ++i){
        sem_wait(&mem->items);
        sem_wait(&mem->mutex);
        int item = queue_pop(&mem->buffer);
        if(num_items <= 20) printf("- Consumed %d, now have %lu items\n", item, mem->buffer.size);
        sem_post(&mem->mutex);
        sem_post(&mem->slots);
        consume(item);
        if(item != i+1) printf("Expecting to consume %d but consumed %d\n", i+1, item);
    }
    printf("Consumed %d items, with a total value of %d\n", num_items, total_consumed);
    return NULL;
}

int main(int argc, char *argv[]){
    int num_items = atoi(argv[1]);
    const int N = atoi(argv[2]);

    create_shared_memory();
    sem_init(&mem->slots, SHARED, N);
    sem_init(&mem->items , SHARED, 0);
    sem_init(&mem->mutex, SHARED, 1);

    pthread_t producer_tid;
    pthread_create(&producer_tid, NULL, produce_thread_func, &num_items);
    pthread_t consumer_tid;
    pthread_create(&consumer_tid, NULL, consume_thread_func, &num_items);

    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    free_shared_memory();

    return 0;
}
