@echo on

arm-none-eabi-as --warn --fatal-warnings -mcpu=cortex-m4 flash.s -o flash.o
arm-none-eabi-gcc -Wall -Wextra -Werror -O3 -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-m4 -c main.c
arm-none-eabi-ld -o VGA_Test.elf -T flash.ld flash.o main.o
arm-none-eabi-objcopy VGA_Test.elf VGA_Test.bin -O binary

del /f *.elf
del /f *.o
