#include "shared_memory.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

shared_memory_t *mem = NULL;

void open_shared_memory(void){
    int fd = shm_open(MEM_NAME, O_RDWR, 0600);
    mem = mmap(NULL, sizeof(shared_memory_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
}

void free_shared_memory(void){
    munmap(mem, sizeof(shared_memory_t));
    shm_unlink(MEM_NAME);
}

int total_consumed = 0;
void consume(int item){
    struct timespec req = {
        .tv_sec = 0,
        .tv_nsec = 2000000
    };
    nanosleep(&req, NULL);
    total_consumed += item;
}

int main(int argc, char *argv[]){

    const int num_items = atoi(argv[1]);
    printf("Going to consume %d items\n", num_items);

    open_shared_memory();

    for(int i = 0; i < num_items; ++i){
        sem_wait(&mem->full);
        sem_wait(&mem->mutex);
        int item = queue_pop(&mem->buffer);
        if(num_items <= 20) printf("- Consumed %d, now have %lu items\n", item, mem->buffer.size);
        sem_post(&mem->mutex);
        sem_post(&mem->empty);
        consume(item);
        if(item != i+1) printf("Expecting to consume %d but consumed %d\n", i+1, item);
    }
    printf("Consumed %d items, with a total value of %d\n", num_items, total_consumed);

    free_shared_memory();

    return 0;
}
