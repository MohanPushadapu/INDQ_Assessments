/*
 * r_peak_detector.c
 *
 *  Created on: Aug 28, 2026
 *      Author: mohanpushadapu
 */


void RPeakDetector_Init(RPeakDetector *detector){
	detector->signal_level = 0.0f;
	detector->noise_level = 0.0f;
	detector->threshold = 0.0f;

	detector->previous_sample = 0.0f;

	detector->sample_count = 0.0f;

	detector->last_peak_sample = 0;

	detector->initialization_samples = 0;

	detector->initialized = 0;

	detector->r_peak_detected = 0;
}

uint8_t RPeakDetector_Update(
		RPeakDetector *detector,
		float input
		){
	uint8_t is_peak = 0;

	detector->r_peak_detected = 0;


	if (!detector->initialized){
		detector->initialization_samples++;

		if (detector->initialization_samples ==1){
			detector->noise_level = input;
			detector->signal_level = input;
		}
		else {
			if (input > detector->signal_level){
				detector->signal_level = input;
			}

			if (input < detector->noise_level){
				detector->noise_level = input;
			}
		}

		if (detector->initialization_samples >=INITIALIZATION_SAMPLES){
			detector->threshold = detector->noise_level + ALPHA * (detector->signal_level - detector->noise_level);

			detector->initialized = 1;
		}

		detector->previous_sample = input;
		detector->sample_count++;

		return 0;
	}

	if (input < detector->previous_sample){
		is_peak=1;
	}

	if (is_peak){
		float peak_value = detector->previous_sample;

		if (peak_value > detector->threshold){
			uint32_t samples_since_peak = detector->sample_count - detector->last_peak_sample;
			if (samples_since_peak >= REFRACTORY_SAMPLES){
				if (samples_since_peak >= MIN_RR_SAMPLES || detecotr->last_peak_sample == 0){
					detector->r_peak_detected=1;

					detector->last_peak_sample = detector->sample_count;

					detector->signal_level = (1.0f-UPDATE_RATE) * detector->signal_level + UPDATE_RATE*peak_value;
				}
			}
		}
		else{
			detector->noise_level = (1.0f-UPDATE_RATE)*detector->noise_level + UPDATE_RATE*peak_value;
		}

		detector->threshold = detector->noise_level + ALPHA*(detector->signal_level - detector->noise_level);
	}

	detector->previous_sample = input;
	detector->sample_count++;

	return detector->r_peak_detected;
}

float RPeakDetector_GetThreshold(RPeakDetector *detector){
	return detector->threshold;
}
