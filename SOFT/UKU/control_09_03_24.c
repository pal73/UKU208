#include "global_define.h"
#include "25lc640.h"
#include "control.h"
#include "mess.h"
#include "gran.h"
#include "common_func.h"
#include "eeprom_map.h"
#include "avar_hndl.h"
#include <LPC21XX.H>

#define KOEFPOT  105L



//extern char u_net_av_stat,u_net_av_stat_;


extern const unsigned short ADR_KI0BAT[2];

   


extern BAT_STAT bat[2];

extern signed short		bat_u_old_cnt;



extern signed short load_U;
extern signed short load_I;
extern signed short u_necc,u_necc_;
extern signed short main_cnt_5Hz;
extern signed short num_necc;
extern signed short num_necc_Imax;
extern signed short num_necc_Imin;
//extern char bSAME_IST_ON;
//extern signed short Unet,unet_store;
//extern char bat_cnt_to_block[2];
//extern enum  {bisON=0x0055,bisOFF=0x00aa}BAT_IS_ON[2];
extern signed mat_temper;

extern signed short Ktout[3];




//***********************************************
//Аварии
typedef struct  
	{
     unsigned int bAN:1; 
     unsigned int bAB1:1; 
     unsigned int bAB2:1;
     unsigned int bAS1:1;
     unsigned int bAS2:1;
     unsigned int bAS3:1;
     unsigned int bAS4:1;
     unsigned int bAS5:1;
     unsigned int bAS6:1;
     unsigned int bAS7:1;
     unsigned int bAS8:1;
     unsigned int bAS9:1;
     unsigned int bAS10:1;
     unsigned int bAS11:1;
     unsigned int bAS12:1;
     }avar_struct;
     
extern union 
{
avar_struct av;
int avar_stat;
}a,a_;

//***********************************************
//АЦП
short adc_buff[16][16],adc_buff_[16];
char adc_cnt,adc_cnt1,adc_ch;
short zero_cnt;
enum {asCH=1,asNET_WAIT=2,asNET_RDY=3,asNET=4} adc_stat=asCH;
unsigned short net_buff[32],net_buff_;
char net_buff_cnt;
short ADWR,period_cnt;
char rele_stat;
char bRELE_OUT;


extern int mess_par0[MESS_DEEP],mess_par1[MESS_DEEP],mess_data[2];

extern signed short TBAT;
extern signed short Kunet;
extern signed short Kubat[2];
extern unsigned short ad7705_buff[2][16],ad7705_buff_[2];
extern unsigned short Kibat0[2];
extern signed short Kibat1[2];
extern signed short Ktbat[2];
//extern signed short bat_Ib[2];
short adc_buff_out_[3];
extern char kb_full_ver;
extern signed short Kuload;

signed short bat_ver_cnt=150;
extern signed short Isumm;
extern char ND_out[3];
extern signed short tout[4];


short plazma_adc_cnt;

extern char cntrl_plazma;

extern const short ptr_bat_zar_cnt[2];

//***********************************************
//Управление вентилятором
signed char vent_stat=0;

//***********************************************
//Управление ШИМом
signed short cntrl_stat=600;
signed short cntrl_stat_old=600;
signed short cntrl_stat_new;
signed short Ibmax;

//***********************************************
//Самокалиброввка
signed short samokalibr_cnt;



//***********************************************
//Выравнивание токов
short avg_main_cnt=20;
short i_avg_max,i_avg_min,i_avg_summ,i_avg; 
short avg;
char bAVG;
char avg_cnt;  
char avg_num; 

//**********************************************
//Контроль наличия батарей
signed short 	main_kb_cnt;
signed short 	kb_cnt_1lev;
signed short 	kb_cnt_2lev;
char 		kb_full_ver;
char kb_start[2];

//**********************************************
//Работа с БПСами
char num_of_wrks_bps;
char bps_all_off_cnt,bps_mask_off_cnt,bps_mask_on_off_cnt;
char bps_hndl_2sec_cnt;
unsigned short bps_on_mask,bps_off_mask;

//***********************************************
//Спецфункции
enum {spcOFF=0,spcKE, spcVZ}spc_stat=spcOFF;
char spc_bat;
char spc_phase;

//***********************************************
//Состояние первичной сети
//char u_net_av_stat,u_net_av_stat_;
signed short net_U,net_Ustore;
char bFF,bFF_;
signed short net_F,hz_out,hz_out_cnt;
signed char unet_drv_cnt;
char net_av;

//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//Внешние

//**********************************************
//Коэффициенты, отображаемые из EEPROM

extern signed short Ktsrc[2];
extern signed short Kusrc[2];
extern signed short Kisrc[2];
extern signed short Ki0src[2];
extern signed short Kubat[2];
extern unsigned short Kibat0[2];
extern signed short Kibat1[2];
extern signed short Ktbat[2];
extern signed short Kunet;
extern signed short Ktout[3];
extern signed short Kuload;

extern signed short MAIN_IST;
extern signed short UMAX;
extern signed short UB0;
extern signed short UB20;
extern signed short TMAX;
extern signed short TSIGN;
extern signed short AV_OFF_AVT;
extern signed short USIGN;
extern signed short UMN;
extern signed short ZV_ON;
extern signed short IKB;
extern signed short KVZ;
extern signed short IMAX;
extern signed short KIMAX;
extern signed short APV_ON;
extern signed short IZMAX;
extern signed short U0B;
extern signed short TZAS;
extern signed short VZ_HR;
extern signed short TBAT;
extern signed short U_AVT;
extern signed short DU;
extern signed short PAR;

extern signed short NUMBAT;
extern signed short NUMIST;
extern signed short NUMINV;
extern signed short NUMDT;
extern signed short NUMSK;
extern signed short NUMEXT;

extern enum  {apvON=0x0055,apvOFF=0x00aa}apv_on1,apv_on2;
extern signed short apv_on2_time;
extern enum  {bisON=0x0055,bisOFF=0x00aa}BAT_IS_ON[2];
extern signed short BAT_DAY_OF_ON[2];
extern signed short BAT_MONTH_OF_ON[2];
extern signed short BAT_YEAR_OF_ON[2];
extern signed short BAT_C_NOM[2];
extern signed short BAT_RESURS[2];
extern signed short BAT_C_REAL[2];

extern unsigned short AUSW_MAIN;
extern unsigned long 	AUSW_MAIN_NUMBER;
extern unsigned short AUSW_DAY;
extern unsigned short AUSW_MONTH;
extern unsigned short AUSW_YEAR;
extern unsigned short AUSW_UKU;
extern unsigned short AUSW_UKU_SUB;
extern unsigned long AUSW_UKU_NUMBER;
extern unsigned long	AUSW_BPS1_NUMBER;
extern unsigned long  AUSW_BPS2_NUMBER;
extern unsigned short AUSW_RS232;
extern unsigned short AUSW_PDH;
extern unsigned short AUSW_SDH;
extern unsigned short AUSW_ETH;

extern signed short TMAX_EXT_EN[3];
extern signed short TMAX_EXT[3];
extern signed short TMIN_EXT_EN[3];
extern signed short TMIN_EXT[3];
extern signed short T_EXT_REL_EN[3];
extern signed short T_EXT_ZVUK_EN[3];
extern signed short T_EXT_LCD_EN[3];
extern signed short T_EXT_RS_EN[3];

extern signed short SK_SIGN[4];
extern signed short SK_REL_EN[4];
extern signed short SK_ZVUK_EN[4];
extern signed short SK_LCD_EN[4];
extern signed short SK_RS_EN[4];

extern enum {AVZ_1=1,AVZ_2=2,AVZ_3=3,AVZ_6=6,AVZ_12=12,AVZ_OFF=0}AVZ;
extern unsigned short HOUR_AVZ;
extern unsigned short MIN_AVZ;
extern unsigned short SEC_AVZ;
extern unsigned short DATE_AVZ;
extern unsigned short MONTH_AVZ;
extern unsigned short YEAR_AVZ;
extern unsigned short AVZ_TIME;
extern enum {mnON=0x55,mnOFF=0xAA}MNEMO_ON;
extern unsigned short MNEMO_TIME;

