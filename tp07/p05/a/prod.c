#include "shared_memory.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SHARED 1

shared_memory_t *mem = NULL;

void create_shared_memory(void){
    int fd = shm_open(MEM_NAME, O_CREAT|O_RDWR, 0600);
    ftruncate(fd, sizeof(shared_memory_t));
    mem = mmap(NULL, sizeof(shared_memory_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    shared_memory_init(mem);
}

int total_produced = 0;
int produce(int i){
    struct timespec req = {
        .tv_sec = 0,
        .tv_nsec = 1000000
    };
    nanosleep(&req, NULL);
    int item = i+1;
    total_produced += item;
    return item;
}

int main(int argc, char *argv[]){
    
    const int num_items = atoi(argv[1]);
    printf("Going to produce %d items\n", num_items);
    const int N = atoi(argv[2]);

    create_shared_memory();
    sem_init(&mem->empty, SHARED, N);
    sem_init(&mem->full , SHARED, 0);
    sem_init(&mem->mutex, SHARED, 1);
    
    for(int i = 0; i < num_items; ++i){
        int item = produce(i);
        sem_wait(&mem->empty);
        sem_wait(&mem->mutex);
        queue_push(&mem->buffer, item);
        if(num_items <= 20) printf("+ Produced %d, now have %lu items\n", item, mem->buffer.size);
        sem_post(&mem->mutex);
        sem_post(&mem->full);
    }
    printf("Produced %d items, with a total value of %d\n", num_items, total_produced);

    return 0;
}