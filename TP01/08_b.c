#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    assert(argc == 3);
    srand(time(NULL));
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int i = 0;
    int n;

    struct tms *tms_start = malloc(sizeof(struct tms));
    struct tms *tms_end   = malloc(sizeof(struct tms));
    clock_t start, end;

    start = times(tms_start);

    do{
        n = rand()%n1;
        printf("%d %d\n", i, n);
        ++i;
    }while(n != n2);

    end = times(tms_end);

    const int ticks_seg = sysconf(_SC_CLK_TCK);

    printf("Tempo real: %f s\n", (float)(end-start)/ticks_seg);
    printf("Tempo user: %f s\n", (float)(tms_end->tms_utime - tms_start->tms_utime)/ticks_seg);
    printf("Tempo syst: %f s\n", (float)(tms_end->tms_stime - tms_start->tms_stime)/ticks_seg);

    return 0;
}
