################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/I2C_comm.c \
../Core/Src/MAX30112.c \
../Core/Src/PC_product_codes.c \
../Core/Src/UTILS_utils.c \
../Core/Src/WC_water_contact.c \
../Core/Src/i2c_communication_struct.c \
../Core/Src/i2c_memory.c \
../Core/Src/main.c \
../Core/Src/pec.c \
../Core/Src/rtc_conversions.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/I2C_comm.o \
./Core/Src/MAX30112.o \
./Core/Src/PC_product_codes.o \
./Core/Src/UTILS_utils.o \
./Core/Src/WC_water_contact.o \
./Core/Src/i2c_communication_struct.o \
./Core/Src/i2c_memory.o \
./Core/Src/main.o \
./Core/Src/pec.o \
./Core/Src/rtc_conversions.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/I2C_comm.d \
./Core/Src/MAX30112.d \
./Core/Src/PC_product_codes.d \
./Core/Src/UTILS_utils.d \
./Core/Src/WC_water_contact.d \
./Core/Src/i2c_communication_struct.d \
./Core/Src/i2c_memory.d \
./Core/Src/main.d \
./Core/Src/pec.d \
./Core/Src/rtc_conversions.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../../lfrt_library -I../../lfrt_library/Src -I../../lfrt_library/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/I2C_comm.cyclo ./Core/Src/I2C_comm.d ./Core/Src/I2C_comm.o ./Core/Src/I2C_comm.su ./Core/Src/MAX30112.cyclo ./Core/Src/MAX30112.d ./Core/Src/MAX30112.o ./Core/Src/MAX30112.su ./Core/Src/PC_product_codes.cyclo ./Core/Src/PC_product_codes.d ./Core/Src/PC_product_codes.o ./Core/Src/PC_product_codes.su ./Core/Src/UTILS_utils.cyclo ./Core/Src/UTILS_utils.d ./Core/Src/UTILS_utils.o ./Core/Src/UTILS_utils.su ./Core/Src/WC_water_contact.cyclo ./Core/Src/WC_water_contact.d ./Core/Src/WC_water_contact.o ./Core/Src/WC_water_contact.su ./Core/Src/i2c_communication_struct.cyclo ./Core/Src/i2c_communication_struct.d ./Core/Src/i2c_communication_struct.o ./Core/Src/i2c_communication_struct.su ./Core/Src/i2c_memory.cyclo ./Core/Src/i2c_memory.d ./Core/Src/i2c_memory.o ./Core/Src/i2c_memory.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pec.cyclo ./Core/Src/pec.d ./Core/Src/pec.o ./Core/Src/pec.su ./Core/Src/rtc_conversions.cyclo ./Core/Src/rtc_conversions.d ./Core/Src/rtc_conversions.o ./Core/Src/rtc_conversions.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

