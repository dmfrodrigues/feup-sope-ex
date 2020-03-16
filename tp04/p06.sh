gcc -Wall limit.c -o limit
gcc -Wall prog.c -o prog
./limit 12 ./prog "I'm alive!"
echo $?
./limit 60 ./prog "I'm still alive!"
echo $?
