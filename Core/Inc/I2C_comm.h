/*
 * I2C_comm.h
 *
 * I2C Stands for I2C Communication
 *
 *  Created on: Oct 14, 2021
 *      Author: Irfan Sehic
 *
 * Copyright (c) 2021 Oxygen scientific GmbH. All rights reserved.
 *
 */
#ifndef INC_I2C_COMM_H_
#define INC_I2C_COMM_H_

#include "hardware_defines.h"

#if(PLATFORM == PLATFORM_STM32)

#define I2C_RECOVERY_TRIALS (3)

#include "stdint.h"
#include "stm32l4xx.h"

uint8_t I2C_read_reg_8bit(I2C_HandleTypeDef*  hi2c, uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
uint8_t I2C_write_reg_8bit(I2C_HandleTypeDef* hi2c, uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);

uint8_t I2C_read_data(I2C_HandleTypeDef*  hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Length);
uint8_t I2C_write_data(I2C_HandleTypeDef* hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Length);
#endif

#if(INCLUDE_I2C_RESET)
uint8_t I2C_reset(I2C_HandleTypeDef* hi2c, GPIO_TypeDef* I2Cx_SDA_port, uint16_t I2Cx_SDA_pin, GPIO_TypeDef* I2Cx_SCL_port, uint16_t I2Cx_SCL_pin);
uint8_t I2C_blocked(GPIO_TypeDef* I2Cx_SDA_port, uint16_t I2Cx_SDA_pin, GPIO_TypeDef* I2Cx_SCL_port, uint16_t I2Cx_SCL_pin);
#endif

#endif /* INC_I2C_COMM_H_ */
