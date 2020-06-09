#!/bin/bash

set -e

gcc -Wall p01_a.c -o p01_a
echo -e "2 5\n" | ./p01_a # 7
