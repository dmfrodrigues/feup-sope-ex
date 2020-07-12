#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    char name[256];

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
    }

    return 0;
}