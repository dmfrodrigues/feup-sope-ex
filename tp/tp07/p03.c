// PROGRAMA p01.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXELEMS 10000000  // nr. max de posicoes
#define MAXTHREADS 100     // nr. max de threads
#define min(a, b) (a) < (b) ? (a) : (b)

int npos;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;  // mutex p/a sec.critica
int buf[MAXELEMS], pos = 0, val = 0;              // variaveis partilhadas

void *fill(void *nr) {
    while (1) {
        pthread_mutex_lock(&mut);
        if (pos >= npos) {
            pthread_mutex_unlock(&mut);
            return NULL;
        }
        buf[pos] = val;
        pos++;
        val++;
        pthread_mutex_unlock(&mut);
        *(int *)nr += 1;
    }
}

void *verify(void *arg) {
    for (int k = 0; k < npos; k++){
        pthread_mutex_lock(&mut);
        int pos_ = pos;
        pthread_mutex_unlock(&mut);
        if(k >= pos_) { --k; continue; }
        if (buf[k] != k) // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int nthr, count[MAXTHREADS];    // array para contagens
    pthread_t tidf[MAXTHREADS], tidv;  // tids dos threads

    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n", argv[0]);
        return 1;
    }

    npos = min(atoi(argv[1]), MAXELEMS);    // no. efectivo de posicoes
    nthr = min(atoi(argv[2]), MAXTHREADS);  // no. efectivo de threads

    for (int k = 0; k < nthr; k++) {            // criacao das threads 'fill'
        count[k] = 0;
        pthread_create(&tidf[k], NULL, fill, &count[k]);
    }
    pthread_create(&tidv, NULL, verify, NULL);

    int total = 0;
    for (int k = 0; k < nthr; k++) {  // espera threads 'fill'
        pthread_join(tidf[k], NULL);
        printf("count[%d] = %d\n", k, count[k]);
        total += count[k];
    }
    printf("total count = %d\n", total);  // mostra total
    
    pthread_join(tidv, NULL);  // espera thread 'verify'
    return 0;
}
