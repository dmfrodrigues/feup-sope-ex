// PROGRAMA p01.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#define MAXELEMS 10000000  // nr. max de posicoes
#define MAXTHREADS 100     // nr. max de threads
#define min(a, b) (a) < (b) ? (a) : (b)
#define SHARED 1 //partilhado entre threads do mesmo processo

int npos;

sem_t *sem = NULL;  // semaforo p/a sec.critica
const char *SEM_NAME = "/sem1";

const char *BUF_NAME = "/buf1";
int *buf = NULL;
const char *POS_NAME = "/pos1";
int *pos = NULL;
const char *VAL_NAME = "/val1";
int *val = NULL;              // variaveis partilhadas

void *fill(void *nr) {
    while (1) {
        sem_wait(sem);
        if (*pos >= npos) {
            sem_post(sem);
            return NULL;
        }
        buf[*pos] = *val;
        (*pos)++;
        (*val)++;
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
    // Semaforo
    sem = sem_open(SEM_NAME, O_CREAT, 0600, 1);
    // buf
    int buf_fd = shm_open(BUF_NAME, O_CREAT|O_RDWR, 0600);
    ftruncate(buf_fd, sizeof(int)*MAXELEMS);
    buf = mmap(NULL, sizeof(int)*MAXELEMS, PROT_READ|PROT_WRITE, MAP_SHARED, buf_fd, 0);
    // pos
    int pos_fd = shm_open(POS_NAME, O_CREAT|O_RDWR, 0600);
    ftruncate(pos_fd, sizeof(int));
    pos = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, pos_fd, 0);
    *pos = 0;
    // val
    int val_fd = shm_open(VAL_NAME, O_CREAT|O_RDWR, 0600);
    ftruncate(val_fd, sizeof(int));
    val = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, val_fd, 0);
    *val = 0;

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

    sem_close(sem); sem = NULL; sem_unlink(SEM_NAME);
    munmap(buf, sizeof(int)*MAXELEMS); buf = NULL; shm_unlink(BUF_NAME);
    munmap(pos, sizeof(int)         ); pos = NULL; shm_unlink(POS_NAME);
    munmap(val, sizeof(int)         ); val = NULL; shm_unlink(VAL_NAME);

    return 0;
}
