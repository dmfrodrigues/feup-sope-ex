#include "queue.h"

void queue_init(queue_t *q){
    q->size = 0;
    q->left = 0;
}

void queue_push(queue_t *q, int elem){
    size_t pos = (q->left + q->size)%QUEUE_SIZE;
    q->elems[pos] = elem;
    ++q->size;
}

int queue_pop(queue_t *q){
    int res = q->elems[q->left];
    --q->size;
    q->left = (q->left+1)%QUEUE_SIZE;
    return res;
}
