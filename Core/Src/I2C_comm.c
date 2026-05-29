/*
 * I2C_comm.c
 *
 * I2C Stands for I2C Communication
 *
 *  Created on: Oct 14, 2021
 *      Author: Irfan Sehic
 *
 * @brief I2C Communication Module
 *
 * This module provides an interface for reading and writing data to the I2C interface
 * using the I2C protocol.
 *
 * Copyright (c) 2021 Oxygen scientific GmbH. All rights reserved.
 *
 */

#include "I2C_comm.h"
#include <stdio.h>

#define BSP_ERROR_NONE                    	0
#define BSP_ERROR_NO_INIT                	-1
#define BSP_ERROR_WRONG_PARAM            	-2
#define BSP_ERROR_BUSY                   	-3
#define BSP_ERROR_PERIPH_FAILURE         	-4
#define BSP_ERROR_COMPONENT_FAILURE      	-5
#define BSP_ERROR_UNKNOWN_FAILURE        	-6
#define BSP_ERROR_UNKNOWN_COMPONENT      	-7
#define BSP_ERROR_BUS_FAILURE            	-8
#define BSP_ERROR_CLOCK_FAILURE          	-9
#define BSP_ERROR_MSP_FAILURE            	-10
#define BSP_ERROR_FEATURE_NOT_SUPPORTED     -11
#define BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE   -102

#define BUS_I2C1_POLL_TIMEOUT               0x1000U


#include "I2C_comm.h"
#include "main.h"


/**
 * @brief Initializes the microsecond delay function.
 *
 * This function initializes the microsecond delay function.
 *
 * @return Clock cycle counter has started (TRUE or FALSE).
 *
 * @note This function must be called before using the _delay_us function.
 *
 */
uint8_t _delay_us_init(void) {

	/* Disable TRC */
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;

	/* Enable TRC */
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

	/* Disable clock cycle counter */
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;

	/* Enable  clock cycle counter */
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

	/* Reset the clock cycle counter value */
	DWT->CYCCNT = 0;

	/* 3 NO OPERATION instructions */
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");

	/* Check if clock cycle counter has started */
	if (DWT->CYCCNT) {
		return 0; /* clock cycle counter started*/
	} else {
		return 1; /* clock cycle counter not started*/
	}
}


/**
 * @brief Delays for a specified number of microseconds.
 *
 * This function generates a delay of the specified number of microseconds.
 *
 * @param microseconds The number of microseconds to delay.
 *
 * @note This function uses the DWT clock cycle counter to generate the delay.
 * The _delay_us_init function must be called before using this function.
 *
 */
__STATIC_INLINE void _delay_us(volatile uint32_t microseconds) {

	uint32_t clk_cycle_start = DWT->CYCCNT;

	/* Go to number of cycles for system */
	microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);

	/* Delay till end */
	while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}


/**
 * @brief Reads an 8-bit register from an I2C device.
 *
 * This function reads an 8-bit register from an I2C device using the HAL_I2C_Mem_Read function.
 *
 * @param hi2c Pointer to an I2C_HandleTypeDef structure that contains the configuration information for the specified I2C.
 * @param DevAddr The 7-bit address of the I2C device.
 * @param Reg The address of the register to read.
 * @param pData Pointer to the buffer that will store the read data.
 * @param Length The number of bytes to read.
 *
 * @return The status of the I2C read operation.
 *
 * @note This function uses the HAL_I2C_Mem_Read function to perform the read operation.
 */
uint8_t I2C_read_reg_8bit(I2C_HandleTypeDef* hi2c, uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
    HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(hi2c, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length, 8);

    return ret;
}


/**
 * @brief Writes an 8-bit register from an I2C device.
 *
 * This function writes an 8-bit register from an I2C device using the HAL_I2C_Mem_Read function.
 *
 * @param hi2c Pointer to an I2C_HandleTypeDef structure that contains the configuration information for the specified I2C.
 * @param DevAddr The 7-bit address of the I2C device.
 * @param Reg The address of the register to read.
 * @param pData Pointer to the buffer that will store the read data.
 * @param Length The number of bytes to read.
 *
 * @return The status of the I2C write operation.
 *
 * @note This function uses the HAL_I2C_Mem_Write function to perform the read operation.
 */
uint8_t I2C_write_reg_8bit(I2C_HandleTypeDef* hi2c, uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
    HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(hi2c, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length, 8);

    return ret;
}


/**
 * @brief Reads data from an I2C device.
 *
 * This function reads data from an I2C device using the HAL_I2C_Master_Receive function.
 *
 * @param hi2c Pointer to an I2C_HandleTypeDef structure that contains the configuration information for the specified I2C.
 * @param DevAddr The 7-bit address of the I2C device.
 * @param pData Pointer to the buffer that will store the read data.
 * @param Length The number of bytes to read.
 *
 * @return The status of the I2C read operation.
 *
 * @note This function uses the HAL_I2C_Master_Receive function to perform the read operation.
 */
