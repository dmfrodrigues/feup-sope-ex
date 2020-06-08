gcc -Wall p07_b.c

echo RUN 1:
./a.out 1 || exit 1
echo $?
# RUN 1:
# Main done!
# Executing exit handler 2
# Executing exit handler 2
# Executing exit handler 1
# 0

echo RUN 2:
./a.out 2 && exit 1
echo $?
# RUN 2:
# Aborted (core dumped)
# 134

echo RUN 3:
./a.out 3 && exit 1
echo $?
# RUN 3:
# Main done!
# Executing exit handler 2
# Executing exit handler 3
# Executing exit handler 1
# 3
