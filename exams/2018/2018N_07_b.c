#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 1024

struct Request {
    pid_t pid;
    size_t nbytes;
    char data[1000];
};

void createRequest(const char *filename, struct Request *req);

struct Reply {
    size_t nbytes;
    char data[1000];
};

void writeRequest(const struct Request *req, int to){
    char buf[BUF_SIZE];
    char *cur = buf;
    *cur = req->pid   ; cur += sizeof(pid_t );
    *cur = req->nbytes; cur += sizeof(size_t);
    memcpy(cur, req->data, req->nbytes); cur += req->nbytes;
    write(to, buf, cur-buf);
}

void readReply(struct Reply *res, int fr){
    read(fr, &res->nbytes, sizeof(size_t));
    read(fr, res->data, res->nbytes);
}

int main(int argc, char *argv[]) {
    if(argc != 2) return 1;
    
    char ansfifo_name[256];
    sprintf(ansfifo_name, "/tmp/ans%d", getpid());
    mkfifo(ansfifo_name, 0660);
    
    struct Request req;
    createRequest(argv[1], &req);
    int reqfifo_fd = open("/tmp/requests", O_WRONLY);
    writeRequest(&req, reqfifo_fd);
    close(reqfifo_fd);

    struct Reply res;
    int ansfifo_fd = open(ansfifo_name, O_RDONLY);
    readReply(&res, ansfifo_fd);
    close(ansfifo_fd);
    write(STDOUT_FILENO, res.data, res.nbytes);
    
    unlink(ansfifo_name);

    return 0;
}

void createRequest(const char *filename, struct Request *req) {
    int file = open(filename, O_RDONLY);
    char buffer[BUF_SIZE];  // BUF_SIZE < 1000
    size_t n;
    req->pid = getpid();
    req->nbytes = 0;
    while((n = read(file, buffer, BUF_SIZE)) > 0) {
        memcpy(&req-> data[req-> nbytes], buffer, n);
        req-> nbytes += n;
    }
    close(file);
}
