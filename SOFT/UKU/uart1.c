#include "uart1.h"
#include <LPC21XX.H> 
#include "main.h"
#include "25lc640.h"
#include "eeprom_map.h"
#include "control.h"
#include "uart0.h"
#include "cmd.h"
#include "gran.h"
#include "common_func.h"
#include "avar_hndl.h"


char bRXIN1;
char UIB1[20];
char flag1;
char rx_buffer1[RX_BUFFER_SIZE1];
char tx_buffer1[TX_BUFFER_SIZE1];
unsigned short rx_wr_index1,rx_rd_index1,rx_counter1;
unsigned short tx_wr_index1,tx_rd_index1,tx_counter1;
char rx_buffer_overflow1;
char plazma_uart1;
char uart1_mess[10];
char data_rs1[40];
enum_usart1_router_stat usart1_router_stat;
char usart1_router_wrk;
char memo_out1[100];
//char suzz[4];
char UIB10[30];
char usart1_router_cnt;
char plazma_suz[5];
//-----------------------------------------------
void putchar1(char c)
{
while (tx_counter1 == TX_BUFFER_SIZE1);
if (tx_counter1 || ((U1LSR & 0x60)==0))
   {
   tx_buffer1[tx_wr_index1]=c;
   if (++tx_wr_index1 == TX_BUFFER_SIZE1) tx_wr_index1=0;
   ++tx_counter1;
   }
else U1THR=c;
}

//-----------------------------------------------
void uart_out1 (char num,char data0,char data1,char data2,char data3,char data4,char data5)
{                
char i,t=0;
//char *ptr=&data1;
char UOB1[16]; 
UOB1[0]=data0;
UOB1[1]=data1;
UOB1[2]=data2;
UOB1[3]=data3;
UOB1[4]=data4;
UOB1[5]=data5;

for (i=0;i<num;i++)
	{
	t^=UOB1[i];
	}    
UOB1[num]=num;
t^=UOB1[num];
UOB1[num+1]=t;
UOB1[num+2]=END;

for (i=0;i<num+3;i++)
	{
	putchar1(UOB1[i]);
	}   	
}

//-----------------------------------------------
void uart_out_adr1 (char *ptr, unsigned char len)
{
char UOB[300]/*={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}*/;
unsigned char i,t=0;

//suzz[3]++;

for(i=0;i<len;i++)
	{
	UOB[i]=ptr[i];
	t^=UOB[i];
	}

UOB[len]=len;
t^=len;	
UOB[len+1]=t;	
UOB[len+2]=END;
 
for (i=0;i<len+3;i++)
	{
	putchar1(UOB[i]);
	}   
}
//-----------------------------------------------
void uart1_init(void)
{

SET_REG(PINSEL0,1,8*2,2);
SET_REG(PINSEL0,1,9*2,2);

SET_REG(U1LCR,1,7/*DLAB*/,1);//U0LCR_bit.DLAB=1;
U1DLL=(unsigned)(60000000UL/(BAUD_RATE1*16));
U1DLM=(unsigned)(60000000UL/(BAUD_RATE1*16*256));
SET_REG(U1LCR,0,7/*DLAB*/,1);//U0LCR_bit.DLAB=0;
U1LCR=0x03;
U1FCR=0;

VICProtection = 0;
VICIntEnClr |= (1 << VIC_UART1); 
VICIntSelect &= ~(1 << VIC_UART1);
VICVectAddr3=(unsigned)uart1_interrupt;
VICVectCntl3 = 0x20 | VIC_UART1;
VICIntEnable |= (1  << VIC_UART1);

U1IER=0x03;



}


//-----------------------------------------------
char getchar1(void)
{
char data;
while (rx_counter1==0);
data=rx_buffer1[rx_rd_index1];
if (++rx_rd_index1 == RX_BUFFER_SIZE1) rx_rd_index1=0;
--rx_counter1;
return data;
}

//***********************************************
__irq void uart1_interrupt(void)
{
char /*status,*/u1iir,data;

//status=U1LSR;
u1iir=U1IIR;
   	
if((u1iir&0x0f)==4)
	{
	data=U1RBR;
	rx_buffer1[rx_wr_index1]=data;
   	bRXIN1=1;
  	if (++rx_wr_index1 == RX_BUFFER_SIZE1) rx_wr_index1=0;
   	if (++rx_counter1 == RX_BUFFER_SIZE1)
      	{
      	rx_counter1=0;
      	rx_buffer_overflow1=1;
      	}
     
   	}
else if((u1iir&0x0f)==2)
	{
	if (tx_counter1)
   		{
   		//usart1_router_wrk=1;
   		--tx_counter1;
   		U1THR=tx_buffer1[tx_rd_index1];
   		if (++tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
   		}
   	else if(usart1_router_stat==ursXPORT)usart1_router_wrk=0;	
	} 
VICVectAddr = 0;  	
}
 

//-----------------------------------------------
void uart_in_an1(void)
{
char i;
//motor_ind[0]^=0b0001000;
plazma_suz[0]++;

if(UIB1[1]!=0x51)
{
for(i=0;i<24;i++)
	{
	UIB10[i]=UIB1[i];
	}
}
uart1_mess[0]++;

if((UIB1[0]==0x55)&&(UIB1[1]==0x66))
	{
	
	uart_out1(2,0x57,0x66,0,0,0,0);
	}

else if((UIB1[0]==CMND)&&(UIB1[1]==1))
	{
//	adc_buff_out_[0]=UIB1[2]+(UIB1[3]*256);
//	adc_buff_out_[1]=UIB1[4]+(UIB1[5]*256);
	}

else if((UIB1[0]==CMND)&&(UIB1[1]==2))
	{
//	adc_buff_out_[2]=UIB1[2]+(UIB1[3]*256);
//	in_stat_out[0]=UIB1[4];
//	in_stat_out[1]=UIB1[5];
	}
	
else if((UIB1[0]==CMND)&&(UIB1[1]==QWEST)&&(UIB1[2]==PUTTM))
	{
//	adc_buff_out_[0]=UIB1[3]+(UIB1[4]*256);
//	adc_buff_out_[1]=UIB1[5]+(UIB1[6]*256);
//	adc_buff_out_[2]=UIB1[7]+(UIB1[8]*256);
//	in_stat_out[0]=UIB1[9];
//	in_stat_out[1]=UIB1[10];
//	in_stat_out[2]=UIB1[11];
//	in_stat_out[3]=UIB1[12];	
	}	


		
if((UIB1[0]==0x55)&&(!PT1)&&(!UIB1[2])&&(!UIB1[3])&&
	(((UIB1[4]&0xf0)==0x10)||((UIB1[4]&0xf0)==0x20))&&((UIB1[4]&0x0f)==0x0a)
	&&(UIB1[(UIB1[1]&0x1f)+5]==crc_87(UIB1,(UIB1[1]&0x1f)+5))&&(UIB1[(UIB1[1]&0x1f)+6]==crc_95(UIB1,(UIB1[1]&0x1f)+5)))
	{
	//suz[1]++;
	//suz[0]++;
	//suz
	//((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==1)&&(UIB1[5]==1))
	
	if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==4)&&(UIB1[5]==2)&&(UIB1[6]==2))
		{
		//suz[2]++;
		if((UIB1[7]==1)&&(UIB1[8]==1)) 
			{
			lc640_write_int(EE_MAIN_IST,0);
/////			cnt_src[1]=10;
			}
		else if((UIB1[7]==2)&&(UIB1[8]==2))
			{
			lc640_write_int(EE_MAIN_IST,1);
/////			cnt_src[0]=10;
			}
		
/////		St_[0]&=0x63;
/////		St_[1]&=0x63;
		
     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+4;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=0x02;
     	memo_out1[6]=0x02;
     	memo_out1[7]=UIB1[7];
     	memo_out1[8]=UIB1[8];
     	memo_out1[9]=crc_87(memo_out1,9);
		memo_out1[10]=crc_95(memo_out1,9);
     	uart_out_adr1(memo_out1,11); 
     	
		} 
	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==3)&&(UIB1[5]==3)&&(UIB1[6]==3))
		{ 
plazma_uart1++;
/////		if(!(St&0x03)&&(NUMBAT))
			{
/////			spc_stat=spc_VZ;
/////			cnt_vz_sec_=3600UL*UIB1[7];
			memo_out1[6]=0xff;
			}
/////		else
 			{
 			memo_out1[6]=0x01;	
 			}	


     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+2;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=0x03;
     	
         	memo_out1[7]=crc_87(memo_out1,7);
		memo_out1[8]=crc_95(memo_out1,7);
     	uart_out_adr1(memo_out1,9); 		
     	

		}
		
	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==2)&&(UIB1[5]==7)&&(UIB1[6]==7))
		{ 

/////		spc_stat=spc_OFF;
				
     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+2;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=0x07;
     	memo_out1[6]=0xff;
         	memo_out1[7]=crc_87(memo_out1,7);
		memo_out1[8]=crc_95(memo_out1,7);
     	uart_out_adr1(memo_out1,9); 		
     	
  
		}			

	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==2)&&(UIB1[5]==4)&&(UIB1[6]==4))
		{ 
 ///// 		if(!(St&0x02)&&(NUMBAT))
			{
/////			spc_stat=spc_KE;
			//zar_cnt_ee_ke=0;
////			zar_cnt=0L;
			memo_out1[6]=0xff;
			}
/////		else
			{
			memo_out1[6]=0x01;	
			}		        
		
     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+2;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=0x04;
     	
         	memo_out1[7]=crc_87(memo_out1,7);
		memo_out1[8]=crc_95(memo_out1,7);
     	uart_out_adr1(memo_out1,9); 		
     	
     	}		    

	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==2)&&(UIB1[5]==8)&&(UIB1[6]==8))
		{ 

////    		spc_stat=spc_OFF;

     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+2;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=0x08;
     	memo_out1[6]=0xff;
         	memo_out1[7]=crc_87(memo_out1,7);
		memo_out1[8]=crc_95(memo_out1,7);
     	uart_out_adr1(memo_out1,9); 		
     	

		}
		
	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==2)&&(UIB1[5]==6)&&(UIB1[6]==6))
		{ 
		//plazma++;
     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+2;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=0x06;
     	memo_out1[6]=0x06;
         	memo_out1[7]=crc_87(memo_out1,7);
		memo_out1[8]=crc_95(memo_out1,7);
     	uart_out_adr1(memo_out1,9); 		
     	
		}	

	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==4)&&(UIB1[5]==5)&&(UIB1[6]==5)&&(UIB1[7]==1)&&(UIB1[8]==1))
		{ 
  		
/////		St_[0]|=0x20;
/////		St_[1]&=0xdf;
/////		St&=0xfb;
/////		cnt_imax=0;  
/////		cnt_src[1]=10;
/////		cnt_alias_blok=60;
		
     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+4;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=5;
     	memo_out1[6]=5; 
     	memo_out1[7]=1;
     	memo_out1[8]=1;     	
         	memo_out1[9]=crc_87(memo_out1,9);
		memo_out1[10]=crc_95(memo_out1,9);
     	uart_out_adr1(memo_out1,11); 		
     	
     	
		}	

	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==4)&&(UIB1[5]==5)&&(UIB1[6]==5)&&(UIB1[7]==2)&&(UIB1[8]==2))
		{ 

/////		St_[1]|=0x20;
/////		St_[0]&=0xdf;
/////		St&=0xfb;
/////		cnt_imax=0;  
/////		cnt_src[0]=10;
/////		cnt_alias_blok=60;
		
     	memo_out1[0]=0x55;
     	memo_out1[1]=0x20+4;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0);
     	memo_out1[5]=5;
     	memo_out1[6]=5; 
     	memo_out1[7]=2;
     	memo_out1[8]=2;     	
         	memo_out1[9]=crc_87(memo_out1,9);
		memo_out1[10]=crc_95(memo_out1,9);
     	uart_out_adr1(memo_out1,11); 		
     	
     		
     	

		}	

	else if((C_D1)&&(FR1)&&((UIB1[1]&0x1f)==1)&&(UIB1[5]==1))
		{
		
		//suz[1]++;
		//suz[2]++;
//		plazma++;
		uart1_mess[1]++;
		
		memo_out1[0]=0x55;
     	memo_out1[1]=0x1D;
     	memo_out1[2]=0;
     	memo_out1[3]=0;
     	memo_out1[4]=((UIB1[4]>>4)&0x0f)+((UIB1[4]<<4)&0xf0); 
     	memo_out1[5]=0x01;
     	memo_out1[6]=data_rs1[0];
		memo_out1[7]=data_rs1[1];
		memo_out1[8]=data_rs1[2];
		memo_out1[9]=data_rs1[3];
		memo_out1[10]=data_rs1[4];
		memo_out1[11]=data_rs1[5];
		memo_out1[12]=data_rs1[6];
    		memo_out1[13]=data_rs1[7];
		memo_out1[14]=data_rs1[8];													
		memo_out1[15]=data_rs1[9];
		memo_out1[16]=data_rs1[10];
		memo_out1[17]=data_rs1[11];
		memo_out1[18]=data_rs1[12];
		memo_out1[19]=data_rs1[13];
		memo_out1[20]=data_rs1[14];
		memo_out1[21]=data_rs1[15];
		memo_out1[22]=data_rs1[16];
		memo_out1[23]=data_rs1[17]; 
		memo_out1[24]=data_rs1[18];													
		memo_out1[25]=data_rs1[19];
		memo_out1[26]=data_rs1[20];
		memo_out1[27]=data_rs1[21];
		memo_out1[28]=data_rs1[22];
		memo_out1[29]=data_rs1[23];
		memo_out1[30]=data_rs1[24];
		
		memo_out1[31]=crc_87(memo_out1,31);
		memo_out1[32]=crc_95(memo_out1,31);
	
          uart_out_adr1(memo_out1,33); 
		}					
	
	}	
	
