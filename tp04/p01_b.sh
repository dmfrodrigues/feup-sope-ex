set -e

gcc -Wall p01_b.c -o p01b
./kill.sh 1s -SIGINT ./p01b &
./p01b
echo $?
