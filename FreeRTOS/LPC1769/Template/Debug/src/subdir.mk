################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc17.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\wsRTO\CMSISv2p00_LPC17xx\inc" -I"C:\wsRTO\Lib_FreeRTOS_7p0p1\demo_code" -I"C:\wsRTO\Lib_API_CAPI\inc" -I"C:\wsRTO\Lib_Contenedores\inc" -I"C:\wsRTO\Lib_MCU_LPC176x\inc" -I"C:\wsRTO\Lib_FreeRTOS_7p0p1\FreeRTOS_include" -I"C:\wsRTO\Lib_FreeRTOS_7p0p1\FreeRTOS_portable" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


