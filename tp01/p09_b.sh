set -e

for i in {1..10}
do
    sudo mkdir "$1/TP$(printf '%02d' $i)"
done
