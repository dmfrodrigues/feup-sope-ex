#include <pthread.h>

#define NB 10

const int F = 10;
void get_food(void){}

int food_bits = 0;

int finish = 0;
void* bird(void* arg) {
    while(finish == 0) {
        if(food_bits == 0) {
            get_food();
            food_bits = F;
        }
    }
    return NULL;
}

int main() {
    pthread_t tid_bird, tid_baby[NB];
    ...;
    pthread_create(&tid_bird, NULL, bird, NULL);
    for(...) {
        ...;
        pthread_create(..., ..., baby, ...);
    }
    return 0;
}