if((UIB1[0]==0x33)&&(UIB1[4+UIB1[2]]==crc_87(UIB1,4+UIB1[2]))&&(UIB1[5+UIB1[2]]==crc_95(UIB1,4+UIB1[2])))
	{
	
 	if((UIB1[1]==0x51)&&(UIB1[4]==1))
		{
		unsigned char lengt,i;
		
		//plazma_suz[1]++;
		lengt=83;

		lengt+=NUMBAT*13;
		lengt+=NUMIST*10;
		//lengt+=3*4;
		//lengt+=4*2;
		
		//lengt=30;

		memo_out1[0]=0x33;
		memo_out1[1]=0x61;
	    	memo_out1[2]=lengt;
	    	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;		
	    	


	     memo_out1[4]=0x01;       //ответ на запрос телеметрии

		memo_out1[5]=NUMBAT;	//Структура - количество введенных батарей.
		memo_out1[6]=NUMIST;	//Структура - количество БПСов в структуре.
		memo_out1[7]=0/*K[NUMINV]*/;	//Структура - количество инверторов в структуре.
		memo_out1[8]=3;//Структура - количество внешних датчиков температур.
		memo_out1[9]=4;	// Структура - количество внешних логических входов(сухие контакты).
		memo_out1[10]=0;	//Структура, количество внешних исполнительных устройств
		
		memo_out1[11]=10;	//Первая плата расширения.
		memo_out1[12]=10;	//Наличие блока информации о климатконтроле.
		memo_out1[13]=0;	//Резерв, не анализируется.


		memo_out1[14]=23;	//Номер байта, с которого начинается блок информации о первичной сети питания.
		memo_out1[15]=30;	//Номер байта, с которого начинается блок информации о нагрузке.
		
		
		lengt=36;
		memo_out1[16]=lengt;	//Номер байта, с которого начинается блок информации о батареях (Если 0xFF, то информация о батареях не передается).
	    	if(memo_out1[5]==0)memo_out1[16]=0xff;
		              
		lengt+=(13*memo_out1[5]);
		memo_out1[17]=lengt;	//Номер байта, с которого начинается блок информации о БПСах (Если 0xFF, то информация о БПСах не передается).
		if(NUMIST==0)memo_out1[17]=0xff;
		
		lengt+=(10*NUMIST);
		memo_out1[18]=lengt;//Номер байта, с которого начинается блок информации об инверторах (Если 0xFF, то информация об инверторах не передается).
          /*if(K[NUMINV]==0)*/memo_out1[18]=0xff;
           
          //lengt+=0;
		memo_out1[19]=lengt;	//Номер байта, с которого начинается блок информации об внешних датчиках температуры (Если 0xFF, то информация об внешних датчиках температуры не передается).
          //if(NUMDT==0)memo_out1[19]=0xff;
          
          lengt+=(4*3);
		memo_out1[20]=lengt;	//Номер байта, с которого начинается блок информации об внешних логических входах (Если 0xFF, то информация об внешних логических входах  не передается).
          //if(NUMSK==0)memo_out1[20]=0xff;
 
 
          lengt+=(2*4);
		memo_out1[21]=lengt;	//Номер байта, с которого начинается блок информации об спецфункциях

          lengt+=1;
		memo_out1[22]=0xff;	//Номер байта, с которого начинается блок информации об исполнительных устройствах

          //lengt+=1;
		memo_out1[23]=lengt;	//Номер байта, с которого начинается блок информации об параметрах платы расширения
		
		lengt+=14;
		memo_out1[24]=lengt;	//Номер байта, с которого начинается блок информации о климатконтроле

          //Блок информации о первичной сети питания

          lengt=memo_out1[14]+4;
          
		//net_F=plazma_suz[1]++;
		//net_U=234;
		               //net_U=plazma_suz[0];
  		memo_out1[lengt++]=(char)net_U;		//Напряжение питающей сети (дискретность 1В), младший байт.
		memo_out1[lengt++]=(char)(net_U/256);	//Напряжение питающей сети (дискретность 1В), старший байт.
		memo_out1[lengt++]=(char)net_F;		//Частота питающей сети (дискретность 0,1Гц), младший байт.
		memo_out1[lengt++]=(char)(net_F/256);	//Частота питающей сети (дискретность 0,1Гц), старший байт.
		memo_out1[lengt++]=1;	//Резерв, не анализируется.
		memo_out1[lengt++]=1;	//Резерв, не анализируется.
		memo_out1[lengt]=2;	// Байт состояния питающей сети.
          if(avar_stat&0x0001) memo_out1[lengt]|=0x01;
		//0	0	0	0	0	0	F	А
		//А: Авария(1 - активно).
		//F: 0 - частота не измеряется, байты 2 3 блока информации о нагрузке не анализируются, информация о частоте сети на экран терминальной программы не выводится.

		//Блок информации о нагрузке
		lengt=memo_out1[15]+4;

		//load_U=1234;
		//load_I=4321;
		memo_out1[lengt++]=(char)load_U; 		//Напряжение нагрузки (дискретность 100мВ), младший байт.
		memo_out1[lengt++]=(char)(load_U/256); 	//Напряжение нагрузки (дискретность 100мВ), старший байт.
		memo_out1[lengt++]=(char)load_I; 		//Ток нагрузки (дискретность 100мА), младший байт.
		memo_out1[lengt++]=(char)(load_I/256); 	//Ток нагрузки (дискретность 100мА), старший байт.
		memo_out1[lengt++]=1; //Резерв, не анализируется.
		memo_out1[lengt++]=1; //Резерв, не анализируется.

		//Блок информации о батареях
          
		if(memo_out1[16]!=0xff)
			{
			lengt=memo_out1[16]+4;

			for(i=0;i<memo_out1[5];i++)
				{
				char ttt;
				//bat[i]._Ub=345+i;
				memo_out1[lengt++]=i+1; 	//Номер батареи(начиная с 1). Если 0xFF, то на экране программы батарея не нумеруется.
				memo_out1[lengt++]=(char)bat[i]._Ub; 		//Напряжение батареи (дискретность 100мВ), младший байт.
				memo_out1[lengt++]=(char)(bat[i]._Ub/256); //Напряжение батареи (дискретность 100мВ), старший байт.
				memo_out1[lengt++]=(char)bat[i]._Ib; 		//Ток батареи (дискретность 10мА, со знаком), младший байт.
				memo_out1[lengt++]=(char)((bat[i]._Ib)>>8); 	//Ток батареи (дискретность 10мА, со знаком), старший байт.
				memo_out1[lengt++]=(char)bat[i]._Tb; 		//Температура батареи (дискретность ?С, со знаком), младший байт.
				memo_out1[lengt++]=(char)(bat[i]._Tb/256); //Температура батареи (дискретность ?С, со знаком), старший байт.
				
				ttt=0; 
				if((bat[i]._av)&0x01)ttt|=0x01;
				if(bat[i]._Ib>0)ttt|=0x02;
				if((bat[i]._av)&0x02)ttt|=0x04;
				if((bat[i]._Ub<(USIGN*10))&&(BAT_IS_ON[i]==bisON))ttt|=0x08;
				memo_out1[lengt++]=ttt; //Байт состояния батареи.
				
				//0	0	0	0	0	AS	Z	А
	               //А: Авария(1 - активно) - батарея не выявлена в ходе последнего контроля наличия батареи(на экране терминальной программы все графы данной батареи заменить надписью "Авария, батарея отсутствует")
				//Z: Заряд:  если 1 - батарея заряжается. 
				//AS: Асимметрия батареи: если 1 - аварийное состояние
			     
				if(BAT_C_REAL[i]==0x5555)
					{
					memo_out1[lengt++]=(char)(BAT_C_NOM[i]*10); //Емкость батареи (дискретность 100мА*Ч), младший байт.
					memo_out1[lengt++]=(char)((BAT_C_NOM[i]*10)/256); //Емкость батареи (дискретность 100мА*Ч), старший байт.//Если емкость батареи 0xFFFF, то в графе "Емкость" прочерк.
					}
				else
					{	
					memo_out1[lengt++]=(char)BAT_C_REAL[i]; //Емкость батареи (дискретность 100мА*Ч), младший байт.
					memo_out1[lengt++]=(char)(BAT_C_REAL[i]/256); //Емкость батареи (дискретность 100мА*Ч), старший байт.//Если емкость батареи 0xFFFF, то в графе "Емкость" прочерк.
		    	    		}
		    	    	
		    	    	    	
		    	    	
		    	    	if(BAT_C_REAL[i]==0x5555)memo_out1[lengt++]=0xff;//Заряд батареи в %..
		    	    	else memo_out1[lengt++]=bat[i]._zar;

		    		memo_out1[lengt++]=1; //Резерв, не анализируется.
				memo_out1[lengt++]=1; //Резерв, не анализируется.
	   			}
         		}       
                
		//Блок информации об БПСах

		if(memo_out1[17]!=0xff)
			{
			lengt=memo_out1[17]+4;

			for(i=0;i<memo_out1[6];i++)
				{
				
				//char src_off;
				
				/////if(i==0)src_off=OFFBP1;
				/////else src_off=OFFBP2;
				
				
				
				memo_out1[lengt++]=i+1; //Номер БПСа (начиная с 1).
	    			memo_out1[lengt++]=(char)(bps[i]._Uii); 		//Напряжение БПСа (дискретность 100мВ), младший байт.
				memo_out1[lengt++]=(char)((bps[i]._Uii)>>8); 	//Напряжение БПСа (дискретность 100мВ), старший байт.
				memo_out1[lengt++]=(char)(bps[i]._Ii); 			//Ток БПСа (дискретность 100мА), младший байт.
				memo_out1[lengt++]=(char)((bps[i]._Ii)>>8); 		//Ток БПСа (дискретность 100мА), старший байт.
				memo_out1[lengt++]=(char)(bps[i]._Ti); 			//Температура БПСа (дискретность ?С, со знаком), младший байт.
				memo_out1[lengt++]=(char)((bps[i]._Ti)>>8); 		//Температура БПСа (дискретность ?С, со знаком), старший байт.
				
				memo_out1[lengt]=0; 							//Байт состояния БПСа.
                    if(bps[i]._av&(1<<2))memo_out1[lengt]=BIN8(1000); //авария по Umin
				else if(bps[i]._av&(1<<1))memo_out1[lengt]=BIN8(100); //авария по Umax
				else if(bps[i]._av&(1<<0))memo_out1[lengt]=BIN8(10); //авария по Tmax
				else if(bps[i]._state==bsBL)memo_out1[lengt]=BIN8(100000); //заблокирован
				else if(bps[i]._state==bsWRK)memo_out1[lengt]=BIN8(1); //Работает
				//0	0	EB 	АС	AM	AU	АT	W
                    lengt++;
				//W: Рабочее состояние (1 - активно) - БПС в работе.(На экране параметры работы БПСа)
 				//Если 0 то по-порядку анализируются биты:
				//AT: Авария по перегреву БПСа (1 - активно), ("Перегрев").
				//AU: Авария по заниженному напряжению (1 - активно), ("Занижено Uвых").
				//AM: Авария по завышенному напряжению (1 - активно), ("Завышено Uвых").
				//AC: Авария по отсутствию связи с БПС (1 - активно), ("Разрыв связи").
				//EB: Внешняя блокировка БПС (заблокирован по связи оператором), ("Заблокирован извне").
				//Если 5 вышеперечисленных битов в нуле, значит ("В резерве"). 
                   	
				memo_out1[lengt++]=1; //Резерв, не анализируется.
				memo_out1[lengt++]=1; //Резерв, не анализируется.
                    }     
   
               }
 
 		//Блок информации о внешних датчиках температуры
 		if(memo_out1[19]!=0xff)
			{
			lengt=memo_out1[19]+4;

			for(i=0;i<memo_out1[8];i++)
				{
				memo_out1[lengt++]=i+1; 					//Номер датчика температуры.
				memo_out1[lengt++]=(char)t_ext[i]; 		//Температура датчика (дискретность ?С, со знаком), младший байт.
				memo_out1[lengt++]=(char)(t_ext[i]/256); 	//Температура датчика (дискретность ?С, со знаком), старший байт.
				memo_out1[lengt]=0; 					//Байт состояния датчика 
				if(ND_EXT[i]) memo_out1[lengt]|=0x01;
				lengt++;
				}
         		}       

 		if(memo_out1[20]!=0xff)
			{
			lengt=memo_out1[20]+4;

			for(i=0;i<memo_out1[9];i++)
				{
				memo_out1[lengt++]=i+1; 					//Номер сухого контакта.
				memo_out1[lengt]=0; 		               
				if(sk_stat[i]==ssON)memo_out1[lengt]|=0x01;
				if(sk_av_stat[i]==sasON)memo_out1[lengt]|=0x02;
                    lengt++;
				}
         		} 
               
          lengt=memo_out1[21]+4;     
          if(spc_stat==spcOFF) memo_out1[lengt++]=0;
          else if(spc_stat==spcKE)
               {
               if(spc_bat==0)memo_out1[lengt++]=1;
               else if(spc_bat==1)memo_out1[lengt++]=2;
               }
          else if(spc_stat==spcVZ) memo_out1[lengt++]=10;

		//memo_out1[lengt++]=0;
		/////if(lc640_read_int(EE_IU1))memo_out0[lengt]|=0x01;;
          /////if(lc640_read_int(EE_IU2))memo_out0[lengt]|=0x02;
		/////if(lc640_read_int(EE_IU3))memo_out0[lengt]|=0x04;
		/////if(lc640_read_int(EE_IU4))memo_out0[lengt]|=0x08;
		     

          
          lengt=memo_out1[23]+4;

              /*Uvv[0]=201;
              Uvv[1]=202;
              Uvv[3]=203;

              vvod_pos=2;*/  
              //power_current=432;
              //power_summary=123456789;

		memo_out1[lengt++]=(char)Uvv0; 		//Напряжение ввода 1, младший байт.
		memo_out1[lengt++]=(char)(Uvv0/256); 	//Напряжение ввода 1, старший байт.
		memo_out1[lengt++]=(char)Uvv[1]; 		//Напряжение ввода 2, младший байт.
		memo_out1[lengt++]=(char)(Uvv[1]/256); 	//Напряжение ввода 2, старший байт.
		memo_out1[lengt++]=(char)Uvv[1]; 		//Напряжение ПЭС, младший байт.
		memo_out1[lengt++]=(char)(Uvv[1]/256); 	//Напряжение ПЭС, старший байт.
		memo_out1[lengt++]=(char)power_current; 		//мгновенная мощность, младший байт.
		memo_out1[lengt++]=(char)(power_current/256); 	//мгновенная мощность, старший байт.
		memo_out1[lengt++]=*((char*)&power_summary); 		//суммарная потребленная мощность, младший байт.
		memo_out1[lengt++]=*(((char*)&power_summary)+1); 	     //суммарная потребленная мощность, 1-й байт.
		memo_out1[lengt++]=*(((char*)&power_summary)+2); 		//суммарная потребленная мощность, 2-й байт.
		memo_out1[lengt++]=*(((char*)&power_summary)+3); 	     //суммарная потребленная мощность, старший байт.
		memo_out1[lengt++]=(char)pos_vent; 		          //Позиция регулятора вентилятора.
		memo_out1[lengt++]=(char)vvod_pos; 	               //Активный ввод

		//Блок информации о климат-контроле.
          lengt=memo_out1[24]+4;
		memo_out1[lengt++]=(char)t_box; 		//Температура шкафа, младший байт.
		memo_out1[lengt++]=(char)(t_box/256); 	//Температура шкафа, старший байт.
		if(av_tbox_stat==atsON)memo_out1[lengt++]=1;	//Аварийность температуры шкафа
		else if(av_tbox_stat!=atsON)memo_out1[lengt++]=0;
		
		if((tloaddisable_cmnd>=0)&&(tloaddisable_cmnd<=11))memo_out1[lengt++]=5;
		else if(tloaddisable_stat==tldsON)memo_out1[lengt++]=0;	//Включенность нагрузки
		else if(tloaddisable_stat==tldsOFF)memo_out1[lengt++]=1;
		else if(tloaddisable_stat==tldsMNL)memo_out1[lengt++]=5;

		memo_out1[lengt++]=tloaddisable_cmnd; 		//Переменная, управляющая включением нагрузки.

		if((tbatdisable_cmnd>=0)&&(tbatdisable_cmnd<=11))memo_out1[lengt++]=5;
		else if(tbatdisable_stat==tbdsON)memo_out1[lengt++]=0;	//Включенность батареи
		else if(tbatdisable_stat==tbdsOFF)memo_out1[lengt++]=1;
		else if(tbatdisable_stat==tbdsMNL)memo_out1[lengt++]=5;

		memo_out1[lengt++]=tbatdisable_cmnd; 		//Переменная, управляющая включением батареи.

		memo_out1[lengt++]=main_vent_pos; 			//позиция вентилятора.

          memo_out1[memo_out1[2]+4]=crc_87(memo_out1,memo_out1[2]+4);
		memo_out1[memo_out1[2]+5]=crc_95(memo_out1,memo_out1[2]+4);
		uart_out_adr1(memo_out1,memo_out1[2]+6);
		//uart_out_adr1(dig,150);
//		plazma_suz[0]=memo_out1[2]+6;
		/*
		memo_out0[0]=0x33;
		memo_out0[1]=0x61;
		memo_out0[2]=60;
		memo_out0[3]=lengt;
		memo_out0[64]=crc_87(memo_out0,64);
		memo_out0[65]=crc_95(memo_out0,64);
		uart_out_adr1(memo_out0,66);*/
		
		          
 		}
		

/*Блок информации о внешних датчиках температуры

Байт данных [0]: Номер датчика (начиная с 1).
Байт данных [1]: Температура датчика (дискретность ?С, со знаком), младший байт.
Байт данных [2]: Температура датчика (дискретность ?С, со знаком),  старший байт.
Байт данных [3]: Байт состояния датчика.

0	0	0 	0	0	0	АT	A

А: Неисправность датчика (1 - активно), ("Датчик неисправен")
AT: Авария по температуре (1 - активно), ("Температура датчика не в допуске").

Блок информации о внешних логических входах

Байт данных [0]: Номер входа (начиная с 1).
Байт данных [1]: Байт состояния входа.

0	0	0 	0	0	0	АT	A

А: Активность входа (1 - активно), ("Состояние активное/неактивное")
AВ: Аварийность входа (1 - активно), ("Авария").*/

	else if((UIB1[1]==0x52)&&(UIB1[4]==2)&&(UIB1[5]==2))   //установить основной БПС
		{
		//suzz[2]++;
		if((UIB1[6]==1)&&(UIB1[7]==1)) 
			{
			lc640_write_int(EE_MAIN_IST,0);
			/////cnt_src[1]=10;
			}
		else if((UIB1[6]==2)&&(UIB1[7]==2))
			{
			lc640_write_int(EE_MAIN_IST,1);
			/////cnt_src[0]=10;
			}
		
		/////St_[0]&=0x63;
		/////St_[1]&=0x63;
		
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=4;
     	memo_out1[3]=0x03;
     	
     	memo_out1[4]=UIB1[4];
     	memo_out1[5]=UIB1[5];
     	memo_out1[6]=UIB1[6];
     	memo_out1[7]=UIB1[7];
     	
         	memo_out1[8]=crc_87(memo_out1,8);
		memo_out1[9]=crc_95(memo_out1,8);
     	uart_out_adr1(memo_out1,10); 		
		}			

	else if((UIB1[1]==0x52)&&(UIB1[4]==9)&&(UIB1[5]==9))   //Включить параллельную работу
		{
          //plazma_suz[2]++;
		lc640_write_int(EE_PAR,1);

     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=9;
     	memo_out1[5]=0xff;
     	
         	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
		}			

	else if((UIB1[1]==0x52)&&(UIB1[4]==10)&&(UIB1[5]==10))   //Выключить параллельную работу
		{
          ///plazma_suz[3]++;
		lc640_write_int(EE_PAR,0);

     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=10;
     	memo_out1[5]=0xff;
     	
         	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
		}			


	else if((UIB1[1]==0x52)&&(UIB1[4]==3)&&(UIB1[5]==3))   //выравнивающий заряд старт
		{
          //plazma_suz[2]++;
          //plazma_suz[3]=UIB1[6];
          //
		if(!(avar_stat&0x07)&&(NUMBAT))
			{
          	char temp;
          	temp=vz_start(UIB1[6]);
          	if((temp==22)||(temp==33)) 
          		{
          		memo_out1[5]=0x01;
          		} 
			else  
          		{
				memo_out1[5]=0xff;
          		}          
			
			}
		else
 			{
 			memo_out1[5]=0x01;	
 			}	
		
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=0x03;
     	
     	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
		}			

	else if((UIB1[1]==0x52)&&(UIB1[4]==4)&&(UIB1[5]==4) /*&& ((UIB1[6]==1)||(UIB1[6]==2))*/ )	//контроль емкости старт 	
		{
          //plazma_suz[2]++;
          //plazma_suz[3]=UIB1[6];
          ke_start(UIB1[6]-1);
		if(ke_start_stat==kssYES) memo_out1[5]=0xff;
          else memo_out1[5]=0x01;

		memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	memo_out1[4]=4;
          	
         	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
     		
		}	
	
	else if((UIB1[1]==0x52)&&(UIB1[4]==5)&&(UIB1[5]==5)&&(UIB1[6])&&(UIB1[6]<=NUMIST)&&(UIB1[6]==UIB1[7])) 	//Выключение источника 
		{
          //plazma_suz[2]++;
          //plazma_suz[3]=UIB1[6];
          bps[UIB1[6]-1]._ist_blok_host_cnt=3000;
		
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=4;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=5;
     	memo_out1[5]=5;
     	memo_out1[6]=UIB1[6];
     	memo_out1[7]=UIB1[6];
         	memo_out1[8]=crc_87(memo_out1,8);
		memo_out1[9]=crc_95(memo_out1,8);
     	uart_out_adr1(memo_out1,10); 		
		}
		

	else if((UIB1[1]==0x52)&&(UIB1[4]==7)&&(UIB1[5]==7))	//Выключение спецфункций
		{
		
		spc_stat=spcOFF;
		memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	memo_out1[4]=7;
     	memo_out1[5]=0xff;
     	
         	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
		}					
		
	else if((UIB1[1]==0x52)&&(UIB1[4]==8)&&(UIB1[5]==8))	//Разблокировать источники
		{      
		char i;

          for(i=0;i<NUMIST;i++)
               {
               bps[i]._ist_blok_host_cnt=0;
               }
		
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=8;
     	memo_out1[5]=0xff;
     	
         	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
		}		


	else if((UIB1[1]==0x52)&&(UIB1[4]==37))	//Изменить состояние исполнительных устройств
		{      
		
		/////if(UIB1[5]&0x01)
		/////	{
		/////	if(UIB1[6]&0x01)lc640_write_int(EE_IU1,1);
		/////	else lc640_write_int(EE_IU1,0);
		/////	}

		/////if(UIB1[5]&0x02)
		/////	{
		/////	if(UIB1[6]&0x02)lc640_write_int(EE_IU2,1);
		/////	else lc640_write_int(EE_IU2,0);
		/////	}

		/////if(UIB1[5]&0x04)
		/////	{
		/////	if(UIB1[6]&0x04)lc640_write_int(EE_IU3,1);
		/////	else lc640_write_int(EE_IU3,0);
		/////	}

		/////if(UIB1[5]&0x08)
		/////	{
		/////	if(UIB1[6]&0x08)lc640_write_int(EE_IU4,1);
		/////	else lc640_write_int(EE_IU4,0);
		/////	}
		
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=8;
     	memo_out1[5]=0xff;
     	
         	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
		}


	else if((UIB1[1]==0x51)&&(UIB1[4]==0x0c))
		{
		plazma_suz[1]++;
		
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x61;
     	memo_out1[2]=2;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	memo_out1[4]=0x0c;
     	memo_out1[5]=lc640_read_int(CNT_EVENT_LOG);
		plazma_suz[3]=memo_out1[5];
         	memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 		
		}	

	else if((UIB1[1]==0x51)&&(UIB1[4]==0x0d))
		{
		//char temp;
		unsigned int tempUI/*,tempUI_*/;
		//unsigned long tempUL;
		//char av_head[4]/*,av_data_on[8]/*,av_data_off[8]/*,av_data[4]*/;		
	
		tempUI=lc640_read_int(PTR_EVENT_LOG);
		tempUI=ptr_carry(tempUI,64,-1*(((signed)UIB1[5])-1));
		tempUI*=32;
		tempUI+=EVENT_LOG;	
		
	
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x61;
     	memo_out1[2]=34;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=0x0D;
     	memo_out1[5]=UIB1[5];
     	lc640_read_long_ptr(tempUI,&memo_out1[6]);
     	lc640_read_long_ptr(tempUI+4,&memo_out1[10]);
     	lc640_read_long_ptr(tempUI+8,&memo_out1[14]);
     	lc640_read_long_ptr(tempUI+12,&memo_out1[18]);
     	lc640_read_long_ptr(tempUI+16,&memo_out1[22]);
     	lc640_read_long_ptr(tempUI+20,&memo_out1[26]);
     	lc640_read_long_ptr(tempUI+24,&memo_out1[30]);
     	lc640_read_long_ptr(tempUI+28,&memo_out1[34]);
     	
         	memo_out1[38]=crc_87(memo_out1,38);
		memo_out1[39]=crc_95(memo_out1,38);
     	uart_out_adr1(memo_out1,40); 		
		}	




	else if((UIB1[1]==0x51)&&(UIB1[4]==30)&&(UIB1[5]==30))	//Запрос номера таблицы установок и ее глубины
		{      
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x61;
     	memo_out1[2]=5;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=30;
     	memo_out1[5]=NUM_OF_SET_TABL;
     	memo_out1[6]=NUM_OF_SET_TABL;
     	memo_out1[7]=DEEP_OF_SET_TABL;
     	memo_out1[8]=DEEP_OF_SET_TABL;     	     	     	
     	
         	memo_out1[9]=crc_87(memo_out1,9);
		memo_out1[10]=crc_95(memo_out1,9);
     	uart_out_adr1(memo_out1,11); 		
		}		


	else if((UIB1[1]==0x51)&&(UIB1[4]==31))	//Запрос параметра из таблицы установок 
		{      
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x61;
     	memo_out1[2]=4;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=31;
     	memo_out1[5]=UIB1[5];
     	
     	if(UIB1[5]==20)		*((signed short*)&memo_out1[6])=MAIN_IST;
     	else if(UIB1[5]==40)	*((signed short*)&memo_out1[6])=ZV_ON;
     	else if(UIB1[5]==42)	*((signed short*)&memo_out1[6])=TBAT;
     	else if(UIB1[5]==50)	*((signed short*)&memo_out1[6])=UB0;
     	else if(UIB1[5]==51)	*((signed short*)&memo_out1[6])=UB20;   	     	
     	else if(UIB1[5]==52)	*((signed short*)&memo_out1[6])=USIGN;
    		else if(UIB1[5]==53)	*((signed short*)&memo_out1[6])=UMN;     	
     	else if(UIB1[5]==54)	*((signed short*)&memo_out1[6])=U0B;
     	else if(UIB1[5]==55)	*((signed short*)&memo_out1[6])=IKB;
    		else if(UIB1[5]==56)	*((signed short*)&memo_out1[6])=IZMAX;     	
     	else if(UIB1[5]==57)	*((signed short*)&memo_out1[6])=IMAX;
     	else if(UIB1[5]==58)	*((signed short*)&memo_out1[6])=KIMAX;
     	else if(UIB1[5]==59)	*((signed short*)&memo_out1[6])=KVZ;
    		else if(UIB1[5]==60)	*((signed short*)&memo_out1[6])=TZAS;     	
     	else if(UIB1[5]==61)	*((signed short*)&memo_out1[6])=TMAX;
     	else if(UIB1[5]==71)
     		{
/////     		if(apv_on1==apvON) *((signed short*)&memo_out1[6])=1;
/////     		else *((signed short*)&memo_out1[6])=0;
     		}
    		else if(UIB1[5]==72)	
    			{
    			     		{
 /////    		if(apv_on2==apvON) *((signed short*)&memo_out1[6])=1;
 /////    		else *((signed short*)&memo_out1[6])=0;
     		}

    			}   	
/////     	else if(UIB1[5]==73)	*((signed short*)&memo_out1[6])=apv_on2_time;

          else if(UIB1[5]==80)	*((signed short*)&memo_out1[6])=pos_vent;
     	
         	memo_out1[8]=crc_87(memo_out1,8);
		memo_out1[9]=crc_95(memo_out1,8);
     	uart_out_adr1(memo_out1,10); 		
		}	

	else if((UIB1[1]==0x51)&&(UIB1[4]==33))	//Запрос типа устройства и серийного номера 
		{
//		plazma_suz[2]++;
		      
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x61;
     	memo_out1[2]=6;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=33;
     	
		if(AUSW_MAIN==6024)		memo_out1[5]=1;
		else if(AUSW_MAIN==6012)	memo_out1[5]=2;
		else if(AUSW_MAIN==4824)	memo_out1[5]=3;
		else if(AUSW_MAIN==4812)	memo_out1[5]=4;
		else if(AUSW_MAIN==6010)	memo_out1[5]=5;
		else if(AUSW_MAIN==6005)	memo_out1[5]=6;
		else if(AUSW_MAIN==4810)	memo_out1[5]=7;
		else if(AUSW_MAIN==4805)	memo_out1[5]=8;
		else if(AUSW_MAIN==2424)	memo_out1[5]=9;
		else if(AUSW_MAIN==2412)	memo_out1[5]=10;
		else if(AUSW_MAIN==4840)	memo_out1[5]=11;
		else if(AUSW_MAIN==6030)	memo_out1[5]=12;
		else if(AUSW_MAIN==4820)	memo_out1[5]=13;
		else if(AUSW_MAIN==6015)	memo_out1[5]=14;
		else if(AUSW_MAIN==2450)	memo_out1[5]=15;
		else if(AUSW_MAIN==2425)	memo_out1[5]=16;
		else if(AUSW_MAIN==4860)	memo_out1[5]=17;
		else if(AUSW_MAIN==4880)	memo_out1[5]=18;
		else if(AUSW_MAIN==6020)	memo_out1[5]=19;
		else if(AUSW_MAIN==6040)	memo_out1[5]=20;
		else if(AUSW_MAIN==6060)	memo_out1[5]=21;
		else if(AUSW_MAIN==6080)	memo_out1[5]=22;
		
			
     	
     	//*((long*)&memo_out1[6])=54321;//AUSW_MAIN_NUMBER;
     	
		memo_out1[6]=(char)AUSW_MAIN_NUMBER;
		memo_out1[7]=(char)(AUSW_MAIN_NUMBER>>8);
		memo_out1[8]=(char)(AUSW_MAIN_NUMBER>>16);
		memo_out1[9]=(char)(AUSW_MAIN_NUMBER>>24);
     	
         	memo_out1[10]=crc_87(memo_out1,10);
		memo_out1[11]=crc_95(memo_out1,10);
     	uart_out_adr1(memo_out1,12); 		
		}	

	else if((UIB1[1]==0x51)&&(UIB1[4]==34))	//Запрос типа устройства и серийного номера 
		{
		char* ptr;
		char i;
		ptr="Мама мыла раму. У шуры шары";
		      
     	memo_out1[0]=0x34;
     	memo_out1[1]=0x61;
     	memo_out1[2]=29;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=34;
     	memo_out1[5]=27;
     	
     	for(i=0;i<27;i++)
     		{
     		memo_out1[6+i]=ptr[i];
     		}
    	
         	memo_out1[33]=crc_87(memo_out1,33);
		memo_out1[34]=crc_95(memo_out1,33);
     	uart_out_adr1(memo_out1,35); 		
		}	

 	else if((UIB1[1]==0x52)&&(UIB1[4]==38))	//установка переменной управляющей нагрузкой  
		{      
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=3;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
		tloaddisable_cmnd=UIB1[5];

     	memo_out1[4]=38;
     	memo_out1[5]=0xff;
		
		memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 
		}

 	else if((UIB1[1]==0x52)&&(UIB1[4]==39))	//установка переменной управляющей батареей  
		{      
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=3;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
		tbatdisable_cmnd=UIB1[5];

     	memo_out1[4]=39;
     	memo_out1[5]=0xff;
		
		memo_out1[6]=crc_87(memo_out1,6);
		memo_out1[7]=crc_95(memo_out1,6);
     	uart_out_adr1(memo_out1,8); 
		}

 	else if((UIB1[1]==0x51)&&(UIB1[4]==40))
		{
		unsigned char lengt,i;
		
		lengt=209;

		memo_out1[0]=0x33;
		memo_out1[1]=0x61;
	    	memo_out1[2]=lengt;
	    	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;		
	    	memo_out1[4]=40;       //ответ на запрос телеметрии

		lengt=5;

		memo_out1[lengt++]=26;

		//Основной источник  
		memo_out1[lengt++]=20;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=MAIN_IST;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=1;
		memo_out1[lengt++]=0;

		//Звуковая сигнализация  
		memo_out1[lengt++]=40;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=ZV_ON;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=1;
		memo_out1[lengt++]=0;

		//Время проверки цепи батареи  
		memo_out1[lengt++]=42;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TBAT;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=5;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=60;
		memo_out1[lengt++]=0;

		//Uб0° 
		memo_out1[lengt++]=50;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=UB0%256;
		memo_out1[lengt++]=UB0/256;
		memo_out1[lengt++]=200%256;
		memo_out1[lengt++]=200/256;
		memo_out1[lengt++]=800%256;
		memo_out1[lengt++]=800/256;

		//Uб20° 
		memo_out1[lengt++]=51;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=UB20%256;
		memo_out1[lengt++]=UB20/256;
		memo_out1[lengt++]=200%256;
		memo_out1[lengt++]=200/256;
		memo_out1[lengt++]=800%256;
		memo_out1[lengt++]=800/256;

		//Uсигн 
		memo_out1[lengt++]=52;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=USIGN%256;
		memo_out1[lengt++]=USIGN/256;
		memo_out1[lengt++]=20%256;
		memo_out1[lengt++]=20/256;
		memo_out1[lengt++]=80%256;
		memo_out1[lengt++]=80/256;

		//Umin.сети 
		memo_out1[lengt++]=53;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=UMN%256;
		memo_out1[lengt++]=UMN/256;
		memo_out1[lengt++]=150%256;
		memo_out1[lengt++]=150/256;
		memo_out1[lengt++]=250%256;
		memo_out1[lengt++]=250/256;
		
		//U0б 
		memo_out1[lengt++]=54;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=U0B%256;
		memo_out1[lengt++]=U0B/256;
		memo_out1[lengt++]=200%256;
		memo_out1[lengt++]=200/256;
		memo_out1[lengt++]=800%256;
		memo_out1[lengt++]=800/256;

		//Iбк 
		memo_out1[lengt++]=55;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=IKB%256;
		memo_out1[lengt++]=IKB/256;
		memo_out1[lengt++]=1%256;
		memo_out1[lengt++]=1/256;
		memo_out1[lengt++]=1000%256;
		memo_out1[lengt++]=1000/256;

		//Iз.max 
		memo_out1[lengt++]=56;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=IZMAX%256;
		memo_out1[lengt++]=IZMAX/256;
		memo_out1[lengt++]=10%256;
		memo_out1[lengt++]=10/256;
		memo_out1[lengt++]=1000%256;
		memo_out1[lengt++]=1000/256;

		//Imax 
		memo_out1[lengt++]=57;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=IMAX%256;
		memo_out1[lengt++]=IMAX/256;
		memo_out1[lengt++]=10%256;
		memo_out1[lengt++]=10/256;
		memo_out1[lengt++]=300%256;
		memo_out1[lengt++]=300/256;

		//Kimax 
		memo_out1[lengt++]=58;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=KIMAX%256;
		memo_out1[lengt++]=KIMAX/256;
		memo_out1[lengt++]=5%256;
		memo_out1[lengt++]=5/256;
		memo_out1[lengt++]=10%256;
		memo_out1[lengt++]=10/256;

		//Kвыр.зар. 
		memo_out1[lengt++]=59;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=KVZ%256;
		memo_out1[lengt++]=KVZ/256;
		memo_out1[lengt++]=1005%256;
		memo_out1[lengt++]=1005/256;
		memo_out1[lengt++]=1030%256;
		memo_out1[lengt++]=1030/256;

		//KTз.вкл.а.с. 
		memo_out1[lengt++]=60;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TZAS%256;
		memo_out1[lengt++]=TZAS/256;
		memo_out1[lengt++]=0%256;
		memo_out1[lengt++]=0/256;
		memo_out1[lengt++]=3%256;
		memo_out1[lengt++]=3/256;

		//tmax 
		memo_out1[lengt++]=61;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TMAX%256;
		memo_out1[lengt++]=TMAX/256;
		memo_out1[lengt++]=40%256;
		memo_out1[lengt++]=40/256;
		memo_out1[lengt++]=100%256;
		memo_out1[lengt++]=100/256;

		//АПВ 1-й уровень 
		memo_out1[lengt++]=71;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=APV_ON1%256;
		memo_out1[lengt++]=APV_ON1/256;
		memo_out1[lengt++]=0%256;
		memo_out1[lengt++]=0/256;
		memo_out1[lengt++]=1%256;
		memo_out1[lengt++]=1/256;

		//АПВ 2-й уровень 
		memo_out1[lengt++]=72;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=APV_ON2%256;
		memo_out1[lengt++]=APV_ON2/256;
		memo_out1[lengt++]=0%256;
		memo_out1[lengt++]=0/256;
		memo_out1[lengt++]=1%256;
		memo_out1[lengt++]=1/256;

		//Период АПВ2 
		memo_out1[lengt++]=73;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=APV_ON2_TIME%256;
		memo_out1[lengt++]=APV_ON2_TIME/256;
		memo_out1[lengt++]=1%256;
		memo_out1[lengt++]=1/256;
		memo_out1[lengt++]=24%256;
		memo_out1[lengt++]=24/256;

		//Максимальная позиция вентилятора 
		memo_out1[lengt++]=80;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=pos_vent%256;
		memo_out1[lengt++]=pos_vent/256;
		memo_out1[lengt++]=1%256;
		memo_out1[lengt++]=1/256;
		memo_out1[lengt++]=11%256;
		memo_out1[lengt++]=11/256;

		//Температура шкафа максимальная 
		memo_out1[lengt++]=90;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TBOXMAX%256;
		memo_out1[lengt++]=TBOXMAX/256;
		memo_out1[lengt++]=50%256;
		memo_out1[lengt++]=50/256;
		memo_out1[lengt++]=80%256;
		memo_out1[lengt++]=80/256;

		//Уставка температуры шкафа 
		memo_out1[lengt++]=91;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TBOXREG%256;
		memo_out1[lengt++]=TBOXREG/256;
		memo_out1[lengt++]=5%256;
		memo_out1[lengt++]=5/256;
		memo_out1[lengt++]=30%256;
		memo_out1[lengt++]=30/256;

		//Температура аварийного включения вентилятора
		memo_out1[lengt++]=92;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TBOXVENTMAX%256;
		memo_out1[lengt++]=TBOXVENTMAX/256;
		memo_out1[lengt++]=49%256;
		memo_out1[lengt++]=49/256;
		memo_out1[lengt++]=81%256;
		memo_out1[lengt++]=81/256;

		//Температура отключения нагрузки
		memo_out1[lengt++]=93;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TLOADDISABLE%256;
		memo_out1[lengt++]=TLOADDISABLE/256;
		memo_out1[lengt++]=49%256;
		memo_out1[lengt++]=49/256;
		memo_out1[lengt++]=81%256;
		memo_out1[lengt++]=81/256;

		//Температура включения нагрузки
		memo_out1[lengt++]=94;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TLOADENABLE%256;
		memo_out1[lengt++]=TLOADENABLE/256;
		memo_out1[lengt++]=49%256;
		memo_out1[lengt++]=49/256;
		memo_out1[lengt++]=81%256;
		memo_out1[lengt++]=81/256;

		//Температура отключения батарей
		memo_out1[lengt++]=95;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TBATDISABLE%256;
		memo_out1[lengt++]=TBATDISABLE/256;
		memo_out1[lengt++]=49%256;
		memo_out1[lengt++]=49/256;
		memo_out1[lengt++]=81%256;
		memo_out1[lengt++]=81/256;

		//Температура включения батарей
		memo_out1[lengt++]=96;
		memo_out1[lengt++]=0;
		memo_out1[lengt++]=TBATENABLE%256;
		memo_out1[lengt++]=TBATENABLE/256;
		memo_out1[lengt++]=49%256;
		memo_out1[lengt++]=49/256;
		memo_out1[lengt++]=81%256;
		memo_out1[lengt++]=81/256;

         	memo_out1[214]=crc_87(memo_out1,214);
		memo_out1[215]=crc_95(memo_out1,214);
     	uart_out_adr1(memo_out1,216);

		}

	else if((UIB1[1]==0x52)&&(UIB1[4]==32))	//Изменение параметра из таблицы установок 
		{      
     	memo_out1[0]=0x33;
     	memo_out1[1]=0x62;
     	memo_out1[2]=3;
     	memo_out1[3]=CONTROL_BYTE_FOR_XPORT;
     	
     	memo_out1[4]=32;
     	memo_out1[5]=UIB1[5];
     	
     	memo_out1[6]=0xff;
     	
     	if(UIB1[5]==20)
     		{
     		if(UIB1[6]==0x22)
     			{
     			MAIN_IST=UIB1[7]+(UIB1[8]*256);;
     			}
     		else if( (UIB1[6]==0x33) || (UIB1[6]==0x44) || (UIB1[6]==0x55) || (UIB1[6]==0x66) )
     			{
     			if(MAIN_IST) MAIN_IST=0;
     			else MAIN_IST=1;
     			}
     		
     		gran(&MAIN_IST,0,1);
     		lc640_write_int(EE_MAIN_IST,MAIN_IST);
     		}

     	else if(UIB1[5]==40)
     		{
     		if(UIB1[6]==0x22)
     			{
     			ZV_ON=UIB1[7]+(UIB1[8]*256);;
     			}
     		else if( (UIB1[6]==0x33) || (UIB1[6]==0x44) || (UIB1[6]==0x55) || (UIB1[6]==0x66) )
     			{
     			if(ZV_ON) ZV_ON=0;
     			else ZV_ON=1;
     			}
    			gran(&ZV_ON,0,1);
    			lc640_write_int(EE_ZV_ON,ZV_ON);
     		}	

     	else if(UIB1[5]==42)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=5)&&(ttt<=60))
     				{
     				TBAT=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TBAT++;
      		else if(UIB1[6]==0x44)TBAT+=ttt;
     		else if(UIB1[6]==0x55)TBAT--;
      		else if(UIB1[6]==0x66)TBAT-=ttt;
     			
			gran(&TBAT,5,60);
     		lc640_write_int(EE_TBAT,TBAT);
     		}	
     	else if(UIB1[5]==50)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);//*((unsigned short*)&UIB1[7]);
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=10)&&(ttt<=1000))
     				{
     				UB0=ttt;
     				}
     			else memo_out1[6]=0x1;	
     			}
     		
     		else if(UIB1[6]==0x33)UB0++;
      		else if(UIB1[6]==0x44)UB0+=ttt;
     		else if(UIB1[6]==0x55)UB0--;
      		else if(UIB1[6]==0x66)UB0-=ttt;
      		
      		gran(&UB0,10,1000);	  			
     		lc640_write_int(EE_UB0,UB0);
     		}
     			
     	else if(UIB1[5]==51)     		
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);//*((unsigned short*)&UIB1[7]);
     		//ttt=(unsigned short)(*(&UIB1[7]));
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=10)&&(ttt<=1000))
     				{
     				UB20=ttt;
      				}
     			else memo_out1[6]=0x1;	
     			}
     		
     		else if(UIB1[6]==0x33)UB20++;
      		else if(UIB1[6]==0x44)UB20+=ttt;
     		else if(UIB1[6]==0x55)UB20--;
      		else if(UIB1[6]==0x66)UB20-=ttt;

     		gran(&UB20,10,1000);      			  			
     		lc640_write_int(EE_UB20,UB20);
     		}	
     		
     	else if(UIB1[5]==52)     		
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=10)&&(ttt<=1000))
     				{
     				USIGN=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)USIGN++;
      		else if(UIB1[6]==0x44)USIGN+=ttt;
     		else if(UIB1[6]==0x55)USIGN--;
      		else if(UIB1[6]==0x66)USIGN-=ttt;

     		gran(&USIGN,10,1000);     			  			
     		lc640_write_int(EE_USIGN,USIGN);
     		}
     		
     	else if(UIB1[5]==53)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=10)&&(ttt<=1000))
     				{
     				UMN=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)UMN++;
      		else if(UIB1[6]==0x44)UMN+=ttt;
     		else if(UIB1[6]==0x55)UMN--;
      		else if(UIB1[6]==0x66)UMN-=ttt;
      		
     		gran(&UMN,10,1000);	      			  			
     		lc640_write_int(EE_UMN,UMN);
     		}     		     		

     	else if(UIB1[5]==54)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=10)&&(ttt<=1000))
     				{
     				U0B=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)U0B++;
      		else if(UIB1[6]==0x44)U0B+=ttt;
     		else if(UIB1[6]==0x55)U0B--;
      		else if(UIB1[6]==0x66)U0B-=ttt;
      		
     		gran(&U0B,10,1000);	      			  			
     		lc640_write_int(EE_U0B,U0B);
     		}     		
     		
     	else if(UIB1[5]==55)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=1)&&(ttt<=500))
     				{
     				IKB=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)IKB++;
      		else if(UIB1[6]==0x44)IKB+=ttt;
     		else if(UIB1[6]==0x55)IKB--;
      		else if(UIB1[6]==0x66)IKB-=ttt;
      		
     		gran(&IKB,10,1000);	      			  			
     		lc640_write_int(EE_IKB,IKB);
     		}     		

     	else if(UIB1[5]==56)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=10)&&(ttt<=200))
     				{
     				IZMAX=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)IZMAX++;
      		else if(UIB1[6]==0x44)IZMAX+=ttt;
     		else if(UIB1[6]==0x55)IZMAX--;
      		else if(UIB1[6]==0x66)IZMAX-=ttt;
      		
     		gran(&IZMAX,10,200);	      			  			
     		lc640_write_int(EE_IZMAX,IZMAX);
     		}     	     
 
      	else if(UIB1[5]==57)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=1)&&(ttt<=500))
     				{
     				IMAX=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)IMAX++;
      		else if(UIB1[6]==0x44)IMAX+=ttt;
     		else if(UIB1[6]==0x55)IMAX--;
      		else if(UIB1[6]==0x66)IMAX-=ttt;
      		
     		gran(&IMAX,1,500);	      			  			
     		lc640_write_int(EE_IMAX,IMAX);
     		}     	        		
     		
      	else if(UIB1[5]==58)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=5)&&(ttt<=10))
     				{
     				KIMAX=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)KIMAX++;
      		else if(UIB1[6]==0x44)KIMAX+=ttt;
     		else if(UIB1[6]==0x55)KIMAX--;
      		else if(UIB1[6]==0x66)KIMAX-=ttt;
      		
     		gran(&KIMAX,5,10);	      			  			
     		lc640_write_int(EE_KIMAX,KIMAX);
     		} 
     		 
     	else if(UIB1[5]==59)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=1005)&&(ttt<=1030))
     				{
     				KVZ=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)KVZ++;
      		else if(UIB1[6]==0x44)KVZ+=ttt;
     		else if(UIB1[6]==0x55)KVZ--;
      		else if(UIB1[6]==0x66)KVZ-=ttt;
      		
     		gran(&KVZ,1005,1030);	      			  			
     		lc640_write_int(EE_KVZ,KVZ);
     		}      
     		       		       		
      	else if(UIB1[5]==60)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=0)&&(ttt<=3))
     				{
     				TZAS=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TZAS++;
      		else if(UIB1[6]==0x44)TZAS+=ttt;
     		else if(UIB1[6]==0x55)TZAS--;
      		else if(UIB1[6]==0x66)TZAS-=ttt;
      		
     		gran(&TZAS,0,3);	      			  			
     		lc640_write_int(EE_TZAS,TZAS);
     		} 
     		        
      	else if(UIB1[5]==61)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=10)&&(ttt<=100))
     				{
     				TMAX=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TMAX++;
      		else if(UIB1[6]==0x44)TMAX+=ttt;
     		else if(UIB1[6]==0x55)TMAX--;
      		else if(UIB1[6]==0x66)TMAX-=ttt;
      		
     		gran(&TMAX,10,100);	      			  			
     		lc640_write_int(EE_TMAX,TMAX);
     		}         
     				     		     		
      	else if(UIB1[5]==71)
     		{
     		if(UIB1[6]==0x22)
     			{
     			APV_ON1=UIB1[7]+(UIB1[8]*256);;
     			}
     		else if( (UIB1[6]==0x33) || (UIB1[6]==0x44) || (UIB1[6]==0x55) || (UIB1[6]==0x66) )
     			{
     			if(APV_ON1) APV_ON1=0;
     			else APV_ON1=1;
     			}
	    		gran_char(&APV_ON1,0,1);
    			lc640_write_int(EE_APV_ON1,APV_ON1);
     		}	

     	else if(UIB1[5]==72)
     		{
     		if(UIB1[6]==0x22)
     			{
     			APV_ON2=UIB1[7]+(UIB1[8]*256);;
     			}
     		else if( (UIB1[6]==0x33) || (UIB1[6]==0x44) || (UIB1[6]==0x55) || (UIB1[6]==0x66) )
     			{
     			if(APV_ON2) APV_ON2=0;
     			else APV_ON2=1;
     			}
    			gran_char(&APV_ON2,0,1);
    			lc640_write_int(EE_APV_ON2,APV_ON2);
     		}	

     	else if(UIB1[5]==73)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=1)&&(ttt<=24))
     				{
     				APV_ON2_TIME=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)APV_ON2_TIME++;
      		else if(UIB1[6]==0x44)APV_ON2_TIME+=ttt;
     		else if(UIB1[6]==0x55)APV_ON2_TIME--;
      		else if(UIB1[6]==0x66)APV_ON2_TIME-=ttt;
      		
     		gran(&APV_ON2_TIME,1,24);	      			  			
     		lc640_write_int(EE_APV_ON2_TIME,APV_ON2_TIME);
     		} 

      	else if(UIB1[5]==80)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=1)&&(ttt<=11))
     				{
     				pos_vent=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)pos_vent++;
      		else if(UIB1[6]==0x44)pos_vent+=ttt;
     		else if(UIB1[6]==0x55)pos_vent--;
      		else if(UIB1[6]==0x66)pos_vent-=ttt;
      		
     		gran(&pos_vent,1,11);	      			  			
     		lc640_write_int(EE_POS_VENT,pos_vent);
     		} 
 
      	else if(UIB1[5]==90)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=50)&&(ttt<=80))
     				{
     				TBOXMAX=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TBOXMAX++;
      		else if(UIB1[6]==0x44)TBOXMAX+=ttt;
     		else if(UIB1[6]==0x55)TBOXMAX--;
      		else if(UIB1[6]==0x66)TBOXMAX-=ttt;
      		
     		gran(&TBOXMAX,50,80);	      			  			
     		lc640_write_int(EE_TBOXMAX,TBOXMAX);
     		} 

      	else if(UIB1[5]==91)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=5)&&(ttt<=30))
     				{
     				TBOXREG=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TBOXREG++;
      		else if(UIB1[6]==0x44)TBOXREG+=ttt;
     		else if(UIB1[6]==0x55)TBOXREG--;
      		else if(UIB1[6]==0x66)TBOXREG-=ttt;
      		
     		gran(&TBOXREG,5,30);	      			  			
     		lc640_write_int(EE_TBOXREG,TBOXREG);
     		} 
 
       	else if(UIB1[5]==92)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=49)&&(ttt<=81))
     				{
     				TBOXVENTMAX=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TBOXVENTMAX++;
      		else if(UIB1[6]==0x44)TBOXVENTMAX+=ttt;
     		else if(UIB1[6]==0x55)TBOXVENTMAX--;
      		else if(UIB1[6]==0x66)TBOXVENTMAX-=ttt;
      		
     		gran(&TBOXVENTMAX,49,81);	      			  			
     		lc640_write_int(EE_TBOXVENTMAX,TBOXVENTMAX);
     		} 

       	else if(UIB1[5]==93)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=49)&&(ttt<=81))
     				{
     				TLOADDISABLE=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TLOADDISABLE++;
      		else if(UIB1[6]==0x44)TLOADDISABLE+=ttt;
     		else if(UIB1[6]==0x55)TLOADDISABLE--;
      		else if(UIB1[6]==0x66)TLOADDISABLE-=ttt;
      		
     		gran(&TLOADDISABLE,49,81);	      			  			
     		lc640_write_int(EE_TLOADDISABLE,TLOADDISABLE);
     		} 
			 
       	else if(UIB1[5]==94)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=49)&&(ttt<=81))
     				{
     				TLOADENABLE=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TLOADENABLE++;
      		else if(UIB1[6]==0x44)TLOADENABLE+=ttt;
     		else if(UIB1[6]==0x55)TLOADENABLE--;
      		else if(UIB1[6]==0x66)TLOADENABLE-=ttt;
      		
     		gran(&TLOADENABLE,49,81);	      			  			
     		lc640_write_int(EE_TLOADENABLE,TLOADENABLE);
     		}     				     		     		

       	else if(UIB1[5]==95)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=49)&&(ttt<=81))
     				{
     				TBATDISABLE=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TBATDISABLE++;
      		else if(UIB1[6]==0x44)TBATDISABLE+=ttt;
     		else if(UIB1[6]==0x55)TBATDISABLE--;
      		else if(UIB1[6]==0x66)TBATDISABLE-=ttt;
      		
     		gran(&TBATDISABLE,49,81);	      			  			
     		lc640_write_int(EE_TBATDISABLE,TBATDISABLE);
     		} 
			 
       	else if(UIB1[5]==96)
     		{     			
     		signed short ttt;
     		ttt=UIB1[7]+(UIB1[8]*256);;
     		
     		if(UIB1[6]==0x22)
     			{
     			if((ttt>=49)&&(ttt<=81))
     				{
     				TBATENABLE=ttt;
     				}
     			else memo_out1[6]=0x01;	
     			}
     		
     		else if(UIB1[6]==0x33)TBATENABLE++;
      		else if(UIB1[6]==0x44)TBATENABLE+=ttt;
     		else if(UIB1[6]==0x55)TBATENABLE--;
      		else if(UIB1[6]==0x66)TBATENABLE-=ttt;
      		
     		gran(&TBATENABLE,49,81);	      			  			
     		lc640_write_int(EE_TBATENABLE,TBATENABLE);
     		}   
						   				     		     		
         	memo_out1[7]=crc_87(memo_out1,7);
		memo_out1[8]=crc_95(memo_out1,7);
     	uart_out_adr1(memo_out1,9); 		
		}		
	} 			
}
 
