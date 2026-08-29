/*
 * uart_output.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */
#include "uart_output.h"

void UART_Print(const char *str){
	HAL_UART_Transmit(&huart2,(uint8_t *)str,strlen(str),HAL_MAX_DELAY);
}
