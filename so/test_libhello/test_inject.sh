#!/bin/sh
LD_PRELOAD=../inject_libhello/libfakehello.so ./test
