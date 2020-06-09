#!/bin/bash

set -e

gcc -Wall p01_c.c -o p01_c
echo -e "2 5\n" | ./p01_c # 7
