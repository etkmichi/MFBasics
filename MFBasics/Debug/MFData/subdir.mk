################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFData/MFDataObject.cpp \
../MFData/MFDataObjectBuffer.cpp \
../MFData/MFDataSerializer.cpp \
../MFData/MFStructurableData.cpp \
../MFData/MFStructurableDataBuffer.cpp \
../MFData/MFStructurableDataSetup.cpp 

CPP_DEPS += \
./MFData/MFDataObject.d \
./MFData/MFDataObjectBuffer.d \
./MFData/MFDataSerializer.d \
./MFData/MFStructurableData.d \
./MFData/MFStructurableDataBuffer.d \
./MFData/MFStructurableDataSetup.d 

OBJS += \
./MFData/MFDataObject.o \
./MFData/MFDataObjectBuffer.o \
./MFData/MFDataSerializer.o \
./MFData/MFStructurableData.o \
./MFData/MFStructurableDataBuffer.o \
./MFData/MFStructurableDataSetup.o 


# Each subdirectory must supply rules for building sources it contributes
MFData/%.o: ../MFData/%.cpp MFData/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFData

clean-MFData:
	-$(RM) ./MFData/MFDataObject.d ./MFData/MFDataObject.o ./MFData/MFDataObjectBuffer.d ./MFData/MFDataObjectBuffer.o ./MFData/MFDataSerializer.d ./MFData/MFDataSerializer.o ./MFData/MFStructurableData.d ./MFData/MFStructurableData.o ./MFData/MFStructurableDataBuffer.d ./MFData/MFStructurableDataBuffer.o ./MFData/MFStructurableDataSetup.d ./MFData/MFStructurableDataSetup.o

.PHONY: clean-MFData

