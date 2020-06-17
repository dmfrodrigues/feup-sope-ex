int process_dir(char *dirname) {
    DIR *dir;
    struct dirent *entry;
    // struct stat statbuf;
    if(!(dir = opendir(dirname))) return 1;
    while((entry = readdir(dir)) != NULL) {
        charpath[1024];
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