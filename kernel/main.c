#include <stdint.h>
#include "uart.h"

void kmain(void){
    uart_puts("Hello from RISC-V kernel!\n");

    while(1){
        __asm__ volatile ("wfi");
    }
}