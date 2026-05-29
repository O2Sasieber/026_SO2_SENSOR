/*
 * i2c_memory.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Arne Sieber
 *
 * @brief I2C Memory Communication Module
 *
 * This module provides an interface for reading and writing data to a memory area
 * using the I2C protocol.
 *
 *  @copyright Copyright (c) Oxygen Scientific GmbH, 2023
 *
 */


#include "i2c_memory.h"

#define WHO_AM_I_REGISTER 0x40
#define GPIO_OUT_REGISTER 0x41

// magic value
#define WHO_AM_I 0xFB

static uint8_t offset = 0; 		/* index of current RAM cell */
static uint8_t first = 1;		/* first byte --> new offset */
static uint8_t *ram = NULL;		/* pointer to RAM */

volatile uint8_t transfer_direction;
volatile uint8_t transfer_complete;
volatile uint8_t new_rx_data;
volatile uint8_t busy;


/**
 * @brief Checks if there is an ongoing I2C memory communication.
 *
 * This function returns the current busy state of the I2C memory communication.
 *
 * @return 1 if there is an ongoing transmission, 0 if there is currently no communication.
 */
uint8_t I2C_memory_comm_busy(void)
{
	return busy;
}


/**
 * @brief Sets the pointer to the RAM memory.
 *
 * This function updates the internal pointer to the RAM memory.
 *
 * @param r Pointer to the RAM memory.
 */
void set_ram_pointer(uint8_t *r)
{
	ram=r;
}


/**
 * @brief Checks if new receive data is available.
 *
 * This function checks if new receive data is available and clears the new receive data flag if it is.
 *
 * @return 1 if new receive data is available, 0 otherwise.
 */
uint8_t I2C_new_rx_data(void)
{
	if (new_rx_data)
	{
		new_rx_data=0;
		return 1;
	}
	return 0;
}


/**
 * @brief I2C Listen Complete callback.
 *
 * This function is called when the I2C listen operation is complete.
 * It enables the I2C listen interrupt again and updates the new receive data flag if necessary.
 *
 * @param hi2c Pointer to the I2C handle structure.
 */
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	first = 1;
	HAL_I2C_EnableListen_IT(hi2c);	/* slave is ready again */

	if (transfer_direction == I2C_DIRECTION_TRANSMIT) {
		new_rx_data = 1;
	}
}


/**
 * @brief I2C Address callback.
 *
 * This function is called when the I2C address is detected.
 * It sets the transfer direction and updates the new receive data flag if necessary.
 *
 * @param hi2c Pointer to the I2C handle structure.
 * @param TransferDirection The transfer direction (I2C_DIRECTION_RECEIVE or I2C_DIRECTION_TRANSMIT).
 * @param AddrMatchCode The address match code.
 */
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	transfer_direction = TransferDirection;
	busy = 1;

	if( TransferDirection==I2C_DIRECTION_TRANSMIT ) {
		if( first ) {
			HAL_I2C_Slave_Seq_Receive_IT(hi2c, &offset, 1, I2C_NEXT_FRAME);
		} else {
			HAL_I2C_Slave_Seq_Receive_IT(hi2c, ram+offset, 1, I2C_NEXT_FRAME);
		}
	} else {
		HAL_I2C_Slave_Seq_Transmit_IT(hi2c, ram+offset, 1, I2C_NEXT_FRAME);
	}
}


/**
 * @brief I2C Slave Receive Complete callback.
 *
 * This function is called when the I2C slave receive operation is complete.
 * It updates the internal state and prepares for the next receive operation.
 *
 * @param hi2c Pointer to the I2C handle structure.
 *
 */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(first) {
		first = 0;
	} else {
		offset++;
	}
	HAL_I2C_Slave_Seq_Receive_IT(hi2c, ram+offset, 1, I2C_NEXT_FRAME);
}


/**
 * @brief I2C Slave Transmit Complete callback.
 *
 * This function is called when the I2C slave transmit operation is complete.
 * It updates the internal state and prepares for the next transmit operation.
 *
 * @param hi2c Pointer to the I2C handle structure.
 *
 */
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	offset++;
	HAL_I2C_Slave_Seq_Transmit_IT(hi2c, ram+offset, 1, I2C_NEXT_FRAME);
}


/**
 * @brief I2C Error callback.
 *
 * This function is called when an I2C error occurs.
 * It handles the error and updates the internal state accordingly.
 *
 * @param hi2c Pointer to the I2C handle structure.
 *
 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	busy = 0;

	if( HAL_I2C_GetError(hi2c) == HAL_I2C_ERROR_AF) {
		offset--;
	}
}


/**
 * @brief I2C Abort Complete callback.
 *
 * This function is called when the I2C abort operation is complete.
 *
 * @param hi2c Pointer to the I2C handle structure.
 *
 */
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c)
{
	busy = 0;
}
