#!/bin/bash

echo Compiling assembly loader
arm-none-eabi-as --warn --fatal-warnings -mcpu=cortex-m4 flash.s -o flash.o
echo Compiling main.c
arm-none-eabi-gcc -L/lib64/gcc/arm-none-eabi/14.1.0/thumb/v7e-m+fp/hard/ -I/lib64/gcc/arm-none-eabi/14.1.0/include/ -Wall -Wextra -Wpedantic -O3 -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-m4 -fno-builtin -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -c main.c -lgcc -lm -lc -lgcov
echo Linking
arm-none-eabi-ld -o MB190Controller.elf -T flash.ld flash.o main.o
echo Copying to binary file
arm-none-eabi-objcopy MB190Controller.elf MB190Controller.bin -O binary

rm *.elf
rm *.o
echo Writing to microcontroller
st-flash write MB190Controller.bin 0x08000000