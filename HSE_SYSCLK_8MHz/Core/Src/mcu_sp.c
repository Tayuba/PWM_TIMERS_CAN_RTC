/*
 * mcu_sp.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Ayuba Tahiru
 */

#include "stm32f4xx_hal.h"


void HAL_MspInit(void){
/********************* HANDLE LOW LEVEL PROCESSOR SPECIFIC INITS *******************
   * 1. Setup grouping of ARM-CORTEX Mx Processor
   * 2. Enable required system exceptions of the ARM-CORTEX Mx Processor
   * 3.	Configure priority for system exceptions*/

	// 1. Setup grouping
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// 2. Enable required system exceptions
	SCB->SHCSR |= 0x7 << 16; // usage fault, memory fault and bus fault

	// 3. Configure priority for system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

}


void HAL_UART_MspInit(UART_HandleTypeDef *huart){
	GPIO_InitTypeDef gpio_uart;
/********************* b) INITIALIZE LOW LEVEL INITS FOR USART2 PERIPHERAL *******************
	 * 1. Enable USART2 Peripheral clock
	 * 2. Do Pin Muxing Configuration
	 * 3. Enable IRQ and setup interrupt (NVIC Settings)*/

	// 1. Enable USART2 and GPIOA Peripheral clock
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2. Pin Muxing Configuration
	gpio_uart.Pin = GPIO_PIN_2; // UART2 Tx
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; // UART2 Rx
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	// 3. Enable IRQ and setup interrupt (NVIC Settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}
