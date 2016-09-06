#!/bin/sh
g++ -m64 -o testamd64 testPrintIntx64.cc -lpthread -L. -lfoo
g++ -o testi386 testOutputRedisi386.cc -lpthread -L. -lredis
#gcc -pthread -lpthread  threadMax.c
