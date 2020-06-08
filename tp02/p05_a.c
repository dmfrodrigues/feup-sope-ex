#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
    int fd;
    char *text1 = "AAAAA";
    char *text2 = "BBBBB";
    fd = open("f1.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if(fd == -1) printf("Error: %d\n", errno);
    write(fd, text1, 5); getchar();
    write(fd, text2, 5);
    close(fd);
    return 0;
}