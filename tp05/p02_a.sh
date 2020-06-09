#!/bin/bash

set -e

gcc -Wall p02_a.c -o p02_a
echo -e "2 5\n" | ./p02_a # 7
