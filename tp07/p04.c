// PROGRAMA p01.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#define MAXELEMS 10000000  // nr. max de posicoes
#define MAXTHREADS 100     // nr. max de threads
#define min(a, b) (a) < (b) ? (a) : (b)
#define SHARED 1 //partilhado entre threads do mesmo processo

int npos;

sem_t *sem = NULL;  // semaforo p/a sec.critica
const char *SEM_NAME = "/sem1";

int buf[MAXELEMS], pos = 0, val = 0;              // variaveis partilhadas

void *fill(void *nr) {
    while (1) {
        sem_wait(sem);
        if (pos >= npos) {
            sem_post(sem);
            return NULL;
        }
        buf[pos] = val;
        pos++;
        val++;
        sem_post(sem);
        *(int *)nr += 1;
    }
}

void *verify(void *arg) {
    for (int k = 0; k < npos; k++){
        if (buf[k] != k) // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    sem = sem_open(SEM_NAME, O_CREAT, 0600, 1);

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

    int total = 0;
    for (int k = 0; k < nthr; k++) {  // espera threads 'fill'
        pthread_join(tidf[k], NULL);
        printf("count[%d] = %d\n", k, count[k]);
        total += count[k];
    }
    printf("total count = %d\n", total);  // mostra total

    pthread_create(&tidv, NULL, verify, NULL);
    pthread_join(tidv, NULL);  // espera thread 'verify'

    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}
