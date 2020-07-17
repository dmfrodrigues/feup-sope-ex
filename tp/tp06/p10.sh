set -e

gcc -Wall -pthread p10.c -o p10
./p10 1 < p10.in > p10.out
