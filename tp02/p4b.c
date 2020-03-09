#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

#define SMAX 50

typedef struct Student{
    char name[SMAX+1];
    int grade;
} Student_t;

int main(int argc, char *argv[]){
    assert(argc == 3);
    int N = atoi(argv[2]);
    int dst = open(argv[1], O_WRONLY | O_CREAT, 0750);
    for(int i = 0; i < N; ++i){
        Student_t s;
        printf("Student: ");
        scanf("%s", s.name);
        printf("Grade: ");
        scanf("%d", &s.grade);
        write(dst, &s, sizeof(s));
    }
    close(dst);
    return 0;
}
