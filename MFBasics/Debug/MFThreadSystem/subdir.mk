################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFThreadSystem/MFIWakableThread.cpp \
../MFThreadSystem/MFTaskThread.cpp 

CPP_DEPS += \
./MFThreadSystem/MFIWakableThread.d \
./MFThreadSystem/MFTaskThread.d 

OBJS += \
./MFThreadSystem/MFIWakableThread.o \
./MFThreadSystem/MFTaskThread.o 


# Each subdirectory must supply rules for building sources it contributes
MFThreadSystem/%.o: ../MFThreadSystem/%.cpp MFThreadSystem/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFThreadSystem

clean-MFThreadSystem:
	-$(RM) ./MFThreadSystem/MFIWakableThread.d ./MFThreadSystem/MFIWakableThread.o ./MFThreadSystem/MFTaskThread.d ./MFThreadSystem/MFTaskThread.o

.PHONY: clean-MFThreadSystem

