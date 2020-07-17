#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <sys/types.h>

#define QUEUE_SIZE 1000

typedef struct {
    size_t size;
    size_t left;
    int elems[QUEUE_SIZE];
} queue_t;

void queue_init(queue_t *q);

void queue_push(queue_t *q, int elem);

int queue_pop(queue_t *q);

#endif //QUEUE_H_INCLUDED
