#ifndef SHARED_MEMORY_H_INCLUDED
#define SHARED_MEMORY_H_INCLUDED

#include "../queue.h"

#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    queue_t buffer;
    sem_t mutex;
    sem_t slots; //or empty
    sem_t items; //or full
} shared_memory_t;

void shared_memory_init(shared_memory_t *mem);

static const char* const MEM_NAME = "/mem1";

#endif //SHARED_MEMORY_H_INCLUDED