uint8_t I2C_read_data(I2C_HandleTypeDef* hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
    HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(hi2c, DevAddr, (uint8_t*) pData, Length, 8);

    return ret;
}


/**
 * @brief Writes data to an I2C device.
 *
 * This function writes data to an I2C device using the HAL_I2C_Master_Transmit function.
 *
 * @param[in] hi2c Pointer to an I2C_HandleTypeDef structure that contains the configuration information for the specified I2C.
 * @param[in] DevAddr The 7-bit address of the I2C device.
 * @param[in] pData Pointer to the buffer that contains the data to be written.
 * @param[in] Length The number of bytes to write.
 *
 * @return The status of the I2C write operation.
 *
 * @note This function uses the HAL_I2C_Master_Transmit function to perform the write operation.
 */
uint8_t I2C_write_data(I2C_HandleTypeDef* hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(hi2c,  DevAddr, pData, Length, 8);

    return ret;
}


#if(INCLUDE_I2C_RESET)
#define I2C_RESET_TRIALS (10)
/**
 * @brief Resets an I2C bus by releasing a blocked bus.
 *
 * This function attempts to release a blocked I2C bus by toggling the SCL line and checking the SDA line.
 *
 * @param hi2c Pointer to an I2C_HandleTypeDef structure that contains the configuration information for the specified I2C.
 * @param I2Cx_SDA_port Pointer to the GPIO port containing the SDA pin.
 * @param I2Cx_SDA_pin The pin number of the SDA signal on the specified GPIO port.
 * @param I2Cx_SCL_port Pointer to the GPIO port containing the SCL pin.
 * @param I2Cx_SCL_pin The pin number of the SCL signal on the specified GPIO port.
 *
 * @return 1 if the bus is successfully reset, 0 otherwise.
 *
 * @note This function uses a simple algorithm to release a blocked bus and may not work in all cases.
 * @note The I2C bus is de-initialized and re-initialized during the reset process.
 */
uint8_t I2C_reset(I2C_HandleTypeDef* hi2c, GPIO_TypeDef* I2Cx_SDA_port, uint16_t I2Cx_SDA_pin, GPIO_TypeDef* I2Cx_SCL_port, uint16_t I2Cx_SCL_pin) {

	_delay_us_init();

	uint8_t ret = 0;

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* de-initialize I2C */
	HAL_I2C_DeInit(hi2c);

	/* Configure I2C SCL pin as output */
	GPIO_InitStruct.Pin = I2Cx_SCL_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(I2Cx_SCL_port, &GPIO_InitStruct);

	/* Configure I2C SDA pin as input */
	GPIO_InitStruct.Pin = I2Cx_SDA_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(I2Cx_SDA_port, &GPIO_InitStruct);

	/* try to release blocked I2C bus */
	for(uint8_t i=0;i<I2C_RESET_TRIALS;i++) {
		HAL_GPIO_WritePin(I2Cx_SCL_port, I2Cx_SCL_pin, GPIO_PIN_RESET);
		_delay_us(10);
		HAL_GPIO_WritePin(I2Cx_SCL_port, I2Cx_SCL_pin, GPIO_PIN_SET);
		_delay_us(10);

		if(HAL_GPIO_ReadPin(I2Cx_SDA_port, I2Cx_SDA_pin) == GPIO_PIN_SET) {
			ret = 1;
			break;
		}
	}

	/* de-initialize GPIO Pins */
    HAL_GPIO_DeInit(I2Cx_SCL_port, I2Cx_SCL_pin);
    HAL_GPIO_DeInit(I2Cx_SDA_port, I2Cx_SDA_pin);

	/* re-initialize I2C */
	HAL_I2C_Init(hi2c);

	return ret;
}


/**
 * @brief Checks if an I2C bus is blocked.
 *
 * This function checks if an I2C bus is blocked by reading the state of the SDA and SCL lines.
 *
 * @param I2Cx_SDA_port Pointer to the GPIO port containing the SDA pin.
 * @param I2Cx_SDA_pin The pin number of the SDA signal on the specified GPIO port.
 * @param I2Cx_SCL_port Pointer to the GPIO port containing the SCL pin.
 * @param I2Cx_SCL_pin The pin number of the SCL signal on the specified GPIO port.
 *
 * @return 1 if the bus is blocked, 0 otherwise.
 *
 */
uint8_t I2C_blocked(GPIO_TypeDef* I2Cx_SDA_port, uint16_t I2Cx_SDA_pin, GPIO_TypeDef* I2Cx_SCL_port, uint16_t I2Cx_SCL_pin) {
	return ((HAL_GPIO_ReadPin(I2Cx_SDA_port, I2Cx_SDA_pin) == GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(I2Cx_SCL_port, I2Cx_SCL_pin) == GPIO_PIN_RESET)) ? 1 : 0;
}
#endif
