/*
 * signal_quality.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef SIGNAL_QUALITY_H_
#define SIGNAL_QUALITY_H_

#include <stdint.h>



typedef enum {
	SIGNAL_QUALITY_POOR = 0,
	SIGNAL_QUALITY_FAIR,
	SIGNAL_QUALITY_GOOD
}SignalQualityStatus;

typedef struct{
	float signal_level;
	float noise_level;

	float signal_to_noise;

	float rr_mean;
	float rr_variation;

	uint32_t valid_peaks;
	uint32_t total_peaks;

	SignalQualityStatus status;
}SignalQuality;

void SignalQuality_Init(SignalQuality *quality);

void SignalQuality_UpdateSignal(SignalQuality *quality, float integrated);

void SignalQuality_UpdateRR(SignalQuality *quality, float rr_interval);

SignalQualityStatus SignalQuality_GetStatus(SignalQuality *quality);

const char *SignalQuality_GetStatusString(SignalQualityStatus status);

#endif /* SIGNAL_QUALITY_H_ */
