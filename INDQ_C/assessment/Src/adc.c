/*
 * adc.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */
#include "adc.h"

ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim2;

volatile uint16_t adc_value = 0;

static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);

void ADC_Helper_Init(void)
{
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();

  HAL_TIM_Base_Start_IT(&htim2);
}

uint16_t ADC_Helper_TimerISR(void){

	HAL_ADC_Start(&hadc1);

	if (HAL_ADC_PollForConversion(&hadc1,10) == HAL_OK){
				adc_value = HAL_ADC_GetValue(&hadc1);
			}
	HAL_ADC_Stop(&hadc1);

	return adc_value;
}

static void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 719;                 // 72 MHz / 720 = 100 kHz
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 199;                    // 100 kHz / 200 = 500 Hz
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

static void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;

  HAL_ADC_Init(&hadc1);

  /* Configure Channel 0 on PA0 */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;

  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
}
