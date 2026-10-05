#!/usr/bin/env bash

# make main passphrase generator
gcc ./gen.c ./lib/map.c ./lib/stringutils.c ./lib/stack.c -o ./build/gen -g
