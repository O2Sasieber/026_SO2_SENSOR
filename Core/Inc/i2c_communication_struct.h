/*
 * i2c_communication_struct.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Arne Sieber
 *
 * Copyright (c) 2023 Oxygen scientific GmbH. All rights reserved.
 */

#ifndef SRC_I2C_COMMUNICATION_STRUCT_H_
#define SRC_I2C_COMMUNICATION_STRUCT_H_


#include "hardware_defines.h"
#include "main.h"
#include "PC_product_codes.h"


#define I2C_TIMING_SAFETY_FACTOR									(3)														/* safety factor increasing the I2C_COMM_TIMEOUT */
#define SIZE_OF_DATA_BUFFER											(128)													/* I2C data buffer size */

#define F_I2C														(100000)												/* I2C bus speed in [Hz] */
#define I2C_COMM_TIMEOUT(n) 										((n*10000000L*I2C_TIMING_SAFETY_FACTOR/(F_I2C*1000))+1)	/* I2C communication timeout during normal operation in [ms] */
#define I2C_COMM_TIMEOUT_MSS										(250)													/* I2C communication timeout in MSS in [ms] */

#define I2C_RNO_REB_HANDSET_DISPLAY_ADDR 							(RNO_REB_HANDSET_DISPLAY << 1)							/* Handset display I2C address */
#define	I2C_RNO_REB_HUD_DISPLAY_ADDR								(RNO_REB_HUD_DISPLAY << 1)								/* HUD display I2C address */
#define I2C_RNO_REB_LED_DISPLAY_ADDR								(RNO_REB_LED_DISPLAY << 1)								/* LED display I2C address (obsolete) */
#define I2C_RNO_REB_CONTROLLER_ADDR									(RNO_REB_PO2_CONTROLLER << 1)							/* controller I2C address */

#define I2C_NEREO_O2_CO2_MODULE_ADDR								(5 << 1)												/* NEREO O2 CO2 sensor module address */
#define I2C_NEREO_FLOW_METER_MODULE_ADDR							(7 << 1)												/* NEREO FLOW METER module address */

#define RRCI_SOLENOID_OPEN_CAL 										(0xFF)													/* controller interface: define to trigger max. solenoid open time */
#define RRCI_AUTOMATIC_SETPOINT 									(0xFE)													/* controller interface: define to set automatic setpoint adjustment */
#define RRCI_SAFETY_SETPOINT										(0.7f)													/* controller interface: define to set safety setpoint in [bar] */

#define TEXT_NR_OF_CHAR												(20)													/* size of text buffer */


#define CCR_STATUS_CC_STATE 			(1 << 0) 																			/* bit position for OC / BO state in ccsm_t.cc_data.status bytes */
#define CCR_STATUS_HW_ASSEMBLED			(1 << 1)																			/* bit position for device assembled state in ccsm_t.cc_data.status bytes */
#define CCR_STATUS_USB_CHARGING			(1 << 2)																			/* bit position for USB charging state in ccsm_t.cc_data.status bytes */
#define CCR_STATUS_USB_DETECTION		(1 << 3)																			/* bit position for USB detected state in ccsm_t.cc_data.status bytes */
#define CCR_STATUS_FREE1 				(1 << 5)
#define CCR_STATUS_FREE2 				(1 << 6)
#define CCR_STATUS_FREE3		 		(1 << 7)


typedef enum
{
    BUTTON_PRESS_NONE = 0,
    BUTTON_PRESS_DURATION_SHORT = 1,
    BUTTON_PRESS_DURATION_LONG = 2,
    BUTTON_PRESS_DOUBLE = 3,
	BUTTON_PRESS_DURATION_ULTRA_LONG = 4,
} BUTTON_PRESS_DURATION;


//typedef enum
//{
//	CCR_STATUS_NORMAL = 0,
//    CCR_STATUS_CALIBRATION_PASSED,
//	CCR_STATUS_CALIBRATION_FAILED,
//} CCR_STATUS;


// controller system states
typedef enum {
	SM_CONTROLLER_INIT = 0,
	SM_CONTROLLER_PO2_CONTROL,
	SM_CONTROLLER_READY_TO_SLEEP,
	SM_CONTROLLER_SLEEP
} CONTROLLER_STATE;


typedef enum {
	CONTROLLER_STATUS_NORMAL_OPERATION = 0,
	CONTROLLER_STATUS_CALIBRATING = 1,
	CONTROLLER_STATUS_SAVING_CALIBRATION = 2
} CONTROLLER_STATUS;


