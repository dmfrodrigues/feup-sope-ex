gcc -Wall p01a.c -o p01a
./p01_kill.sh 1s -SIGINT ./p01a &
./p01a
echo $?
./p01_kill.sh 1s -SIGUSR1 ./p01a &
./p01a
echo $?
