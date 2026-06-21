#include <stdint.h>
#include "uart.h"
#include "print.h"

void kmain(void){
    uart_puts("Hello from RISC-V kernel!\n");

    uart_puts("Test hex: ");
    uart_puthex(0x80200000ULL);                 /**< RISC-V平台内核加载地址 */
    uart_puts("\n");

    uart_puts("Test dec: ");
    uart_putdec(2026);                          /**< 验证取余逆序算法正确性 */
    uart_puts("\n");

    uart_puts("Kernel boot success.\n");

    while(1){
        __asm__ volatile ("wfi");
    }
}