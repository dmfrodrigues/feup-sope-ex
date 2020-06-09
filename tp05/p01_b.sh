#!/bin/bash

set -e

gcc -Wall p01_b.c -o p01_b
echo -e "2 5\n" | ./p01_b # 7
