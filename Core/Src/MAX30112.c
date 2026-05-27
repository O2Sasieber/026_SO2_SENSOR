#include "MAX30112.h"
#include "algorithm.h"
#include "main.h"
#include "stdio.h"

#define MIN_ADC_READING		200000
#define MAX_ADC_READING		300000
#define DEFAULT_ADC_READING	(MIN_ADC_READING+MAX_ADC_READING)/2
#define MAX_LED_CURRENT		0xFF
#define MIN_LED_CURRENT		0x02


static uint8_t LED_current[2];

uint32_t red[BUFFER_SIZE];
uint32_t ir[BUFFER_SIZE];

int32_t n_sp02; //SPO2 value
int8_t ch_spo2_valid;   //indicator to show if the SP02 calculation is valid
int32_t n_heart_rate;   //heart rate value
int8_t  ch_hr_valid;    //indicator to show if the heart rate calculation is valid

uint8_t max30102_enable_read=1;

volatile uint8_t new_ECG_data=0;
volatile uint8_t new_SPO2_data=0;
volatile uint8_t new_PPG_data=0;
volatile uint8_t new_PT_data;
volatile uint8_t PPG_buffer_full=0;

volatile uint8_t DMA_started=0;

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	uint8_t nr=0;
	static uint32_t index=0;


	//max30102_read_data_dma2(nr, &red[nr][index[nr]],&ir[nr][index[nr]]);

	max30112_read_data_dma2(&red[index], &ir[index]);
	//printf("%d %d %lu %lu\n",get_current(0), get_current(1), red[index],ir[index]);
	new_PPG_data=1;
	index++;
	//index[nr]++;


	/*
	if (index[nr]==BUFFER_SIZE)
	index[nr]=0;
	return;
*/

/*
	if ((index%8==0)&&(index!=0))
	{
		adjust_LED_brightness(0);
		adjust_LED_brightness(1);
		index=0;
	}

*/

	/*
 *
	  if (index[nr]==BUFFER_SIZE)
	  {
		  //brightness_ok();
		  index[nr]=0;
		//  LED3(1);

		  //if (nr==0)
		  //{
		  maxim_heart_rate_and_oxygen_saturation(&ir[nr][0], BUFFER_SIZE, &red[nr][0], &n_sp02[nr], &ch_spo2_valid[nr], &n_heart_rate[nr], &ch_hr_valid[nr], &r[nr]);
		  //rf_heart_rate_and_oxygen_saturation(&ir[nr][0], 100, &red[nr][0], &n_sp02[nr], &ch_spo2_valid[nr], &n_heart_rate[nr], &ch_hr_valid[nr], &ratio[nr], &correl[nr], &r[nr]);
		  //new_SPO2_data[0]=1;
		  //new_SPO2_data[1]=1;
		  //}
		  new_SPO2_data[nr]=1;

		  //LED3(0);
		for(index[nr]=BUFFER_SIZE/5;index[nr]<BUFFER_SIZE;index[nr]++)
		{
			red[nr][index[nr]-(BUFFER_SIZE/5)]=red[nr][index[nr]];
			ir[nr][index[nr]-(BUFFER_SIZE/5)]=ir[nr][index[nr]];
		}
		index[nr]=4*BUFFER_SIZE/5;
		//printf("S %i %i\r\n", (uint16_t) n_sp02, (uint16_t)n_heart_rate);
	  }

	}
	*/

	if (index==BUFFER_SIZE) index=0;

	DMA_started=0;

	//LED2(0);
	//LED1(0);
}







float ratio[NR_OF_MAX30102], correl[NR_OF_MAX30102], r[NR_OF_MAX30102];


I2C_HandleTypeDef  * hi2c;

bool max30112_init(I2C_HandleTypeDef * hi2cx)
{
	hi2c=hi2cx;


	if(max30112_write_reg(REG_FIFO_SYSTEM_CONTROL,RESET)) // reset
			return 1;
	HAL_Delay(10);

	if(max30112_write_reg(REG_INTR_ENABLE_1,0)) // disable interrupts
		return 1;
	if(max30112_write_reg(REG_INTR_ENABLE_2,0))
		return 1;


	if(max30112_write_reg(REG_FIFO_CONFIG,FIFO_STAT_CLR))
		return 1;
	if(max30112_write_reg(REG_FIFO_DATA_CONTROL1,LED1|(LED2<<4)))
		return 1;

	if(max30112_write_reg(REG_FIFO_SYSTEM_CONTROL,FIFO_EN))
		return 1;

	if(max30112_write_reg(REG_PPG_CONFIG1,FS12UA| SPS400|PPG_TINT400US))  // one has to be careful with the ambient light cancellation!!!
		return 1;


	if(max30112_write_reg(REG_PPG_CONFIG2,AV8S|LED_SETTLING5US))
		return 1;


	LED_current[0]=0x50;
	LED_current[1]=0x15;

	if(max30112_write_reg(REG_LED1_PA,LED_current[0]))  // red ... der obere
		return 1;

	if(max30112_write_reg(REG_LED2_PA,LED_current[1]))
		return 1;

	if(max30112_write_reg(REG_INTR_ENABLE_1,PPG_RDY)) // INTR setting, interrupt on new sample
		return 1;

	return 0;

}

