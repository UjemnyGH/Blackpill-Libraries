MEMORY {
    rom : ORIGIN = 0x08000000, LENGTH = 512k
    ram : ORIGIN = 0x20000000, LENGTH = 128k
}

SECTIONS {
    .text : { *(.text*) } > rom
    .rodata : { *(.rodata*) } > rom
    .bss : { *(.bss*) } > ram
}
