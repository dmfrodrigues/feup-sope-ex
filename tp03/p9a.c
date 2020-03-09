#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    if (argc != 2) {
        printf("usage: %s dirname\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0){
        printf(
            "My child is going to execute command              \"ls -laR "
            "%s\"\n",
            argv[1]);
        int statloc;
        wait(&statloc);
        if(WIFEXITED(statloc)){
            printf("Terminated normally with exit status %d\n", WEXITSTATUS(statloc));
        }
    } else if (pid == 0) {
        char *args[] = {"ls", "-laR", argv[1], NULL};
        execve("/bin/ls", args, envp);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}