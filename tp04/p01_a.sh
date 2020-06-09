#!/bin/bash

set -e

gcc -Wall p01_a.c -o p01a
./kill.sh 1s -SIGINT ./p01a &
./p01a
echo $? # 0
./kill.sh 1s -SIGUSR1 ./p01a &
./p01a && exit 1
echo $? # 138
