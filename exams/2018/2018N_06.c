#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char *filename = NULL;
char *destination_dir = NULL;

int process_dir(char *dirname) {
    DIR *dir;
    struct dirent *entry;
    // struct stat statbuf;
    if(!(dir = opendir(dirname))) return 1;
    while((entry = readdir(dir)) != NULL) {
        char path[1024];
        // ‐‐‐ BLOCO A ‐‐‐
        ...;
        if(...) {  //se 'entry' for um diretório
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            ...;  //cria um processo que invoca process_dir()
        }
        // ‐‐‐ FIM DO BLOCO A ‐‐‐
        // ‐‐‐ BLOCO B ‐‐‐
        else if(...) {  //se 'entry' for um ficheiro regular
            ...;
            if(strstr(entry->d_name, filename) != NULL) {  //se o nome do ficheiro contiver filename
                ...;                                        //cria um processo que invoca o utilitário 'cp'
            }
        }
        // ‐‐‐ FIM DO BLOCO B ‐‐‐
    }
    return 0;
}

// Usage: find_and_copy <dir_to_search> <filename> <destination_dir>
int main(int argc, char *argv[]) {
    // 1)
    if(argc != 4) return 1;
    // 2)
    char *dir_to_search = argv[1];
    filename = argv[2];
    destination_dir = argv[3];
    // 3)
    if(signal(SIGINT, SIG_IGN) == SIG_ERR) return 1;
    // 4)
    if(process_dir(dir_to_search)) return 1;

    return 0;
}
