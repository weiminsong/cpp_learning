#!bin/sh

echo "STEP 1: Compiling with Position Independent Code."
gcc -c -Wall -Werror -fpic foo.cpp
echo "A new file named foo.o is generated!"

echo "STEP 2: Creating a shared library from an object file."
gcc -shared -o libfoo.so foo.o
echo "A new file named libfoo.so is generated!"

echo "STEP 3: Telling GCC where to find the shared library and Linking with a shared library."
gcc -L$(pwd) -Wall -o test main.cpp -lfoo
echo "A excutable file named test is generated!"

echo "STEP 4: Tell the system where to find the library, and use it"
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
echo -en '\n'
echo -en '\n'
echo -en '\n'
echo -en '\n'
./test