//**********************************************
//Время
extern signed short main_10Hz_cnt;


//***********************************************
//Аварии
extern unsigned avar_stat;	 	//"Отображение" всех аварийных в данный момент устройств в одном месте
extern unsigned avar_ind_stat; 	//"Отображение" всех не просмотренных аварийных устройств в одном месте
extern unsigned avar_stat_old;
extern unsigned avar_stat_new,avar_stat_offed;
//Структура переменных
//1бит  - питающая сеть
//2бита - батареи
//12бит - БПСы
//5бит  - инверторы
//4бита - внешние датчики температуры
//4бита - внешние сухие контакты

//***********************************************
//Состояние источников
extern BPS_STAT bps[12];

//-----------------------------------------------
void kb_init(void)
{
main_kb_cnt=(TBAT*60)-60/*120*/;
}

//-----------------------------------------------
void kb_hndl(void)
{

static signed short ibat[2],ibat_[2];

if(++main_kb_cnt>=TBAT*60)
	{
	main_kb_cnt=0;
	
	kb_start[0]=0;
	kb_start[1]=0;

	if( (BAT_IS_ON[0]==bisON) && (bat[0]._Ub>80) && ( (abs(bat[0]._Ib<IKB)) || (bat[0]._av) ) ) kb_start[0]=1;
	if( (BAT_IS_ON[1]==bisON) && (bat[1]._Ub>80) && ( (abs(bat[1]._Ib<IKB)) || (bat[1]._av) ) ) kb_start[1]=1;
	
	if( (net_av) || (num_of_wrks_bps==0) || ( (spc_stat!=spcOFF) && (spc_stat!=spcVZ) ) ) 
		{
		kb_start[0]=0;
		kb_start[1]=0;
		}

	if((kb_start[0]==1)||(kb_start[1]==1))
		{
		kb_cnt_1lev=10;
		}
	else kb_cnt_1lev=0;
	}

if(kb_cnt_1lev)
	{
	kb_cnt_1lev--;

	if(kb_cnt_1lev>5)mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_PLUS,30,15);
	else if(kb_cnt_1lev>0) mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_MINUS,30,15);


	if(kb_cnt_1lev==5)
		{
		ibat[0]=abs(bat[0]._Ib);
		ibat[1]=abs(bat[1]._Ib);
		}
	
	if(kb_cnt_1lev==0)
		{
		ibat_[0]=abs(bat[0]._Ib);
		ibat_[1]=abs(bat[1]._Ib);

		kb_cnt_2lev=0;
		if( (ibat[0]+ibat_[0]) < IKB ) 
			{
			kb_cnt_2lev=10;  
			}
		else 
			{
			kb_start[0]=0;
			avar_bat_hndl(0,0);
			}
		
		if( (ibat[1]+ibat_[1]) < IKB )
			{
			kb_cnt_2lev=10;     
			}
		else 
			{
			kb_start[1]=0;
			avar_bat_hndl(1,0);
			}
		}	


	}
else if(kb_cnt_2lev)
	{
	kb_cnt_2lev--;

	if(kb_cnt_2lev>5)mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_PLUS,200,15);
	else if(kb_cnt_2lev>0) mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_MINUS,200,15);


	if(kb_cnt_2lev==5)
		{
		ibat[0]=abs(bat[0]._Ib);
		ibat[1]=abs(bat[1]._Ib);
		}
	
	if(kb_cnt_2lev==0)
		{
		ibat_[0]=abs(bat[0]._Ib);
		ibat_[1]=abs(bat[1]._Ib);

		kb_full_ver=0;

		if( (ibat[0]+ibat_[0]) < IKB ) 
			{
			kb_full_ver=1;  
			}
		else 			
			{
			kb_start[0]=0;
			avar_bat_hndl(0,0);
			}

		if( (ibat[1]+ibat_[1]) < IKB )
			{
			kb_full_ver=1;     
			}
		else			
			{
			kb_start[1]=0;
			avar_bat_hndl(1,0);
			}


		}	
	}

else if(kb_full_ver)
	{
	
	mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_STEP_DOWN,0,15);

	if( abs(bat[0]._Ib) > IKB ) 
		{
		if(kb_start[0]==1)
			{
			kb_start[0]=0;
			avar_bat_hndl(0,0);
			}
		}

	if( abs(bat[1]._Ib) > IKB ) 
		{
		if(kb_start[1]==1)
			{
			kb_start[1]=0;
			avar_bat_hndl(1,0);
			}
		}

	if( (mess_find(MESS2KB_HNDL))	&& (mess_data[0]==PARAM_CNTRL_IS_DOWN) )
		{
		kb_full_ver=0;
		if(kb_start[0]==1) avar_bat_hndl(0,1);
		if(kb_start[1]==1) avar_bat_hndl(1,1);
		}
	}

}


//-----------------------------------------------
void samokalibr_init(void)
{
samokalibr_cnt=1785;
}
//-----------------------------------------------
void samokalibr_hndl(void)
{
if(++samokalibr_cnt>=1800)samokalibr_cnt=0;

if(samokalibr_cnt>=1785U)
	{
	mess_send(MESS2RELE_HNDL,PARAM_RELE_SAMOKALIBR_ENABLE,0,15);
	mess_send(MESS2IND_HNDL,PARAM_SAMOKALIBR,0,15);
	mess_send(MESS2MATEMAT,PARAM_SAMOKALIBR,0,15);
	} 

if(samokalibr_cnt==1799U)
	{
	if(Kibat0[0]!=ad7705_buff_[0]) lc640_write_int(ADR_KI0BAT[0],ad7705_buff_[0]);
	if(Kibat0[1]!=ad7705_buff_[1]) lc640_write_int(ADR_KI0BAT[1],ad7705_buff_[1]);
	
	}	 	
}



//-----------------------------------------------
void ubat_old_drv(void)
{        
bat_u_old_cnt++;
gran_ring(&bat_u_old_cnt,0,8);

bat[0]._u_old[bat_u_old_cnt]=bat[0]._Ub;
bat[1]._u_old[bat_u_old_cnt]=bat[1]._Ub;
}

//-----------------------------------------------
void unet_drv(void)
{
if(net_U<UMN)
	{
	if(unet_drv_cnt<10)
		{
		unet_drv_cnt++;
		if(unet_drv_cnt>=10)
			{
			net_Ustore=net_U;
		 	avar_unet_hndl(1);
			
			}
		}
	else if(unet_drv_cnt>=10)unet_drv_cnt=10;

	if(net_U<net_Ustore) net_Ustore=net_U;	
	}

else if(net_U>UMN)
	{                 
	if(unet_drv_cnt)
		{
		unet_drv_cnt--;
		if(unet_drv_cnt<=0)
			{
			avar_unet_hndl(0);
			}
		}
	else if(unet_drv_cnt<0)unet_drv_cnt=0;
	
	}

}

