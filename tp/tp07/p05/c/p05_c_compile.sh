#!/bin/bash

set -e

gcc -Wall main.c shared_memory.c ../queue.c -lrt -pthread -o main
