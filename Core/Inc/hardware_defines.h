/*
 * hardware_defines.h
 *
 *  Created on: 21.05.2026
 *      Author: benja
 */

#ifndef LFRT_LIBRARY_INC_HARDWARE_DEFINES_H_
#define LFRT_LIBRARY_INC_HARDWARE_DEFINES_H_

#define L0 												(0)
#define L4 												(4)

#define PROJECT_CORE            						(L4)

#define LFR_TRANSMITTER_VERSION 						(2)										/* LFT driver version */
#define TIMER_PERIOD_125kHz                     		(128)									/* LFT 125 kHz timer period (16MHz / 125kHz) */
#define NR_OF_PERIODS                           		(7)										/* LFT number of periods */
#define TIMER2_WINDOW                           		(5)										/* LFT timer2 window */
#define TIMER15_DELAY                           		(TIMER_PERIOD_125kHz-TIMER2_WINDOW)		/* LFT timer15 delay */

#define WATER_CONTACT_USED 								(1)

#define WATER_CONTACT_WAIT_DISCHARGE_MS                 (2)

#define NUM_PO2_SENSORS_ANALOG 							(3)
#define NUM_PO2_SENSORS_TOTAL 							(3)
#define NUM_TEMPSTICK_TEMP_SENSORS 						(5)


#endif /* LFRT_LIBRARY_INC_HARDWARE_DEFINES_H_ */
