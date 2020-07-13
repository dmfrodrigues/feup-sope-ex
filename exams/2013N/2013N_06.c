#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100   // buffer size
char buffer[N];
int ri = 0;     // read index
int wi = 0;     // write index
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
sem_t canIread, canIwrite;

int open_in_fifo(char* fifoName) {
    /* TODO B: opens the FIFO and exits the thread if the open fails,  
       otherwise returns the FIFO descriptor */
}

void* receive(void* p) {
    int f = open_in_fifo(p);
    char c;
    while(read(f, &c, 1)) {
        printf("Read from FIFO %s the value %d\n", (char*)p, c);
        pthread_mutex_lock(&mut);
        buffer[wi++] = c;
        wi %= N;
        pthread_mutex_unlock(&mut);
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
        printf("Write to FIFO %s the value %d\n", (char*)p, buffer[ri]);
        write(f, &buffer[ri++], 1);
        ri %= N;
    }
    close(f);
}

void init_semaphores() {
    //TODO C: initialize both semaphores with the appropriate values
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
    /* TODO A: creates receive() threads, one for each input FIFO and
               one send() thread, as well any other required code */
    free(rt);
    destroy_semaphores();

    return 0;
}