//-----------------------------------------------
void matemat(void)
{
//signed short temp_SS;
signed long temp_SL,temp_SL_;
char /*temp,*/i;

//static char plpl;

temp_SL=(signed long)net_buff_;
temp_SL*=Kunet;
temp_SL/=110000L;
net_U=(signed short)temp_SL;


temp_SL=(signed long)adc_buff_[4];
temp_SL*=Kubat[0];
temp_SL/=500L;
bat[0]._Ub=(signed short)temp_SL;

temp_SL=(signed long)adc_buff_[0];
temp_SL*=Kubat[1];
temp_SL/=500L;
bat[1]._Ub=(signed short)temp_SL;

if(!mess_find_unvol(MESS2MATEMAT))
	{
//	ad7705_buff_[0]=32930;
//	Kibat0[0]=32900;
	temp_SL=(signed long)ad7705_buff_[0];
	temp_SL-=(signed long)Kibat0[0];
	temp_SL*=(signed long)Kibat1[0];
	temp_SL/=900L;
	bat[0]._Ib=(signed short)temp_SL;

	temp_SL=(signed long)ad7705_buff_[1];
	temp_SL-=(signed long)Kibat0[1];
	temp_SL*=(signed long)Kibat1[1];
	temp_SL/=900L;
	bat[1]._Ib=(signed short)temp_SL;
	}

if((adc_buff_[12]>200)&&(adc_buff_[12]<1000))bat[0]._nd=0;
else bat[0]._nd=1;
temp_SL=(signed long)adc_buff_[12];
temp_SL*=Ktbat[0];
temp_SL/=5000L;
temp_SL-=273L;
bat[0]._Tb=(signed short)temp_SL;

if((adc_buff_[10]>200)&&(adc_buff_[10]<1000))bat[1]._nd=0;
else bat[1]._nd=1;
temp_SL=(signed long)adc_buff_[10];
temp_SL*=Ktbat[1];
temp_SL/=5000L;
temp_SL-=273L;
bat[1]._Tb=(signed short)temp_SL;



/*if(Ibat<0)bit_minus=1;
else bit_minus=0;*/

if((kb_full_ver)&&(abs(bat[0]._Ib)>IKB))
	{
	kb_full_ver=0;
	//avar_bat_hndl(0);
	gran(&TBAT,5,60);
     bat_ver_cnt=TBAT*300;
	}

/*temp_SS=0;
if((bat_Ub[0]>=100)&&(BAT_IS_ON[0]==bisON)&&(bat_rel_stat[0]==0)) temp_SS=bat_Ub[0];
if((bat_Ub[1]>=temp_SS)&&(BAT_IS_ON[1]==bisON)&&(bat_rel_stat[1]==0)) temp_SS=bat_Ub[1];
for(temp=0;temp<NUMIST;temp++)
	{
	if((src[temp]._Uii>200)&&(src[temp]._Uii>temp_SS)&&(src[temp]._cnt<5))
		{
		temp_SS=src[temp]._Uii;
		}
	}
load_U=temp_SS;*/


temp_SL=(signed long)adc_buff_[9];
temp_SL*=Kuload;
temp_SL/=500L;
load_U=(signed short)temp_SL;



	
/*else if (Us[0]>=100) Uload=Us[0];
else Uload=Us[1];*/

/*iload=Is[0]+Is[1]-(bat[0]._Ib/10);
if(iload<0) iload=0;*/




/*
if((adc_buff_[6]>200)&&(adc_buff_[6]<1000))ND[0]=0;
else ND[0]=0xff;
temp_SL=(signed long)adc_buff_[6];
temp_SL*=Ktsrc[0];
temp_SL/=5000L;
temp_SL-=273L;
bat_Tb[0]=(signed short)temp_SL;*/




if((adc_buff_out_[0]>200)&&(adc_buff_out_[0]<800))ND_out[0]=0;
else ND_out[0]=0xff;

temp_SL=(signed long)adc_buff_out_[0];
temp_SL*=Ktout[0];
temp_SL/=2000L;
temp_SL-=273L;
tout[0]=(signed short)temp_SL;


if((adc_buff_out_[1]>200)&&(adc_buff_out_[1]<800))ND_out[1]=0;
else ND_out[1]=0xff;

temp_SL=(signed long)adc_buff_out_[1];
temp_SL*=Ktout[1];
temp_SL/=2000L;
temp_SL-=273L;
tout[1]=(signed short)temp_SL;


if((adc_buff_out_[2]>200)&&(adc_buff_out_[2]<800))ND_out[2]=0;
else ND_out[2]=0xff;

temp_SL=(signed long)adc_buff_out_[2];
temp_SL*=Ktout[2];
temp_SL/=2000L;
temp_SL-=273L;
tout[2]=(signed short)temp_SL;


if((BAT_IS_ON[0]==bisON)&&(bat[0]._Ub>200)) Ibmax=bat[0]._Ib;
if((BAT_IS_ON[1]==bisON)&&(bat[1]._Ub>200)&&(bat[1]._Ib>bat[0]._Ib)) Ibmax=bat[1]._Ib;


/*if((Is[0]+Is[1])>IMAX)
	{
	num_necc=2;
	cnt_num_necc=25;
	}
	
else if(((Is[0]+Is[1])*10)<(IMAX*KIMAX))
	{
	if(cnt_num_necc)
		{
		cnt_num_necc--;
		if(cnt_num_necc==0) num_necc=1;
		}
	}	*/


for(i=0;i<NUMIST;i++)
	{
	if(bps[i]._cnt<25)
     	{
     	bps[i]._Ii=bps[i]._buff[0]+(bps[i]._buff[1]*256);
     	bps[i]._Uin=bps[i]._buff[2]+(bps[i]._buff[3]*256);
     	bps[i]._Uii=bps[i]._buff[4]+(bps[i]._buff[5]*256);
     	bps[i]._Ti=(signed)(bps[i]._buff[6]);
     	bps[i]._adr_ee=bps[i]._buff[7];
     	bps[i]._flags_tm=bps[i]._buff[8];
	     bps[i]._rotor=bps[i]._buff[10]+(bps[i]._buff[11]*256);    
     	} 
	else 
     	{
     	bps[i]._Uii=0; 
     	bps[i]._Ii=0;
     	bps[i]._Uin=0;
     	bps[i]._Ti=0;
     	bps[i]._flags_tm=0; 
	     bps[i]._rotor=0;    
     	}
     
     }



load_I=-(bat[0]._Ib/10)-(bat[1]._Ib/10);

Isumm=0;

for(i=0;i<NUMIST;i++)
     {
     if(bps[i]._cnt<5)Isumm+=bps[i]._Ii;
     }  
     
load_I=load_I+Isumm;
if(load_I<0)load_I=0;
	
}


//-----------------------------------------------
void adc_init(void)
{

SET_REG(PINSEL1,1,(28-16)*2,2);
SET_REG(PINSEL1,1,(29-16)*2,2);
SET_REG(PINSEL1,1,(30-16)*2,2);	

SET_REG(PINSEL0,0,(4)*2,2);
SET_REG(PINSEL0,0,(5)*2,2);
SET_REG(PINSEL0,0,(6)*2,2);

SET_REG(IO0DIR,1,4,1);
SET_REG(IO0DIR,1,5,1);
SET_REG(IO0DIR,1,6,1);

period_cnt=0;
zero_cnt=0;
adc_stat=asNET_WAIT;

SET_REG(ADCR,1,21,1);	//PDN=1;
SET_REG(ADCR,14,8,8);	//CLKDIV=14;
SET_REG(ADCR,0,16,1);	//BURST=0;
SET_REG(ADCR,0,17,3);	//CLKS=0;
SET_REG(ADCR,0,22,2);	//TEST=0;
SET_REG(ADCR,1,24,3);	//START=1;

}

