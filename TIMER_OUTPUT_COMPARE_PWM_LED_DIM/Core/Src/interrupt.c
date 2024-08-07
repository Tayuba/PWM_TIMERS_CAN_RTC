/*
 * interrupt.c
 *
 *  Created on: Jul 27, 2024
 *      Author: Ayuba Tahiru
 */


#include "interrupt.h"



extern TIM_HandleTypeDef htimer2;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM2_IRQHandler(void){
	// First call Interrupt Processing API
	HAL_TIM_IRQHandler(&htimer2);
}
