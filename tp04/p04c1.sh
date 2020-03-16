gcc -Wall p04a.c -o p04a
./p01_kill.sh 3s -SIGINT ./p04a &
./p04a
echo $?
