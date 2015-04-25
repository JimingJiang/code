#!/bin/sh
g++ -shared -fPIC fake_hello.* -o libfakehello.so
echo "[+] build done!"
