/**
 * @file print.c
 * @brief 实现内核打印功能
 */
#include "uart.h"
#include "print.h"
#include <stdint.h>

/**
 * @brief 将一个64位整数以十六进制格式打印到串口
 * @param value 要打印的整数
 */
void uart_puthex(uint64_t value)
{
    static const char hex[] = "0123456789abcdef";

    uart_puts("0x");

    for (int i = 60; i >= 0; i -= 4)
    {
        uint8_t digit = (value >> i) & 0xF;
        uart_putc(hex[digit]);
    }
}

/**
 * @brief 将一个64位整数以十进制格式打印到串口
 * @param value 要打印的整数
 */
void uart_putdec(uint64_t value)
{
    char buf[21];
    int i = 0;

    if (value == 0)
    {
        uart_putc('0');

        return;
    }

    while (value > 0)
    {
        buf[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i > 0)
    {
        uart_putc(buf[--i]);
    }
}

/**
 * @brief 内核崩溃处理
 */
void panic(const char *msg)
{
    uart_puts("\n[PANIC] ");
    uart_puts(msg);
    uart_puts("\n");

    while(1)
    {
        __asm__ volatile("wfi");    /**< wfi 是RISC-V电源管理指令，执行后CPU停止执行指令流水线 */
    }
}