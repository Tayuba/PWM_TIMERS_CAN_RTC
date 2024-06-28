/*
 * interrupts.c
 *
 *  Created on: Jun 1, 2024
 *      Author: Ayuba Tahiru
 */

#include "interrupts.h"

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
