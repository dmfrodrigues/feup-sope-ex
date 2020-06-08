gcc -Wall p02c.c -o p02c
./p01_kill.sh 1s -SIGINT ./p02c &
./p01_kill.sh 2s -SIGINT ./p02c &
./p01_kill.sh 2s -SIGINT ./p02c &
./p01_kill.sh 2s -SIGINT ./p02c &
./p01_kill.sh 3s -SIGTERM ./p02c &
./p02c
echo $?
