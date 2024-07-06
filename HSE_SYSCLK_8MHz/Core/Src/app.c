/*
 * app.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Ayuba Tahiru
 */


#include "app.h"



void UART2_Init();
void Error_handler();

// Handle Global Variable for UART
UART_HandleTypeDef huart2;


int main(void){
	uint8_t msg[100];

 	HAL_Init();

	UART2_Init();

	// Print values before change
	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "SYSCLK Before Changed: %ld\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "HCLK Before Changed:  %ld\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "PCLK1 Before Changed: %ld\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "PCLK2 Before Changed: %ld\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;


	// Selecting clock type e.g HSE
	memset(&osc_init, 0, sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK){
		Error_handler();
	}

	// Clock speed Initialization
	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_0) != HAL_OK){
		Error_handler();
	}

	// Save current
	__HAL_RCC_HSI_DISABLE();

	// Re-config SYSTICK
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	UART2_Init();

	// Print values of clock
	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "SYSCLK: %ld\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "HCLK:  %ld\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "PCLK1: %ld\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "PCLK2: %ld\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	while(1);

	return 0;

}



void UART2_Init(){
/********************* a) INITIALIZE HIGH LEVEL INITS FOR USART2 PERIPHERAL, PARAMETER INITIALIZATION *******************/
	// Handle variable linked with USART2
	huart2.Instance = USART2;

	//Parameter Initialization
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl =  UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	//Initialize UART with HAL API
	if(HAL_UART_Init(&huart2) != HAL_OK){
		// Something went wrong!
		Error_handler();
	}
}



void Error_handler(){
	while(1);
}