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
        case -1: perror("fork"); break;
        case 0:  // filho1
            pid = fork();
            switch(pid){
                case -1: perror("fork"); break;
                case 0: //filho2
                    write(STDOUT_FILENO, "Hello ", 6);
                    break;
                default: //filho1
                    wait(NULL);
                    write(STDOUT_FILENO, "my ", 3);
                    break;
            }
            break;
        default:  // pai
            wait(NULL);
            write(STDOUT_FILENO, "friends!\n", 9);
            break;
    }
    return 0;
}