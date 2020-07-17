set -e

gcc -Wall p06_e.c
echo 'This is some random content for infile.txt.\n'\
'It is as meaningless as expected.\n' > infile.txt
echo infile.txt:
cat infile.txt
./a.out
echo $?
echo outfile.txt:
cat outfile.txt
rm infile.txt outfile.txt
