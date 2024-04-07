#!/bin/bash

echo Compiling assembly loader
arm-none-eabi-as --warn --fatal-warnings -mcpu=cortex-m4 flash.s -o flash.o
echo Compiling main.c
arm-none-eabi-gcc -Wall -Wextra -Werror -O3 -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-m4 -c main.c
echo Linking
arm-none-eabi-ld -o ST7735_Tests.elf -T flash.ld flash.o main.o
echo Copying to binary file
arm-none-eabi-objcopy ST7735_Tests.elf ST7735_Tests.bin -O binary

rm *.elf
rm *.o
echo Writing to microcontroller
st-flash write ST7735_Tests.bin 0x08000000