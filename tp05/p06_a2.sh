gcc -Wall p06_reader.c  -o p06_reader
gcc -Wall p06_writter.c -o p06_writter
./p06_writter &
sleep 5
./p06_reader
