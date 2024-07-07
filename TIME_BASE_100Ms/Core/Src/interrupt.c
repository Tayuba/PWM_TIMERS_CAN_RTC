/*
 * interrupts.c
 *
 *  Created on: July 6, 2024
 *      Author: Ayuba Tahiru
 */

#include "interrupt.h"

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
