#include "shared_memory.h"

void shared_memory_init(shared_memory_t *mem){
    queue_init(&mem->buffer);
    pthread_mutex_init(&mem->items_lock, NULL);
    pthread_cond_init (&mem->items_cond, NULL);
    pthread_mutex_init(&mem->slots_lock, NULL);
    pthread_cond_init (&mem->slots_cond, NULL);
}
