#!bin/sh

gcc -c -Wall -Werror -fpic foo.cpp
#gcc -shared -o libfoo.so foo.o
ar -rc libfoo.a foo.o
