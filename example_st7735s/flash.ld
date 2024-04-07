MEMORY {
    rom : ORIGIN = 0x08000000, LENGTH = 0x10000
    ram : ORIGIN = 0x20000000, LENGTH = 0x10000
}

SECTIONS {
    .text : { *(.text*) } > rom
    .rodata : { *(.rodata*) } > rom
    .bss : { *(.bss*) } > ram
}