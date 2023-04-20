################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFTime/MFTickCounter.cpp \
../MFTime/MFTimeHelper.cpp \
../MFTime/MFTimeStructs.cpp 

CPP_DEPS += \
./MFTime/MFTickCounter.d \
./MFTime/MFTimeHelper.d \
./MFTime/MFTimeStructs.d 

OBJS += \
./MFTime/MFTickCounter.o \
./MFTime/MFTimeHelper.o \
./MFTime/MFTimeStructs.o 


# Each subdirectory must supply rules for building sources it contributes
MFTime/%.o: ../MFTime/%.cpp MFTime/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFTime

clean-MFTime:
	-$(RM) ./MFTime/MFTickCounter.d ./MFTime/MFTickCounter.o ./MFTime/MFTimeHelper.d ./MFTime/MFTimeHelper.o ./MFTime/MFTimeStructs.d ./MFTime/MFTimeStructs.o

.PHONY: clean-MFTime