//-----------------------------------------------
void adc_drv(void)
{
short temp_S;
char i;
if(GET_REG( ADDR,31,1))
	{
	plazma_adc_cnt++;
	ADWR=(short)(GET_REG(ADDR,6,10));

	if(adc_stat==asNET_WAIT)
		{
		if(ADWR<20)
			{
			if(zero_cnt<20) 
				{
				zero_cnt++;
				if(zero_cnt>=20)
					{
					adc_stat=asNET_RDY;
					period_cnt=0;
			IO0DIR|=(1<<25);
			IO0CLR|=(1<<25);
					}
				}

			}
		else zero_cnt=0;
		
		period_cnt++;
		if(period_cnt>50)
			{
			adc_stat=asNET_RDY;
			period_cnt=0;
			IO0DIR|=(1<<25);
			IO0CLR|=(1<<25);
			
			}

		}
	 else if(adc_stat==asNET_RDY)
		{
		if(ADWR>20)
			{
			adc_stat=asNET;
			period_cnt=0;
			IO0DIR|=(1<<25);
			IO0SET|=(1<<25);
			net_buff[net_buff_cnt]=0;
			}
		period_cnt++;
		if(period_cnt>200)
			{
			adc_stat=asNET;
			period_cnt=0;
	//		IO0DIR|=(1<<25);
	//		IO0SET|=(1<<25);
			net_buff[net_buff_cnt]=0;
			}
		 }

	else if(adc_stat==asNET)
		{

		net_buff[net_buff_cnt]+=ADWR;
		
		period_cnt++;
		if((ADWR<20)||(period_cnt>100))
			{
			adc_stat=asCH;
			period_cnt=0;
	//		IO0DIR|=(1<<25);
	//		IO0CLR|=(1<<25);
			
			net_buff_cnt++;
			if(net_buff_cnt>=32)
				{
				unsigned long tempUL=0;
				char i;
				net_buff_cnt=0;
				tempUL=0;
				for(i=0;i<32;i++)
					{
					tempUL+=net_buff[i];
					}
				net_buff_=(unsigned short)(tempUL>>5);	
				}
		
			}
		}

	else if(adc_stat==asCH)
		{
		if(++period_cnt>=10)
			{
			period_cnt=0;
			adc_buff[adc_ch][adc_cnt]=ADWR;
		
			if(++adc_ch>=16) 
				{
				adc_ch=0;
				adc_cnt++;
				if(adc_cnt>=16)adc_cnt=0;
				}	

			if((adc_cnt&0x03)==0)
				{
				temp_S=0;
				for(i=0;i<16;i++)
					{
					temp_S+=adc_buff[adc_ch][i];
					adc_buff_[adc_ch]=temp_S>>4;
					}
				}
			
		
			if((adc_ch&0x03)==0) 
				{
				adc_stat=asNET_WAIT;
				IO0DIR|=(1<<25);
				IO0SET|=(1<<25);
				period_cnt=0;
				zero_cnt=0;
				bRELE_OUT=1;
				}
			}




















/*		adc_stat=asNET_WAIT;
		period_cnt=0;
		zero_cnt=0;*/


		} 





/*	if(ADWR>20)
		{
				IO0DIR|=(1<<25);
				IO0SET|=(1<<25);
		}
	if(ADWR<20)
		{
				IO0DIR|=(1<<25);
				IO0CLR|=(1<<25);		} */
	
 /*
	if(adc_stat==asNET_WAIT)
		{
		period_cnt++;
		

		if((period_cnt>200)||((ADWR>100)&&(zero_cnt>10)))
			{
			adc_stat=asNET;
			net_buff[net_buff_cnt]=0;
			IO0CLR|=(1<<25);
			}
		}	
	else if(adc_stat==asNET)
		{
		net_buff[net_buff_cnt]+=ADWR;
		
		if((ADWR<100)||(++period_cnt>300))
			{
			adc_stat=asCH;
			period_cnt=0;
			net_buff_cnt++;
			if(net_buff_cnt>=32)
				{
				unsigned long tempUL=0;
				char i;
				net_buff_cnt=0;
				tempUL=0;
				for(i=0;i<32;i++)
					{
					tempUL+=net_buff[i];
					}
				net_buff_=(unsigned short)(tempUL>>5);	
				}
			net_buff[net_buff_cnt]=0;
			}	
		}
	else if(adc_stat==asCH)
		{
		if(++period_cnt>=20)
			{
			period_cnt=0;
			adc_buff[adc_ch][adc_cnt]=ADWR;
		
			if((adc_cnt&0x03)==0)
				{
				temp_S=0;
				for(i=0;i<16;i++)
					{
					temp_S+=adc_buff[adc_ch][i];
					adc_buff_[adc_ch]=temp_S>>4;
					}
				}
			if(++adc_ch>=16) 
				{
				adc_ch=0;
				adc_cnt++;
				if(adc_cnt>=16)adc_cnt=0;
				}	
		
			if((adc_ch&0x01)==0) 
				{
				adc_stat=asNET_WAIT;
				period_cnt=0;
				zero_cnt=0;
				//bRELE_OUT=1;
				}
			}*//*
				adc_stat=asNET_WAIT;
				period_cnt=0;
				zero_cnt=0;
				IO0DIR|=(1<<25);
				IO0SET|=(1<<25);								
		}				    */	
	} 
	






/*
if(adc_ch&0x02)	SET_REG(IO0SET,1,5,1);
else 			SET_REG(IO0CLR,1,5,1);
if(adc_ch&0x04)	SET_REG(IO0SET,1,6,1);
else 			SET_REG(IO0CLR,1,6,1);
if(adc_ch&0x08)	SET_REG(IO0SET,1,4,1);
else 			SET_REG(IO0CLR,1,4,1); 
								  */
/*
ADCR|=(1<<21);
ADCR=(ADCR&0xffff00ff)|(14<<8);
ADCR=(ADCR&0xfffeffff)|(1<<16);
ADCR&=0xfff1ffff;
ADCR&=0xff3fffff;



PINSEL2&=~(1<<18);
PINSEL2&=~(1<<19);*/


IO1DIR|=(1<<25);
IO1SET|=(1<<25);

if(bRELE_OUT==1)
	{
	char i,temp;
/*	IO1DIR|=(1<<25);
	IO1CLR|=(1<<25);*/
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	IO0CLR|=(1<<6);
	
	bRELE_OUT=0;
//	rele_stat=1;
	temp=rele_stat;
	for(i=0;i<8;i++)
		{
		if(temp&0x80)IO0SET|=(1<<4);
		else IO0CLR|=(1<<4);
		__nop(); 
		__nop();
		__nop();
		__nop();
		IO0SET|=(1<<6);
		__nop();
		__nop();
		__nop();
		__nop();
		__nop(); 
		__nop();
		__nop();
		__nop();
		IO0CLR|=(1<<6);
		__nop();
		__nop();
		__nop();
		__nop();
		temp<<=1;		
		}
	IO1DIR|=(1<<25);
	IO1CLR|=(1<<25);		
	IO1DIR|=(1<<25);
	IO1SET|=(1<<25);

	
		
	}
else 
	{

	if(adc_ch&0x02)	SET_REG(IO0SET,1,5,1);
	else 			SET_REG(IO0CLR,1,5,1);
	if(adc_ch&0x04)	SET_REG(IO0SET,1,6,1);
	else 			SET_REG(IO0CLR,1,6,1);
	if(adc_ch&0x08)	SET_REG(IO0SET,1,4,1);
	else 			SET_REG(IO0CLR,1,4,1); 

	}	
	
if((adc_stat==asNET)
||(adc_stat==asNET_WAIT)
||(adc_stat==asNET_RDY)) 	SET_REG(ADCR,2,0,8);
else if(adc_ch&0x01)		SET_REG(ADCR,8,0,8);
else 					SET_REG(ADCR,4,0,8); 
					   
SET_REG(ADCR,1,24,3);	//START=1;
}
 /*
//-----------------------------------------------
void adc_drv_()
{
short temp_S;
char i;
adc_ch=4;
if(ADDR&0x00000001)
	{
	ADWR=ADDR_bit.VVDDA;
	
	if(++period_cnt>=200)
		{
		period_cnt=0;
		adc_buff[adc_ch][adc_cnt]=ADWR;
		
		if((adc_cnt&0x03)==0)
			{
			temp_S=0;
			for(i=0;i<16;i++)
				{
				temp_S+=adc_buff[adc_ch][i];
				}
			adc_buff_[adc_ch]=temp_S>>4;
			uart_out0(2,*((char*)&adc_buff_[adc_ch]),*(((char*)&adc_buff_[adc_ch])+1),0,0,0,0);

			}
		adc_cnt++;
		if(adc_cnt>=16)adc_cnt=0;
		
		}
	}

PINSEL1_bit.P0_28=1;	
PINSEL1_bit.P0_29=1;	
PINSEL1_bit.P0_30=1;	

PINSEL0_bit.P0_4=0;
PINSEL0_bit.P0_5=0;
PINSEL0_bit.P0_6=0;

IO0DIR_bit.P0_4=1;
IO0DIR_bit.P0_5=1;
IO0DIR_bit.P0_6=1;


if(adc_ch&0x02)IO0SET|=((long)1UL<<5);
else IO0CLR|=((long)1UL<<5);
if(adc_ch&0x04)IO0SET|=((long)1UL<<6);
else IO0CLR|=((long)1UL<<6);
if(adc_ch&0x08)IO0SET|=((long)1UL<<4);
else IO0CLR|=((long)1UL<<4);

ADCR_bit.PDN=1;
ADCR_bit.CLKDIV=14;
ADCR_bit.BURST=0;
ADCR_bit.CLKS=0;
ADCR_bit.TEST=0;

ADCR_bit.SEL=4;
ADCR_bit.START=1;
	

}
*/



