#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]){
    printf("Hello");
    if(argc > 1){
        for(int i = 1; i < argc; ++i){
            printf(" %s", argv[i]);
        }
    }else{
        char *user = getenv("USER_NAME");
        if(user != NULL){
            printf(" %s", user);
        }
    }
    printf("!\n");
    return 0;
}
