set -e

gcc -Wall p07_server.c -o p07_server
gcc -Wall p07_client.c -o p07_client
#./p07_server &
#sleep 1
#echo "7 3" | ./p07_client
