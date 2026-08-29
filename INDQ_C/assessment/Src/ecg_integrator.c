/*
 * ecg_integrator.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#include "ecg_integrator.h"

void MovingAverage_Init(MovingAverage *ma){
	ma->index = 0;
	ma->sum = 0.0f;

	for (int i=0;i<WINDOW_SIZE;i++){
		ma->buffer[i] = 0.0f;
	}
}

float MovingAverage_Update(MovingAverage *ma,float input){
	ma->sum -=ma->buffer[ma->index];

	ma->buffer[ma->index] = input;

	ma->sum += input;

	ma->index++;

	if(ma->index >= WINDOW_SIZE){
		ma->index = 0;
	}
	return ma->sum/WINDOW_SIZE;
}

void ECGProcessor_Init(ECGProcessor *ecg){
	ECG_Derivative_Init(&ecg->derivative);
	MovingAverage_Init(&ecg->integrator);
}

float ECGProcesssor_Update(ECGProcessor *ecg, float filtered_ecg){
	float derivative;
	float squared;
	float integrated;

    /* Derivative */
	derivative = Derivative_Update(&ecg->derivative,
			filtered_ecg);

	/* Squaring */
	squared = derivative * derivative;

	/* Moving-window integration */
	integrated = MovingAverage_Update(
			&ecg->integrator,
			squared
			);

	return integrated;
}

