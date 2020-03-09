#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    if (argc != 2 && argc != 3) {
        printf("usage: %s dirname [dest]\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0)
        printf(
            "My child is going to execute command              \"ls -laR "
            "%s\"\n",
            argv[1]);
    else if (pid == 0) {
        if (argc == 3) {
            int fid = open(argv[2], O_WRONLY | O_CREAT);
            dup2(fid, STDOUT_FILENO);
            close(fid);
        }
        char *args[] = {"ls", "-laR", argv[1], NULL};
        execve("/bin/ls", args, envp);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}