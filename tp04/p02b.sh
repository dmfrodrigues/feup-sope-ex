gcc -Wall p02a.c -o p02a
./p01_kill.sh 1s -SIGTERM ./p02a &
./p01_kill.sh 1s -SIGTERM ./p02a &
./p02a
echo $?
