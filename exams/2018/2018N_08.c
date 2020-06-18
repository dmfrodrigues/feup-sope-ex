#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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

void* baby(void *arg){
    int id = *(int*)arg;
    int n_bits = 0;
    while(true){
        if(food_bits <= 0){
            fprintf(stderr, "I am baby %d, I have already eaten %d bits of food and I am still hungry!\n", id, n_bits);
            while(food_bits <= 0){}
        }
        food_bits--;
        n_bits++;
    }
    return NULL;
}

int main() {
    pthread_t tid_bird, tid_baby[NB];
    pthread_create(&tid_bird, NULL, bird, NULL);
    for(int i = 0; i < NB; ++i) {
        int *i_new = malloc(sizeof(int));
        *i_new = i;
        pthread_create(&tid_baby[i], NULL, baby, i_new);
    }
    return 0;
}