// display system states
typedef enum {
	DISPLAY_BOOTING = 0,
	DISPLAY_RUNNING,
	DISPLAY_SLEEP
} DISPLAY_STATE;


/* sentinel data sent to the display */
typedef struct {

	uint8_t status; 											/* status */
	uint8_t state;												/* sentinel RTC wakeup counter */
	uint8_t remaining_battery_capacity;							/* sentinel remaining battery capacity in [%] */
	uint8_t RSC_perc; 											/* sentinel remaining scrubber capacity in [%] */

	char show_text[TEXT_NR_OF_CHAR];							/* sentinel text message to be shown on the display */

	uint16_t info_word;											/* sentinel info word containing system information */
	uint8_t reserved1;
	uint8_t reserved2;

	uint64_t error_bits;										/* sentinel error bits */

	uint32_t timestamp;											/* sentinel timestamp */
	uint32_t divetime_s;										/* sentinel divetime in [s] */

	float pO2_setpoint_bar;										/* sentinel pO2 setpoint in [bar] */
	float p_ambient_bar;										/* sentinel ambient pressure in [bar] */
	float p_surface_bar;										/* sentinel surface pressure in [bar] */
	float T_ambient_C;											/* sentinel ambient temperature in [°C] */
	float p_tank_O2_bar;										/* sentinel O2 tank pressure in [bar] */
	float p_tank_Dil_bar;										/* sentinel diluent tank pressure in [bar] */
	float pCO2_bar;												/* sentinel pCO2 in [bar]*/
	float battery_voltage_V;									/* sentinel batter voltage in [V] */
	float T_tempstick_C[NUM_TEMPSTICK_TEMP_SENSORS];		    /* sentinel tempstick temperaturs in [°C] */
	float O2_sensor_pO2_bar[NUM_PO2_SENSORS_TOTAL];				/* sentinel pO2 O2 sensors in [bar] */

	uint8_t display_command;									/* sentinel command to control the display */
	uint8_t reserved_3;
	uint8_t reserved_4;
	uint8_t crc;												/* CRC (currently not used) */

} display_rx_data_t;


/* display date processed by the sentinel */
typedef struct {
	uint8_t state;												/* display state (enum DISPLAY_STATE) */
	uint8_t button0_state;										/* display button0 state (enum BUTTON_PRESS_DURATION) */
	uint8_t button1_state;										/* display button1 state (enum BUTTON_PRESS_DURATION) */
	uint8_t display_brightness_level;							/* display brightness level (1-9) */

	uint64_t errorbits;											/* display errorbits */

	uint32_t seq_cnt;											/* sequence counter showing that the display is running */

	uint8_t FW_major;											/* major part of firmware version */
	uint8_t FW_minor;											/* minor part of firmware version */
	uint8_t FW_bugfix;											/* bugfix part of firmware version */
	uint8_t crc;												/* CRC (currently not used) */
} display_tx_data_t;


typedef struct  {
	uint8_t command;											/* I2C command */
	uint8_t status;												/* I2C communication status */
	uint8_t d1;													/* dummy value 1 */
	uint8_t d2;													/* dummy value 2 */
	uint32_t address;											/* destination flash block address */
	uint8_t data[SIZE_OF_DATA_BUFFER];							/* destination flash block content */
	uint8_t data_pec;											/* data PEC */

} I2C_slave_bootloader_struct;


/* information bits for display_rx_data_t resp. controller_rx_data_t struct -> info_word */
#define INFOBIT_GPIO_CC_OC					(0)					/* GPIO pin status CC or OC mode */
#define INFOBIT_GPIO_HW_ASSEMBLED			(1)					/* GPIO pin status device assembled */
#define INFOBIT_GPIO_USB_CONNECTED			(2)					/* GPIO pin status USB connected */
#define INFOBIT_GPIO_USB_CHARGING			(3)					/* GPIO pin status USB charging */
#define INFOBIT_CONFIG_O2_TANK_SENSOR		(4)					/* device has a O2 tank pressure sensor */
#define INFOBIT_CONFIG_DIL_TANK_SENSOR		(5)					/* device has a diluent tank pressure sensor */
#define INFOBIT_CONFIG_DEVICE_TYPE			(6)					/* device type: 0 = 3rd party controller board, 1 = Symbios CCR */
#define INFOBIT_SETPOINT_ID_LSB				(7)					/* setpoint id (2bits: 0 = AUTO, 1 = user setpoint high, 2 = user setpoint low, 3 = safety setpoint) */
#define INFOBIT_SETPOINT_ID_MSB				(8)
#define INFOBIT_SENTINEL_USER_INFO_1  		(9)					/* sentinel user information (4 bits **) */
#define INFOBIT_SENTINEL_USER_INFO_2  		(10)
#define INFOBIT_SENTINEL_USER_INFO_3  		(11)
#define INFOBIT_SENTINEL_USER_INFO_4  		(12)
#define INFOBIT_IS_SURFACE					(13)				/* is diving (1) or on surface (0) */
#define INFOBIT_CALIBRATION_SOLENOID_OPEN   (14)				/* solenoid open during calibration*/
#define INFOBIT_FREE2						(15)

