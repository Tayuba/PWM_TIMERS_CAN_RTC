/*
 * interrupts.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Ayuba Tahiru
 */

#include "interrupts.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
