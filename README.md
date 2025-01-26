# passphrase-generator

## about
passphrase-generator is a fully open-source passphrase generator written in c using /dev/random as the source of randomness. it uses [this wordlist](http://www.webplaces.org/passwords/lists/hexadecimal-65536-list.txt) of 65536 different words, and was sourced from [this repo.](https://gist.github.com/atoponce/95c4f36f2bc12ec13242a3ccc55023af)

## usage
the generated binary (by default it's `<project_folder>/build/passphrase-gen`) will generate a 5 word long passphrase.
for info on extra options run `<project_folder>/build/passphrase-gen -h`

## build instructions
to build on linux systems with gcc installed run:
`git clone https://github.com/Tape-Dispenser/passphrase-generator`
`cd ./passphrase-generator`
`gcc -o ./build/passphrase-gen gen.c ./lib/map.c`
