#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>

#include <pthread.h>

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

void* th_func(void *arg){
    char **path = arg;
    copy_file(path[0], path[1]);
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc < 2) return 1;

    const char *copy_path_dir = argv[1];

    size_t N = 1024, cur = 0;
    pthread_t *tid = malloc(N*sizeof(pthread_t));
    for(size_t i = 2; i < argc; ++i){
        const char *path = argv[i];
        DIR *dir = opendir(path);
        struct dirent *dir_point = NULL;
        while ((dir_point = readdir(dir)) != NULL) {
            if(strcmp(dir_point->d_name, ".") == 0 || 
               strcmp(dir_point->d_name, "..") == 0) continue;
            char *new_path = malloc(PATH_MAX*sizeof(char));{
                strcat(strcat(strcpy(new_path, path), "/"), dir_point->d_name);
                struct stat st;
                lstat(new_path, &st);
                if(!S_ISREG(st.st_mode)) continue;
                char *copy_path = malloc(PATH_MAX*sizeof(char));
                strcat(strcat(strcpy(copy_path, copy_path_dir), "/"), dir_point->d_name);

                while(N <= cur){
                    N *= 2;
                    tid = realloc(tid, N);
                }
                char **arg = malloc(2*sizeof(char*));
                arg[0] = new_path; arg[1] = copy_path;
                pthread_create(&tid[cur], NULL, th_func, arg);
                pthread_join(tid[cur], NULL);
                ++cur;
                // copy_file(new_path, copy_path);
            }
        }
        closedir(dir);
    }


    return 0;
}