/* ** sentinel user information (4 bits)
 * 0 = running
 * 1 = pO2 calibration,
 * 2 = pO2 calibration,
 * 3 = pO2 calibration,
 * 4 = pO2 calibration,
 * 5 = pO2 calibration,
 * 6 = pO2 calibration,
 * 7 = USB mode
 * */


/* sentinel data sent to the controller */
typedef struct {

	float preset_setpoint_bar;									/* sentinel setpoint in [bar] */
	float p_ambient_bar;										/* sentinel ambient pressure in [bar] */
	float p_surface_bar;										/* sentinel surface pressure in [bar] */
	float O2_tank_pressure_bar;									/* sentinel O2 tank pressure ion [bar] */
	float diluent_tank_pressure_bar;							/* sentinel diluent tank pressure ion [bar] */

	uint32_t timestamp;											/* sentinel timestamp */

	uint16_t info_word;											/* sentinel info word containing system information */
	uint16_t battery_mv;										/* sentinel battery voltage in [mV] */

	float pO2_analog_bar[NUM_PO2_SENSORS_ANALOG];				/* sentinel analog pO2  in [bar] */
	float pO2_greenflash_bar;									/* sentinel greenflash pO2 in [bar] */

	float pCO2_bar;												/* pCO2 in [bar] */

	uint64_t sentinel_errorbits;								/* sentinel errorbit */

	uint8_t battery_charge_status_perc;							/* sentinel battery state of charge in [%] */
	uint8_t FO2_calibration_perc_sentinel;						/* sentinel FO2 calibration gas in [%] */
	uint8_t pO2_calibration_linearity_check_failed;				/* sentinel pO2 calibration linearity check result (1 = failed, 0 = OK) */
	uint8_t pCO2_calibration_result;							/* pCO2 calibration result: 0 = FAILED, 1 = PASSED */

	uint16_t wireless_id;										/* wireless id */
	uint8_t reserved2;
	uint8_t new_data_available;									/* new data available flag - has to be the last data byte - */

	uint8_t controller_command;									/* I2C command sent from sentinel to controller */
	uint8_t reserved3;
	uint8_t reserved4;
	uint8_t crc;												/* CRC (currently not used) */

} controller_rx_data_t;


/* controller data processed by the sentinel */
typedef struct {

	uint8_t status;												/* controller status (enum CONTROLLER_STATUS) */
	uint8_t state;												/* controller state (enum CONTROLLER_STATE) */
	uint16_t solenoid_open_ms;									/* solenoid opening time in [ms] */

	float solenoid_valve_opening_time_ms;						/* solenoid valve openingtime in [ms] */
	float pO2_greenflash_bar;									/* calibrated greenflash pO2 in [bar] */
	float pO2_greenflash_raw_bar;								/* raw greenflash pO2 in [bar] */
	float pO2_greenflash_dynamic_calibration_factor;			/* greenflash dynamic calibration factor */
	float pO2_analog_bar[NUM_PO2_SENSORS_ANALOG];				/* analog pO2 in [bar] */
	float pO2_analog_calibration_mV[NUM_PO2_SENSORS_ANALOG];	/* analog calibration value in [mV] */
	float pO2_analog_calibration_pressure_bar;					/* calibration pressure in [bar] */

	uint8_t FO2_calibration_perc;								/* FO2 calibration gas in [%] */
	uint8_t FW_major;
	uint8_t FW_minor;
	uint8_t FW_bugfix;

	float max_pO2_difference_bar;								/* max. pO2 difference in [bar] */

	uint32_t pO2_analog_calibration_timestamp;					/* pO2 calibration timestamp */

	uint64_t controller_errorbits;								/* controller errorbits */

	uint32_t seq_cnt;											/* sequence counter */

	uint8_t active_pO2_setpoint_001bar;							/* active pO2 setpoint in [0.01bar] */
	uint8_t pO2_calibration_successfull;						/* pO2 calibration successful flag */
	uint8_t reserved3;
	uint8_t crc;												/* CRC (currently not used) */

} controller_tx_data_t;



