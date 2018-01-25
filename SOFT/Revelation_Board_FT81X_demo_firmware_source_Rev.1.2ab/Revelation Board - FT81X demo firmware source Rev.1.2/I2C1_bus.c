#include "I2C1_bus.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_syscfg.h"
#include "stm32f0xx_misc.h"
//#include "misc.h"
#define TIMEOUT_MAX    0xFFF

#define SLAVE_ADDRESS 0x3D // the slave address (example)

void init_I2C1(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	  /* Reconfigure and enable I2C1 error interrupt to have the higher priority */
	  NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

	  // enable APB1 peripheral clock for I2C1
	  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	  /* Configure the I2C clock source. The clock is derived from the HSI */
	  RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);

	// enable clock for SCL and SDA pins
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);



	/* setup SCL and SDA pins
	 * You can connect I2C1 to two different
	 * pairs of pins:
	 * 1. SCL on PB6 and SDA on PB7
	 * 2. SCL on PB8 and SDA on PB9
	 *
	 */
		// Connect I2C1 pins to AF
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_4);	// SCL
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_4); // SDA


	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // we are going to use PB6 and PB7
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			// set pins to alternate function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;		// set GPIO speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;			// set output to open drain --> the line has to be only pulled low, not driven high
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			// enable pull up resistors
	GPIO_Init(GPIOA, &GPIO_InitStruct);					// init GPIOB



	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
	I2C_InitStruct.I2C_DigitalFilter = 0x00;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_Timing = 0x20000A0D;

	I2C_Init(I2C1, &I2C_InitStruct);				// init I2C1

	// enable I2C1
	I2C_Cmd(I2C1, ENABLE);
}

/* This function issues a start condition and
 * transmits the slave address + R/W bit
 *
 * Parameters:
 * 		I2Cx --> the I2C peripheral e.g. I2C1
 * 		address --> the 7 bit slave address
 * 		direction --> the tranmission direction can be:
 * 						I2C_Direction_Tranmitter for Master transmitter mode
 * 						I2C_Direction_Receiver for Master receiver
 */
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction){
	uint16_t  timeout = TIMEOUT_MAX;


	// wait until I2C1 is not busy anymore
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
	{
		if(timeout-- == 0)
		{
			init_I2C1();
			break;
		}
	}

	// Send I2C1 START condition
	I2C_GenerateSTART(I2Cx, ENABLE);

	//timeout = TIMEOUT_MAX;
	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	//while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	{
		//if(timeout-- == 0)
		{
		//	init_I2C1();
		//	break;
		}
	}

	// Send slave Address for write
	I2C_Send7bitAddress(I2Cx, address, direction);

	/* wait for I2C1 EV6, check if
	 * either Slave has acknowledged Master transmitter or
	 * Master receiver mode, depending on the transmission
	 * direction
	 */
	if(direction == I2C_Direction_Transmitter){
	/*	timeout = TIMEOUT_MAX;
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		{
			if(timeout-- == 0)
			{
				init_I2C1();
				break;
			}
		}*/
	}
	else if(direction == I2C_Direction_Receiver){
	/*	timeout = TIMEOUT_MAX;
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		{
			if(timeout-- == 0)
			{
				init_I2C1();
				break;
			}
		}*/
	}
}

/* This function transmits one byte to the slave device
 * Parameters:
 *		I2Cx --> the I2C peripheral e.g. I2C1
 *		data --> the data byte to be transmitted
 */
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data){
	uint16_t timeout = TIMEOUT_MAX;
	I2C_SendData(I2Cx, data);
	// wait for I2C1 EV8_2 --> byte has been transmitted
/*
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if(timeout-- == 0)
		{
			init_I2C1();
			break;
		}
	}*/
}

/* This function reads one byte from the slave device
 * and acknowledges the byte (requests another byte)
 */
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx){
	uint16_t timeout = TIMEOUT_MAX;
	// enable acknowledge of recieved data
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// wait until one byte has been received
/*
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) )
	{
		if(timeout-- == 0)
		{
			init_I2C1();
			break;
		}
	}*/
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

/* This function reads one byte from the slave device
 * and doesn't acknowledge the recieved data
 */
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx){
	uint16_t timeout = TIMEOUT_MAX;
	// disabe acknowledge of received data
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	// wait until one byte has been received
/*
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) )
	{
		if(timeout-- == 0)
		{
			init_I2C1();
			break;
		}
	}*/
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

/* This funtion issues a stop condition and therefore
 * releases the bus
 */
void I2C_stop(I2C_TypeDef* I2Cx){
	// Send I2C1 STOP Condition
	I2C_GenerateSTOP(I2Cx, ENABLE);
}

/**
  * @brief  Write value to selected register address
  * @param  Device Address, Register Address, Value to write
  * @retval None
  */
void I2C_WriteDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t RegisterValue)
{
/*  // start a transmission in Master transmitter mode
  I2C_start(I2C1, DeviceAddr, I2C_Direction_Transmitter);

  // write one byte to the slave
  I2C_write(I2C1, RegisterAddr);

  // write another byte to the slave
  I2C_write(I2C1, RegisterValue);

  // stop the transmission
  I2C_stop(I2C1);*/
}



/**
  * @brief  Return value from selected register
  * @param  Device Address, Register Address
  * @retval Read value
  */
uint8_t I2C_ReadDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr)
{
  uint8_t tmp;
  unsigned int timeout;

  timeout = (0x1000 * 10);
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET)
  {
    if((timeout--) == 0) return 0;
  }
  I2C_TransferHandling(I2C1,DeviceAddr, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

/*  timeout = (0x1000 * 10);
   while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
   {
     if((timeout--) == 0) return 0;
   }*/

   I2C_SendData(I2C1, (uint8_t)RegisterAddr);

  // I2C_GenerateSTOP(I2C1,ENABLE);


   timeout = (0x1000 * 10);
      while(I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET)
      {
        if((timeout--) == 0) return 0;
      }

      I2C_TransferHandling(I2C1,DeviceAddr, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Read);

      timeout = (0x1000 * 10);
      while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET)
            {
              if((timeout--) == 0) return 0;
            }
      tmp = I2C_ReceiveData(I2C1);
      I2C_GenerateSTOP(I2C1,ENABLE);

  return tmp;
}

