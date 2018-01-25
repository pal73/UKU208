#define BIN__N(x) (x) | x>>3 | x>>6 | x>>9
#define BIN__B(x) (x) & 0xf | (x)>>12 & 0xf0
#define BIN8(v) (BIN__B(BIN__N(0x##v)))

//***********************************************
//Таймер
char b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz;
short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7;
char bFL5,bFL2,bFL,bFL_;

//***********************************************
//АЦП

short adc_buff[16][16],adc_buff_[16];
char adc_cnt,adc_cnt1,adc_ch;

 
char bp_tumbler[2];

//***********************************************
//Состояние первичной сети
char u_net_av_stat,u_net_av_stat_;
signed short Unet,unet_store;
signed short Hz_cnt,fnet,Hz_out;

//***********************************************
//Состояние внешних датчиков
signed short tout[3];


//***********************************************
//Состояние батарей
char bat_cnt_to_block[2];
char bat_rel_stat[2];
signed bat_Ub[2]; 
signed bat_Ib[2];
signed bat_Tb[2];
char bat_nd[2];
char bat_av_stat[2];
char bat_zar[2];

//***********************************************
//Состояние источников

#define ssOFF 0
#define ssAV 1
#define ssBL 2
#define ssWRK 3
#define ssNOT 4
#define dSRC 3
#define dINV 5

typedef struct
     {
     char _device;    
     char _state;
     char _cnt;
     char _cnt_old;
     char _cnt_more2;
     char _buff[16]; 
     char _av_net;
     char _av_u_max;
     char _av_u_min;
     char _av_temper; 
     signed _Uii; 
     signed _Uin;
     signed _Ii;
     signed _Ti; 
     char _flags_tu;
     //char _flags_tu_old;
     char _is_ready;
     char _is_wrk;
     char _is_link;
     char _is_av;
     signed _vol_u;
     signed _vol_i;
     char _is_on_cnt;
     int _ist_blok_host_cnt_; //блокирование источников извне(CAN или RS), если не 0 то источник заблокирован.
     int _ist_blok_host_cnt;
     int _ist_blok_cnt; //блокирование источников 
     char _flags_tm;     
     char _flags_bp;
     signed _temp_av_cnt;
     signed _umax_av_cnt;
     signed _umin_av_cnt;
     signed _rotor;
     signed _x_; 
     //char _off_bp_cnt;
     char _adr_ee;
     } SRC_STAT; 
     
SRC_STAT src[10];

//***********************************************
//Состояние нагрузки
signed short load_U;
signed short load_I;




//**********************************************
//Коэффициенты, отображаемые из EEPROM
signed short Ktsrc[2];
signed short Kusrc[2];
signed short Kisrc[2];
signed short Ki0src[2];
signed short Kubat[2];
signed short Kibat0[2];
signed short Kibat1[2];
signed short Ktbat[2];
signed short Kunet;
signed short Ktout[3];

signed short MAIN_IST;
signed short UMAX;
signed short UB0;
signed short UB20;
signed short TMAX;
signed short TSIGN;
signed short AV_OFF_AVT;
signed short USIGN;
signed short UMN;
signed short ZV_ON;
signed short IKB;
signed short KVZ;
signed short IMAX;
signed short KIMAX;
signed short APV_ON;
signed short IZMAX;
signed short U0B;
signed short TZAS;
signed short VZ_HR;
signed short TBAT;
signed short U_AVT;
signed short DU;
signed short PAR;

signed short NUMBAT;
signed short NUMIST;
signed short NUMINV;
signed short NUMDT;
signed short NUMSK;


/*
signed short BAT2_DAY_OF_ON;

signed short BAT2_C_REAL;
*/

//signed short ZAR_CNT,ZAR_CNT_KE;
enum  {bisON=0x0055,bisOFF=0x00aa}BAT_IS_ON[2];
signed short BAT_DAY_OF_ON[2];
signed short BAT_MONTH_OF_ON[2];
signed short BAT_YEAR_OF_ON[2];
signed short BAT_C_NOM[2];
signed short BAT_RESURS[2];
signed short BAT_C_REAL[2];

unsigned short AUSW_MAIN;
unsigned long 	AUSW_MAIN_NUMBER;
unsigned short AUSW_DAY;
unsigned short AUSW_MONTH;
unsigned short AUSW_YEAR;
unsigned short AUSW_UKU;
unsigned short AUSW_UKU_SUB;
unsigned long AUSW_UKU_NUMBER;
unsigned long	AUSW_BPS1_NUMBER;
unsigned long  AUSW_BPS2_NUMBER;
unsigned short AUSW_RS232;
unsigned short AUSW_PDH;
unsigned short AUSW_SDH;
unsigned short AUSW_ETH;

