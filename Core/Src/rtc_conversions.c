/*
 * rtc_convertions.c
 *
 * @brief RTC time/date conversion and handling for STM32 platform.
 *
 *  Created on: 20.12.2018
 *      Author: Arne Sieber
 */
#include "rtc_conversions.h"
#include "hardware_defines.h"

#if(PLATFORM == PLATFORM_STM32)
#include "string.h"
#include "stdio.h"

extern RTC_HandleTypeDef hrtc;

static int32_t _utc = 0;

#define DAYS_UNTIL_2021 (738155L)

/**
 * @brief Number of days in each month (except February).
 */
uint8_t days_in_month[12]  =
{
    31, 0, 31, 30,  31, 30, 31, 31,  30, 31, 30, 31
};


#if(1 == 0)
/**
 * @brief Test function to validate RTC conversion logic.
 */
void _test_conversion()
{
    SET_set_utc(0);
    RTC_TimeTypeDef soll_time;
    RTC_DateTypeDef soll_date;

    soll_time.Hours = 14;
    soll_time.Minutes = 10;
    soll_time.Seconds = 30;

    soll_date.Year = 61;
    soll_date.Month = 11;
    soll_date.Date = 15;

    RTC_TimeTypeDef calc_time;
    RTC_DateTypeDef calc_date;

    uint32_t timestamp = RTC_get_2021_utc0_timestamp_from_datetime(&soll_time, &soll_date);

    printf("timestamp = %u\n", timestamp);

    RTC_convert_2021_utc0_timestamp_to_local_time_date(timestamp, &calc_time, &calc_date);
}
#endif


/**
 * @brief Converts a given RTC date/time to a timestamp relative to 1.1.2021 00:00:00 UTC.
 * @param time Pointer to RTC time structure.
 * @param date Pointer to RTC date structure.
 * @return Timestamp (seconds since 1.1.2021 00:00:00 UTC).
 */
uint32_t _convert_time_date_to_2021_utc0_timestamp(RTC_TimeTypeDef* time, RTC_DateTypeDef* date)
{
    uint32_t y;
    uint32_t m;
    uint32_t d;
    uint64_t t;

    //Year
    // y = date->Year;
    y = (2000 + date->Year); // first convert to unix time, starting 1970

    //Month of year
    m = date->Month;
    //Day of month
    d = date->Date;

    //January and February are counted as months 13 and 14 of the previous year
    if (m <= 2)
    {
        m += 12;
        y -= 1;
    }

    //Convert years to days
    t = (365 * y) + (y / 4) - (y / 100) + (y / 400);
    //Convert months to days
    t += (30 * m) + (3 * (m + 1) / 5) + d;
    //Unix time starts on January 1st, 1970
    t -= 719561;
    //Convert days to seconds
    t *= 86400;
    //Add hours, minutes and seconds
    t += (3600 * time->Hours) + (60 * time->Minutes) + time->Seconds;

    return t - 1609459200L; // convert to 2021
}


/**
 * @brief Gets the current timestamp relative to 1.1.2021 00:00:00 UTC from RTC.
 * @return Current timestamp.
 */
uint32_t RTC_get_2021_utc0_timestamp()
{
    RTC_TimeTypeDef t;
    RTC_DateTypeDef d;

    HAL_RTC_GetTime(&hrtc, &t, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &d, RTC_FORMAT_BIN);

    return _convert_time_date_to_2021_utc0_timestamp(&t, &d);
}


/**
 * @brief Converts a specific date/time to a timestamp relative to 1.1.2021 00:00:00 UTC.
 * @param time Pointer to RTC time structure.
 * @param date Pointer to RTC date structure.
 * @return Corresponding timestamp.
 */
uint32_t RTC_get_2021_utc0_timestamp_from_datetime(RTC_TimeTypeDef* time, RTC_DateTypeDef* date)
{
    return _convert_time_date_to_2021_utc0_timestamp(time, date);
}


/**
 * @brief Displays the current time and date into string buffers.
 * @param showtime Pointer to time string buffer.
 * @param showtime_size Size of time buffer.
 * @param showdate Pointer to date string buffer.
 * @param showdate_size Size of date buffer.
 */
void RTC_CalendarShow(uint8_t* showtime, uint16_t showtime_size, uint8_t* showdate, uint16_t showdate_size)
{
    RTC_DateTypeDef sdatestructureget;
    RTC_TimeTypeDef stimestructureget;

    /* Get the RTC current Time */
    HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
    /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
    /* Display time Format : hh:mm:ss */
    snprintf((char*) showtime, showtime_size, "%02d:%02d:%02d", stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
    /* Display date Format : mm-dd-yy */
    snprintf((char*) showdate, showdate_size, "%02d-%02d-%d", sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);
}


/**
 * @brief Retrieves the current UTC time from RTC.
 * @param t Pointer to RTC time structure.
 */
void RTC_get_utc0_time(RTC_TimeTypeDef* t)
{
    HAL_RTC_GetTime(&hrtc, t, RTC_FORMAT_BIN);
}


/**
 * @brief Retrieves the current UTC date from RTC.
 * @param t Pointer to RTC date structure.
 */
void RTC_get_utc0_date(RTC_DateTypeDef* t)
{
    HAL_RTC_GetDate(&hrtc, t, RTC_FORMAT_BIN);
}


/**
 * @brief Retrieves the current local date from RTC.
 * @param t Pointer to RTC date structure.
 */
void RTC_get_local_date(RTC_DateTypeDef* t)
{
    HAL_RTC_GetDate(&hrtc, t, RTC_FORMAT_BIN);
}


/**
 * @brief Helper to fetch and discard time/date (used for initialization).
 */
void RTC_CalendarShow2(void)
{
    RTC_DateTypeDef sdatestructureget;
    RTC_TimeTypeDef stimestructureget;
    HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
}


/**
 * @brief Initializes the RTC module.
 */
void RTC_init(void)
{
    RTC_CalendarShow2();
}


/**
 * @brief Sets the RTC time and date using UTC0 reference.
 * @param sTime Pointer to RTC time structure.
 * @param sDate Pointer to RTC date structure.
 */
void RTC_set_utc0_time(RTC_TimeTypeDef* sTime, RTC_DateTypeDef* sDate)
{
    sTime->DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime->StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
        return;
    }

    if (HAL_RTC_SetDate(&hrtc, sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
       	return;
    }

#if(HUDC == 1) || (DC23 == 1)
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, RTC_MAGIC_HUDC);
#endif
}


