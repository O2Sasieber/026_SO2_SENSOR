/*
 * i2c_memory.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Arne Sieber
 *
 * @copyright Copyright (c) Oxygen Scientific GmbH, 2023
 *
 */

#ifndef SRC_I2C_MEMORY_H_
#define SRC_I2C_MEMORY_H_


#include "main.h"

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c);
void set_ram_pointer(uint8_t * r);
uint8_t I2C_new_rx_data(void);
uint8_t I2C_memory_comm_busy(void);

/* timing consideration:
 * 100 kHz transmission frequency
 * ~ 100 us / byte */

#endif /* SRC_I2C_MEMORY_H_ */
