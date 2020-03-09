#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#define NMAX 255
#define TMAX 100

int main(void){
    char buf[NMAX];
    char *tok[TMAX];
    while(fgets(buf, NMAX, stdin) != NULL){
        char *p = NULL;
        p = strtok(buf, " ")
    }

    return 0;
}
