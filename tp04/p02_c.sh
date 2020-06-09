set -e

gcc -Wall p02_c.c -o p02c
./kill.sh  1s -SIGINT ./p02c &
./kill.sh  2s -SIGINT ./p02c &
./kill.sh  2s -SIGINT ./p02c &
./kill.sh  2s -SIGINT ./p02c &
./kill.sh  3s -SIGTERM ./p02c &
./kill.sh 25s -SIGKILL ./p02c &
./p02c && exit 1
echo $?
