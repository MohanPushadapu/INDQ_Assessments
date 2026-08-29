/*
 * uart_output.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef UART_OUTPUT_H_
#define UART_OUTPUT_H_

#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

void UART_Print(const char *str);

#endif /* UART_OUTPUT_H_ */
