#include <stdint.h>
#include "uart.h"
#include "print.h"
#include "trap.h"

/**
 * @brief 证书读取函数，读取CSR寄存器
 */
static inline uint64_t read_mhartid(void)
{
    uint64_t value;
    __asm__ volatile ("csrr %0, mhartid" : "=r"(value));   /**< 汇编指令模板，第一个冒号后是输出字段，从硬件读数据给C变量而不是把C变量传进去 */
    return value;
}

/**
 * @brief 读取 X2通用寄存器
 */
static inline uint64_t read_sp(void)
{
    uint64_t value;
    __asm__ volatile ("mv %0, sp" : "=r"(value));         /**< 将value值映射到一个通用寄存器，该寄存器作为mv指令的目标操作数 */
    return value;
}

void kmain(void){
    uart_puts("Hello from RISC-V kernel!\n");

    uart_puts("Test hex: ");
    uart_puthex(0x80200000ULL);                 /**< RISC-V平台内核加载地址 */
    uart_puts("\n");

    uart_puts("Test dec: ");
    uart_putdec(2026);                          /**< 验证取余逆序算法正确性 */
    uart_puts("\n");

    uart_puts("Hart id: ");
    uart_putdec(read_mhartid());
    uart_puts("\n");

    uart_puts("sp: ");
    uart_puthex(read_sp());
    uart_puts("\n");

    trap_init();

    uart_puts("Kernel boot success.\n");

    while(1){
        __asm__ volatile ("wfi");
    }
}