gcc -Wall 06_e.c
echo -e 'This is some random content for infile.txt.\nIt is as meaningless as expected.\n' > infile.txt
echo infile.txt:
cat infile.txt
./a.out
echo $?
echo outfile.txt:
cat outfile.txt
rm infile.txt outfile.txt
