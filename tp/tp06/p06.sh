#!/bin/bash
set -e -x
gcc -Wall -pthread p06_server.c -o p06_server
gcc -Wall -pthread p06_client.c -o p06_client
./p06_server &
sleep 1
echo $(./p06_client sum 2 3)
echo $(./p06_client sub 2 3)
echo $(./p06_client mul 2 3)
echo $(./p06_client div 2 3)
echo $(./p06_client mul 0 0)