//-----------------------------------------------
void avg_hndl(void)
{ 
char i;

#define AVGCNTMAX	5
if(avg_main_cnt)
	{
	avg_main_cnt--;
	goto avg_hndl_end;
	}                 

avg_num=0;

for(i=0;i<NUMIST;i++)
	{
	if((bps[i]._state==bsWRK)&&(bps[i]._cnt<20))avg_num++;
	}

/*if((K[NUMI]>=1)&&(bps_state[0]==ssWRK))	avg_num++;
if((K[NUMI]>=2)&&(bps_state[1]==ssWRK))	avg_num++;
if((K[NUMI]>=3)&&(bps_state[2]==ssWRK))	avg_num++;*/

	
if(avg_num<2)
	{
	goto avg_hndl_end;
	}
	
else
	{
	i_avg_min=5000;
	i_avg_max=0;
	i_avg_summ=0;
	for(i=0;i<NUMIST;i++)
		{
		if(bps[i]._state==bsWRK)
			{
			if(bps[i]._Ii>i_avg_max)i_avg_max=bps[i]._Ii;
			if(bps[i]._Ii<i_avg_min)i_avg_min=bps[i]._Ii;
			
			i_avg_summ+=bps[i]._Ii;
			}
		}
	i_avg=i_avg_summ/avg_num;	
	
	if(i_avg_min==0)i_avg_min=1;

	avg=i_avg_max;
	avg*=100;
	avg/=i_avg_min;

	if(avg>160) bAVG=1;
	if(avg<120) bAVG=0;

	if(bAVG==1)
		{
		for(i=0;i<NUMIST;i++)
			{
			if(bps[i]._state==bsWRK)
				{
				if(bps[i]._Ii>i_avg)bps[i]._x_--;
				if(bps[i]._Ii<i_avg)bps[i]._x_++;
			
				if(bps[i]._x_<-50)bps[i]._x_=-50;
				if(bps[i]._x_>50)bps[i]._x_=50;	
				}
			}		
		}			
	}   	 


avg_hndl_end:
__nop();  
}

/*//-----------------------------------------------
void bp_on_(char in)
{
bp_tumbler[in-1]=1;
}

//-----------------------------------------------
void bp_off_(char in)
{
bp_tumbler[in-1]=0;
}
 */
//-----------------------------------------------
void rele_hndl(void)
{
static char cnt_rel_sam;
char temp;
/*if(mess_find(MESS_BAT1_OFF))rele_stat|=(1<<6);
else rele_stat&=(~(1<<6));

if(mess_find(MESS_BAT2_OFF))rele_stat|=(1<<4);
else rele_stat&=(~(1<<4));*/

/*if(mess_find(MESS_BAT_CONTROL))
	{
	if(mess_data[0]&0x0001)cnt_rel_bat[0]=20;//rele_stat|=(1<<6);
	if(mess_data[0]&0x0002)cnt_rel_bat[1]=20;//rele_stat|=(1<<4);
	if(mess_data[1]&0x0001)
		{
		cnt_rel_bat[0]=0;
		rele_stat&=(~(1<<6));
		}
	if(mess_data[1]&0x0002)
		{
		cnt_rel_bat[1]=0;
		rele_stat&=(~(1<<4));
		}
	}*/
//else rele_stat&=(~(1<<4))&(~(1<<6));	

if(mess_find(MESS_RELSAM_ON))
	{
	cnt_rel_sam=10;
	//IO1DIR=(1UL<<21);
	//IO1SET=(1UL<<21);
	}
/*else
	{
	if(mess_find(MESS_BAT_CONTROL))
	{	*/
/*
if(cnt_rel_bat[0])
	{
	cnt_rel_bat[0]--;
	rele_stat&=(~(1<<6));
	if(!cnt_rel_bat[0])rele_stat|=(1<<6);
	}


if(cnt_rel_bat[1])
	{
	cnt_rel_bat[1]--;
	rele_stat&=(~(1<<4));
	if(!cnt_rel_bat[1])rele_stat|=(1<<4);
	}*/


temp=0;

if(bat[0]._rel_stat)
	{
	temp|=(1<<SHIFT_REL_BAT1);
	}  
//else rele_stat&=(~(1<<6));	

if(bat[1]._rel_stat)
	{
	temp|=(1<<SHIFT_REL_BAT2);
	}
//else rele_stat&=(~(1<<4));



if(cnt_rel_sam) cnt_rel_sam--;

IODIR1|=(1UL<<21);	
if(mess_find_unvol((MESS2RELE_HNDL))&&(PARAM_RELE_SAMOKALIBR_ENABLE)) IOSET1=(1UL<<21);
else if (cnt_rel_sam) IOSET1=(1UL<<21);
else IOCLR1=(1UL<<21);



if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV))
	{
	if(mess_data[1]==0) temp|=(1<<SHIFT_REL_AV);
	}
else 
	{
	if(!(avar_ind_stat)) temp|=(1<<SHIFT_REL_AV);
	}

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
	{
	if(mess_data[1]==0) temp|=(1<<SHIFT_REL_AV_NET);
	}
else 
	{
	if(!(avar_ind_stat&0x00000001)) temp|=(1<<SHIFT_REL_AV_NET);
	}


if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
	{
	if(mess_data[1]==0) temp|=(1<<SHIFT_REL_AV_BAT);
	}
else 
	{
	if(!(avar_ind_stat&0x00000006)) temp|=(1<<SHIFT_REL_AV_BAT);
	}

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT))
	{
	if(mess_data[1]==0) temp|=(1<<SHIFT_REL_VENT);
	}
else 
	{
	if(!vent_stat) temp|=(1<<SHIFT_REL_VENT);
	}

rele_stat=temp;

}

