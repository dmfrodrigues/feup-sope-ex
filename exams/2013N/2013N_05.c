#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    // 1.
    const char *dir1 = argv[1];
    const char *dir2 = argv[2];
    const char *dt = argv[3];
    // 2.
    pid_t pid = fork();
    if(pid == 0){
        execlp("bckp", "bckp", dir1, dir2, dt, NULL);
        perror("bckp");
        exit(1);
    } else {
        int status;
        if(wait(&status) != pid){
            perror("wait");
            exit(1);
        }
        if(status) exit(1);
    }
    // 3.
    DIR *dirp = opendir(dir1);
    struct dirent *direntp = NULL;
    struct stat stat_buf;
    while((direntp = readdir(dirp)) != NULL){
        char dir1_dir11[1024];
        sprintf(dir1_dir11, "%s/%s", dir1, direntp->d_name);
        stat(dir1_dir11, &stat_buf);
        if(!S_ISDIR(stat_buf.st_mode)) continue;
        pid_t pid = fork();
        if(pid == 0){
            char dir2_dir11[1024];
            sprintf(dir2_dir11, "%s/%s", dir2, direntp->d_name);
            execlp("bckp", "bckp", dir1_dir11, dir2_dir11, dt, NULL);
        } else {
            int status;
            wait(&status);
        }
    }

    return 0;
}