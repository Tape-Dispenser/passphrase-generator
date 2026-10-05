#!/usr/bin/env bash

# make main passphrase generator
gcc ./gen.c ./lib/map.c -o ./build/gen

# make test.c
gcc ./test.c ./lib/map.c -o ./build/test
