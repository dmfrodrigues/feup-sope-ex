gcc -Wall p01b.c -o p01b
./p01_kill.sh 1s -SIGINT ./p01b &
./p01b
echo $?
