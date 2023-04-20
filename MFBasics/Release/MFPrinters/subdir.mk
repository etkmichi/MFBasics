################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFPrinters/MFConsolePrinter.cpp \
../MFPrinters/MFPrintSetup.cpp \
../MFPrinters/MFPrintTarget.cpp \
../MFPrinters/MFPrintTask.cpp \
../MFPrinters/MFPrinterface.cpp 

CPP_DEPS += \
./MFPrinters/MFConsolePrinter.d \
./MFPrinters/MFPrintSetup.d \
./MFPrinters/MFPrintTarget.d \
./MFPrinters/MFPrintTask.d \
./MFPrinters/MFPrinterface.d 

OBJS += \
./MFPrinters/MFConsolePrinter.o \
./MFPrinters/MFPrintSetup.o \
./MFPrinters/MFPrintTarget.o \
./MFPrinters/MFPrintTask.o \
./MFPrinters/MFPrinterface.o 


# Each subdirectory must supply rules for building sources it contributes
MFPrinters/%.o: ../MFPrinters/%.cpp MFPrinters/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFPrinters

clean-MFPrinters:
	-$(RM) ./MFPrinters/MFConsolePrinter.d ./MFPrinters/MFConsolePrinter.o ./MFPrinters/MFPrintSetup.d ./MFPrinters/MFPrintSetup.o ./MFPrinters/MFPrintTarget.d ./MFPrinters/MFPrintTarget.o ./MFPrinters/MFPrintTask.d ./MFPrinters/MFPrintTask.o ./MFPrinters/MFPrinterface.d ./MFPrinters/MFPrinterface.o

.PHONY: clean-MFPrinters

