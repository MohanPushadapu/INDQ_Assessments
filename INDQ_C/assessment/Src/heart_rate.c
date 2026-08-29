/*
 * heart_rate.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */
#include "heart_rate.h"

void HeartRate_Init(HeartRate *hr){
	hr->previous_peak_sample = 0;

	hr->rr_samples = 0;

	hr->rr_interval = 0;
	hr->heart_rate = 0.0f;

	hr->first_peak = 1;
	hr->valid = 0;
}

float HeartRate_Update(HeartRate *hr, uint32_t peak_sample){
	uint32_t rr_samples;
	float alpha = 0.8f;
	float heart_rate = 0.0f;

	if (hr->first_peak){
		hr->previous_peak_sample = peak_sample;

		hr->first_peak = 0;
		hr->vaild = 0;

		return 0.0f;
	}

	rr_samples = peak_sample - hr->previous_peak_sample;

	if (rr_samples >=MIN_RR_SAMPLES && rr_samples <= MAX_RR_SAMPLES){
		hr->rr_samples == rr_samples;

		hr->rr_interval = (float)rr_samples / HEART_FS;

		heart_rate = 60.0f/hr->rr_interval;

		hr->heart_rate = alpha*heart_rate + (1-alpha)*hr->heart_rate;

		hr->valid = 1;
	}
	hr->previous_peak_sample = peak_sample;

	return hr->heart_rate;
}

float HeartRate_GetBPM(HeartRate *hr){
	return hr->heart_rate;
}
