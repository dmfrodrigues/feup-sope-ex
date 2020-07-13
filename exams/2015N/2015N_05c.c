#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    char name[256];

    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid == 0){
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        char formatter_path[256];
        sprintf(formatter_path, "%s/formatter", getenv("HOME"));
        execl(formatter_path, formatter_path, NULL);
    }
    close(fd[0]);

    const char *dir_name = argv[1];
    const char *special_name = argv[2];
    DIR *dirp = opendir(dir_name);
    if(dirp == NULL){ perror(dir_name); exit(1); }
    struct dirent *direntp;
    struct stat stat_buf;
    while((direntp = readdir(dirp)) != NULL){
        char d_name[1024];
        sprintf(d_name, "%s/%s", dir_name, direntp->d_name);
        stat(d_name, &stat_buf);

        strcpy(name, direntp->d_name);

        int type = 0;
        if(S_ISREG(stat_buf.st_mode)) type = 1;
        if(S_ISDIR(stat_buf.st_mode)) type = 2;
        if(strcmp(direntp->d_name, special_name) == 0) type = 100;
        ino_t inode = direntp->d_ino;
        blkcnt_t sz = stat_buf.st_blocks;

        write(fd[1], &type, sizeof(int));
        write(fd[1], &inode, sizeof(ino_t));
        write(fd[1], &sz, sizeof(blkcnt_t));
        write(fd[1], name, strlen(name)+1);
    }

    return 0;
}