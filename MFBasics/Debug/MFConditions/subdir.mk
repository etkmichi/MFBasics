################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFConditions/MFArealCheck.cpp \
../MFConditions/MFBaseCondition.cpp 

CPP_DEPS += \
./MFConditions/MFArealCheck.d \
./MFConditions/MFBaseCondition.d 

OBJS += \
./MFConditions/MFArealCheck.o \
./MFConditions/MFBaseCondition.o 


# Each subdirectory must supply rules for building sources it contributes
MFConditions/%.o: ../MFConditions/%.cpp MFConditions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFConditions

clean-MFConditions:
	-$(RM) ./MFConditions/MFArealCheck.d ./MFConditions/MFArealCheck.o ./MFConditions/MFBaseCondition.d ./MFConditions/MFBaseCondition.o

.PHONY: clean-MFConditions

