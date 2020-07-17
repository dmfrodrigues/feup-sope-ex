set -e

gcc -Wall p02_a.c -o p02a
./kill.sh  1s -SIGINT ./p02a &
./kill.sh  2s -SIGINT ./p02a &
./kill.sh  3s -SIGINT ./p02a &
./kill.sh  4s -SIGINT ./p02a &
./kill.sh 25s -SIGTERM ./p02a &
./p02a && exit 1
echo $?
