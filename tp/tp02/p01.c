#include <unistd.h>
#include <termios.h>
#include <string.h>

#define MAX_PSWD 20

int read_password(char *s){
    struct termios term, oldterm;
    tcgetattr(STDIN_FILENO, &oldterm);
    term = oldterm;
    term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

    const char echo = '*';
    char ch;
    int i = 0;
    while(i < MAX_PSWD && read(STDIN_FILENO, &ch, 1) && ch != '\n'){
        s[i++] = ch;
        write(STDOUT_FILENO, &echo, 1);
    }
    s[i] = '\0';
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);

    return 0;
}

int main(){
    char s[MAX_PSWD+1];
    write(STDOUT_FILENO, "Password? ", 10);
    read_password(s);
    write(STDOUT_FILENO, "\nPassword: ", 11);
    write(STDOUT_FILENO, s, strlen(s));
    write(STDOUT_FILENO, "\n", 1);
    return 0;
}