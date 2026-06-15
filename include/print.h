/**
 * @file print.h
 * @brief 提供内核打印功能的接口
 */
#ifndef PRINT_h
#define PRINT_h

#include <stdint.h>

void uart_puthex(uint64_t value);
void uart_putdec(uint64_t value);
void panic(const char *msg);

#endif /* PRINT_h */