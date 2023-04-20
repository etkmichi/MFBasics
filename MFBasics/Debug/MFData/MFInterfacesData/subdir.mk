################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFData/MFInterfacesData/MFIBufferSink.cpp \
../MFData/MFInterfacesData/MFIDataObjectWrite.cpp \
../MFData/MFInterfacesData/MFISerializable.cpp \
../MFData/MFInterfacesData/MFIStructSource.cpp \
../MFData/MFInterfacesData/MFIStructurableDataCreator.cpp 

CPP_DEPS += \
./MFData/MFInterfacesData/MFIBufferSink.d \
./MFData/MFInterfacesData/MFIDataObjectWrite.d \
./MFData/MFInterfacesData/MFISerializable.d \
./MFData/MFInterfacesData/MFIStructSource.d \
./MFData/MFInterfacesData/MFIStructurableDataCreator.d 

OBJS += \
./MFData/MFInterfacesData/MFIBufferSink.o \
./MFData/MFInterfacesData/MFIDataObjectWrite.o \
./MFData/MFInterfacesData/MFISerializable.o \
./MFData/MFInterfacesData/MFIStructSource.o \
./MFData/MFInterfacesData/MFIStructurableDataCreator.o 


# Each subdirectory must supply rules for building sources it contributes
MFData/MFInterfacesData/%.o: ../MFData/MFInterfacesData/%.cpp MFData/MFInterfacesData/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFData-2f-MFInterfacesData

clean-MFData-2f-MFInterfacesData:
	-$(RM) ./MFData/MFInterfacesData/MFIBufferSink.d ./MFData/MFInterfacesData/MFIBufferSink.o ./MFData/MFInterfacesData/MFIDataObjectWrite.d ./MFData/MFInterfacesData/MFIDataObjectWrite.o ./MFData/MFInterfacesData/MFISerializable.d ./MFData/MFInterfacesData/MFISerializable.o ./MFData/MFInterfacesData/MFIStructSource.d ./MFData/MFInterfacesData/MFIStructSource.o ./MFData/MFInterfacesData/MFIStructurableDataCreator.d ./MFData/MFInterfacesData/MFIStructurableDataCreator.o

.PHONY: clean-MFData-2f-MFInterfacesData

