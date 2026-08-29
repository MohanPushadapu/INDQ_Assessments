/*
 * ecg_filter.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef ECG_FILTER_H_
#define ECG_FILTER_H_

#include <stdint.h>

typedef struct {
	float b[5];
	float a[5];

	float x[5];
	float y[5];
}ECG_Filter;

void ECG_Filter_Init(ECG_Filter *f,const float b[5], const float a[5]);

float ECG_Filter_Update(ECG_Filter *f, float input);

#endif /* ECG_FILTER_H_ */
