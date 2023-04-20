################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFObjects/MFConfigValue.cpp \
../MFObjects/MFObject.cpp 

CPP_DEPS += \
./MFObjects/MFConfigValue.d \
./MFObjects/MFObject.d 

OBJS += \
./MFObjects/MFConfigValue.o \
./MFObjects/MFObject.o 


# Each subdirectory must supply rules for building sources it contributes
MFObjects/%.o: ../MFObjects/%.cpp MFObjects/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFObjects

clean-MFObjects:
	-$(RM) ./MFObjects/MFConfigValue.d ./MFObjects/MFConfigValue.o ./MFObjects/MFObject.d ./MFObjects/MFObject.o

.PHONY: clean-MFObjects

