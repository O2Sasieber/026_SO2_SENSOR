################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Seafile/BENJAMIN/03_STM32_REPOSITORIES/lfrt_library/Src/LF_transmit.c \
C:/Seafile/BENJAMIN/03_STM32_REPOSITORIES/lfrt_library/Src/LF_transmitter_structs.c \
C:/Seafile/BENJAMIN/03_STM32_REPOSITORIES/lfrt_library/Src/generate_id.c 

OBJS += \
./Core/lfrt_library/Src/LF_transmit.o \
./Core/lfrt_library/Src/LF_transmitter_structs.o \
./Core/lfrt_library/Src/generate_id.o 

C_DEPS += \
./Core/lfrt_library/Src/LF_transmit.d \
./Core/lfrt_library/Src/LF_transmitter_structs.d \
./Core/lfrt_library/Src/generate_id.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lfrt_library/Src/LF_transmit.o: C:/Seafile/BENJAMIN/03_STM32_REPOSITORIES/lfrt_library/Src/LF_transmit.c Core/lfrt_library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../../lfrt_library -I../../lfrt_library/Src -I../../lfrt_library/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/lfrt_library/Src/LF_transmitter_structs.o: C:/Seafile/BENJAMIN/03_STM32_REPOSITORIES/lfrt_library/Src/LF_transmitter_structs.c Core/lfrt_library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../../lfrt_library -I../../lfrt_library/Src -I../../lfrt_library/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/lfrt_library/Src/generate_id.o: C:/Seafile/BENJAMIN/03_STM32_REPOSITORIES/lfrt_library/Src/generate_id.c Core/lfrt_library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../../lfrt_library -I../../lfrt_library/Src -I../../lfrt_library/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lfrt_library-2f-Src

clean-Core-2f-lfrt_library-2f-Src:
	-$(RM) ./Core/lfrt_library/Src/LF_transmit.cyclo ./Core/lfrt_library/Src/LF_transmit.d ./Core/lfrt_library/Src/LF_transmit.o ./Core/lfrt_library/Src/LF_transmit.su ./Core/lfrt_library/Src/LF_transmitter_structs.cyclo ./Core/lfrt_library/Src/LF_transmitter_structs.d ./Core/lfrt_library/Src/LF_transmitter_structs.o ./Core/lfrt_library/Src/LF_transmitter_structs.su ./Core/lfrt_library/Src/generate_id.cyclo ./Core/lfrt_library/Src/generate_id.d ./Core/lfrt_library/Src/generate_id.o ./Core/lfrt_library/Src/generate_id.su

.PHONY: clean-Core-2f-lfrt_library-2f-Src

