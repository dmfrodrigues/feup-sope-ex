set -e

rm -f $1 $1.o
if gcc -Wall $1.c -o $1 > /dev/null 2>&1 ; then
    ./$1
else
    echo COMPILATION ERROR 
fi

