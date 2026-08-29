/*
 * signal_quality.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#include "signal_quality.h"

#define GOOD_SNR_THRESHOLD    5.0f
#define FAIR_SNR_THRESHOLD    2.0f

#define GOOD_RR_VARIATION     0.10f
#define FAIR_RR_VARIATION     0.20f

#define QUALITY_UPDATE_RATE   0.01f

void SignalQuality_Init(SignalQuality *quality){
	quality->signal_level = 0.0f;
	quality->noise_level = 0.0f;

	quality->signal_to_noise = 0.0f;

	quality->rr_mean = 0.0f;
	quality->rr_variation = 0.0f;

	quality->valid_peaks = 0;
	quality->total_peaks = 0;

	quality->status = SIGNAL_QUALITY_POOR;
}

void SignalQuality_Update(SignalQuality *quality, float integrated){
	if (integrated>quality->signal_level){
		quality->signal_level = (1.0f-QUALITY_UPDATE_RATE)*quality->signal_level + QUALITY_UPDATE_RATE*integrated;
	}

	if (integrated<quality->noise_level || quality->noise_level ==0.0f){
		quality->noice_level = (1.0f - QUALITY_UPDATE_RATE)*quality->noice_level + QUALITY_UPDATE_RATE*integrated;
	}

	if (quality->noice_level>0.0f){
		quality->signal_to_noise = quality->signal_level/quality->noise_level;
	}
}

Void SignalQuality_UpdateRR(SignalQuality *quality, float rr_interval){

	quality->total_peaks++;

	if (rr_interval <=0.0f){
		return;
	}

	if (quality->valid_peaks ==0){
		quality->rr_mean = rr_interval;
		quality->rr_variation = 0.0f;

		quality->valid_peaks = 1;
		return;
	}

	float deviation = fabsf(rr_interval - quality->rr_mean)/quality->rr_mean;

	quality->rr_variation = 0.9f * quality->rr_variation + 0.1f * deviation;

	quality->rr_mean = 0.9f * quality->rr_mean + 0.1f * rr_interval;

	quality->valid_peaks++;
}

SignalQualityStatus SignalQuality_GetStatus(SignalQuality *quality){
	SignalQualityStatus status = SIGNAL_QUALITY_POOR;

	if (quality->signal_to_noise >= GOOD_SNR_THRESHOLD){
		status = SIGNAL_QUALITY_GOOD;
	}
	else if (quality->signal_to_noise >=FAIR_SNR_THRESHOLD){
		status = SIGNAL_QUALITY_FAIR;
	}

	if (quality->valid_peaks >=3){
		if (quality->rr_variatiion > FAIR_RR_VARIATION){
			status =SIGNAL_QUALITY_POOR;
		}
		else if (quality->rr_variation >GOOD_RR_VARIATION){
			if (status == SIGNAL_QUALITY_GOOD){
				status = SIGNAL_QUALITY_FAIR;
			}
		}
	}

	quality->status = status;

	return status;
}

const char *SignalQuality_GetStatusString(SignalQualityStatus status){
	switch(status){
	case SIGNAL_QUALITY_GOOD:
		return "GOOD";
	case SIGNAL_QUALITY_FAIR:
		return "FAIR";
	case SIGNAL_QUALITY_POOR:
	default:
		return "POOR";
	}
}
