/**
 * @file trap.h
 * @brief 故障处理头文件
 */

 #ifndef TRAP_H
 #define TRAP_H

#include <stdint.h>

void trap_init(void);
void trap_handle(void);

#endif