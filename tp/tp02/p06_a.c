#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    DIR* dirp;
    struct dirent* direntp;
    struct stat stat_buf;
    char* str;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
        exit(1);
    }

    if((dirp = opendir(argv[1])) == NULL) {
        perror(argv[1]);
        exit(2);
    }

    while((direntp = readdir(dirp)) != NULL) {
        char d_fname[255];
        strcat(strcat(strcpy(d_fname, argv[1]), "/"), direntp->d_name);
        if(stat(d_fname, &stat_buf)) printf("%s: errno: %d\n", d_fname, errno);
        if(S_ISREG(stat_buf.st_mode))
            str = "regular";
        else if(S_ISDIR(stat_buf.st_mode))
            str = "directory";
        else
            str = "other";
        printf("%-30s - %-15s - %ld\n", d_fname, str, stat_buf.st_ino);
    }
    closedir(dirp);
    exit(0);
}