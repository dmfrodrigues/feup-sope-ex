set -e

gcc -Wall p08_chg.c -o p08_chg
gcc -Wall p08_trl_chg.c -o p08_trl_chg
./p08_trl_chg &
sleep 0.5
./p08_chg User1
sleep 0.6
./p08_chg User2
sleep 0.4
./p08_chg "User 3 (me)"
sleep 0.5
./p08_chg User4
sleep 5
./p08_chg User5
sleep 2.5
./p08_chg User6
