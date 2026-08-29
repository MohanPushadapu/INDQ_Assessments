/*
 * ecg_integrator.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef ECG_INTEGRATOR_H_
#define ECG_INTEGRATOR_H_

#include "ecg_derivative.h"

#define WINDOW_SIZE			75


typedef struct{
	float buffer[WINDOW_SIZE];
	uint32_t index;
	float sum;
} MovingAverage;

typedef struct {
	ECG_Derivative derivative;
	MovingAverage integrator;
}ECGProcessor;

void MovingAverage_Init(MovingAverage *ma);

float MovingAverage_Update(MovingAverage *ma,float input);

void ECGProcessor_Init(ECGProcessor *ecg);

float ECGProcesssor_Update(ECGProcessor *ecg, float filtered_ecg);


#endif /* ECG_INTEGRATOR_H_ */
