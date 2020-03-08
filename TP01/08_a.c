#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main(int argc, char *argv[]){
    assert(argc == 3);
    srand(time(NULL));
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int i = 0;
    int n;
    do{
        n = rand()%n1;
        printf("%d %d\n", i, n);
        ++i;
    }while(n != n2);
    return 0;
}
