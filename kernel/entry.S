.section .text.init
.global _start

_start:
    la sp, boot_stack_top
    call kmain

1:
    j 1b

.section .bss.stack
.align 12
boot_stack:
    .space 4096
boot_stack_top: