/*
 * mcu_sp.c
 *
 *  Created on: July 6, 2024
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


void  HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim){
/********************* b) INITIALIZE LOW LEVEL INITS FOR TIMER6 PERIPHERAL*******************/
	// 1. Enable Timer clock
	__HAL_RCC_TIM6_CLK_ENABLE();

	// 2. Enable IRQ of Timer
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	// Setup Priority for TIM6_DAC_IRQn
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
}
