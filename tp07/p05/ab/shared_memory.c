#include "shared_memory.h"

void shared_memory_init(shared_memory_t *mem){
    queue_init(&mem->buffer);
}
