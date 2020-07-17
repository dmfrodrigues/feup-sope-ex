echo Creating files
rm -rf $1
mkdir -p $1
for ((i = 0; i < $2; i++)); do
    touch $1/$i.txt
done
echo Created files
