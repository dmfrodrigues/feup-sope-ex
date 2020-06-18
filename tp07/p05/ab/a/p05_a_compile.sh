#!/bin/bash

set -e

gcc -Wall prod.c ../shared_memory.c ../../queue.c -lrt -pthread -o prod
gcc -Wall cons.c ../shared_memory.c ../../queue.c -lrt -pthread -o cons