//-----------------------------------------------
void bps_hndl(void)
{
static unsigned char sh_cnt0/*,sh_cnt1,sh_cnt2,*/,b1Hz_sh/*,b2Hz_sh*/;
char ptr__,i;

if(sh_cnt0<10)
	{
	sh_cnt0++;
	if(sh_cnt0>=10)
		{
		sh_cnt0=0;
		b1Hz_sh=1;
		}
	}














/*if(sh_cnt1<5)
	{
	sh_cnt1++;
	if(sh_cnt1==5)
		{
		sh_cnt1=0;
		b2Hz_sh=1;
		}
	} */


/*
if(mess_find(MESS_SRC_ON_OFF))
	{
	if(mess_data[0]==_MESS_SRC_MASK_BLOK_2SEC)
		{
		char i;
		for(i=0;i<NUMIST;i++)
			{
			if(mess_data[1]&(1<<i))src[i]._ist_blok_cnt=20;
			}
		
		}
	else if(mess_data[0]==_MESS_SRC_MASK_UNBLOK)
		{
		char i;
		for(i=0;i<NUMIST;i++)
			{
			if(mess_data[1]&(1<<i))src[i]._ist_blok_cnt=0;
			}
		
		}
	}
	
else if(mess_find(_MESS_SRC_MASK_ON))
	{				
	if(mess_data[0]==_MESS_SRC_MASK_ON)
		{
		char i;
		for(i=0;i<NUMIST;i++)
			{
			if(mess_data[1]&(1<<i))
				{
				src[i]._ist_blok_cnt=0;
				src[i]._flags_tu=2;
				}
			}
		
		}				
	}*/



/*else*/ 
bps_on_mask=0;
bps_off_mask=0;

if(mess_find_unvol(MESS2BPS_HNDL))
	{
	if(mess_data[0]==PARAM_BPS_ALL_OFF_AFTER_2SEC)
		{
		bps_off_mask=0xffff;
		}

	if(mess_data[0]==PARAM_BPS_MASK_OFF_AFTER_2SEC)
		{
		bps_off_mask=mess_data[1];
		}

	if(mess_data[0]==PARAM_BPS_MASK_ON)
		{
		bps_on_mask=mess_data[1];
		}

	if(mess_data[0]==PARAM_BPS_ALL_ON)
		{
		bps_on_mask=0xffff;
		}

	if(mess_data[0]==PARAM_BPS_MASK_ON_OFF_AFTER_2SEC)
		{
		bps_on_mask=mess_data[1];
		bps_off_mask=~(mess_data[1]);
		}


	for(i=0;i<=NUMIST;i++)
		{
		if(bps_off_mask&(1<<i)) bps[i]._blok_cnt++;
		else bps[i]._blok_cnt=0;
		gran(&bps[i]._blok_cnt,0,50);
		if(bps[i]._blok_cnt>20) bps[i]._flags_tu=1;
		if(bps_on_mask&(1<<i)) bps[i]._flags_tu=0;
	     }

	
/*

	if(bps_all_off_cnt>20)
		{
		for(i=0;i<=NUMIST;i++)
			{
	     	bps[i]._flags_tu=1;
	     	}
		}
	else if(bps_mask_off_cnt>20)
		{
		for(i=0;i<=NUMIST;i++)
			{
			if(mess_data[1]&(1<<i)) bps[i]._flags_tu=1;
	     	}
		}	
		
	else if(bps_mask_on_off_cnt>20)
		{
		for(i=0;i<=NUMIST;i++)
			{
			if(mess_data[1]&(1<<i)) bps[i]._flags_tu=1;
			else bps[i]._flags_tu=0;
	     	}
		}
		
	if(mess_data[0]==PARAM_BPS_MASK_ON)
		{
		for(i=0;i<=NUMIST;i++)
			{
			if(mess_data[1]&(1<<i)) bps[i]._flags_tu=0;
	     	}
		}
*/										
	}


else if(b1Hz_sh)
	{
	ptr__=0;
     for(i=0;i<=NUMIST;i++)
		{
	     bps[i]._flags_tu=1;
	     }	
  	     
  	for(i=0;(i<NUMIST)&&(ptr__<num_necc);i++)
  		{
  	     if((bps[i]._state==bsRDY)||(bps[i]._state==bsWRK))
  	         	{
  	         	bps[i]._flags_tu=0;
  	         	ptr__++;
  	         	}
  	     } 
  	}


for(i=0;i<NUMIST;i++)
     {
     if(bps[i]._ist_blok_host_cnt!=0)
          {
          bps[i]._flags_tu=99;
	     bps[i]._ist_blok_host_cnt--;
          }
     }




b1Hz_sh=0;


num_of_wrks_bps=0;
for(i=0;i<NUMIST;i++)
	{
	if(bps[i]._state==bsWRK)num_of_wrks_bps++;
	}
}

//биты аварий в приходящих сообщениях от источников
#define AV_T	1
#define AVUMAX	3
#define AVUMIN	4

//-----------------------------------------------
void bps_drv(char in)
{
char temp;
temp=bps[in]._flags_tm;

if(!(temp&(1<<AV_T)))
	{
	if(bps[in]._temp_av_cnt) 
		{
		bps[in]._temp_av_cnt=0;
		/*if((av_cnt_bps[in,0]<=0)&&(K[NUMI]>in))
			{    */
			//av_cnt_bps[in,0]=0;
	//	    	avar_s_hndl(in,0,0);

		/*	} */
		} 	

	}

else if(temp&(1<<AV_T))
	{
	if(bps[in]._temp_av_cnt<1200) 
		{
		bps[in]._temp_av_cnt++;
		if(bps[in]._temp_av_cnt>=1200)
			{
			bps[in]._temp_av_cnt=1200;
		   //	avar_s_hndl(in,0,1);
			}
		}
	//else if(av_cnt_bps[in,0]>10) av_cnt_bps[in,0]--;	 
	}


		
/*if((temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt) 
		{
		bps[in]._umax_av_cnt--;
		if(bps[in]._umax_av_cnt<=0)
			{
			bps[in]._umax_av_cnt=0;
		  	if((K[APV]!=ON)||((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afOFF)))avar_s_hndl(in,1,1);
			if((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afON))
				{
				apv_cnt[in,0]=APV_INIT;
				apv_cnt[in,1]=APV_INIT;
				apv_cnt[in,2]=APV_INIT;
				apv_flags[in]=afOFF;
				}			
			}
		} 
	}		
else if(!(temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt<10) 
		{
		bps[in]._umax_av_cnt++;
		if(bps[in]._umax_av_cnt>=10)
			{
			bps[in]._umax_av_cnt=10;
			avar_s_hndl(in,1,0);
	 //		apv_cnt[in,0]=0;
	//		apv_cnt[in,1]=0;
	 //		apv_cnt[in,2]=0;			
			}
		}
	else if(bps[in]._umax_av_cnt>10) bps[in]._umax_av_cnt--;		 
	}

if(temp&(1<<AVUMIN))
	{
	if(bps[in]._umin_av_cnt) 
		{
		bps[in]._umin_av_cnt--;
		if(bps[in]._umin_av_cnt<=0)
			{
			bps[in]._umin_av_cnt=0;
	    		if((K[APV]!=ON)||((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afOFF)))avar_s_hndl(in,2,1);
			if((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afON))
				{
				apv_cnt[in,0]=APV_INIT;
				apv_cnt[in,1]=APV_INIT;
				apv_cnt[in,2]=APV_INIT;
				apv_flags[in]=afOFF;
				}				
			}
		} 
	}	
	
else if(!(temp&(1<<AVUMIN)))
	{
	if(bps[in]._umin_av_cnt<10) 
		{
		bps[in]._umin_av_cnt++;
		if(bps[in]._umin_av_cnt>=10)
			{
			bps[in]._umin_av_cnt=10;
		///////	avar_s_hndl(in,2,0);
		//	apv_cnt[in,0]=0;
		//	apv_cnt[in,1]=0;
		//	apv_cnt[in,2]=0;
			}
		}
	else if(bps[in]._umin_av_cnt>10)bps[in]._umin_av_cnt--;	 
	}*/



if (bps[in]._av&0x0f)					bps[in]._state=bsAV;
else if ( (net_av) && 
		(bps[in]._Uii<200))				bps[in]._state=bsOFF_AV_NET;
else if (bps[in]._flags_tm&BIN8(100000))	bps[in]._state=bsRDY;
else if (bps[in]._cnt<20)				bps[in]._state=bsWRK;



//else if(bps[in]._flags_tm&BIN8(100000)) bps[in]._state=ssBL;
//else if((!(bps[in]._flags_tm&BIN8(100000)))&&(net_U>100))bps[in]._state=ssWRK;
//else bps[0]._state=ssNOT;

//bps[in]._is_ready=0;
//bps[in]._is_wrk=0;
//if(bps[in]._av_net) bps[in]._flags_bp='N';// не подключен
//else if(bps[in]._av_u_max) bps[in]._flags_bp='P';// завышено напряжение(u_.av_.bAS1T)) bps_state[0]=ssAV;
//else if(bps[in]._av_u_min) bps[in]._flags_bp='M';// занижено напряжение
//else if(bps[in]._av_temper) bps[in]._flags_bp='T';// температура
//else if(bps[in]._flags_tm&BIN8(100000)) 
//	{
//	bps[in]._flags_bp='B';// заблокирован
//	bps[in]._is_ready=1;
//	}
//else if((!(bps[in]._flags_tm&BIN8(100000)))&&(net_U>100))
//     {
//     bps[in]._flags_bp='W';// работает
//     bps[in]._is_ready=1;
//     bps[in]._is_wrk=1;
     
//     }
//else bps[in]._is_ready=1;     





/*
bps[in]._flags_tu&=BIN8(11111110);
if(bps[in]._ist_blok_cnt)
	{
	bps[in]._ist_blok_cnt--;
	bps[in]._flags_tu|=BIN8(1);
	}

	   */ 

//Пересброс БПСа при потере связи
if(bps[in]._cnt>=10) bps[in]._flags_tu|=BIN8(10000000);
else bps[in]._flags_tu&=BIN8(1111111);
	
bps[in]._vol_u=cntrl_stat+bps[in]._x_;	
 
}

