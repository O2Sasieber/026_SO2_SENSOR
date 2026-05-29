/*
 * i2c_communication_struct.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Arne Sieber
 *
 * @brief I2C communication structure implementation.
 *
 * This file contains the implementation of the I2C communication structure,
 * including functions for bit manipulation and information bit setting.
 *
 * Copyright (c) 2023 Oxygen scientific GmbH. All rights reserved.
 *
 */

#include "i2c_communication_struct.h"

#include "i2c_memory.h"
#include <math.h>


/**
 * @brief Get bit state.
 *
 * @param bits Input value where the bit state has to be exacted from.
 * @param bit_position Bit position.
 *
 * @retval Result (0 or 1).
 */
uint8_t i2c_get_bitstate(uint16_t bits, uint16_t bit_position) {
	return ((bits & bit_position) == 0) ? 0 : 1;
}


/**
 * @brief Set bit.
 *
 * @param bits Pointer to input value where the bit has to be set.
 * @param bit_position Bit position.
 *
 */
void i2c_set_bit(volatile uint16_t *bits, uint16_t bit_position)
{
    *bits = *bits | (bit_position);
}


/**
 * @brief Clear bit.
 *
 * @param bits Pointer to input value where the bit has to be cleared.
 * @param bit_position Bit position.
 *
 */
void i2c_clear_bit(volatile uint16_t *bits, uint16_t bit_position)
{
	*bits = *bits & (~bit_position);
}


/**
 * @brief Function to extract k bits from bit_position position.
 *
 * @param value Input value.
 * @param n_bits Number of bits.
 * @param bit_position Bit position.
 * @return Extracted value as integer.
 */
uint16_t i2c_bits_extracted(uint16_t value, uint16_t n_bits, uint16_t bit_position)
{
    return (((1 << n_bits) - 1) & (value >> (bit_position - 1)));
}


/**
 * @brief Set infobit function.
 *
 * @param info_word Pointer to info_word where the bit has to be set or cleared.
 * @param state Bit state.
 * @param bit Bit position.
 *
 */
void i2c_set_infobit(volatile uint16_t* info_word, volatile uint8_t state, uint16_t bit) {

	if(state) {
		i2c_set_bit(info_word, bit);
	} else {
		i2c_clear_bit(info_word, bit);
	}
}
