/*
 * app.c
 *
 *  Created on: July 6, 2024
 *      Author: Ayuba Tahiru
 */


#include "app.h"



void UART2_Init(void );
void Error_handler(void );
void SystemClock_Config();
void Timer6_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer6;
GPIO_InitTypeDef led;


int main(void){

 	HAL_Init();

 	SystemClock_Config();

 	GPIO_Init();

 	Timer6_Init();

 	// Start timer
 	HAL_TIM_Base_Start(&htimer6);
 	while(1){
		while(!(TIM6->SR & TIM_SR_UIF));
		TIM6->SR = 0;
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
 	}


	return 0;

}




void SystemClock_Config(){


}


void Timer6_Init(void){
/********************* a) INITIALIZE HIGH LEVEL INITS FOR TIMER6 PERIPHERAL, PARAMETER INITIALIZATION *******************/
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 64000 - 1;
	if(HAL_TIM_Base_Init(&htimer6) != HAL_OK){
		Error_handler();
	}
}


void GPIO_Init(void){
	__HAL_RCC_GPIOD_CLK_ENABLE();
	led.Pin = GPIO_PIN_12;
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &led);
}


void Error_handler(void){
	while(1);
}
