#include <sys/types.h>

typedef enum {
    operation_sum = 0,
    operation_sub = 1,
    operation_mul = 2,
    operation_div = 3
} operation_t;

typedef struct {
    operation_t op;
    double a, b;
    pid_t pid;
} request_t;
