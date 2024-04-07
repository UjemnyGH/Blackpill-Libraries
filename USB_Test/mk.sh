#!/bin/bash

echo Compiling assembly loader
arm-none-eabi-as --warn --fatal-warnings -mcpu=cortex-m4 flash.s -o flash.o
echo Compiling main.c
arm-none-eabi-gcc -Wall -Wextra -Werror -O3 -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-m4 -c main.c
echo Linking
arm-none-eabi-ld -o USB_Test.elf -T flash.ld flash.o main.o
echo Copying to binary file
arm-none-eabi-objcopy USB_Test.elf USB_Test.bin -O binary

rm *.elf
rm *.o
echo Writing to microcontroller
st-flash write USB_Test.bin 0x08000000
