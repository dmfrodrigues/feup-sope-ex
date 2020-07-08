#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define NB 10

const int F = 10;
void get_food(void){}

int finish = 0;

int food_bits = 0;
pthread_mutex_t food_bits_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* bird(void* arg) {
    while(finish == 0) {
        pthread_mutex_lock(&food_bits_mutex);
        while(food_bits != 0)
            pthread_cond_wait(&cond, &food_bits_mutex);
        get_food();
        food_bits = F; pthread_cond_signal(&cond);
        pthread_mutex_unlock(&food_bits_mutex);
    }
    return NULL;
}

void* baby(void *arg){
    int id = *(int*)arg;
    int n_bits = 0;
    while(true){
        pthread_mutex_lock(&food_bits_mutex);
        if(food_bits <= 0){
            fprintf(stderr, "I am baby %d, I have already eaten "
                            "%d bits of food and "
                            "I am still hungry!\n", id, n_bits);
            while(food_bits <= 0)
                pthread_cond_wait(&cond, &food_bits_mutex);
        }
        food_bits--; pthread_cond_signal(&cond);
        n_bits++;
        pthread_mutex_unlock(&food_bits_mutex);
    }
    int *ret = malloc(sizeof(int));
    *ret = n_bits;
    return ret;
}

int main() {
    pthread_t tid_bird, tid_baby[NB];
    pthread_create(&tid_bird, NULL, bird, NULL);
    for(int i = 0; i < NB; ++i) {
        int *i_new = malloc(sizeof(int));
        *i_new = i;
        pthread_create(&tid_baby[i], NULL, baby, i_new);
    }
    int *ret = NULL;;
    for(int i = 0; i < NB; ++i){
        pthread_join(tid_baby[i], (void**)&ret);
        int total_bits = *ret;
        fprintf(stdout, "Baby number %d has eaten "
                        "%d bits of food\n", i, total_bits);
    }
    return 0;
}
