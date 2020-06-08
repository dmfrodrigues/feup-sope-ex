sleep $1
echo Killing $(ps u | grep "$3" | head -n 1 | awk '{print $2}') with $2
kill $2 $(ps u | grep "$3" | head -n 1 | awk '{print $2}')
