#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <pthread.h>

typedef int val_t;

typedef struct{
    size_t M, N;
    val_t **el;
} matrix_t;
int matrix_read(matrix_t *mat){
    scanf("%lu %lu", &mat->M, &mat->N);
    mat->el = calloc(mat->M, sizeof(val_t *));
    for(size_t m = 0; m < mat->M; ++m)
        mat->el[m] = calloc(mat->N, sizeof(val_t));
    for(size_t m = 0; m < mat->M; ++m){
        for(size_t n = 0; n < mat->N; ++n){
            scanf("%d", &mat->el[m][n]);
        }
    }
    return EXIT_SUCCESS;
}
int matrix_print(const matrix_t *mat){
    printf("%lu %lu\n", mat->M, mat->N);
    for(size_t m = 0; m < mat->M; ++m){
        printf("%d", mat->el[m][0]);
        for(size_t n = 1; n < mat->N; ++n){
            printf(" %d", mat->el[m][n]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
int matrix_mul_compute_element(const matrix_t *A, const matrix_t *B, matrix_t *C,
                               size_t m, size_t n){
    val_t ret = 0;
    size_t K = A->N;
    for(size_t k = 0; k < K; ++k){
        ret += A->el[m][k]*B->el[k][n];
    }
    C->el[m][n] = ret;
    return EXIT_SUCCESS;
}

int matrix_mul_normal(const matrix_t *A, const matrix_t *B, matrix_t *C){
    for(size_t m = 0; m < C->M; ++m){
        for(size_t n = 0; n < C->N; ++n){
            if(matrix_mul_compute_element(A, B, C, m, n)) return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

typedef struct{
    const matrix_t *A, *B;
    matrix_t *C;
    size_t n;
} arg_a_t;
void* matrix_mul_a_column(void *arg_in){
    arg_a_t *arg = arg_in;
    int *ret = malloc(sizeof(int));
    *ret = EXIT_SUCCESS;
    for(size_t m = 0; m < arg->C->M; ++m){
        if(matrix_mul_compute_element(arg->A, arg->B, arg->C, m, arg->n)){
            *ret = EXIT_FAILURE;
            return ret;
        }
    }
    return ret;
}
int matrix_mul_a(const matrix_t *A, const matrix_t *B, matrix_t *C){
    pthread_t *tid = calloc(C->N, sizeof(pthread_t));
    for(size_t n = 0; n < C->N; ++n){
        arg_a_t *arg = malloc(sizeof(arg_a_t));
        arg->A = A;
        arg->B = B;
        arg->C = C;
        arg->n = n;
        if(pthread_create(&tid[n], NULL, matrix_mul_a_column, arg)) exit(1);
    }
    for(size_t n = 0; n < C->N; ++n){
        int *ret;
        pthread_join(tid[n], (void **)&ret);
        if(*ret) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

typedef struct {
    const matrix_t *A, *B;
    matrix_t *C;
    size_t m, n;
} arg_b_t;
void* matrix_mul_b_el(void *arg_in){
    arg_b_t *arg = arg_in;
    int *ret = malloc(sizeof(int));
    *ret = EXIT_SUCCESS;
    if(matrix_mul_compute_element(arg->A, arg->B, arg->C, arg->m, arg->n)){
        *ret = EXIT_FAILURE;
        return ret;
    }
    return ret;
}
int matrix_mul_b(const matrix_t *A, const matrix_t *B, matrix_t *C){
    pthread_t *tid = calloc(C->M*C->N, sizeof(pthread_t));
    for(size_t m = 0; m < C->M; ++m){
        for(size_t n = 0; n < C->N; ++n){
            arg_b_t *arg = malloc(sizeof(arg_b_t));
            arg->A = A;
            arg->B = B;
            arg->C = C;
            arg->m = m;
            arg->n = n;
            if(pthread_create(&tid[m*C->N+n], NULL, matrix_mul_b_el, arg)) exit(1);
        }
    }
    for(size_t i = 0; i < C->M*C->N; ++i){
        int *ret;
        pthread_join(tid[i], (void **)&ret);
        if(*ret) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int num_threads;
typedef struct {
    const matrix_t *A, *B;
    matrix_t *C;
    size_t l, r;
} arg_c_t;
void* matrix_mul_c_compute(void *arg_in){
    int *ret = malloc(sizeof(int));
    *ret = EXIT_SUCCESS;
    arg_c_t *arg = arg_in;
    for(size_t i = arg->l; i < arg->r; ++i){
        size_t m = i/arg->C->N, n = i%arg->C->N;
        if(matrix_mul_compute_element(arg->A, arg->B, arg->C, m, n)){
            *ret = EXIT_FAILURE;
            return ret;
        }
    }
    return ret;
}
int matrix_mul_c(const matrix_t *A, const matrix_t *B, matrix_t *C){
    size_t MN = C->M*C->N;
    size_t l = 0;
    pthread_t *tid = calloc(sizeof(pthread_t), num_threads);
    for(int t = 0; t < num_threads; ++t){
        size_t delta = (MN-l)/(num_threads-t);
        size_t r = l + delta;
        arg_c_t *arg = malloc(sizeof(arg_c_t));
        arg->A = A;
        arg->B = B;
        arg->C = C;
        arg->l = l;
        arg->r = r;
        if(pthread_create(&tid[t], NULL, matrix_mul_c_compute, arg)) exit(EXIT_FAILURE);
    }
    for(int t = 0; t < num_threads; ++t){
        int *ret = NULL;
        pthread_join(tid[t], (void **)&ret);
        if(*ret) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

size_t next_i;
typedef struct{
    const matrix_t *A, *B;
    matrix_t *C;
} arg_d_t;
void* matrix_mul_d_work(void *arg_in){
    int *ret = malloc(sizeof(int));
    *ret = EXIT_SUCCESS;
    arg_d_t *arg = arg_in;
    size_t i;
    while((i = next_i) < arg->C->M*arg->C->N){
        next_i = i+1;
        size_t m = i/arg->C->N, n = i%arg->C->N;
        if(matrix_mul_compute_element(arg->A, arg->B, arg->C, m, n)){
            *ret = EXIT_FAILURE;
            return ret;
        }
    }
    return ret;
}
int matrix_mul_d(const matrix_t *A, const matrix_t *B, matrix_t *C){
    next_i = 0;
    arg_d_t *arg = malloc(sizeof(arg_d_t));
    arg->A = A;
    arg->B = B;
    arg->C = C;
    pthread_t *tid = calloc(sizeof(pthread_t), num_threads);
    for(int t = 0; t < num_threads; ++t){
        if(pthread_create(&tid[t], NULL, matrix_mul_d_work, arg)) exit(EXIT_FAILURE);
    }
    for(int t = 0; t < num_threads; ++t){
        int *ret = NULL;
        pthread_join(tid[t], (void **)&ret);
        if(*ret) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int matrix_mul(const matrix_t *A, const matrix_t *B, matrix_t *C,
               int (*f)(const matrix_t*, const matrix_t*, matrix_t*)){
    if(A->N != B->M) return EXIT_FAILURE;
    C->M = A->M;
    C->N = B->N;
    C->el = calloc(C->M, sizeof(val_t *));
    for(size_t m = 0; m < C->M; ++m)
        C->el[m] = calloc(C->N, sizeof(val_t));
    return f(A, B, C);
}

int main(int argc, char *argv[]){
    if(argc != 4) return EXIT_FAILURE;
    
    int in_filedes = open(argv[1], O_RDONLY);
    dup2(in_filedes, STDIN_FILENO);

    int out_filedes = creat(argv[2], S_IRWXU);
    dup2(out_filedes, STDOUT_FILENO);

    sscanf(argv[3], "%d", &num_threads);

    matrix_t A, B;
    matrix_read(&A);
    matrix_read(&B);
    matrix_t C;
    matrix_mul(&A, &B, &C, matrix_mul_a);
    matrix_print(&C);
    matrix_mul(&A, &B, &C, matrix_mul_b);
    matrix_print(&C);
    matrix_mul(&A, &B, &C, matrix_mul_c);
    matrix_print(&C);
    matrix_mul(&A, &B, &C, matrix_mul_d);
    matrix_print(&C);  
    return 0;
}
