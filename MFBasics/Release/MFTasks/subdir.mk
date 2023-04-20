################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFTasks/MFAbstractDataProcessingTask.cpp \
../MFTasks/MFAbstractTask.cpp \
../MFTasks/MFCallbackTask.cpp \
../MFTasks/MFTaskManager.cpp 

CPP_DEPS += \
./MFTasks/MFAbstractDataProcessingTask.d \
./MFTasks/MFAbstractTask.d \
./MFTasks/MFCallbackTask.d \
./MFTasks/MFTaskManager.d 

OBJS += \
./MFTasks/MFAbstractDataProcessingTask.o \
./MFTasks/MFAbstractTask.o \
./MFTasks/MFCallbackTask.o \
./MFTasks/MFTaskManager.o 


# Each subdirectory must supply rules for building sources it contributes
MFTasks/%.o: ../MFTasks/%.cpp MFTasks/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFTasks

clean-MFTasks:
	-$(RM) ./MFTasks/MFAbstractDataProcessingTask.d ./MFTasks/MFAbstractDataProcessingTask.o ./MFTasks/MFAbstractTask.d ./MFTasks/MFAbstractTask.o ./MFTasks/MFCallbackTask.d ./MFTasks/MFCallbackTask.o ./MFTasks/MFTaskManager.d ./MFTasks/MFTaskManager.o

.PHONY: clean-MFTasks

