#include <stdio.h>
#include <stdlib.h>

void fexit1(void){
    printf("Executing exit handler 1\n");
}
void fexit2(void){
    printf("Executing exit handler 2\n");
}

int main(){
    atexit(fexit1);
    atexit(fexit2);
    printf("Main done!\n");
    return 0;
}
