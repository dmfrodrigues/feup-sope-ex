set -e

gcc -Wall p02_a.c -o p02a
./kill.sh 1s -SIGTERM ./p02a &
./kill.sh 1s -SIGTERM ./p02a &
./p02a && exit 1
echo $?
