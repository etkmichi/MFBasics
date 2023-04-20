################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Interfaces/Informations/MFIInfoList.cpp 

CPP_DEPS += \
./Interfaces/Informations/MFIInfoList.d 

OBJS += \
./Interfaces/Informations/MFIInfoList.o 


# Each subdirectory must supply rules for building sources it contributes
Interfaces/Informations/%.o: ../Interfaces/Informations/%.cpp Interfaces/Informations/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Interfaces-2f-Informations

clean-Interfaces-2f-Informations:
	-$(RM) ./Interfaces/Informations/MFIInfoList.d ./Interfaces/Informations/MFIInfoList.o

.PHONY: clean-Interfaces-2f-Informations

