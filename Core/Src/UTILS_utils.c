/*
 * UTILS_utils.c
 *
 * UTILS stands for Utilities
 *
 *  Created on: Aug 3, 2021
 *      Author: Peter Casapicola
 */

#include "hardware_defines.h"

#if(PLATFORM == PLATFORM_STM32)
#include "stm32l4xx_hal.h"
#endif

#include "UTILS_utils.h"
#include "string.h"
#include "stdio.h"
#include "math.h"
#include "stdint.h"


static uint8_t _is_metric = TRUE;


uint32_t UTILS_map_u32(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
    return (x - in_min) * ((out_max - out_min) / (in_max - in_min)) + out_min;
}

float UTILS_map_f(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * ((out_max - out_min) / (in_max - in_min)) + out_min;
}

int32_t UTILS_map_i32(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
    return (x - in_min) * ((out_max - out_min) / (in_max - in_min)) + out_min;
}

float UTILS_rng_f32(uint32_t n)
{
    return (n >> 8) * 0x1p-24f;
}

uint8_t UTILS_bfr_compare(uint8_t *bfr1, uint8_t *bfr2, uint8_t bfr_size) {

	for(uint8_t i=0; i<bfr_size; i++) {

//		printf("%02x <=> %02x\n", bfr1[i], bfr2[i]);

		if(bfr1[i] != bfr2[i]) {
			return FALSE;
		}
	}

	return TRUE;
}

uint32_t UTILS_get_mean(uint32_t a[], uint8_t a_len)
{
    uint8_t i = 0;
    uint64_t result = 0;

    for (i = 0; i < a_len; i++)
    {
        result += a[i];
    }

    return (uint32_t) (result / a_len);
}

uint32_t UTILS_get_minmax(uint32_t a[], uint8_t a_len, bool min)
{
    uint8_t i = 0;
    uint32_t result = (min) ? 0xFFFFFFFF : -1 * 0xFFFFFFFF;
    for (i = 0; i < a_len; i++)
    {
        switch (min)
        {
            case true:
                if (result < a[i])
                {
                    result = a[i];
                }
                break;
            case false:
                if (result > a[i])
                {
                    result = a[i];
                }
                break;

        }
    }
    return result;
}

/**
 * HAL Systick has to be active (is wakeup source)
 * @param ms: Delay time in milliseconds
 */
void UTILS_delay_with_sleep(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
#if(PLATFORM == PLATFORM_STM32)
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
#endif
    }
}

void UTILS_delay_us(uint32_t us)
{
#if(PLATFORM == PLATFORM_STM32)
    for(uint32_t i = 0; i < us; i++)
    {
        for(uint32_t j = 0; j < 100000/8/1000; j++)
        {
            __ASM volatile ("NOP");
        }
    }
#endif
}

uint32_t UTILS_get_decimals(float a, uint8_t dec)
{
        return fmod(a, 1.0f)*pow(10, dec);
}

float UTILS_unit_pressure(float bar)
{
    if(!_is_metric) {
    	bar *= 14.5038f;

    	if(bar < 50) {
    		return 0;
    	}
    }

    return bar;
}

float UTILS_unit_depth(float m)
{
	if(!_is_metric)
	{
		m *= METER_TO_FEET;
	}

    return m;
}

float UTILS_unit_depth_to_meter(float depth)
{
	if(!_is_metric)
	{
		depth *= FEET_TO_METER;
	}

    return depth;
}

float UTILS_unit_ascent_speed(float m_per_min)
{
	if(!_is_metric)
	{
		m_per_min *= METER_TO_FEET;
	}

    return m_per_min;
}

uint16_t UTILS_unit_depth_deco(uint16_t ceiling_m)
{
	if(!_is_metric)
		return ceiling_m / 3U * 10U;
	else
		return ceiling_m;
}

uint16_t UTILS_unit_depth_rounded(float depth_m)
{
	return (uint16_t)(UTILS_unit_depth(depth_m) + (0.5));
}

float UTILS_unit_temperature(float C)
{
    return _is_metric ? C : ((C * 1.8f) + 32);
}

// boundary check function
uint8_t UTILS_boundary_check(int16_t val, int16_t min, int16_t max) {

	if((val >= min) && (val <= max)) {
		return TRUE;
	}

	return FALSE;
}

int UTILS_replace_char(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}

void UTILS_set_bit_U32(uint32_t *bitarray, uint32_t bit_position) {
	*bitarray = *bitarray | (bit_position);
}

void UTILS_clear_bit_U32(uint32_t *bitarray, uint32_t bit_position) {
	*bitarray = *bitarray & (~bit_position);
}

void UTILS_set_bit_U16(uint16_t *bitarray, uint16_t bit_position) {
	*bitarray = *bitarray | (bit_position);
}

void UTILS_clear_bit_U16(uint16_t *bitarray, uint16_t bit_position) {
	*bitarray = *bitarray & (~bit_position);
}

uint8_t UTILS_get_bit(uint32_t bitarray, uint32_t bit_position) {
    return (bitarray & bit_position) ? 1 : 0;
}

