#ifndef __MAX30112_H
#define __MAX30112_H

#include "stm32l4xx_hal.h"

#define bool uint8_t

#define REG_INTR_STATUS_1 0x00
#define REG_INTR_STATUS_2 0x01
#define REG_INTR_ENABLE_1 0x02
#define REG_INTR_ENABLE_2 0x03
#define REG_FIFO_WR_PTR 0x04
#define REG_OVF_COUNTER 0x05
#define REG_FIFO_RD_PTR 0x06
#define REG_FIFO_DATA 0x07
#define REG_FIFO_CONFIG 0x08
#define REG_FIFO_DATA_CONTROL1	0x09
#define REG_FIFO_DATA_CONTROL2	0x0A
#define REG_FIFO_SYSTEM_CONTROL	0x0D
#define REG_PPG_CONFIG1			0x0E
#define REG_PPG_CONFIG2			0x0F
#define REG_PROX_INT_THRESHOLD	0x10
#define REG_LED1_PA 0x11
#define REG_LED2_PA 0x12
#define REG_LED_RANGE	0x14
#define REG_PILOT_PA	0x15
#define REG_PART_ID		0xFF

#define A_FULL		1<<7
#define PPG_RDY		1<<6
#define ALC_OVF		1<<5
#define PROX_INT	1<<4
#define LED_COMPB	1<<3
#define PWR_RDY		1

#define VDD_OOR		1<<7

#define FIFO_STAT_CLR	1<<6
#define A_FULL_TYPE		1<<5
#define FIFO_RO			1<<4

#define LED1			1
#define LED2			2
#define PILOT_LED1		5
#define DIRECT_AMBIENT	0xC
#define LED1_LED2		0x0D




#define FCLK_CTRL	1<<4
#define LP_MODE		1<<3
#define FIFO_EN 	1<<2
#define SHDN		1<<1
#define RESET		1



#define PPG_ADC_RGE_POS	6
#define PPG_SR_POS		2
#define PPG_TINT_POS	0

#define FD1_POS			0
#define FD2_POS			4
#define FD3_POS			0
#define FD4_POS			4

#define FS6UA			0<<6
#define FS12UA			1<<6
#define FS24UA			2<<6
#define FS48UA			3<<6

#define SPS20			0<<2
#define SPS25			1<<2
#define SPS50			2<<2
#define SPS84			3<<2
#define SPS100			4<<2
#define SPS200			5<<2
#define SPS400			6<<2
#define SPS800			7<<2
#define SPS1000			8<<2
#define SPS1600			9<<2
#define SPS3200			A<<2
#define SPS20DP			B<<2
#define SPS25DP			C<<2
#define SPS50DP			D<<2
#define SPS84DP			E<<2
#define SPS100DP		F<<2

#define PPG_TINT50US	0
#define PPG_TINT100US	1
#define PPG_TINT200US	2
#define PPG_TINT400US	3

#define LED_SETTLING2US5	0<<3
#define LED_SETTLING5US		1<<3
#define LED_SETTLING10US	2<<3
#define LED_SETTLING20US	3<<3

#define AV1S		0
#define AV2S		0x01
#define AV4S		0x02
#define AV8S		0x03
#define AV16S		0x04
#define AV32S		0x05

#define LED1_RGE50MA 	0
#define LED1_RGE100MA 	1
#define LED1_RGE150MA 	2
#define LED1_RGE200MA 	3

#define LED2_RGE50MA 	0<<2
#define LED2_RGE100MA 	1<<2
#define LED2_RGE150MA 	2<<2
#define LED2_RGE200MA 	3<<2

#define MAX30112_ADDR				0xC0


#define NR_OF_MAX30102	1




bool max30112_init(I2C_HandleTypeDef * hi2cx);
bool max30112_write_reg(uint8_t uch_addr, uint8_t uch_data);
bool max30112_read_reg(uint8_t uch_addr, uint8_t *puch_data);

void max30112_read_data_dma1(void);
void max30112_read_data_dma2(uint32_t *pun_red_led, uint32_t *pun_ir_led);
uint32_t get_max30112_red(void);
uint32_t get_max30112_ir(void);

uint8_t adjust_LED_brightness(uint8_t i);
uint8_t get_current(uint8_t i);

uint8_t get_MAX30112_DMA_started(void);


#endif
