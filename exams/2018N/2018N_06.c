#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

char *filename = NULL;
char *destination_dir = NULL;

int process_dir(char *dirname) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    if(!(dir = opendir(dirname))) return 1;
    while((entry = readdir(dir)) != NULL) {
        char path[1024];
        // --- BLOCO A ---
        sprintf(path, "%s/%s", dirname, entry->d_name);
        if(stat(path, &statbuf)) return 1;
        if(S_ISDIR(statbuf.st_mode)) {  //se 'entry' for um diretorio
            /**
             * This instruction is fundamental since it rejects the
             * 'pseudofolders' `.` (current folder) and
             * `..` (parent folder).
             * Otherwise, `process_dir` would be called over and over again
             * for the first folder and its successive parents.
             */
            if(strcmp(entry->d_name, ".") == 0 ||
               strcmp(entry->d_name, "..") == 0)
                continue;
            pid_t pid = fork();
            if(pid == 0)/** Child */{
                process_dir(path);
                exit(0);
            } else if(pid < 0) return 1;
        }
        // --- FIM DO BLOCO A ---
        // --- BLOCO B ---
        else if(S_ISREG(statbuf.st_mode)){//se 'entry' for ficheiro regular
            //se o nome do ficheiro contiver filename
            if(strstr(entry->d_name, filename) != NULL) {
                //cria um processo que invoca o utilitario 'cp'
                pid_t pid = fork();
                if(pid == 0)/** Child */{
                    if(execlp("cp", "cp", path, destination_dir, NULL))
                        return 1;
                } else if(pid < 0) return 1;                                       
            }
        }
        // --- FIM DO BLOCO B ---
    }
    return 0;
}

// Usage: find_and_copy <dir_to_search> <filename> <destination_dir>
// Example: ./find_and_copy 2018N_06_testdir/src file 2018N_06_testdir/dst
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
