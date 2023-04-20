################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFTasks/MFInterfacesTasks/MFITaskProvider.cpp 

CPP_DEPS += \
./MFTasks/MFInterfacesTasks/MFITaskProvider.d 

OBJS += \
./MFTasks/MFInterfacesTasks/MFITaskProvider.o 


# Each subdirectory must supply rules for building sources it contributes
MFTasks/MFInterfacesTasks/%.o: ../MFTasks/MFInterfacesTasks/%.cpp MFTasks/MFInterfacesTasks/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFTasks-2f-MFInterfacesTasks

clean-MFTasks-2f-MFInterfacesTasks:
	-$(RM) ./MFTasks/MFInterfacesTasks/MFITaskProvider.d ./MFTasks/MFInterfacesTasks/MFITaskProvider.o

.PHONY: clean-MFTasks-2f-MFInterfacesTasks

