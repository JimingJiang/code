#!/bin/sh
g++ -fPIC hello.* -shared -o libhello.so
echo "[+] build done!"
