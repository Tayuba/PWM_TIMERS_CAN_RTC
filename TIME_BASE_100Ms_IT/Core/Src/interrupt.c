/*
 * interruptIT.c
 *
 *  Created on: Jul 7, 2024
 *      Author: Ayuba Tahiru
 */



#include "interrupt.h"

extern TIM_HandleTypeDef htimer6;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM6_DAC_IRQHandler(void){
	// First call Interrupt Processing API
	HAL_TIM_IRQHandler(&htimer6);
}
