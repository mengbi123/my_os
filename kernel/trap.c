/**
 * @file trap.c
 * @brief 异常处理函数
 */

 #include <stdint.h>

 #include "uart.h"
 #include "print.h"
 #include "trap.h"

 extern void trap_entry(void);

 static inline void write_stvec(uint64_t addr)
 {
   __asm__ volatile("csrw stvec, %0" : : "r"(addr));
 }

 static inline uint64_t read_scause(void)
 {
    uint64_t value;
    __asm__ volatile ("csrr %0, scause" : "=r"(value));
    return value;
 }

 static inline uint64_t read_sepc(void)
 {
    uint64_t value;
    __asm__ volatile ("csrr %0, sepc" : "=r"(value));
    return value;
 }

 static inline uint64_t read_stval(void)
 {
    uint64_t value;
    __asm__ volatile ("csrr %0, stval" : "=r"(value));
    return value;
 }

 void trap_init(void)
 {
   write_stvec((uint64_t)trap_entry);

   uart_puts("Trap initialized.\n");
 }

 void trap_handler(void)
 {
    uart_puts("\n=== TRAP ===\n");

    uart_puts("scause=");
    uart_puthex(read_scause());
    uart_puts("\n");

    uart_puts("sepc=");
    uart_puthex(read_sepc());
    uart_puts("\n");

    uart_puts("stval=");
    uart_puthex(read_stval());
    uart_puts("\n");

    while(1);
 }