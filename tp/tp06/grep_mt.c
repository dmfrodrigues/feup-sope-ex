#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>

#include <pthread.h>
#include <errno.h>

/*
int copy_file(const char *src_path, const char *dst_path){
    int src = open(src_path, O_RDONLY);
    int dst = creat(dst_path, 0);
    char ch[PIPE_BUF];
    int r;
    while((r = read(src, ch, PIPE_BUF)) != 0){
        write(dst, ch, r);
    }
    close(src);
    close(dst);
    return 0;
}
*/

#define LINES_MAX_SIZE 1024

int search_in(const char *to_search, const char *filepath, int **lines, int *lines_size){
    char *l = NULL; size_t l_size = 0;
    FILE *file = fopen(filepath, "r");
    *lines_size = 0;
    *lines = malloc(LINES_MAX_SIZE*sizeof(int));
    int num_line = 1;
    while(getline(&l, &l_size, file) != -1){
        if(strstr(l, to_search) != NULL){
            (*lines)[(*lines_size)++] = num_line;
        }
        ++num_line;
    }
    return EXIT_SUCCESS;
}

typedef struct {
    const char *to_search, *filepath;
} arg_struct_t;

typedef struct {
    int *lines;
    int lines_size;
} ret_struct_t;

void* th_func(void *arg){
    arg_struct_t *arg_struct = arg;
    int *lines = NULL;
    int lines_size;
    search_in(arg_struct->to_search, arg_struct->filepath, &lines, &lines_size);
    ret_struct_t *ret_struct = malloc(sizeof(ret_struct_t));
    ret_struct->lines = lines;
    ret_struct->lines_size = lines_size;
    return ret_struct;
}

int main(int argc, char *argv[]){
    if(argc < 2) return 1;
    const char *to_search = argv[1];

    pthread_t *tid = malloc((argc-2)*sizeof(pthread_t));

    for(size_t i = 2; i < argc; ++i){

        arg_struct_t *arg = malloc(sizeof(arg_struct_t));
        arg->to_search = to_search;
        arg->filepath  = argv[i];

        pthread_create(&tid[i-2], NULL, th_func, arg);
    }

    for(size_t i = 2; i < argc; ++i){
        ret_struct_t *ret = NULL;
        pthread_join(tid[i-2], (void**)&ret);

        for(int j = 0; j < ret->lines_size; ++j){
            printf("Found in %s, line %d\n", argv[i], ret->lines[j]);
        }
    }

    return 0;
}
