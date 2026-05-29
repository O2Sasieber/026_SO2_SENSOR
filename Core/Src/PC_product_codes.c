/*
 * PC_product_codes.c
 *
 *  Created on: 11.07.2023
 *      Author: Benjamin Kuch
 *
 * @brief Product functions.
 *
 * This file provides a set of functions prviding product information like product code, serial number, hardware id, etc.
 *
 * @copyright Copyright (c) Oxygen Scientific GmbH, 2023
 *
 */

#include "PC_product_codes.h"
#include "hardware_defines.h"
#include <string.h>


/**
 * @brief Getter function which returns the device serial number.
 *
 * @retval Serial number.
 *
 */
uint32_t PC_get_serial_number(void) {
	uint32_t sn;
	memcpy(&sn, (void*)SERIAL_NUMBER_ADDRESS, sizeof(uint32_t));
    return sn;
}


/**
 * @brief Getter function which returns the device hardware ID.
 *
 * @retval Hardware ID.
 *
 */
uint8_t PC_get_HW_id(void) {
	uint32_t HW_id;
	memcpy(&HW_id, (void*)LOGISTIC_DATA_ADDRESS, sizeof(uint32_t));
    return (uint8_t)((HW_id >> 24) & 0xFF);
}


/**
 * @brief Getter function which returns the device ID.
 *
 * @retval Device ID.
 *
 */
uint8_t PC_get_device_id(void) {
#if(PLATFORM == PLATFORM_STM32)
	uint32_t serial = PC_get_serial_number();
	return (uint8_t)((serial / 10000) % 100);
#else
#if(HUD == 1)
    return RNO_HUD;
#endif
#if(DC23 == 1)
    return RNO_ONE;
#endif
#endif
}


/**
 * @brief Getter function which returns the device sub ID.
 *
 * @retval Device sub ID.
 *
 */
uint8_t PC_get_device_subid(void) {
#if(PLATFORM == PLATFORM_STM32)
	uint32_t device_subid;
	memcpy(&device_subid, (void*)LOGISTIC_DATA_ADDRESS, sizeof(uint32_t));
    return (uint8_t)((device_subid >> 8) & 0xFF);
#else
    return 0;
#endif
}


/**
 * @brief Getter function which returns the device I2C address.
 *
 * @retval Device I2C address.
 *
 */
uint8_t PC_get_I2C_address(void) {
	uint32_t i2c_address;
	memcpy(&i2c_address, (void*)LOGISTIC_DATA_ADDRESS, sizeof(uint32_t));
    return (uint8_t)(i2c_address & 0xFF);
}
