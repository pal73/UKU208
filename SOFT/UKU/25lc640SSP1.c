#include "25lc640SSP1.h"
#include "LPC17xx.H"
#include "main.h"

#ifndef SSP1_DEFINED
#define SSP1_DEFINED



char ssp1(char in)
{

LPC_SSP1->DR=in;
while(!(LPC_SSP1->SR & (1<<2)));
return LPC_SSP1->DR;

 

}

#endif

//----------------------------------------------- 
//настройка SPI1
void ssp1_config(void)
{ 
SET_REG( LPC_PINCON->PINSEL0, 0, (5)*2, 2);
SET_REG( LPC_PINCON->PINSEL0, 2, (7)*2, 2);
SET_REG( LPC_PINCON->PINSEL0, 2, (8)*2, 2);
SET_REG( LPC_PINCON->PINSEL0, 2, (9)*2, 2); 

LPC_SC->PCONP |= 1 <<10;	//enable POWER to SSP0 (redundant following reset)
LPC_SC->PCLKSEL0 |= 1<<20;	//pclk = cclk
LPC_SSP1->CPSR |= 16;	//internal divider

LPC_SSP1->CR0=0;
LPC_SSP1->CR1=0;
LPC_SSP1->CR0 |= 3<<6;	//clock phase
LPC_SSP1->CR0 |= 7<<0;	// 8 bits
LPC_SSP1->CR1 |= 1<<1;	//enable SSP

LPC_GPIO0->FIODIR |= (1<<5);	//make output
}


