#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int fd;
    char *text1 = "AAAAA";
    char *text2 = "BBBBB";

    fd = open("f1.txt", O_CREAT | O_TRUNC | O_WRONLY | O_SYNC, 0600);
    if (fd == -1) printf("Error: %d\n", errno);
    write(fd, text1, 5);
    write(fd, text2, 5);
    close(fd);
    return 0;
}