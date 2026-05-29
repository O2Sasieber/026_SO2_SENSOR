/*
 * WC_water_contact.h
 *
 *  Created on: 24.04.2023
 *      Author: benja
 */

#ifndef HARDWARE_WC_WATER_CONTACT_H_
#define HARDWARE_WC_WATER_CONTACT_H_

#include "hardware_defines.h"
#include <stdint.h>

#if(WATER_CONTACT_USED == 1)
void WC_reset_is_charged_flag(void);
uint8_t WC_get_charged_flag(void);
void WC_charge_water_contact_cap(void);
void WC_discharge_water_contact_cap(void);
uint8_t WC_is_dry(void);
uint16_t WC_get_dicharge_time(void);
void WC_check_discharge_pin(void);
#endif

#endif /* HARDWARE_WC_WATER_CONTACT_H_ */