//-----------------------------------------------
char index_offset1 (signed char index,signed char offset)
{
index=index+offset;
if(index>=RX_BUFFER_SIZE1) index-=RX_BUFFER_SIZE1; 
if(index<0) index+=RX_BUFFER_SIZE1;
return index;
}

//-----------------------------------------------
char control_check1(char index)
{
char i=0,ii=0,iii;

if(rx_buffer1[index]!=END) goto error_cc;

ii=rx_buffer1[index_offset1(index,-2)];
iii=0;
for(i=0;i<=ii;i++)
	{
	iii^=rx_buffer1[index_offset1(index,-2-ii+i)];
	}
if (iii!=rx_buffer1[index_offset1(index,-1)]) goto error_cc;	


//success_cc:
return 1;
//goto end_cc;
error_cc:
return 0;
//goto end_cc;

//end_cc:
//__nop();
}

//-----------------------------------------------
void uart_in1(void)
{
char temp,i/*,count*/;

__disable_irq();

if(rx_buffer_overflow1)
	{
	rx_wr_index1=0;
	rx_rd_index1=0;
	rx_counter1=0;
	rx_buffer_overflow1=0;
	}    
usart1_router_wrk=1;	
if(rx_counter1&&(rx_buffer1[index_offset1(rx_wr_index1,-1)])==END)
	{
	
     temp=rx_buffer1[index_offset1(rx_wr_index1,-3)];
    	if(temp<20) 
    		{
    		if(control_check1(index_offset1(rx_wr_index1,-1)))
    			{
    		
    			rx_rd_index1=index_offset1(rx_wr_index1,-3-temp);
    			for(i=0;i<temp;i++)
				{
				UIB1[i]=rx_buffer1[index_offset1(rx_rd_index1,i)];
				} 
			rx_rd_index1=rx_wr_index1;
			rx_counter1=0;
			uart_in_an1();
			if(usart1_router_stat==ursMEGA)usart1_router_wrk=0;
    			}
 	
    		} 
    	}	


__enable_irq();     
}   	

