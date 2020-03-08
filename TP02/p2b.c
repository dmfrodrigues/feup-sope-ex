#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int src = open("infile.txt", O_RDONLY);
    int dst = open("outfile.txt", O_WRONLY | O_CREAT, 0750);
    char ch;
    while(read(src, &ch, 1) != 0){
        write(dst, &ch, 1);
    }
    close(src);
    close(dst);
    return 0;
}
