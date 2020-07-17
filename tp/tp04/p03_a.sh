set -e

gcc -Wall p03_a.c -o p03a
./kill.sh  5.5 -SIGUSR2 ./p03a &
./kill.sh 12.5 -SIGUSR1 ./p03a &
./kill.sh 20.5 -SIGTERM ./p03a &
./p03a && exit 1
echo $?

# v=1 v=2 v=3 v=4 v=5
# Killing 12122 ("./p03a") with -SIGUSR2
# v=4 v=3 v=2 v=1 v=0 v=-1 v=-2
# Killing 12122 ("./p03a") with -SIGUSR1
# v=-1 v=0 v=1 v=2 v=3 v=4 v=5 v=6 v=7
# Killing 12122 ("./p03a") with -SIGTERM
# ./p03_a.sh: line 7: 12122 Terminated              ./p03a
