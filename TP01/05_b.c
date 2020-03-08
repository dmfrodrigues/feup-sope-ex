#include <stdio.h>
#include <string.h>

const char *user_str = "USER=";
const int user_sz = 5;

int main(int argc, char *argv[], char *envp[]){
    printf("Hello");
    if(argc > 1){
        for(int i = 1; i < argc; ++i){
            printf(" %s", argv[i]);
        }
    }else{
        int i;
        for(i = 0; envp[i] != NULL; ++i){
            if(strncmp(envp[i], user_str, user_sz) == 0) break;
        }
        if(envp[i] != NULL){
            printf(" %s", envp[i]+user_sz);
        }
    }
    printf("!\n");
    return 0;
}
