set -e

gcc -Wall p04.c -pthread -lrt -o p04
./p04 7000 10
