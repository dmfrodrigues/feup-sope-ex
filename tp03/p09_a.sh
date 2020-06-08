gcc -Wall p9a.c -o p9a
./p9a somedirs
./p9a a
./p9a lotsofdirs &
sleep 1s
kill $(ps u | grep "ls -laR" | head -n 1 | awk '{print $2}')
