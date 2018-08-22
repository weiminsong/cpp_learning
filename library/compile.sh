#!bin/sh

gcc -c -Wall -Werror -I$(pwd)/foo -fpic bar.cpp 
gcc -shared  -o libbar.so bar.o

gcc -L$(pwd) -L$(pwd)/foo -Wall -o test main.cpp -lfoo -I$(pwd)/foo -lbar

export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$(pwd)/foo:$LD_LIBRARY_PATH
echo -en '\n'
echo -en '\n'
echo -en '\n'
echo -en '\n'

./test
