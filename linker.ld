ENTRY(_start)

SECTIONS 
{
    . = 0x80200000;

    .text : {
        *(.text.init)
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(bss*)
        *(COMMON)
    }
}