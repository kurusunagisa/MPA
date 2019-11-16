#! /bin/sh

gcc -Wall -c mulprec.c

gcc -Wall -o check.exe $1 mulprec.o -lm

./check.exe