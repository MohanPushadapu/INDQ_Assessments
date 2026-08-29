/*
 * heart_rate.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef HEART_RATE_H_
#define HEART_RATE_H_

#include <stdint.h>

#define HEART_FS 500.0f

#define MIN_RR_SAMPLES 125     /* 250 ms = 240 BPM */
#define MAX_RR_SAMPLES 1000    /* 2 seconds = 30 BPM */

typedef struct{
	uint32_t previous_peak_sample;

	uint32_t rr_samples;

	float rr_interval;
	float heart_rate;

	uint8_t first_peak;
	uint8_t vaild;

}HeartRate;

void HeartRate_Init(HeartRate *hr);

float HeartRate_Update(HeartRate *hr,uint32_t peak_sample);

float HeartRate_GetBPM(HeartRate *hr);

#endif /* HEART_RATE_H_ */
