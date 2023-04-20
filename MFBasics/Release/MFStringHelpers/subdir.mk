################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFStringHelpers/MFToString.cpp 

CPP_DEPS += \
./MFStringHelpers/MFToString.d 

OBJS += \
./MFStringHelpers/MFToString.o 


# Each subdirectory must supply rules for building sources it contributes
MFStringHelpers/%.o: ../MFStringHelpers/%.cpp MFStringHelpers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFStringHelpers

clean-MFStringHelpers:
	-$(RM) ./MFStringHelpers/MFToString.d ./MFStringHelpers/MFToString.o

.PHONY: clean-MFStringHelpers

