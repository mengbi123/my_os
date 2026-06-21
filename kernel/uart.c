#include <stdint.h>
#include "uart.h"

#define UART0_BASE 0x10000000UL
#define UART_THR 0X00
#define UART_LSR 0x05
#define UART_LSR_THRE 0x20

/**
 * @brief 读取寄存器
 */
static inline uint8_t mmio_read8(uintptr_t addr) {
    return *(volatile uint8_t*)addr;  /**< 关键字 volatile 禁止优化读取，强制每一次都读取 */
}

/**
 * @brief 写入寄存器
 */
static inline void mmio_write8(uintptr_t addr, uint8_t value) {
    *(volatile uint8_t*)addr = value;
}

void uart_putc(char c) {
    while ((mmio_read8(UART0_BASE + UART_LSR) & UART_LSR_THRE) == 0);
    mmio_write8(UART0_BASE + UART_THR, (uint8_t)c);
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') {
            uart_putc('\r');
        }
        uart_putc(*s++);
    }
}