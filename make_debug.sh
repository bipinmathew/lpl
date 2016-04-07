#!/bin/bash
make clean
./configure CFLAGS="-g -O2 -std=gnu99 -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition" CPPFLAGS=-DDEBUG
make
