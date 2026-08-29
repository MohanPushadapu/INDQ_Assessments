/*
 * ecg_filter.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */


#include "ecg_filter.h"




void ECG_Filter_Init(ECG_Filter *f,const float b[5], const float a[5]){
	for(int i=0;i<5;i++){
		f->b[i] = b[i];
		f->a[i] = a[i];

		f->x[i] = 0.0f;
		f->y[i] = 0.0f;
	}
}

float ECG_Filter_Update(ECG_Filter *f,float input){

	f->x[4] = f->x[3];
	f->x[3] = f->x[2];
	f->x[2] = f->x[1];
	f->x[1] = f->x[0];
	f->x[0] = input;

	f->y[4] = f->y[3];
	f->y[3] = f->y[2];
	f->y[2] = f->y[1];
	f->y[1] = f->y[0];

	f->y[0] = 	(f->b[0] * f->x[0]) +
            	(f->b[1] * f->x[1]) +
				(f->b[2] * f->x[2]) +
				(f->b[3] * f->x[3]) +
				(f->b[4] * f->x[4]) -
				(f->a[1] * f->y[1]) -
				(f->a[2] * f->y[2]) -
				(f->a[3] * f->y[3]) -
				(f->a[4] * f->y[4]);

	return f->y[0];
}
