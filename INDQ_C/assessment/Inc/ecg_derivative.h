/*
 * ecg_derivative.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef ECG_DERIVATIVE_H_
#define ECG_DERIVATIVE_H_

#define FS 500.0f
#define DT (1.0f/FS)

const struct{
	float previous;
}ECG_Derivative;

void ECG_Derivatice_Init(ECG_Derivative *d);

void ECG_Derivative_Update(ECG_Derivative *d,float input);

#endif /* ECG_DERIVATIVE_H_ */
