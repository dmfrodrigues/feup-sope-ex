#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[]){
    int src = open(argv[1], O_RDONLY);
    int dst = STDIN_FILENO;
    char ch;
    if(argc == 3){
        dst = open(argv[2], O_WRONLY | O_CREAT, 0750);
        dup2(dst, STDOUT_FILENO);
    }
    while(read(src, &ch, 1) != 0){
        write(STDOUT_FILENO, &ch, 1);
    }
    if(argc == 3) close(dst);
    close(src);
    return 0;
}
