################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_program.c \
../GI_program.c \
../LED_program.c \
../RTOS_TMR_program.c \
../RTOS_program.c \
../SSD_program.c \
../main.c 

OBJS += \
./DIO_program.o \
./GI_program.o \
./LED_program.o \
./RTOS_TMR_program.o \
./RTOS_program.o \
./SSD_program.o \
./main.o 

C_DEPS += \
./DIO_program.d \
./GI_program.d \
./LED_program.d \
./RTOS_TMR_program.d \
./RTOS_program.d \
./SSD_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


