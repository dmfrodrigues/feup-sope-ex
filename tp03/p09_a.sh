set -e

gcc -Wall p09_a.c -o p09_a
./p09_a .
./p09_a a
./p09_a / &
sleep 1s
kill $(ps u | grep "ls -laR" | head -n 1 | awk '{print $2}')
