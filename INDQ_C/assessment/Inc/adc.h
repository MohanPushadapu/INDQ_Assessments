/*
 * adc.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f1xx_hal.h" // Adjust header based on your specific family (e.g., stm32f4xx_hal.h)

/* External Peripheral Handles */
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;

/* Global variable holding latest reading */
extern volatile uint32_t adc_value;

/* Function Prototypes */
void ADC_Helper_Init(void);
uint16_t ADC_Helper_TimerISR(void);

#endif /* ADC_H_ */
