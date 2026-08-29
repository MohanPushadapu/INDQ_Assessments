/*
 * main.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#include <stdint.h>
#include <math.h>


// CONFIGURATION
#define FS					500.0f
#define WINDOW_SIZE			75

#define LOW_CUTOFF			5.0f
#define HIGH_CUTOFF			20.0f

// Moving integration buffer

typedef struct{
	float buffer[WINDOW_SIZE];
	uint32_t index;
	float sum;
} MovingAverage;

// Initialize moving average.

void MovingAverage_Init(MovingAverage *ma){
	ma->index = 0;
	ma->sum = 0.0f;

	for (int i=0;i<WINDOW_SIZE;i++){
		ma->buffer[i] = 0.0f;
	}
}

float MovingAverageUpdate(MovingAverage *ma,float input){
	ma->sum -=ma->buffer[ma->index];

	ma->buffer[ma->index] = input;

	ma->sum += input;

	ma->index++;

	if(ma->index >= WINDOW_SIZE){
		ma->index = 0;
	}
	return ma->sum/WINDOW_SIZE;
}

//Derivative

typedef struct{
	float previous;
}Derivative;

void Derivative_Init(Derivative *d){
	d->previous = 0.0f;
}

float Derivative_Update(Derivative *d, float input){
	float output;

	output = (input -d->previous) *FS;

	d->previous = input;
	return output;
}

typedef struct {
	Devivative derivative;
	MovingAverage integrator;
}ECGProcessor;

void ECGProcessor_Init(ECGProcessor *ecg){
	Derivative_Init(&ecg->derivative);
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

ECGProcessor ecg;

ECGProcessor_Init(ecg);

while(1){
	float adc_value;
	float filtered;
	float qrs_signal;

	adc_value = Read_ADC();

	filtered = Bandpass_Update(adc_value);

	qrs_signal = ECGProcessor_Update(&ecg,filtered);
}

