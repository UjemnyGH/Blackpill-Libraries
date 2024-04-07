@echo on

gcc -Ofast -Os -static -m64 -std=c2x -Wall -Wextra -Wpedantic -Werror -o creator src/*.c -lm -lpthread
copy /B "creator.exe" "../" /B