bool max30112_write_reg(uint8_t uch_addr, uint8_t uch_data)
/**
* \brief        Write a value to a MAX30102 register
* \par          Details
*               This function writes a value to a MAX30102 register
*
* \param[in]    uch_addr    - register address
* \param[in]    uch_data    - register data
*
* \retval       true on success
*/
{
	 uint8_t packet[2];
	 packet[0]=uch_addr;
	 packet[1]=uch_data;

	  while(HAL_I2C_Master_Transmit(hi2c, (uint16_t)MAX30112_ADDR, packet, 2, 100)!= HAL_OK)
	  {
		printf("I2C command error\n");

		  /* Error_Handler() function is called when Timeout error occurs.
		   When Acknowledge failure occurs (Slave don't acknowledge its address)
		   Master restarts communication */
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF)
		{
			printf("I2C DISP COMMAND Error\n");
			return 1;
		}
	  }
	  return 0;
}

bool max30112_read_reg(uint8_t uch_addr, uint8_t *puch_data)
/**
* \brief        Read a MAX30102 register
* \par          Details
*               This function reads a MAX30102 register
*
* \param[in]    uch_addr    - register address
* \param[out]   puch_data    - pointer that stores the register data
*
* \retval       true on success
*/
{
	 uint8_t packet[1];
	 packet[0]=uch_addr;

	  while(HAL_I2C_Master_Transmit(hi2c, (uint16_t)MAX30112_ADDR, packet, 1, 100)!= HAL_OK)
	  {
		return 1;
		  /* Error_Handler() function is called when Timeout error occurs.
		   When Acknowledge failure occurs (Slave don't acknowledge its address)
		   Master restarts communication */
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF)
		{
			printf("I2C DISP COMMAND Error\n");
			return 1;
		}
	  }



	 while(HAL_I2C_Master_Receive(hi2c, (uint16_t)MAX30112_ADDR, puch_data, 1, 100)!= HAL_OK)
		  {
			return 1;
		 	 /* Error_Handler() function is called when Timeout error occurs.
			   When Acknowledge failure occurs (Slave don't acknowledge its address)
			   Master restarts communication */
			if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF)
			{
				printf("I2C DISP COMMAND Error\n");
				return 1;
			}
		  }
	 return 0;
}

static uint8_t read_command=0;
static uint8_t istat1;
uint8_t data[12];
//volatile uint32_t red, ir;
volatile uint32_t chan[2];

void max30112_data_read_command(void)
{
    uint8_t packet[1];
	packet[0]=REG_FIFO_DATA;

	while(HAL_I2C_Master_Transmit(hi2c, (uint16_t)MAX30112_ADDR, packet, 1, 100)!= HAL_OK)
	  {
		/* Error_Handler() function is called when Timeout error occurs.
		   When Acknowledge failure occurs (Slave don't acknowledge its address)
		   Master restarts communication */
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF)
		{
			Error_Handler();
		}
	  }
	read_command=1;
}


void max30112_read_data_dma1(void)
{
	if (read_command==0) {
		max30112_read_reg(REG_INTR_STATUS_1, &istat1);
	}
	max30112_data_read_command();
	HAL_I2C_Master_Receive_DMA(hi2c, (uint16_t)MAX30112_ADDR, data, 12);
	DMA_started=1;
}

uint8_t get_MAX30112_DMA_started(void)
{
	return DMA_started;
}


void max30112_read_data_dma2(uint32_t *pun_red_led, uint32_t *pun_ir_led)
{

	for (uint8_t i=0; i<2;i++)
	{
		chan[i]=(unsigned char) data[i*3+ 0];
		chan[i]<<=8;
		chan[i]|=(unsigned char) data[i*3 + 1];
		chan[i]<<=8;
		chan[i]|=(unsigned char) data[i*3 +2];
		chan[i]&=0x07FFFFL;
	}


	/*
	ir=(unsigned char) data[3];
	ir<<=8;
	ir|=(unsigned char) data[4];
	ir<<=8;
	ir|=(unsigned char) data[5];


	red&=0x07FFFFL;
	ir&=0x07FFFFL;
	 */

	*pun_ir_led=chan[1];
	*pun_red_led=chan[0];
}

uint32_t get_max30112_red(void)
{
	return chan[0];
}

uint32_t get_max30112_ir(void)
{
	return chan[1];
}

uint8_t adjust_LED_brightness(uint8_t i)
{
	uint32_t current;
	if ((chan[i]<MIN_ADC_READING)&&(LED_current[i]<MAX_LED_CURRENT))
	{
		current=(uint32_t)LED_current[i]*DEFAULT_ADC_READING;
		current/=chan[i];
		if (current>MAX_LED_CURRENT) current=MAX_LED_CURRENT;
	}
	else if ((chan[i]>MAX_ADC_READING)&&(LED_current[i]>MIN_LED_CURRENT))
	{
		current=(uint32_t)LED_current[i]*DEFAULT_ADC_READING;
		current/=chan[i];
		if (current<MIN_LED_CURRENT) current=MIN_LED_CURRENT;
	}
	else return 0;

	LED_current[i]=(uint8_t)current;
	max30112_write_reg(REG_LED1_PA+i,LED_current[i]);
	return 1;
}

uint8_t get_current(uint8_t i)
{
	return LED_current[i];
}













