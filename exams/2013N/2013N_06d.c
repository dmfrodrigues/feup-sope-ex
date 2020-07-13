#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define N 100   // buffer size
char buffer[N];
int ri = 0;     // read index
int wi = 0;     // write index
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
sem_t canIread, canIwrite;

int open_in_fifo(char* fifoName) {
    int fd = open(fifoName, O_RDONLY);
    if(fd == -1){
        int *status = malloc(sizeof(int));
        *status = -1;
        pthread_exit(status);
    }
    return fd;
}

void* receive(void* p) {
    int f = open_in_fifo(p);
    char c;
    while(read(f, &c, 1)) {
        printf("Read from FIFO %s the value %d\n", (char*)p, c);
        sem_wait(&canIwrite);           //<===
        pthread_mutex_lock(&mut);
        buffer[wi++] = c;
        wi %= N;
        pthread_mutex_unlock(&mut);
        sem_post(&canIwrite);           //<===
    }
    close(f);
}

int open_out_fifo(char* fifoName) {
    /* Opens the FIFO and exits the program if it fails,
       otherwise returns the FIFO descriptor */
}

void* send(void* p) {
    int f = open_out_fifo(p);
    for(;;) {
        sem_wait(&canIread);            //<===
        printf("Write to FIFO %s the value %d\n", (char*)p, buffer[ri]);
        write(f, &buffer[ri++], 1);
        ri %= N;
        sem_post(&canIwrite);           //<===
    }
    close(f);
}

void init_semaphores() {
    sem_init(&canIread , 0, 0);
    sem_init(&canIwrite, 0, N);
}

void destroy_semaphores() {
    sem_destroy(&canIread);
    sem_destroy(&canIwrite);
}

int main(int argc, char** argv) {
    pthread_t st;   // send thread
    pthread_t* rt;  // receive threads
    if(argc < 3) {
        perror("Usage ./mux f1 [f2 [..[fn]]] fout\n");
        exit(1);
    }
    init_semaphores();

    pthread_create(&st, NULL, send, argv[argc-1]);
    const size_t n_threads = argc-1;
    rt = calloc(n_threads, sizeof(pthread_t));
    for(size_t i = 0; i < n_threads; ++i){
        pthread_create(&rt[i], NULL, receive, argv[i+1]);
    }

    free(rt);
    destroy_semaphores();

    return 0;
}