################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ControlMapper.cpp \
../Game.cpp \
../Globals.cpp \
../InputManager.cpp \
../MainMenu.cpp \
../ResolutionManager.cpp \
../TextureManager.cpp \
../main.cpp 

OBJS += \
./ControlMapper.o \
./Game.o \
./Globals.o \
./InputManager.o \
./MainMenu.o \
./ResolutionManager.o \
./TextureManager.o \
./main.o 

CPP_DEPS += \
./ControlMapper.d \
./Game.d \
./Globals.d \
./InputManager.d \
./MainMenu.d \
./ResolutionManager.d \
./TextureManager.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


