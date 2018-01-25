#include "ad7705.h"
#include "25lc640.h"
#include <LPC17xx.H>
//#include "global_define.h"
#include "main.h"

unsigned short ad7705_res1,ad7705_res2;
unsigned short ad7705_buff[2][16],ad7705_buff_[2];
unsigned short ad7705_res;
char b7705ch,ad7705_wrk_cnt;
unsigned short cnt_ad7705_vis,cnt_ad7705_vis_wrk;
signed short ad7705_plazma;


//----------------------------------------------- 
//настройка SPI1
void spi1_ad7705_config(void)
{
SET_REG( LPC_PINCON->PINSEL0, 3, 15*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (16-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 3, (17-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 3, (18-16)*2, 2); 
/*
S1SPCCR=100;
S1SPCR=0x3f; */


LPC_SPI->SPCCR=20;
LPC_SPI->SPCR=0x38;
}
//-----------------------------------------------
void ad7705_reset(void)
{
//short i;
///IO1DIR|=(1UL<<23);
LPC_GPIO2->FIODIR|=(1<<13);
///IO1CLR|=(1UL<<23);
LPC_GPIO2->FIOCLR|=(1<<13);
delay_ms(10);
///IO1SET|=(1UL<<23);
LPC_GPIO2->FIOPIN|=(1<<13);
}

//-----------------------------------------------
void ad7705_write(char in)
{
char i;
///IO0DIR|=(1UL<<11);
LPC_GPIO0->FIODIR|=(1UL<<11);
//IO0SET|=(1UL<<11);
LPC_GPIO0->FIOPIN|=(1UL<<11);
spi1_ad7705_config();
///IO0CLR|=(1UL<<11);
for(i=0;i<5;i++)LPC_GPIO0->FIOPIN&=~(1UL<<11);
spi1(in);
///for(i=0;i<5;i++)IO0CLR|=(1UL<<11);
///IO0SET|=(1UL<<11);
for(i=0;i<5;i++)LPC_GPIO0->FIOPIN&=~(1UL<<11);
for(i=0;i<5;i++)LPC_GPIO0->FIOPIN|=(1UL<<11);
spi1_unconfig();                   
}


//-----------------------------------------------
void ad7705_read(char num)
{
//char temp;
char i;
 
LPC_GPIO0->FIODIR|=(1UL<<11);

LPC_GPIO0->FIOPIN|=(1UL<<11);
spi1_ad7705_config();

///IO0CLR|=(1UL<<11);
for(i=0;i<5;i++)LPC_GPIO0->FIOPIN&=~(1UL<<11);
ad7705_res=0;
if(num==1) 
	{
	ad7705_res=spi1(0);
	}
else if(num==2)
	{
	*(((char*)(&ad7705_res))+1)=spi1(0); 
	*(((char*)(&ad7705_res)))=spi1(0);
	}	   

///IO0CLR|=(1UL<<11);

for(i=0;i<5;i++)LPC_GPIO0->FIOPIN&=~(1UL<<11);
for(i=0;i<5;i++)LPC_GPIO0->FIOPIN|=(1UL<<11);

spi1_unconfig();                                            
}

//-----------------------------------------------
void ad7705_drv(void)
{
//__disable_irq();


	ad7705_write(0x08);
	ad7705_read(1);


///IO0DIR|=(1UL<<11);
///IO0DIR&=~(1UL<<10);

if(!(ad7705_res&0x0001))
	{
	ad7705_write(0x38+b7705ch);
	ad7705_read(2);
	//ad7705_buff[0][0]=ad7705_res;

	ad7705_plazma++;
	

	if(!b7705ch)
		{
		ad7705_buff[0][ad7705_wrk_cnt]=ad7705_res;
		ad7705_res1=ad7705_res;
		}
	else if(b7705ch) 
		{
		ad7705_buff[1][ad7705_wrk_cnt]=ad7705_res;
		ad7705_res2=ad7705_res;
		} 

	if(b7705ch)
		{
		b7705ch=0;
		ad7705_wrk_cnt++;
		if(ad7705_wrk_cnt>=16)ad7705_wrk_cnt=0;
		
		if((ad7705_wrk_cnt&0x01)==0)
			{
			unsigned temp_U;
			char i,ii;

			for(i=0;i<2;i++)
				{
				temp_U=0;
				for(ii=0;ii<16;ii++)
					{
					temp_U+=(unsigned long)ad7705_buff[i][ii];
					}
				ad7705_buff_[i]=(unsigned short)(temp_U>>4);
				}	
			} 
		}	
		
		
	else b7705ch=1;
	
	//b7705ch=1;
    
	if(!b7705ch) ad7705_write(0x20);
	else if(b7705ch) ad7705_write(0x21);

	ad7705_write(BIN8(1101)); 

	if(!b7705ch) ad7705_write(0x10);
	else if(b7705ch) ad7705_write(0x11);

	ad7705_write(0x44);	
	
	}
/*
ad7705_write(0x20);
ad7705_write(BIN8(1101));
ad7705_write(0x10);
ad7705_write(0x44);
*/
//	__enable_irq();


/*
if(((ad7705_res1&0x0fff)==0x0000)||((ad7705_res1&0x0fff)==0x0fff)||((ad7705_res2&0x0fff)==0x0000)||((ad7705_res2&0x0fff)==0x0fff))
{
if(cnt_ad7705_vis<50)
	{
	cnt_ad7705_vis++;
	if(cnt_ad7705_vis>=50) cnt_ad7705_vis_wrk=50;
		
	}
}
else cnt_ad7705_vis=0;

if(cnt_ad7705_vis_wrk)
	{
	cnt_ad7705_vis_wrk--;

	if(cnt_ad7705_vis_wrk==30)
		{
		ad7705_reset();
		ad7705_write(0x20);
		ad7705_write(BIN8(1101)); 
		ad7705_write(0x10);
		ad7705_write(0x44); 
	     }
	else if(cnt_ad7705_vis_wrk==20)
		{              
		ad7705_reset();
		ad7705_write(0x20);
		ad7705_write(BIN8(1101)); 
		ad7705_write(0x10);
		ad7705_write(0x44); 
	     }	
	else if(cnt_ad7705_vis_wrk==10)
		{              
		ad7705_reset();
		ad7705_write(0x20);
		ad7705_write(BIN8(1101)); 
		ad7705_write(0x10);
		ad7705_write(0x44); 
	     }
	else if(cnt_ad7705_vis_wrk==2)
		{

	     }		        		          
	}         
else 
	{

	}*/	
	
}

//-----------------------------------------------
void ad7705_drv_(void)
{
b7705ch++;
b7705ch&=0x0001;

ad7705_write(0x20+b7705ch);
ad7705_write(BIN8(1101));
ad7705_write(0x10+b7705ch);
ad7705_write(0x44);


ad7705_drv_loop:

ad7705_write(0x08);
ad7705_read(1);

if(ad7705_res&0x0001)  goto ad7705_drv_loop;
else 
	{
	ad7705_write(0x38+b7705ch);
	ad7705_read(2);
	ad7705_plazma++;
	}
	
}

 

