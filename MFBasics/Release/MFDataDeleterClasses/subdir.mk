################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFDataDeleterClasses/MFDataDeleterThread.cpp \
../MFDataDeleterClasses/MFDataDeletion.cpp \
../MFDataDeleterClasses/MFDeletionTask.cpp 

CPP_DEPS += \
./MFDataDeleterClasses/MFDataDeleterThread.d \
./MFDataDeleterClasses/MFDataDeletion.d \
./MFDataDeleterClasses/MFDeletionTask.d 

OBJS += \
./MFDataDeleterClasses/MFDataDeleterThread.o \
./MFDataDeleterClasses/MFDataDeletion.o \
./MFDataDeleterClasses/MFDeletionTask.o 


# Each subdirectory must supply rules for building sources it contributes
MFDataDeleterClasses/%.o: ../MFDataDeleterClasses/%.cpp MFDataDeleterClasses/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFDataDeleterClasses

clean-MFDataDeleterClasses:
	-$(RM) ./MFDataDeleterClasses/MFDataDeleterThread.d ./MFDataDeleterClasses/MFDataDeleterThread.o ./MFDataDeleterClasses/MFDataDeletion.d ./MFDataDeleterClasses/MFDataDeletion.o ./MFDataDeleterClasses/MFDeletionTask.d ./MFDataDeleterClasses/MFDeletionTask.o

.PHONY: clean-MFDataDeleterClasses

