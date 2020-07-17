set -e

gcc -Wall p01_c.c -o p01c
./kill.sh 1s -SIGINT ./p01c &
./p01c
echo $?
