gcc -Wall p03a.c -o p03a
./p01_kill.sh  5.5 -SIGUSR2 ./p03a &
./p01_kill.sh 12.5 -SIGUSR1 ./p03a &
./p01_kill.sh 20.5 -SIGTERM ./p03a &
./p03a
echo $?
