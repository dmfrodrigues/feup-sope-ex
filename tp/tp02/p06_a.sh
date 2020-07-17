set -e

rm -rf mydir
mkdir -p mydir
echo "Hello world!" > mydir/temp.txt
ln -s $(pwd)/mydir/temp.txt mydir/temp1.txt
ln $(pwd)/mydir/temp.txt mydir/temp2.txt
gcc -Wall p06_a.c -o p06_a
ls -la mydir
./p06_a mydir
cat mydir/temp.txt
cat mydir/temp1.txt
cat mydir/temp2.txt
rm mydir/temp.txt
cat mydir/temp.txt && exit 1
cat mydir/temp1.txt && exit 1
cat mydir/temp2.txt
rm mydir/temp2.txt
cat mydir/temp.txt && exit 1
cat mydir/temp1.txt && exit 1
cat mydir/temp2.txt && exit 1
rm mydir/temp1.txt