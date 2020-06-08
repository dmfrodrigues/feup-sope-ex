rm -rf mydir
mkdir -p mydir
echo "Hello world!" > mydir/temp.txt
ln -s $(pwd)/mydir/temp.txt mydir/temp1.txt
ln $(pwd)/mydir/temp.txt mydir/temp2.txt
gcc -Wall p6a.c -o p6a
ls -la mydir
./p6a mydir
cat mydir/temp.txt
cat mydir/temp1.txt
cat mydir/temp2.txt
rm mydir/temp.txt
cat mydir/temp.txt
cat mydir/temp1.txt
cat mydir/temp2.txt
rm mydir/temp2.txt
cat mydir/temp.txt
cat mydir/temp1.txt
cat mydir/temp2.txt
rm mydir/temp1.txt