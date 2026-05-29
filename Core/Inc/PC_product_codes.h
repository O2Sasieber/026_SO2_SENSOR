/*! \file ******************************************************************
 *
 * \brief Oxygen Scientific product codes.
 *
 *  Author: Benjamin Kuch
 *  Date: 11.07.2023
 *
 *  Copyright (c) 2023 Oxygen scientific GmbH. All rights reserved.
 *
 ***************************************************************************/

#ifndef CORE_PC_PRODUCT_CODES_H_
#define CORE_PC_PRODUCT_CODES_H_

#include <stdint.h>


// product codes
#define RNO_HUD 					(1)				/* 001 HUD dive computer*/
#define RNO_TANK_POD 				(2)				/* 002 TANK-POD */
#define RNO_REB						(3)				/* 003 Rebreather */
#define O2S_GREENFLASH				(4)				/* 004 GREENFLASH SENSOR */
#define RNO_DATALOGGER 				(5)				/* 005 DATALOGGER */
#define RNO_NAV 					(6)				/* 006 GPS-NAV */
#define RNO_ONE						(7)				/* 007 Handset dive computer */
#define RNO_COMP					(9)				/* 009 External compass */
#define RNO_CCR_POD					(11)			/* 011 CCR-POD */
#define RNO_CCR_PPORT				(12)			/* 012 CCR-PPORT */
#define RNO_CCR_CONTROLLER			(13)			/* 013 CCR-CONTROLLER SUBMATIX */
#define CCR_CONTROLLER_SCUBATRON	(16)			/* 016 CCR_CONTROLLER SUBATRON */
#define TRIMIX_ANALYZER				(17)			/* 017 Trimix analyzer */


// device subIDs rebreather
#define RNO_REB_SENTINEL 			(0) 			/* STM32L452 - HOST */
#define RNO_REB_PO2_CONTROLLER 		(1) 			/* STM32L431 - SLAVE */
#define RNO_REB_HANDSET_DISPLAY		(2) 			/* STM32L431 - SLAVE */
#define RNO_REB_HUD_DISPLAY			(3) 			/* STM32L431 - SLAVE */
#define RNO_REB_LED_DISPLAY			(4) 			/* STM32L431 - SLAVE */


// device subID bit positions dive computer
#define SUBID_BIT0_LOCKED 			(1 << 0)		/* device locked/unlocked */
#define SUBID_BIT1_MILITARY 		(1 << 1)		/* device military/civil */


// flash addresses
#define LOGISTIC_DATA_ADDRESS		(0x080077F8)	/* (FLASH_BASE + VECT_TAB_OFFSET - 0x08) */
#define SERIAL_NUMBER_ADDRESS	   	(0x080077FC)	/* (FLASH_BASE + VECT_TAB_OFFSET - 0x04) */


uint32_t PC_get_serial_number(void);
uint8_t PC_get_HW_id(void);
uint8_t PC_get_device_id(void);
uint8_t PC_get_I2C_address(void);
uint8_t PC_get_device_subid(void);

#endif /* CORE_PC_PRODUCT_CODES_H_ */
