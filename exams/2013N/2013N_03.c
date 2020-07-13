#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int redirectStdin(const char *file_path) {
    int file_fd = open(file_path, O_RDONLY);
    if(file_fd == -1) return -1;
    if(dup2(file_fd, STDIN_FILENO) == -1) return -1;
    return 0;
}

int main(int argc, char *argv[]) {                                //<===
  int numValuesRead, value;
  const char *file_path = argv[1];                                //<===
  if(redirectStdin(file_path) < 0) {                              //<===
    perror("redirectStdin");
    exit(1);
  }
  
  numValuesRead = scanf("%d", &value);
  if(numValuesRead == 1) {
    printf("'value' = %d was read from '%s'\n", value, file_path);//<===
    exit(0);
  }
  else {
    printf("Error reading 'value' from '%s'\n", file_path);       //<===
    exit(1);
  }
}
