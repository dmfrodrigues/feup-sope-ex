gcc -Wall p09_server.c -o p09_server
gcc -Wall p09_client.c -o p09_client
./p09_server &
sleep 1
./p09_client ls -la
sleep 1
./p09_client du ../../
sleep 7.5
./p09_client git status