//----------------------------------------------- 
//выключение SPI1
void ssp1_unconfig(void)
{ 

SET_REG( LPC_PINCON->PINSEL0, 0, 15*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (16-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (17-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (18-16)*2, 2);

LPC_SSP1->CR1 &= ~(1<<1);	//enable SSP
}

//----------------------------------------------- 
//Разрешение записи
void lc640_wren(void)
{

ssp1_config();

CS_ON

ssp1(0x06); 

CS_OFF

ssp1_unconfig();
}

//-----------------------------------------------
//Чтение из м-мы регистра состояния
char lc640_rdsr(void)
{
char temp;

ssp1_config();
CS_ON
ssp1(0x05);
temp=ssp1(0xff);
CS_OFF
ssp1_unconfig();
return temp;
}

//----------------------------------------------- 
//Чтение из м-мы байта по адр. ADR
int lc640_read(int ADR)
{
int temp;
temp=0;

while(lc640_rdsr()&0x01)
	{
	}
ssp1_config();
CS_ON
CS_ON
ssp1(0x03);
temp=*(((char*)&ADR)+1);
ssp1(temp);
temp=*((char*)&ADR);
ssp1(temp);
temp=ssp1(0xff);
CS_OFF
CS_OFF
ssp1_unconfig();
return temp;

}

//----------------------------------------------- 
//Чтение из м-мы слова по адр. ADR
int lc640_read_int(int ADR)
{
char temp;
int temp_i;


//LPC_GPIO0->FIODIR|=0x00000002;
//LPC_GPIO0->FIOSET|=0x00000002;



while(lc640_rdsr()&0x01)
	{
	}

//lc640_rdsr();
//IO0DIR_bit.P0_11=1;
//IO0SET_bit.P0_11=1;
ssp1_config();
CS_ON
ssp1(0x03);
temp=*(((char*)&ADR)+1);
ssp1(temp);
temp=*((char*)&ADR);
ssp1(temp);
temp=ssp1(0xff);
temp_i=ssp1(0xff);
temp_i<<=8;
temp_i+=temp;
CS_OFF
CS_OFF
ssp1_unconfig();

//LPC_GPIO0->FIOCLR|=0x00000002;
return temp_i;
}

//----------------------------------------------- 
//Чтение из м-мы 4 байт по адр. ADR
long lc640_read_long(int ADR)
{
char temp0,temp1,temp2;
long temp_i;
while(lc640_rdsr()&0x01)
	{
	}
ssp1_config();
CS_ON
ssp1(0x03);
temp0=*(((char*)&ADR)+1);
ssp1(temp0);
temp0=*((char*)&ADR);
ssp1(temp0);
temp0=ssp1(0xff);
temp1=ssp1(0xff);
temp2=ssp1(0xff);
temp_i=ssp1(0xff);
temp_i<<=8;
temp_i+=temp2;
temp_i<<=8;
temp_i+=temp1;
temp_i<<=8;
temp_i+=temp0;
CS_OFF
CS_OFF
ssp1_unconfig();
return temp_i;
}

//----------------------------------------------- 
//Чтение из м-мы 4 байт по адр. ADR
void lc640_read_long_ptr(int ADR,char* out_ptr)
{
char temp0/*,temp1,temp2*/;
//long temp_i;
while(lc640_rdsr()&0x01)
	{
	}
ssp1_config();
CS_ON
ssp1(0x03);
temp0=*(((char*)&ADR)+1);
ssp1(temp0);
temp0=*((char*)&ADR);
ssp1(temp0);
out_ptr[0]=ssp1(0xff);
out_ptr[1]=ssp1(0xff);
out_ptr[2]=ssp1(0xff);
out_ptr[3]=ssp1(0xff);
CS_OFF
CS_OFF
ssp1_unconfig();
}

//----------------------------------------------- 
//Чтение из м-мы N байт по адр. ADR
void lc640_read_str(int ADR, char* ram_ptr, char num)
{
char temp0,i;
while(lc640_rdsr()&0x01)
	{
	}
ssp1_config();
CS_ON
ssp1(0x03);
temp0=*(((char*)&ADR)+1);
ssp1(temp0);
temp0=*((char*)&ADR);
ssp1(temp0);

for(i=0;i<num;i++)
	{
	*ram_ptr++=ssp1(0xff);
	}
CS_OFF
CS_OFF
ssp1_unconfig();
}

//-----------------------------------------------
//Запись байта in по адресу ADR
char lc640_write(int ADR,char in)
{
char temp; 

while(lc640_rdsr()&0x01)
	{
	}
lc640_wren();
ssp1_config();	
CS_ON
ssp1(0x02);
temp=*(((char*)&ADR)+1);
ssp1(temp);
temp=*((char*)&ADR);
ssp1(temp);
temp=ssp1(in);
CS_OFF
CS_OFF
ssp1_unconfig(); 
return temp;
}

//-----------------------------------------------
//Запись слова in по адресу ADR
char lc640_write_int(short ADR,short in)
{
char temp; 
while(lc640_rdsr()&0x01)
	{
	}
lc640_wren();
ssp1_config();	
CS_ON
ssp1(0x02);
temp=*(((char*)&ADR)+1);
ssp1(temp);
temp=*((char*)&ADR);
ssp1(temp);
temp=*((char*)&in);
ssp1(temp);
temp=*(((char*)&in)+1);
ssp1(temp);
CS_OFF
CS_OFF
ssp1_unconfig();
return temp;
}  

//-----------------------------------------------
//Запись 4 байт in по адресу ADR
char lc640_write_long(int ADR,long in)
{
char temp; 

while(lc640_rdsr()&0x01)
	{
	}
lc640_wren();	
ssp1_config();
CS_ON
ssp1(0x02);
temp=*(((char*)&ADR)+1);
ssp1(temp);
temp=*((char*)&ADR);
ssp1(temp);
temp=*((char*)&in);
ssp1(temp);
temp=*(((char*)&in)+1);
ssp1(temp);
temp=*(((char*)&in)+2);
ssp1(temp);
temp=*(((char*)&in)+3);
ssp1(temp);           
CS_OFF
CS_OFF  
ssp1_unconfig();
return temp;
}

//-----------------------------------------------
//Запись 4 байт in по адресу ADR
char lc640_write_long_ptr(int ADR,char* in)
{
char temp; 

while(lc640_rdsr()&0x01)
	{
	}
lc640_wren();	
ssp1_config();
CS_ON
ssp1(0x02);
temp=*(((char*)&ADR)+1);
ssp1(temp);
temp=*((char*)&ADR);
ssp1(temp);
temp=in[0];
ssp1(temp);
temp=in[1];
ssp1(temp);
temp=in[2];
ssp1(temp);
temp=in[3];
ssp1(temp);

CS_OFF
CS_OFF  
ssp1_unconfig();
return temp;
}		
