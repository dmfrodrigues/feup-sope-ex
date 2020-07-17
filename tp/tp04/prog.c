#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    for(int i = 0; i < 6; ++i){
        sleep(5);
        printf("%s\n", argv[1]);
    }
    return 0;
}
