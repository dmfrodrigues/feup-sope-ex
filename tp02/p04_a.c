#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[]){
    assert(argc == 2);
    int dst = open(argv[1], O_WRONLY | O_CREAT, 0750);
    char ch;
    while(read(STDIN_FILENO, &ch, 1) != 0){
        write(dst, &ch, 1);
    }
    close(dst);
    return 0;
}