signed short TMAX_EXT_EN[3];
signed short TMAX_EXT[3];
signed short TMIN_EXT_EN[3];
signed short TMIN_EXT[3];
signed short T_EXT_REL_EN[3];
signed short T_EXT_ZVUK_EN[3];
signed short T_EXT_LCD_EN[3];
signed short T_EXT_RS_EN[3];

signed short SK_SIGN[4];
signed short SK_REL_EN[4];
signed short SK_ZVUK_EN[4];
signed short SK_LCD_EN[4];
signed short SK_RS_EN[4];

enum {AVZ_1=1,AVZ_2=2,AVZ_3=3,AVZ_6=6,AVZ_12=12,AVZ_OFF=0}AVZ;
unsigned short HOUR_AVZ;
unsigned short MIN_AVZ;
unsigned short SEC_AVZ;
unsigned short DATE_AVZ;
unsigned short MONTH_AVZ;
unsigned short YEAR_AVZ;
unsigned short AVZ_TIME;

//***********************************************
//Спецфункции
enum {spc_OFF=0,spc_KE1p1,spc_KE1p2,spc_KE2p1,spc_KE2p2,spc_VZ}spc_stat=spc_OFF;


signed short cntrl_stat=600,cntrl_stat_old/*,cntrl_stat_i*/;
signed short Ibmax;
signed short u_necc,u_necc_;
signed short main_cnt_5Hz;
signed short num_necc;
signed short cnt_num_necc;
char bSAME_IST_ON;
signed mat_temper;


#include <LPC21xx.H>                        /* LPC21xx definitions */
#include "Timer.h"
#include "gran.c"
#include "control.c"
#include "eeprom_map.c"


char flag=0;






void wait (void)  {                         /* wait function */
  unsigned long i;

  i = timeval;
  while ((i + 10) != timeval);              /* wait 100ms */
}

//***********************************************
//***********************************************
//***********************************************
//***********************************************
//***********************************************
__irq void timer1_interrupt(void) 
{
//__enable_interrupt(); 
T1IR = 0xff; // Clear timer 0 interrupt line.
/*
#if(UKU_VERSION==900)
bFF=IO0PIN_bit.P0_22;

if(bFF!=bFF_)
	{
	Hz_out++;
	}        
bFF_=bFF;    
#endif
*/

adc_drv();

if(++t0cnt5>=200)
     {
     t0cnt5=0;
     b50Hz=1;
     }
     
if(++t0cnt>=100)
     {
     t0cnt=0;
     b100Hz=1;

     Hz_cnt++;
     if(Hz_cnt>=500)
	     {	
	     Hz_cnt=0;
	     fnet=Hz_out;
	     Hz_out=0;
	     }

     if(++t0cnt0>=10)
	     {
	     t0cnt0=0;
	     b10Hz=1;
	     //beep_drv();
	     }

     if(t0cnt0==5)
	     {
	     //beep_drv();
	     }

     if(++t0cnt1>=20)
	     {
	     t0cnt1=0;
	     b5Hz=1;
	     
 		if(bFL5)bFL5=0;
  		else bFL5=1;	     
	     }

     if(++t0cnt2>=50)
	     {
	     t0cnt2=0;
	     b2Hz=1;
	     
	     if(bFL2)bFL2=0;
	     else bFL2=1;

		flag=1;
	     }         

     if(++t0cnt3>=100)
	     {
	     t0cnt3=0;
	     b1Hz=1;
	    	if(bFL)bFL=0;
	     else 
	     	{
	     	bFL=1;
	     	if(bFL_)bFL_=0;
	     	else bFL_=1;
	     	}
	     }
     }

VICVectAddr = 0;

}

//***********************************************
__irq void timer0_interrupt(void) 
{	
/*if(BPS1_spa_leave)T0EMR_bit.EM1=0; 
else T0EMR_bit.EM1=1;
if(BPS2_spa_leave)T0EMR_bit.EM3=0; 
else T0EMR_bit.EM3=1;
T0IR = 0xff;*/
}

//===============================================
//===============================================
//===============================================
//===============================================
int main (void) 
{
unsigned int j;                           /* LED var */

IODIR1 |= (1<<21);                        /* P1.16..23 defined as Outputs */

init_timer1();

while (1)  
	{  
	while(!flag);
	IOSET1 = (1<<21);
	flag=0;   
	while(!flag);
	IOCLR1 = (1<<21);
	flag=0; 	                              
/*   	for (j = 0; j < 1000000; j ++) 
		{  
      	IOSET1 = (1<<21);                                
		}
   	for (j = 0; j < 1000000; j ++) 
		{  
      	IOCLR1 = (1<<21);                                
		}*/
	}
}