/**
 * @brief Converts a timestamp (since 1.1.2021 UTC0) to local time and date.
 * @param timestamp Timestamp in seconds since 1.1.2021 00:00:00 UTC.
 * @param time Pointer to RTC time structure to fill.
 * @param date Pointer to RTC date structure to fill.
 */
void RTC_convert_2021_utc0_timestamp_to_local_time_date(uint32_t timestamp, RTC_TimeTypeDef* time,
                                                   RTC_DateTypeDef* date)
{
#if(PLATFORM == PLATFORM_STM32)

    // Time passed since 1.1.2021 00:00:00
    // Year == 0 is 2000
    int32_t offs = _utc * 3600;
    uint32_t ts = timestamp + offs;

    time->Seconds = ts % 60;
    ts = ts / 60; // now minutes
    time->Minutes = ts % 60;
    ts = ts / 60; // now hours
    time->Hours = ts % 24;
    ts = ts / 24; // now has days

    ts = ts + DAYS_UNTIL_2021 + 2;

    uint32_t abs_year = ((ts * 400 ) - 300 + 4 - 1 ) / 146097;

    ts = ts - ( (uint32_t) abs_year * 365 +
            ( abs_year + 3 ) / 4 - ( abs_year - 1 ) / 100 + ( abs_year - 1 ) / 400 );

    date->Year = abs_year - 2000;

    if(RTC_is_leap_year(2000 + date->Year))
    {
        days_in_month[1] = 29;
    }
    else
    {
        days_in_month[1] = 28;
    }

    date->Month = 1;
    while (days_in_month[date->Month - 1 ] < ts )
    {
        ts = ts - days_in_month[date->Month - 1 ];
        date->Month++;
    }
    date->Date = ts;
#endif
}

#else

uint32_t fake_rtc = 0;

/**
 * @brief Fake RTC timestamp used for non-STM32 platforms (simulated).
 */
void RTC_set_2021_utc0_timestamp(uint32_t f_rtc)
{
	fake_rtc = f_rtc;
}


/**
 * @brief Sets a simulated timestamp for RTC.
 * @param f_rtc Fake timestamp value to set.
 */
uint32_t RTC_get_2021_utc0_timestamp(void)
{
    return fake_rtc;
}
#endif


/**
 * @brief Sets RTC using a local time structure, accounting for UTC offset.
 * @param p Pointer to structure holding time and date.
 * @param utc UTC offset in hours.
 */
void RTC_set_time(time_and_date_t* p, int8_t utc)
{
    // p is local time

#if(PLATFORM == PLATFORM_STM32)
    RTC_TimeTypeDef sTime = { 0 };
    RTC_DateTypeDef sDate = { 0 };

    _utc = utc;

    sTime.Hours = p->h;
    sTime.Minutes = p->min;
    sTime.Seconds = p->s;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    sDate.Month = p->m;
    sDate.Date = p->d;
    sDate.Year = p->y;

    uint32_t ts = _convert_time_date_to_2021_utc0_timestamp(&sTime, &sDate); // Local time as 2021 UTC0 timestamp

    uint32_t toffs =  2*(_utc * 3600); // Local 2021 time with UTC

    ts = ts - toffs; // Remove utc offset, twice, because the local function adds UTC
    // UTC removed twice, will be added once, so now we have UTC0
    RTC_convert_2021_utc0_timestamp_to_local_time_date(ts, &sTime, &sDate);

    RTC_set_utc0_time(&sTime, &sDate);
#endif
}


/**
 * @brief Checks if a year is a leap year.
 * @param y Full year (e.g., 2024).
 * @return 1 if leap year, 0 otherwise.
 */
uint8_t RTC_is_leap_year(uint32_t y)
{
    return (y % 400 == 0 || ( y % 4 == 0 && y % 100 != 0 ));
}


/**
 * @brief Converts a UTC0 timestamp to human-readable strings for time and date.
 * @param rtc_utc0_timestamp Timestamp since 1.1.2021 00:00:00 UTC.
 * @param time Output time string buffer.
 * @param time_size Size of time buffer.
 * @param date Output date string buffer.
 * @param date_size Size of date buffer.
 */
void RTC_timestamp_as_strings(uint32_t rtc_utc0_timestamp, char* time, uint8_t time_size, char* date, uint8_t date_size) {

#if(PLATFORM == PLATFORM_STM32)
    RTC_TimeTypeDef t;
    RTC_DateTypeDef d;

    RTC_convert_2021_utc0_timestamp_to_local_time_date(rtc_utc0_timestamp, &t, &d);

    snprintf(time, time_size, "%02u:%02u:%02u", t.Hours, t.Minutes, t.Seconds);
    snprintf(date, date_size, "%04u-%02u-%02u", d.Year + 2000, d.Month, d.Date);
#else
    snprintf(time, time_size, "20:47:03");
    snprintf(date, date_size, "2023-06-25");
#endif
}
