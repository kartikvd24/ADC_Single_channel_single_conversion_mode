/*
 * uart.c
 *
 *  Created on: Jul 29, 2025
 *      Author: desai
 */



#include "uart.h"
#define GPIOAEN (1U<<0)
#define UART_EN (1U<<17)
#define  CR1_RX (1U<<2)
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUD_RATE 115200
#define CR1_TE (1U<<3)
#define SR_TXE (1U<<7)
#define SR_RXE (1U<<5)

static uint16_t compute_uart_div(uint32_t Perif_clk,uint32_t Baudrate);
void UART2_RXTX_INIT(void);
void uart2_write(int ch);
static  void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t Perif_clk,uint32_t Baudrate);
int __io_putchar(int ch);



static  void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t Perif_clk,uint32_t Baudrate){
	USARTx->BRR=compute_uart_div(Perif_clk,Baudrate);
}


static uint16_t compute_uart_div(uint32_t Perif_clk,uint32_t Baudrate){
	return ((Perif_clk +(Baudrate/2U))/Baudrate);

}




void UART2_RXTX_INIT(void){
	/*************congiure uart gpio pin*************/
	//enable clock to gpioa
	RCC->AHB1ENR|=GPIOAEN;
	//set pa2 to alternate function mode
	GPIOA->MODER|=(1U<<5);
	GPIOA->MODER&=~(1U<<4);
	//set pa2 alternate function type to UART_TX(AF07)
	GPIOA->AFR[0]|=(1U<<8);//for afrl low arf[0] and for afr high arf[1]
	GPIOA->AFR[0]|=(1U<<9);
	GPIOA->AFR[0]|=(1U<<10);
	GPIOA->AFR[0]&=~(1U<<11);

   //set pa3 to alternate function mode as it is rx value
	GPIOA->MODER|=(1U<<7);
	GPIOA->MODER&=~(1U<<6);


	GPIOA->AFR[0]|=(1U<<12);//for afrl low arf[0] and for afr high arf[1]
	GPIOA->AFR[0]|=(1U<<13);
	GPIOA->AFR[0]|=(1U<<14);
	GPIOA->AFR[0]&=~(1U<<15);


	/*configure uart module*/
	//enable clock  to uart2
	RCC->APB1ENR|=UART_EN;
	//configure baud rate
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUD_RATE);
	//configure the transfer direction
	USART2->CR1 =CR1_TE|CR1_RX;

	USART2->CR1|=(1U<<13);
	//enable uart module
}

char uart2_read(void){
	/*recive flag should not be o*/
	while(!(USART2->SR & SR_RXE)){}

	//return the data
	return USART2->DR;
}
void uart2_write(int ch){
	//make sure the transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}
	//write to transmit data register
	USART2->DR = ch & 0xff;

}
int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}
