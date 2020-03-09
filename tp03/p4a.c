#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 50000

int main(void) {
    pid_t pid;
    pid = fork();
    switch (pid) {
        case -1:
            perror("fork");
            break;
        case 0:  // filho
            write(STDOUT_FILENO, "Hello ", 6);
            break;
        default:  // pai
            wait(NULL);
            write(STDOUT_FILENO, "world !\n", 8);
    }
    return 0;
}