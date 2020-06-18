#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 256

void full_copy(int from, int to);

int main(int argc, char *argv[]){
    if(argc != 2) return 1;
    int inputfile_fd = open(argv[1], O_RDONLY);
    if(inputfile_fd == -1) return 1;
    int pipe_to[2];
    int pipe_fr[2];
    pipe(pipe_to);
    pipe(pipe_fr);
    pid_t pid = fork();
    if(pid == 0){
        close(pipe_to[1]); dup2(pipe_to[0], STDIN_FILENO);
        close(pipe_fr[0]); dup2(pipe_fr[1], STDOUT_FILENO);
        execlp("./compress.sh", "./compress.sh", NULL);
        return 1;
    } else if(pid < 0) return 1;
    close(pipe_to[0]);
    close(pipe_fr[1]);
    full_copy(inputfile_fd, pipe_to[1]);
    full_copy(pipe_fr[0], STDOUT_FILENO);
    return 0;
}

void full_copy(int from, int to){
    char buffer[BUF_SIZE]; // BUF_SIZE < 1000
    size_t n;
    while ((n = read(from,buffer,BUF_SIZE)) > 0)
        write(to, buffer, n);
    close(from);
    close(to);
}
