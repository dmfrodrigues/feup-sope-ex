#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * 1. Sim, um handler pode ser instalado mais que uma vez,
 * e será corrido mais que uma vez.
 * 
 * 2. Se abort() for chamado antes de escrever "Main done!",
 * ocorre um 'core dump' e os handlers não são chamados.
 * 
 * 3. Se algum dos handlers terminar com exit(),
 * o programa termina com o código de saída fornecido como argumento a exit();
 */

void fexit1(void){
    printf("Executing exit handler 1\n");
}
void fexit2(void){
    printf("Executing exit handler 2\n");
}
void fexit3(void){
    printf("Executing exit handler 3\n");
    exit(3);
}

int main(int argc, char *argv[]){
    if(strcmp(argv[1], "1") == 0){
        atexit(fexit1);
        atexit(fexit2);
        atexit(fexit2);
        printf("Main done!\n");
        return 0;
    }
    if(strcmp(argv[1], "2") == 0){
        atexit(fexit1);
        atexit(fexit2);
        abort();
        printf("Main done!\n");
        return 0;
    }
    if(strcmp(argv[1], "3") == 0){
        atexit(fexit1);
        atexit(fexit3);
        atexit(fexit2);
        printf("Main done!\n");
        return 0;
    }
    return 0;
}
