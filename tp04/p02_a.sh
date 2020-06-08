gcc -Wall p02a.c -o p02a
./p01_kill.sh 1s -SIGINT ./p02a &
./p01_kill.sh 2s -SIGINT ./p02a &
./p02a
echo $?