//-----------------------------------------------
void bat_hndl(void)
{
/*if(mess_find(_MESS_BAT_MASK_ON))
	{
	if(mess_data[0]==_MESS_BAT_MASK_ON)
		{
		char i;
		for(i=0;i<2;i++)
			{
			if(mess_data[1]&(1<<i))
				{
				bat[i]._cnt_to_block=0;
     			bat[i]._rel_stat=0;
     			}
			}
		}
	}
if(mess_find(_MESS_BAT_MASK_OFF))
	{		
	if(mess_data[0]==_MESS_BAT_MASK_OFF)
		{
		char i;
		for(i=0;i<2;i++)
			{
			if((mess_data[1]&(1<<i)) && (bat[i]._cnt_to_block==0) && (bat[i]._rel_stat==0))
				{
				bat[i]._cnt_to_block=20;
				bat[i]._rel_stat=1;
     			}
			}
		
		}		
	}*/

if(mess_find_unvol(MESS2BAT_HNDL))
	{ 
	char i;
	
	if(mess_data[0]==PARAM_BAT_ALL_OFF_AFTER_2SEC)
		{
		for(i=0;i<MAX_NUM_OF_BAT;i++)
			{
			if(bat[i]._cnt_to_block<50)bat[i]._cnt_to_block++;
			}
		}

	else if(mess_data[0]==PARAM_BAT_MASK_OFF_AFTER_2SEC)
		{
		for(i=0;i<MAX_NUM_OF_BAT;i++)
			{
			if(mess_data[1]&(1<<i))
				{
				if(bat[i]._cnt_to_block<50) bat[i]._cnt_to_block++;
				}
			else bat[i]._cnt_to_block=0;
			}
		}
	else 
	 	{
		for(i=0;i<MAX_NUM_OF_BAT;i++)
			{
			bat[i]._cnt_to_block=0;
			}

		}
	for(i=0;i<MAX_NUM_OF_BAT;i++)
		{
		if(bat[i]._cnt_to_block>20)bat[i]._rel_stat=1;
		else bat[i]._rel_stat=0;
		}

	}

else 
	{
	char i;
	for(i=0;i<MAX_NUM_OF_BAT;i++)
		{
		bat[i]._cnt_to_block=0;
		bat[i]._rel_stat=0;
		}

	}

/*if(mess_find_unvol(MESS2BAT_HNDL1))
	{
	if(PARAM_BAT_ON)
		{
		char i;
		for(i=0;i<MAX_NUM_OF_BAT;i++)
			{
			if(mess_data[1]&(1<<i))
				{
				bat[i]._cnt_to_block=0;
				bat[i]._rel_stat=0;
				}
			}
		}
	} */
}

//-----------------------------------------------
void bat_drv(char in)
{

if(main_10Hz_cnt==50)
	{
	if(!bat[in]._rel_stat)
		{
		if(bat[in]._Ub<80) avar_bat_hndl(in,1);
		}
	}







/*if(bat[in]._cnt_to_block)
	{
	bat[in]._cnt_to_block--;
	if(!(bat[in]._cnt_to_block))
		{
		//bat[in]._rel_stat=1;
		}
	}
*/







}






	






//-----------------------------------------------
void u_necc_hndl(void)
{
signed long temp_SL;
//signed short temp_SS;
static unsigned char unh_cnt0,unh_cnt1/*,unh_cnt2*/,b1Hz_unh/*,b2Hz_unh*/;
signed short t[2];
char i;

//temp_SS=0;


if(unh_cnt0<10)
	{
	unh_cnt0++;
	if(unh_cnt0>=10)
		{
		unh_cnt0=0;
		b1Hz_unh=1;
		}
	}

if(unh_cnt1<5)
	{
	unh_cnt1++;
	if(unh_cnt1==5)
		{
		unh_cnt1=0;
//		b2Hz_unh=1;
		}
	} 



if(mess_find_unvol(MESS2UNECC_HNDL))
	{		
	if(mess_data[0]==PARAM_UNECC_SET)
		{
		u_necc=mess_data[1];
		}		
	}


else if(b1Hz_unh)
	{
	
	if((BAT_IS_ON[0]!=bisON) && (BAT_IS_ON[1]!=bisON))
		{
		u_necc=U0B;
		}
	else 
		{
		for(i=0;i<2;i++)
			{
			if(BAT_IS_ON[i]==bisON)
				{
				if(bat[1]._nd)t[i]=20;
				else t[i]=bat[i]._Tb;
				}
			else
				{
				t[i]=-20;
				}
			}
		if(t[0]>t[1])mat_temper=t[0];
		else mat_temper=t[1];
		
	
		if(mat_temper<0)temp_SL=UB0; 
		else 
			{
			if(mat_temper>40)mat_temper=40; 
			temp_SL=(UB20-UB0)*10;
			temp_SL*=mat_temper;
			temp_SL/=200;
			temp_SL+=UB0;
			}
		if(spc_stat==spcVZ)
			{
			temp_SL*=KVZ;
			temp_SL/=1000U;
			}
		u_necc=(unsigned int)temp_SL;
		}  
	}






gran(&u_necc,400,UMAX);
}


//-----------------------------------------------
void num_necc_hndl(void)
{
//signed short tempSS;

//tempSS==num_necc-1;
//gran(&tempSS,0,NUMIST);

num_necc_Imax=IMAX*num_necc;
num_necc_Imin=(IMAX*num_necc)-(2*IMAX)+((IMAX*KIMAX)/10);

if((Isumm>num_necc_Imax)&&(num_necc<NUMIST)) num_necc++;
else if ((Isumm<num_necc_Imin)&&(num_necc>1)) num_necc--;

if(PAR) num_necc=NUMIST;

gran(&num_necc,1,NUMIST);

}

