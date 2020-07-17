gcc -Wall p03_b.c
./a.out
ret=$?
echo $ret
if [ "$ret" -eq "0" ]; then
    exit 1
fi
