/*
 * rtc_utils.h
 *
 *  Created on: 20.12.2018
 *      Author: ARNES
 */

#ifndef RTC_CONVERSIONS_H_
#define RTC_CONVERSIONS_H_

#include <stdint.h>
#include "hardware_defines.h"

typedef struct
{
    uint8_t s; 		// 0 - 59
    uint8_t min; 	// 0 - 59
    uint8_t h; 		// 0 - 23
    uint8_t d; 		// 1 - 31
    uint8_t m; 		// 1 - 12
    uint8_t y; 		// 0 - 99
    uint8_t offset; // 0 - 24
} time_and_date_t;

#if(PLATFORM == PLATFORM_STM32)

#include "stm32l4xx_hal.h"

#define DAYS_JAN (31)
#define DAYS_FEB (28)
#define DAYS_MAR (31)
#define DAYS_APR (30)

#define DAYS_MAY (31)
#define DAYS_JUN (30)
#define DAYS_JUL (31)
#define DAYS_AUG (31)

#define DAYS_SEP (30)
#define DAYS_OCT (31)
#define DAYS_NOV (30)
#define DAYS_DEC (31)

void RTC_CalendarShow(uint8_t* showtime, uint16_t showtime_size, uint8_t* showdate, uint16_t showdate_size);
void RTC_CalendarShow2(void);

void RTC_init(void);
void RTC_systick_handler(void);
void RTC_get_utc0_time(RTC_TimeTypeDef* t);
void RTC_get_utc0_date(RTC_DateTypeDef* t);

void RTC_set_utc0_time(RTC_TimeTypeDef* sTime, RTC_DateTypeDef* sDate);

uint32_t RTC_get_diff_in_seconds(RTC_TimeTypeDef* t1, RTC_DateTypeDef* d1,
                                 RTC_TimeTypeDef* t2, RTC_DateTypeDef* d2);
uint32_t RTC_get_2021_utc0_timestamp(void);
uint32_t RTC_get_2021_utc0_timestamp_from_datetime(RTC_TimeTypeDef* time, RTC_DateTypeDef* date);

void RTC_convert_2021_utc0_timestamp_to_local_time_date(uint32_t timestamp, RTC_TimeTypeDef* time,
                                                   RTC_DateTypeDef* date);
#else
void RTC_set_2021_utc0_timestamp(uint32_t f_rtc);
uint32_t RTC_get_2021_utc0_timestamp(void);
#endif
uint8_t RTC_is_leap_year(uint32_t y);
void RTC_set_time(time_and_date_t* p, int8_t utc);
void RTC_timestamp_as_strings(uint32_t rtc_utc0_timestamp, char* time, uint8_t time_size, char* date, uint8_t date_size);

#endif /* RTC_UTILS_H_ */
