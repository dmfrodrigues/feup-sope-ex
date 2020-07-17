#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>

#include <pthread.h>

typedef int val_t;

int comp(const void *lhs, const void *rhs){
    return *(val_t*)lhs-*(val_t*)rhs;
}

typedef struct{
    val_t *base;
    int N;
    int num_threads;
} arg_t;

void* mysort(void *arg_in){
    int *ret = malloc(sizeof(int));
    *ret = EXIT_SUCCESS;
    const arg_t *arg = arg_in;

    if(arg->N == 1) return ret;
    if(arg->num_threads <= 1){
        qsort(arg->base, arg->N, sizeof(val_t), comp);
        return ret;
    }

    arg_t *arg1 = malloc(sizeof(arg_t));
    arg_t *arg2 = malloc(sizeof(arg_t));

    arg1->N = arg->N/2;
    arg2->N = arg->N - arg1->N;
    
    arg1->base = arg->base;
    arg2->base = arg->base + arg1->N;

    arg1->num_threads = arg->num_threads/2;
    arg2->num_threads = arg->num_threads - arg1->num_threads;

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, mysort, arg1);
    pthread_create(&tid2, NULL, mysort, arg2);

    int *ret_ = NULL;
    pthread_join(tid1, (void**)&ret_); if(*ret_){ *ret = EXIT_FAILURE; return ret; }
    pthread_join(tid2, (void**)&ret_); if(*ret_){ *ret = EXIT_FAILURE; return ret; }
    
    //merge
    val_t *new = calloc(arg->N, sizeof(val_t));
    size_t l = 0, r = 0, curr = 0;
    while(l < arg1->N && r < arg2->N){
        if(comp(&arg1->base[l], &arg2->base[r]) <= 0) new[curr++] = arg1->base[l++];
        else                                          new[curr++] = arg2->base[r++];
    }
    while(l < arg1->N) new[curr++] = arg1->base[l++];
    while(r < arg2->N) new[curr++] = arg2->base[r++];
    memcpy(arg->base, new, arg->N*sizeof(val_t));
    free(new);

    return ret;
}

int main(int argc, char *argv[]){
    if(argc != 2) return EXIT_FAILURE;
    int num_threads;
    sscanf(argv[1], "%d", &num_threads);

    int N;
    scanf("%d", &N);
    val_t *base = calloc(sizeof(val_t), N);
    for(int n = 0; n < N; ++n){
        scanf("%d", &base[n]);
    }

    arg_t *arg = malloc(sizeof(arg_t));
    arg->base = base;
    arg->N = N;
    arg->num_threads = num_threads;
    int *ret = mysort(arg);
    if(*ret) return EXIT_FAILURE;
    printf("%d", base[0]);
    for(int n = 1; n < N; ++n){
        printf(" %d", base[n]);
    }
    printf("\n");

    return 0;
}
