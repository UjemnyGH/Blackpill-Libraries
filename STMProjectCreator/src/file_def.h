#ifndef __FILE_DEF_
#define __FILE_DEF_

const char* gFlashAsm = 
"/*@-----CPU-INFO-----*/\n"
".cpu cortex-%s\n"
".thumb\n"
"/*@-----CPU-INFO-----*/\n"
"\n"
".thumb_func\n"
".global _start\n"
"_start:\n"
"    stacktop: .word 0x20001000\n"
"    .word reset\n"
"\n"
".thumb_func\n"
"reset:\n"
"    bl stmMain\n"
"    b defHandler\n"
"\n"
".thumb_func\n"
"defHandler: b .\n"
"\n"
".end\n"
"\n";

const char* gFlashLd = 
"MEMORY {\n"
"    rom : ORIGIN = 0x08000000, LENGTH = %s\n"
"    ram : ORIGIN = 0x20000000, LENGTH = %s\n"
"}\n"
"\n"
"SECTIONS {\n"
"    .text : { *(.text*) } > rom\n"
"    .rodata : { *(.rodata*) } > rom\n"
"    .bss : { *(.bss*) } > ram\n"
"}\n";

const char* gMainC = 
"int stmMain() {\n"
"\n"
"\twhile(1) {\n"
"\t\t// Program loop\n"
"\t}\n\n"
"\treturn 0;\n"
"}\n";

const char* gCompBat = 
"@echo on\n"
"\n"
"arm-none-eabi-as --warn --fatal-warnings -mcpu=cortex-%s flash.s -o flash.o\n"
"arm-none-eabi-gcc -Wall -Wextra -Werror -O3 -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-%s -c main.c\n"
"arm-none-eabi-ld -o %s.elf -T flash.ld flash.o main.o\n"
"arm-none-eabi-objcopy %s.elf %s.bin -O binary\n"
"\n"
"del /f *.elf\n"
"del /f *.o\n";

const char* gMkSh = 
"#!/bin/bash\n"
"\n"
"echo Compiling assembly loader\n"
"arm-none-eabi-as --warn --fatal-warnings -mcpu=cortex-%s flash.s -o flash.o\n"
"echo Compiling main.c\n"
"arm-none-eabi-gcc -Wall -Wextra -Werror -O3 -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-%s -c main.c\n"
"echo Linking\n"
"arm-none-eabi-ld -o %s.elf -T flash.ld flash.o main.o\n"
"echo Copying to binary file\n"
"arm-none-eabi-objcopy %s.elf %s.bin -O binary\n"
"\n"
"rm *.elf\n"
"rm *.o\n"
"echo Writing to microcontroller\n"
"st-flash write %s.bin 0x08000000\0";

#endif