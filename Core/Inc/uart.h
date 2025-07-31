/*
 * uart.h
 *
 *  Created on: Jul 29, 2025
 *      Author: desai
 */
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void UART2_RXTX_INIT(void);

void uart2_write(int ch);
int __io_putchar(int ch); // Needed only if you want to redirect printf output

#endif /* UART_H_ */
