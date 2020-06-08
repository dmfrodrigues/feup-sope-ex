gcc -Wall p01c.c -o p01c
./p01_kill.sh 1s -SIGINT ./p01c &
./p01c
echo $?
