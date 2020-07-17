set -e

gcc -Wall p04_a.c -o p04a
./kill.sh 3s -SIGINT ./p04a &
./p04a && exit 1
echo $?
