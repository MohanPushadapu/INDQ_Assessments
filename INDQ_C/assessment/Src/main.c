
#include "main.h"
#include "ecg_filter.h"
#include "ecg_integrator.h"
#include "r_peak_detector.h"
#include "heart_rate.h"
#include "signal_quality.h"
#include "adc.h"
#include "uart_output.h"

static ECG_Filter filter;
static ECGProcessor processor;
static RPeakDetector detector;
static HeartRate heart_rate;
static SignalQuality quality;

static float filtered_ecg;
static float integrated;
static uint8_t r_peak;
static float bpm;
static SignalQualityStatus status;
static const char *status_str;

static const float b_coeffs[5] = {
		0.007820f, 0.0f, -0.015640, 0.0f, 0.007820f
};

static const float a_coeffs[5] = {
    1.0f, -3.705189f, 5.180304f, --3.240903f, 0.766007f
};

int main(void)
{
	HAL_Init();

	SystemClock_Config();

	ADC_Helper_Init();
	MX_USART2_UART_Init();

	ECG_Filter_Init(&filter,b_coeffs[5],a_coeffs[5]);
	ECGProcessor_Init(&processor);
	RPeakDetector_Init(&detector);
	HeartRate_Init(&heart_rate);
	SignalQuality_Init(&quality);

	while(1)
	{

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM2){
		uint16_t adc_value = ADC_Helper_TimerISR();

//		Filtered ECG Value.
		filtered_ecg = ECG_Filter_Update(&filter,adc_value);

		// QRS envelope
		integrated = ECGProcessor_Update(&processor,filtered_ecg);

		SignalQuality_UpdateSignal(&quality, integrated);

		// R-Peaks
		r_peak = RPeakDetector_Update(&detector,integrated);

		// Heart Rate
		if (r_peak){

			bpm = HeartRate_Update(&heart_rate,detector.sample_count);

			if (heart_rate.valid){
				SignalQuality_UpdateRR(&quality,heart_rate.rr_interval);
			}
		}

		// Quality Status
		status = SignalQuality_GetStatus(&quality);
		status_str = SignalQuality_GetStatusString(status);


		// Filtered ECG/R-Peak/Heart Rate/Signal quality via UART
		char buffer[64];
		snprintf(buffer,sizeof(buffer),"%.3f,%u,%.1f,%s\r\n", // @suppress("Float formatting support")
				filtered_ecg,
				r_peak,
				bpm,
				status_str);

		UART_Print(buffer);

	}
}
