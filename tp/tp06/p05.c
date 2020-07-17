#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
    double a, b;
} th_args_t;

void* th_sum(void *arg){
    double *arr = arg;
    
    double *ret = malloc(sizeof(double));
    *ret = arr[0]+arr[1];
    
    return ret;
}

void* th_sub(void *arg){
    double *arr = arg;

    double *ret = malloc(sizeof(double));
    *ret = arr[0]-arr[1];

    return ret;
}

void* th_mul(void *arg){
    th_args_t *st = arg;

    double *ret = malloc(sizeof(double));
    *ret = st->a * st->b;

    return ret;
}

void* th_div(void *arg){
    th_args_t *st = arg;

    double *ret = malloc(sizeof(double));
    *ret = st->a / st->b;

    return ret;
}

int main(){
    double a, b;
    scanf("%lf %lf", &a, &b);

    double *arr = malloc(2*sizeof(double)); arr[0] = a; arr[1] = b;
    th_args_t *st = malloc(sizeof(th_args_t)); st->a = a; st->b = b;

    pthread_t tid[4];
    pthread_create(&tid[0], NULL, th_sum, arr);
    pthread_create(&tid[1], NULL, th_sub, arr);
    pthread_create(&tid[2], NULL, th_mul, st);
    pthread_create(&tid[3], NULL, th_div, st);

    void *ret = NULL;
    pthread_join(tid[0], &ret); printf("sum: %lf\n", *(double *)ret);
    pthread_join(tid[1], &ret); printf("sub: %lf\n", *(double *)ret);
    pthread_join(tid[2], &ret); printf("mul: %lf\n", *(double *)ret);
    pthread_join(tid[3], &ret); printf("div: %lf\n", *(double *)ret);

    return 0;
}