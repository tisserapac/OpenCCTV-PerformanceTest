################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opencctv/util/performance_test/DateTime.cpp \
../src/opencctv/util/performance_test/TestDataModel.cpp \
../src/opencctv/util/performance_test/Timer.cpp 

OBJS += \
./src/opencctv/util/performance_test/DateTime.o \
./src/opencctv/util/performance_test/TestDataModel.o \
./src/opencctv/util/performance_test/Timer.o 

CPP_DEPS += \
./src/opencctv/util/performance_test/DateTime.d \
./src/opencctv/util/performance_test/TestDataModel.d \
./src/opencctv/util/performance_test/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/opencctv/util/performance_test/%.o: ../src/opencctv/util/performance_test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


