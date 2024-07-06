/*
 * app.c
 *
 *  Created on: July 6, 2024
 *      Author: Ayuba Tahiru
 */


#include "app.h"



void UART2_Init(void );
void Error_handler(void );
void SystemClock_Config_HSE(uint8_t freq);


// Handle Global Variable for UART
UART_HandleTypeDef huart2;


int main(void){
	uint8_t msg[100];

 	HAL_Init();

 	SystemClock_Config_HSE(HCLK_120MHZ);

	UART2_Init();

	// Print values of clock
	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "SYSCLK With HSE: %ldHz\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "HCLK With HSE::  %ldHz\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "PCLK1 With HSE:: %ldHz\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf((char * )msg, "PCLK2 With HSE:: %ldHz\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, msg, strlen((char * )msg), HAL_MAX_DELAY);




	while(1);

	return 0;

}



void UART2_Init(void){
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


void SystemClock_Config_HSE(uint8_t freq){
	uint8_t FLatency = 0;
	// Variable to select RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) types
	RCC_OscInitTypeDef osc_init;

	// Variable to configure RCC System, AHB and APB busses
	RCC_ClkInitTypeDef clk_init;


	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE; // Clock source selected
	osc_init.HSEState = RCC_HSE_BYPASS; // HSI is ON by default, you can ignore this step
	osc_init.PLL.PLLState = RCC_PLL_ON; // Turn PLL ON
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE; // PLL Clock source

	switch(freq){
		case HCLK_50MHZ :{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			// Clock speed Initialization
			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_1WS;
			break;
		}
		case HCLK_84MHZ:{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			// Clock speed Initialization
			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_2WS;
			break;
		}
		case HCLK_120MHZ:{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			// Clock speed Initialization
			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_3WS;
			break;
		}
		default:{
			return;
		}
	}

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK){
		Error_handler();
	}

	if(HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK){
		Error_handler();
	}

	// Systick Configuration
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

void Error_handler(void){
	while(1);
}
