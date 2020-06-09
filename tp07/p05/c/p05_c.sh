#!/bin/bash

set -e

gcc -Wall main.c shared_memory.c ../queue.c -lrt -pthread -o main

sleep 1
./main 10 100

sleep 1
./main 10 2

sleep 1
./main 10 1
