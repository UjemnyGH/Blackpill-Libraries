#!/bin/bash

echo Compiling
gcc -Ofast -Os -static -m64 -std=c2x -Wall -Wextra -Wpedantic -Werror -o creator src/*.c -lm -lpthread
echo Copying executable
cp creator ../