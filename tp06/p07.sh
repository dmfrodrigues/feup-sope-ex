set -e

gcc -Wall -pthread p07.c -o p07
rm -rf ../test
mkdir ../test
./p07 ../test ../tp05 .
