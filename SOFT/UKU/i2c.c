#include "i2c.h"
#include <LPC21xx.H>
#include "main.h"

#define SCL_HIGH() IO0CLR=(1UL<<SCL__);IO0DIR&=~(1UL<<SCL__);
#define SCL_LOW()  IO0CLR=(1UL<<SCL__);IO0DIR|=(1UL<<SCL__);
//#define SCL_DIR_INPUT() PORTF|=0x80; DDRF&=0x7f;
#define SCL_PIN IO0PIN&(1<<SCL__) 

#define SDA_HIGH() IO0CLR=(1UL<<SDA__);IO0DIR&=~(1UL<<SDA__);
#define SDA_LOW()  IO0CLR=(1UL<<SDA__);IO0DIR|=(1UL<<SDA__);
//#define SDA_DIR_INPUT() PORTF|=0x40; DDRF&=0xB0;
#define SDA_PIN IO0PIN&(1<<SDA__) 
 
//#define i2c_Start()		i2c_Restart()
#define i2c_WriteTo(address)	i2c_Open((address), I2C_WRITE)
#define i2c_ReadFrom(address)	i2c_Open((address), I2C_READ)



//-----------------------------------------------
void i2c_Start(void)
{
                      // ensure clock is low 
//SDA_HIGH()                     // ensure data is high 

//delay_us(I2C_TM_DATA_SU);
//SDA_HIGH()
//SDA_HIGH()
//SDA_HIGH()
//SDA_HIGH()
//SDA_HIGH()

SDA_LOW()
SCL_HIGH()
//delay_us(I2C_TM_SCL_HIGH);
SCL_HIGH()
SCL_HIGH()
SCL_HIGH()
SCL_HIGH()

SCL_LOW()
SCL_LOW()
SCL_LOW()
SCL_LOW()                      // the high->low transition 
//delay_us(I2C_TM_START_HD);
//SDA_LOW()
//SDA_LOW()
//SDA_LOW()
return;
}    

//-----------------------------------------------
void i2c_Restart(void)
{
SCL_LOW()                      // ensure clock is low 
SDA_HIGH()                     // ensure data is high 

//delay_us(I2C_TM_DATA_SU);
SDA_HIGH()
SDA_HIGH()
SDA_HIGH()
SDA_HIGH()
SDA_HIGH()


SCL_HIGH()
//delay_us(I2C_TM_SCL_HIGH);
SCL_HIGH()
SCL_HIGH()
SCL_HIGH()
SCL_HIGH()

SDA_LOW()                      // the high->low transition 
//delay_us(I2C_TM_START_HD);
SDA_LOW()
SDA_LOW()
SDA_LOW()
return;
}    



//-----------------------------------------------
unsigned char i2c_SendByte(unsigned char byte)
{
signed char i;
SCL_LOW()
//delay_us(I2C_TM_DATA_SU);
SCL_LOW()

for(i=8; i>=1; i--)
	{
     if(byte&0x80)
         	{
         	SDA_HIGH()
         	}
     else
         	{
         	SDA_LOW()
         	}
     //delay_us(I2C_TM_SCL_HIGH);
     byte<<=1;
     SCL_HIGH()
     SCL_HIGH()
     SCL_HIGH()
     SCL_HIGH()
	//delay_us(I2C_TM_DATA_SU);
	SCL_LOW()


	//	DelayUs(I2C_TM_SCL_HIGH);	/* clock high time */
 	}

SDA_HIGH()
return 0;
}

//-----------------------------------------------
unsigned char i2c_SendAddress(unsigned char address, unsigned char rw)
{
return i2c_SendByte(address | (rw&0x01));
} 


//-----------------------------------------------
signed char i2c_ReadAcknowledge(void)
{
unsigned char ack;
SDA_HIGH()
SCL_LOW()
//delay_us(I2C_TM_SCL_TO_DATA);
SCL_LOW()
SCL_LOW()
SCL_LOW()

SCL_HIGH()                              /* make clock is low */
		/* disable data line - listen for ack */
//delay_us(I2C_TM_SCL_TO_DATA);		/* SCL low to data out valid */
SCL_HIGH()
SCL_HIGH()
SCL_HIGH()

if(SDA_PIN) ack = 1;
else ack = 0;

SCL_LOW()		/* float clock high */
//delay_us(I2C_TM_DATA_SU);
					/* read the acknowledge */
return	ack;				
}

//-----------------------------------------------
char i2c_ReadByte(void)
{
unsigned char i;
unsigned char byte = 0;
SDA_HIGH();
for(i=0; i<8; i++)
	{
	                      /* drive clock low */
	//delay_us(I2C_TM_SCL_LOW);	/* min clock low  period */
	//SCL_LOW()
	//SCL_LOW()
	//SCL_LOW()
	SCL_LOW()
	SDA_HIGH();		/* release data line */
	//SCL_HIGH();		/* float clock high */
	//delay_us(I2C_TM_SCL_HIGH);
	//SCL_HIGH();
	SCL_HIGH();
	SCL_HIGH();
	byte = byte << 1;		/* read the next bit */ 
	if(SDA_PIN) byte|=1;
	else byte&=0xfe;
	SCL_LOW()
	}
return byte;
}

//-----------------------------------------------
void i2c_SendAcknowledge(unsigned char status)
{

SCL_LOW()
SCL_LOW()
if(status&0x01)
	{
     SDA_LOW()                          /* drive line low -> more to come */
     }
else
	{
     SDA_HIGH()
	}
//delay_us(I2C_TM_DATA_SU);
SCL_HIGH()			/* float clock high */
//delay_us(I2C_TM_SCL_HIGH);
SCL_HIGH()
SCL_HIGH()
SCL_HIGH()
SCL_LOW()
SCL_LOW()
return;
}

//-----------------------------------------------
void i2c_Stop(void)
{
SDA_LOW()                      /* ensure data is low first */
SCL_HIGH()

//delay_us(I2C_TM_DATA_SU);
//SCL_DIR_INPUT()		/* float clock high */
SCL_HIGH()
//delay_us(I2C_TM_STOP_SU);
SCL_HIGH()
SCL_HIGH()
SCL_HIGH()

SDA_HIGH()                     /* the low->high data transistion */
//delay_us(I2C_TM_BUS_FREE);	/* bus free time before next start */
SDA_HIGH()
SDA_HIGH()
SDA_HIGH()
SDA_HIGH()

//SDA_DIR_INPUT()            /* float data high */
SDA_HIGH()
return;
}
