################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ecg_derivative.c \
../Src/ecg_filter.c \
../Src/ecg_integrator.c \
../Src/heart_rate.c \
../Src/main.c \
../Src/r_peak_detector.c \
../Src/signal_quality.c \
../Src/uart_output.c 

C_DEPS += \
./Src/ecg_derivative.d \
./Src/ecg_filter.d \
./Src/ecg_integrator.d \
./Src/heart_rate.d \
./Src/main.d \
./Src/r_peak_detector.d \
./Src/signal_quality.d \
./Src/uart_output.d 

OBJS += \
./Src/ecg_derivative.o \
./Src/ecg_filter.o \
./Src/ecg_integrator.o \
./Src/heart_rate.o \
./Src/main.o \
./Src/r_peak_detector.o \
./Src/signal_quality.o \
./Src/uart_output.o 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Users/mohanpushadapu/Documents/WORK/Job Applications/INDQ_/INDQ_C/assessment/Inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Src

clean-Src:
	-$(RM) ./Src/ecg_derivative.d ./Src/ecg_derivative.o ./Src/ecg_filter.d ./Src/ecg_filter.o ./Src/ecg_integrator.d ./Src/ecg_integrator.o ./Src/heart_rate.d ./Src/heart_rate.o ./Src/main.d ./Src/main.o ./Src/r_peak_detector.d ./Src/r_peak_detector.o ./Src/signal_quality.d ./Src/signal_quality.o ./Src/uart_output.d ./Src/uart_output.o

.PHONY: clean-Src

