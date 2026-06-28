.section .text
.global trap_entry

trap_entry:
    addi sp, sp, -16

    sd ra, 0(sp)

    call trap_handler

    ld ra, 0(sp)

    addi sp, sp, 16

    sret