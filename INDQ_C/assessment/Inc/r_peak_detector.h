/*
 * r_peak_detector.h
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */

#ifndef R_PEAK_DETECTOR_H_
#define R_PEAK_DETECTOR_H_

#include "ecg_derivative.h"

#define REFRACTORY_PERIOD 			200.0f
#define MIN_RR_INTERVAL 			250.0f

#define REFRACTORY_SAMPLES ((uint32_t)(REFRACTORY_PERIOD * FS/1000.0f)
#define MIN_RR_SAMPLES ((uint32_t)(MIN_RR_INTERVAL * FS/1000.0f))

#define ALPHA 				0.25f
#define UPDATE_RATE 		0.125f

#define INITIALIZATION_TIME_SEC  1.0f

#define INITIALIZATION_SAMPLES \
    ((uint32_t)(INITIALIZATION_TIME_SEC * ECG_FS))


typedef struct {
	float signal_level;
	float noise_level;
	float threshold;

	float previous_sample;

	uint32_t sample_count;
	uint32_t last_peak_sample;

	uint32_t initialization_samples;
	uint8_t initialized;

	uint8_t r_peak_detected;
}RPeakDetector;

void RPeakDetector_Init(RPeakDetector *detector);

uint8_t RPeakDetector_Update(
    RPeakDetector *detector,
    float input
);

float RPeakDetector_GetThreshold(
    RPeakDetector *detector
);

#endif /* R_PEAK_DETECTOR_H_ */
