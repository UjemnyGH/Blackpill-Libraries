MEMORY {
    rom : ORIGIN = 0x08000000, LENGTH = 512k
    ram : ORIGIN = 0x20000000, LENGTH = 128k
}

SECTIONS {
    .text : { *(.text*) } > rom
    .rodata : { *(.rodata*) } > rom
    .bss : { *(.bss*) } > ram
}
/*
.ARM.extab :
{
    *(.ARM.extab* .gnu.linkonce.armextab.*)
} > IROM
*/
/*
* Arm stack unwinding.
* If removed may cause random crashes.
*/
/*.ARM.exidx :
{
    __exidx_start = .;
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    __exidx_end = .;
} > IROM*/