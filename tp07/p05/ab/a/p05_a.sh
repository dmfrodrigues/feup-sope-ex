set -e

gcc -Wall prod.c ../shared_memory.c ../../queue.c -lrt -pthread -o prod
gcc -Wall cons.c ../shared_memory.c ../../queue.c -lrt -pthread -o cons

./prod 10 100 &
./cons 10

sleep 1

./prod 10 2 &
./cons 10

sleep 1

./prod 10 1 &
./cons 10
