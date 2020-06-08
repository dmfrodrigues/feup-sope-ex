#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[]){
    assert(argc == 2);
    int src = open(argv[1], O_RDONLY);
    char ch;
    while(read(src, &ch, 1) != 0){
        write(STDOUT_FILENO, &ch, 1);
    }
    close(src);
    return 0;
}
