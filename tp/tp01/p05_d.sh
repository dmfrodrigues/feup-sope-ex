set -e

USER_NAME='Diogo Rodrigues'
echo USER_NAME:
printenv USER_NAME && exit 1
export USER_NAME
echo USER_NAME:
printenv USER_NAME
gcc -Wall p05_d.c
./a.out Rui Silva
./a.out
