/*
 * UTILS_utils.c
 *
 * UTILS stands for Utilities
 *
 *  Created on: Aug 3, 2021
 *      Author: Peter Casapicola
 */

#ifndef INC_UTILS_UTILS_H_
#define INC_UTILS_UTILS_H_

#include <stdint.h>
#include <stdbool.h>


#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef METER_TO_FEET
#define METER_TO_FEET (3.28084f)
#endif

#ifndef FEET_TO_METER
#define FEET_TO_METER (0.3048f)
#endif


#define struct_member_size(type, member) sizeof(((type *)0)->member)

float UTILS_map_f(float x, float in_min, float in_max, float out_min, float out_max);
uint32_t UTILS_map_u32(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
int32_t UTILS_map_i32(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);
float UTILS_rng_f32(uint32_t n);
uint8_t UTILS_bfr_compare(uint8_t *bfr1, uint8_t *bfr2, uint8_t bfr_size);
int16_t UTILS_get_random_duration(uint16_t duration);
uint32_t UTILS_get_minmax(uint32_t a[], uint8_t a_len, bool min);
uint32_t UTILS_get_mean(uint32_t a[], uint8_t a_len);
void UTILS_delay_with_sleep(uint32_t ms);

//char* UTILS_get_multipurpose_buffer_512(void);
//void UTILS_release_multipurpose_buffer_512(void);
void UTILS_delay_us(uint32_t us);

uint32_t UTILS_get_decimals(float a, uint8_t dec);
//void UTILS_number_to_mmmss(uint32_t val, char* str);
float UTILS_unit_pressure(float bar);
float UTILS_unit_ascent_speed(float m_per_min);
float UTILS_unit_depth(float m);
float UTILS_unit_depth_to_meter(float depth);
uint16_t UTILS_unit_depth_deco(uint16_t m);
uint16_t UTILS_unit_depth_rounded(float depth_m);
float UTILS_unit_temperature(float C);
uint8_t UTILS_boundary_check(int16_t val, int16_t min, int16_t max);
int UTILS_replace_char(char *str, char orig, char rep);
void UTILS_set_bit_U16(uint16_t *bitarray, uint16_t bit_position);
void UTILS_clear_bit_U16(uint16_t *bitarray, uint16_t bit_position);
void UTILS_set_bit_U32(uint32_t *bitarray, uint32_t bit_position);
void UTILS_clear_bit_U32(uint32_t *bitarray, uint32_t bit_position);
uint8_t UTILS_get_bit(uint32_t bitarray, uint32_t bit_position);

#endif /* INC_UTILS_UTILS_H_ */
