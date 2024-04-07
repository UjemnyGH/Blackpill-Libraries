@echo on

arm-none-eabi-as --warn --fatal-warnings -mcpu=cortex-m4 flash.s -o flash.o
arm-none-eabi-gcc -Wall -Wextra -Werror -O3 -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-m4 -c main.c
arm-none-eabi-ld -o ST7735_Tests.elf -T flash.ld flash.o main.o
arm-none-eabi-objcopy ST7735_Tests.elf ST7735_Tests.bin -O binary

del /f *.elf
del /f *.o