//-----------------------------------------------
void cntrl_hndl(void)
{
static char	ch_cnt0,b1Hz_ch;

if(ch_cnt0<10)
	{
	ch_cnt0++;
	if(ch_cnt0>=10)
		{
		ch_cnt0=0;
		b1Hz_ch=1;
		}
	}
//signed long temp_L;

//plazma=0;

/*if(St&0x01)
	{
	cntrl_stat=0;
     old_cntrl_stat=0;
     }
else*//* if((kb_cnt[0]>15)&&(kb_cnt[0]<=30))
	{
	cntrl_stat=old_cntrl_stat-30;
	gran(&cntrl_stat,30,970);
	}
else*/ /*if((kb_cnt[0]<=15)&&(kb_cnt[0]>0))
	{
	cntrl_stat=old_cntrl_stat+30;
	gran(&cntrl_stat,30,970);
	} 
else*//* if((kb_cnt[1]>15)&&(kb_cnt[1]<=30))
	{
	cntrl_stat=old_cntrl_stat-100;
	gran(&cntrl_stat,30,970);
	}
else if((kb_cnt[1]<=15)&&(kb_cnt[1]>0))
	{
	cntrl_stat=old_cntrl_stat+100;
	gran(&cntrl_stat,30,970);
	}
else if(kb_full_ver)
	{
	cntrl_stat-=50;
	if(cntrl_stat<30)
		{
		if((av_stat&0x0002)==0)avar_bat_hndl(1);
		kb_full_ver=0;
		gran(&TBAT,5,60);
     	bat_ver_cnt=TBAT*300;
		}
	gran(&cntrl_stat,30,970);
	} 	 	


else*/ 
/*if(mess_find(_MESS_FAST_REG))
	{
 	if(load_U>u_necc)
		{
		if(((load_U-u_necc)>10)&&(cntrl_stat>0))cntrl_stat-=50;
		else if(cntrl_stat)cntrl_stat--;
		}
	else if(load_U<u_necc)
		{
		if(((u_necc-load_U)>10)&&(cntrl_stat<1015))cntrl_stat+=50;
		else	if(cntrl_stat<1020)cntrl_stat++;
		}		
	}


if(mess_find(_MESS_SRC_PWM))
	{				
	if(mess_data[0]==_MESS_SRC_PWM)
		{
		cntrl_stat=mess_data[1];
		}				
	}  */


//cntrl_stat++;



if(mess_find_unvol(MESS2CNTRL_HNDL))
	{
	if(mess_data[0]==PARAM_CNTRL_STAT_PLUS)
		{
		cntrl_stat=cntrl_stat_old+mess_data[1];
		}
	else if(mess_data[0]==PARAM_CNTRL_STAT_MINUS)
		{
		cntrl_stat=cntrl_stat_old-mess_data[1];
		}
	else if(mess_data[0]==PARAM_CNTRL_STAT_STEP_DOWN)
		{
		cntrl_stat--;

		if((cntrl_stat<=30)||(load_U<USIGN)) mess_send(MESS2KB_HNDL,PARAM_CNTRL_IS_DOWN,0,10);

		}
	else if(mess_data[0]==PARAM_CNTRL_STAT_SET)
		{
		cntrl_stat=mess_data[1];
		}

	else if(mess_data[0]==PARAM_CNTRL_STAT_FAST_REG)
		{
		if(load_U>u_necc)
			{
			if(((load_U-u_necc)>10)&&(cntrl_stat>0))cntrl_stat-=5;
			else if((cntrl_stat)&&b1Hz_ch)cntrl_stat--;
			}
		else if(load_U<u_necc)
			{	
			if(((u_necc-load_U)>10)&&(cntrl_stat<1015))cntrl_stat+=5;
			else	if((cntrl_stat<1020)&&b1Hz_ch)cntrl_stat++;
			}	
		 }

	}

else if(b1Hz_ch)
	{
	cntrl_stat_new=cntrl_stat_old;
	
	if((Ibmax/10)>(2*IZMAX))
		{
		cntrl_stat_new-=50;
		}		
	else if(((Ibmax/10)<(IZMAX*2))&&(Ibmax>(IZMAX*11)))
		{
		cntrl_stat_new-=5;
		}   
	else if((Ibmax<(IZMAX*11))&&((Ibmax/10)>IZMAX))
		{
		cntrl_stat_new--;
		}
		
	else if(load_U<u_necc)
		{
		if(load_U<(u_necc-(UB0-UB20)))
			{
			if(Ibmax<0)
				{
				cntrl_stat_new+=50;
				}
			else if(Ibmax<(IZMAX*5))
				{
				cntrl_stat_new+=5;
				}
			else if(Ibmax<((IZMAX*95)/10))
				{
				cntrl_stat_new++;
				}					
			}
		else if(load_U<(u_necc-((UB0-UB20)/4)))
			{
			if(Ibmax<(IZMAX*5))
				{
				cntrl_stat_new+=5;
				}
			else if(Ibmax<((IZMAX*95)/10))
				{
				cntrl_stat_new++;
				}					
			}	
		else if(load_U<(u_necc-1))
			{
			if(Ibmax<((IZMAX*95)/10))
				{
				cntrl_stat_new++;
				}					
			}					
		}	
	else if((load_U>u_necc)/*&&(!cntrl_blok)*/)
		{
		if(load_U>(u_necc+(UB0-UB20)))
			{
			cntrl_stat_new-=30;
			}
		else if(load_U>(u_necc+((UB0-UB20)/4)))
			{
			cntrl_stat_new-=5;
			}	
		else if(load_U>(u_necc+1))
			{
			cntrl_stat_new--;
			}					
		}
	gran(&cntrl_stat_new,10,1010);			
	cntrl_stat_old=cntrl_stat_new;
	cntrl_stat=cntrl_stat_new;	
	}

	
gran(&cntrl_stat,10,1010); 
b1Hz_ch=0;
}
 
//-----------------------------------------------
void zar_drv(void)
{
unsigned short tempUS,tempUS_;
unsigned short int b_zar; 
char i;
//Ibat[0]=5000;                     
                            
for (i=0;i<2;i++)
	{
	if(BAT_C_REAL[i]==0x5555) tempUS_=BAT_C_NOM[i]*10;
	else tempUS_=BAT_C_REAL[i];
          
     b_zar=bat[i]._zar;
          
	if((bat[i]._Ib>-10000L)&&(bat[i]._Ib<10000L))
		{
		if(bat[i]._Ib<0)
			{
			if((b_zar>0)||((b_zar==0)&&(bat[i]._zar_cnt>0))) 
				{
				bat[i]._zar_cnt+=bat[i]._Ib;
				if(bat[i]._zar_cnt<=-360000L)
					{
					bat[i]._zar_cnt=0;
					
					tempUS=bat[i]._zar;
					
					if(tempUS)
						{
						tempUS--;
						lc640_write_int(ptr_bat_zar_cnt[i],tempUS);
                              }
			          }
			 	}
			}
		else if(bat[i]._Ib>0)
			{           
			if(b_zar>((tempUS_/10)+1))
				{
				lc640_write_int(ptr_bat_zar_cnt[i],tempUS);
				bat[i]._zar_cnt=0;
				}    
			else if((b_zar<=tempUS_/10)/*||((b_zar==tempUI_/10)*//*&&(zar_cnt[i]<0))*/)
				{
				bat[i]._zar_cnt+=(bat[i]._Ib*100L)/KOEFPOT;
				if(bat[i]._zar_cnt>=360000L)
					{
					tempUS=lc640_read_int(ptr_bat_zar_cnt[i]); 
										
					if(tempUS<=tempUS_/10)
						{
						tempUS++;
						lc640_write_int(ptr_bat_zar_cnt[i],tempUS);
                              bat[i]._zar_cnt=0;
						}
					}
				}	
			}
		}	
			
	tempUS=lc640_read_int(ptr_bat_zar_cnt[i]);
		           	
	tempUS*=10;
	tempUS+=(int)(bat[i]._zar_cnt/36000L);
	tempUS*=100;

	if(tempUS_==0) tempUS=0;
	else tempUS/=tempUS_;

/*	Zbat[i]=(signed)tempUI;
	gran(&Zbat[i],0,100); */
     }
 /*    
if(wrk[0]==ON)
	{
	if(Ibat_integr[0]<36000)
		{          
		Ibat_integr[0]+=abs(Ibat[0]);
		if(Ibat_integr[0]>=36000)
			{
			Ibat_integr[0]=0;
			Ibat_integr_[0]++;
			}
		}
	else 
		{
		Ibat_integr[0]=0;
		}	
	}     

if(wrk[1]==ON)
	{
	if(Ibat_integr[1]<36000)
		{          
		Ibat_integr[1]+=abs(Ibat[1]);
		if(Ibat_integr[1]>=36000)
			{
			Ibat_integr[1]=0;
			Ibat_integr_[1]++;
			}
		}
	else 
		{
		Ibat_integr[1]=0;
		}	
	}     
*/		
}



