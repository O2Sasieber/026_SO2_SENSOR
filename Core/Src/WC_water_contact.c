/*
 * WC_water_contact.c
 *
 *  Created on: 24.04.2023
 *      Author: benja
 */

#include "WC_water_contact.h"
#include "main.h"
#include "UTILS_utils.h"


#if(WATER_CONTACT_USED == 1)


static volatile uint8_t _is_charged_water_contact = 0;
static uint16_t dicharge_time = 0;

void WC_reset_is_charged_flag(void) {
	_is_charged_water_contact = 0;
}

uint8_t WC_get_charged_flag(void) {
	return _is_charged_water_contact;
}

void WC_charge_water_contact_cap(void)
{
    if(_is_charged_water_contact)
    {
        return;
    }
#if(PLATFORM == PLATFORM_STM32)
    _is_charged_water_contact = 1;

    GPIO_InitTypeDef GPIO_InitStruct =  { 0 };
    HAL_GPIO_DeInit(WATER_CONTACT_GPIO_Port, WATER_CONTACT_Pin);
    GPIO_InitStruct.Pin = WATER_CONTACT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(WATER_CONTACT_GPIO_Port, &GPIO_InitStruct);

    // 2ms to charge
    uint32_t tout = 200;
    while(tout)
    {
        UTILS_delay_us(10);
        tout--;
    }
#endif
}



void WC_discharge_water_contact_cap(void) {

#if(PLATFORM == PLATFORM_STM32)
    GPIO_InitTypeDef GPIO_InitStruct =  { 0 };
    HAL_GPIO_DeInit(WATER_CONTACT_GPIO_Port, WATER_CONTACT_Pin);
    GPIO_InitStruct.Pin = WATER_CONTACT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(WATER_CONTACT_GPIO_Port, &GPIO_InitStruct);

    // Discharge time in uS
   // 100 kOhm - 99
   // 400 kOhm - 154
   // 800 kOhm - 275
   // 1 MOhm   - 400
   // 4 MOhm   - 3800
   // 10 MOhm - 10400 <-- soldered in parallel
   uint32_t tout = WATER_CONTACT_WAIT_DISCHARGE_MS * 100; // *10
   dicharge_time=0;

   while(HAL_GPIO_ReadPin(WATER_CONTACT_GPIO_Port, WATER_CONTACT_Pin) && tout)
   {
	   dicharge_time+=10;
	   UTILS_delay_us(10);
       tout--;
   }
#endif
}


uint8_t WC_is_dry(void) {
	return (dicharge_time == WATER_CONTACT_WAIT_DISCHARGE_MS * 1000) ? 1 : 0;
}


/*
 *
 * TODO: change to this
uint16_t _discharge_water_contact_cap()
{
    GPIO_InitTypeDef GPIO_InitStruct =  { 0 };
    HAL_GPIO_DeInit(USB_DETECT_EXTI8_GPIO_Port, USB_DETECT_EXTI8_Pin);
    GPIO_InitStruct.Pin = USB_DETECT_EXTI8_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USB_DETECT_EXTI8_GPIO_Port, &GPIO_InitStruct);

    // Discharge time in uS
   // 100 kOhm - 99
   // 400 kOhm - 154
   // 800 kOhm - 275
   // 1 MOhm   - 400
   // 4 MOhm   - 3800
   // 10 MOhm - 10400 <-- soldered in parallel
   uint32_t tout = WATER_CONTACT_WAIT_DISCHARGE_MS * 100;
	while(tout)
	{
		UTILS_delay_us(10);
		tout--;
		if (HW_get_USB_detect()==0) return (WATER_CONTACT_WAIT_DISCHARGE_MS * 100-tout)*10; // [us];
	}
	return 0xFFFF;  // timeout
	}
*/

uint16_t WC_get_dicharge_time(void) {
	return dicharge_time;
}


void WC_check_discharge_pin(void) {

//#if(PLATFORM == PLATFORM_STM32)
//    if(_is_charged_water_contact) {
//        uint32_t tout = 15;
//        while(tout && HW_get_USB_detect())
//        {
//            tout--;
//            HAL_Delay(1);
//        }
//
//        _is_charged_water_contact = 0;
//    }
//#endif
}

#endif
