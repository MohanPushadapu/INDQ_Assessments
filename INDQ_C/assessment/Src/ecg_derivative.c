/*
 * ecg_derivative.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */


#include "ecg_derivative.h"


void ECG_Derivative_Init(ECG_Derivative *d){
	d->previous = 0.0f;
}

float ECG_Derivative_Update(ECG_Derivative *d, float input){
	float output;

	output = (input - d->previous)/DT;

	d->previous = input;

	return output;
}
