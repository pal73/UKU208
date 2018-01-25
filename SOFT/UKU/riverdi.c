#include "riverdi.h"
#include "LPC17xx.H"
#include "main.h"

//-----------------------------------------------
void delayus(int us)
{
signed  i,uus=20*us;

for(i=0;i<uus;i++)
	{
	__nop();
	}
}

//----------------------------------------------- 
//настройка SPI1
void spi1_config(void)
{ 

SET_REG( LPC_PINCON->PINSEL0, 3, 15*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (16-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 3, (17-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 3, (18-16)*2, 2); 
/*
S1SPCCR=100;
S1SPCR=0x3f; */

LPC_SPI->SPCCR=1;
LPC_SPI->SPCR=0x20;
}


//----------------------------------------------- 
//выключение SPI1
void spi1_unconfig(void)
{ 

SET_REG( LPC_PINCON->PINSEL0, 0, 15*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (16-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (17-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (18-16)*2, 2);

LPC_SPI->SPCR=0x00;
}

//-----------------------------------------------
char spi1(char in)
{
LPC_SPI->SPDR=in;
while(!(LPC_SPI->SPSR&(1<<7)));
return LPC_SPI->SPDR;
}

//-----------------------------------------------
char rd8(long addr)
{
char temp;
RIV_CS_ON
spi1((char)((addr>>16)&0x3f));
spi1((char)((addr>>8)&0xff));
spi1((char)((addr)&0xff));
spi1((char)(0x55));
temp = spi1(0x55);
RIV_CS_OFF
return temp;
}

//-----------------------------------------------
short rd16(long addr)
{
char temp[2];
RIV_CS_ON
spi1((char)((addr>>16)&0x3f));
spi1((char)((addr>>8)&0xff));
spi1((char)((addr)&0xff));
spi1((char)(0x55));
temp[0] = spi1(0x55);
temp[1] = spi1(0x55);

RIV_CS_OFF
return *((short*)temp);
}

//-----------------------------------------------
int rd32(long addr)
{
char temp[4];
RIV_CS_ON
spi1((char)((addr>>16)&0x3f));
spi1((char)((addr>>8)&0xff));
spi1((char)((addr)&0xff));
spi1((char)(0x55));
temp[0] = spi1(0x55);
temp[1] = spi1(0x55);
temp[2] = spi1(0x55);
temp[3] = spi1(0x55);
RIV_CS_OFF
return *((int*)temp);
}

//-----------------------------------------------
char wr8(long addr, char in)
{
//char temp;
RIV_CS_ON
spi1((char)(((addr>>16)&0x3f)|0x80));
spi1((char)((addr>>8)&0xff));
spi1((char)((addr)&0xff));
spi1(in); 
RIV_CS_OFF
//return temp;
}

//-----------------------------------------------
char wr16(long addr, short in)
{
char temp;
RIV_CS_ON
spi1((char)(((addr>>16)&0x3f))|0x80);
spi1((char)((addr>>8)&0xff));
spi1((char)((addr)&0xff));
spi1((char)in);
spi1((char)(in>>8));
RIV_CS_OFF
return temp;
}
//-----------------------------------------------
char wr32(long addr, int in)
{
char temp;
RIV_CS_ON
spi1((char)(((addr>>16)&0x3f))|0x80);
spi1((char)((addr>>8)&0xff));
spi1((char)((addr)&0xff));
spi1((char)in);
spi1((char)(in>>8));
spi1((char)(in>>16));
spi1((char)(in>>24));
RIV_CS_OFF
return temp;
}
//-----------------------------------------------
void command_active(void)
{
RIV_CS_ON
spi1(0);
spi1(0);
spi1(0);
RIV_CS_OFF
}

//-----------------------------------------------
void host_command(char cmd)
{
RIV_CS_ON
spi1(cmd);
spi1(0x00);
spi1(0x00);
RIV_CS_OFF



}