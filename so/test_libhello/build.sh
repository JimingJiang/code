#!/bin/sh
g++ -I../libhello -c test.cc
g++ test.o -L../libhello -Wl,-rpath=../libhello -lhello -o test
if [ "$? " -eq "0" ]
then
	echo "[+]build done!"
else
	echo "[+]build fail!"
	exit 0
fi

./test
