/*
 * app.c
 *
 *  Created on: Jun 1, 2024
 *      Author: Ayuba Tahiru
 */


#include "app.h"

#define TRUE 1
#define FALSE 0

void SystemClockConfig(void);
void UART2_Init();
uint8_t Convert_to_Capital(uint8_t rcvd_data);
void Error_handler();

// Handle Global Variable for UART
UART_HandleTypeDef huart2;

char *msg = "This Application convert Lower cases letters to Upper cases using Interrupt!\r\n";
uint8_t data_container[100];
uint8_t rcvd_data;
int32_t count = 0;
uint8_t reception_completed = FALSE;

int main(void){

 	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	if(HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY)!= HAL_OK){
		// Something went wrong!
		Error_handler();
	}

	while(reception_completed != TRUE){
		HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);
	}




	while(1);

	return 0;

}


void SystemClockConfig(void){

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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(rcvd_data == '\r'){


		data_container[count++] = '\r';

		HAL_UART_Transmit(&huart2, data_container, count, HAL_MAX_DELAY);
		reception_completed = TRUE;
	}else{
		data_container[count++] = Convert_to_Capital(rcvd_data);

	}

}

uint8_t Convert_to_Capital(uint8_t rcvd_data){
	if(rcvd_data >= 'a' && rcvd_data <= 'z'){
		rcvd_data = rcvd_data - ('a' - 'A');
	}
	return rcvd_data;
}

void Error_handler(){
	while(1);
}