typedef struct {
	controller_rx_data_t sentinel_data;
	controller_tx_data_t controller_data;

} I2C_slave_comm_rno_reb_controller;




/* input data and configuration data */
typedef struct {

	uint8_t command;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;

	uint8_t reserved4;
	uint8_t reserved5;
	uint8_t reserved6;
	uint8_t crc;											/* CRC (currently not used) */

} nereo_CO2_o2_module_rx_data_t;


/* measuremnt data */
typedef struct {

	uint32_t seq_cnt;
	int32_t pO2_0_mV;
	int32_t pO2_1_mV;
	int32_t pO2_2_mV;

	int16_t dC0;
	int16_t dC1;

	int16_t t01deg;
	uint8_t reserved4;
	uint8_t crc;

}  nereo_CO2_o2_module_tx_data_t;


typedef struct {

	uint8_t command;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;

	uint8_t reserved4;
	uint8_t reserved5;
	uint8_t reserved6;
	uint8_t crc;											/* CRC (currently not used) */

} nereo_SpO2_meter_rx_data_t;


typedef struct {

	uint32_t seq_cnt;

	uint32_t led_red;

	uint32_t led_ir;

	uint8_t current_red;
	uint8_t current_ir;
	uint8_t reserved;
	uint8_t crc;


//	uint8_t heart_rate_bpm;									/* heart rate in [bpm] */
//	uint8_t R;												/* R value */
//	uint8_t SpO2_perc;										/* SpO2 in [%] */
//	uint8_t signal_quality;									/* Signal quality [0-7] */
//
//	uint8_t charging;										/* Charging indicator [TRUE or FALSE] */
//	uint8_t battery;										/* Battery state in charge [0-3] */
//	uint8_t reserved;
//	uint8_t crc;											/* CRC (currently not used) */

} nereo_SpO2_meter_tx_data_t;


/* input data and configuration data */
typedef struct {

	uint8_t command;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;

	uint8_t reserved4;
	uint8_t reserved5;
	uint8_t reserved6;
	uint8_t crc;												/* CRC (currently not used) */

} nereo_flow_meter_module_rx_data_t;


/* measuremnt data */
typedef struct {

	float tof_diff;

//	uint32_t seq_cnt;
//
//	float tof_diff[25];
//
//	uint8_t idx;
//	uint8_t reserved2;
//	uint8_t reserved3;
//	uint8_t crc;

}  nereo_flow_meter_module_tx_data_t;



#define I2C_OK									(0x00)
#define I2C_NOK									(0x01)
#define I2C_BUSY								(0x02)


/* I2C commands */
#define I2C_CMD_RESET							(0x96)			/* I2C command: reset device */
#define I2C_CMD_PREPARE_SLEEP					(0x68)			/* I2C command: prepare sleep */
#define I2C_CMD_SLEEP							(0x69)			/* I2C command: go to sleep */
#define I2C_CMD_JUMP_TO_APPLICATION				(0xC3)			/* I2C command: jump to application */
#define I2C_CMD_ERASE_FLASH						(0xA5)			/* I2C command: erase flash */
#define I2C_CMD_PROGRAM_FLASH					(0xE7)			/* I2C command: program flash */
#define I2C_CMD_SAVE_SETTINGS					(0x32)			/* I2C command: save settings */
#define I2C_CMD_O2_SENSOR_CALIBRATION_DIGITAL	(0x30)			/* I2C command: pO2 calibration with greenflash pO2 sensor */
#define I2C_CMD_O2_SENSOR_CALIBRATION_ANALOG	(0x34)			/* I2C command: pO2 calibration without greenflash pO2 sensor */
#define I2C_CMD_DISPLAY_UPATE 					(0x56)			/* I2C command: update display */
#define I2C_CMD_DISPLAY_CLEAR 					(0x57)			/* I2C command: clear display */
#define I2C_CMD_ENABLE_GREENFLASH_SENSOR		(0x38)			/* I2C command: enable greenflash sensor */



uint8_t i2c_get_bitstate(uint16_t bits, uint16_t bit_position);
void i2c_set_bit(volatile uint16_t *bits, uint16_t bit_position);
void i2c_clear_bit(volatile uint16_t *bits, uint16_t bit_position);
uint16_t i2c_bits_extracted(uint16_t value, uint16_t k, uint16_t bit_position);
void i2c_set_infobit(volatile uint16_t* info_word, volatile uint8_t state, uint16_t bit);


#endif /* SRC_I2C_COMMUNICATION_STRUCT_H_ */
