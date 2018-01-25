//#include "25lc640.h"
#include "control.h"
#include "mess.h"
#include "gran.h"
#include "common_func.h"
#include "eeprom_map.h"
#include "avar_hndl.h"
#include "main.h"
#include "beep.h"
#include "snmp_data_file.h" 
#include "sacred_sun.h"
#include <LPC17xx.h>

#define KOEFPOT  105L







extern signed short u_necc,u_necc_,u_necc_up,u_necc_dn;
extern signed short main_cnt_5Hz;
extern signed short num_necc;
extern signed short num_necc_Imax;
extern signed short num_necc_Imin;
//extern char bSAME_IST_ON;
//extern signed short Unet,unet_store;
//extern char bat_cnt_to_block[2];
//extern enum  {bisON=0x0055,bisOFF=0x00aa}BAT_IS_ON[2];
extern signed mat_temper;




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
}a__,a_;

//***********************************************
//АЦП
long adc_buff[16][16];
signed short adc_buff_max[12],adc_buff_min[12]={5000,5000,5000,5000,5000,5000,5000,5000,5000,5000},unet_buff_max,unet_buff_min=5000;
char adc_self_ch_cnt,adc_ch_net;
short adc_buff_[16];
char adc_cnt,adc_cnt1,adc_ch,adc_ch_cnt;
short zero_cnt;
enum_adc_stat adc_stat=asCH;
unsigned short net_buff[32],net_buff_,net_metr_buff_[3];
char net_buff_cnt;
short ADWR,period_cnt,non_zero_cnt;
char rele_stat;
char bRELE_OUT;
signed short adc_self_ch_buff[3],adc_self_ch_disp[3];
long main_power_buffer[8],main_power_buffer_;
short adc_result;
short main_power_buffer_cnt;
short adc_gorb_cnt,adc_zero_cnt;
char adc_window_flag;
short adc_window_cnt;
short adc_net_buff_cnt;


extern int mess_par0[MESS_DEEP],mess_par1[MESS_DEEP],mess_data[2];

extern signed short TBAT;
extern signed short Kunet;
extern signed short Kubat[2];

extern unsigned short Kibat0[2];
extern signed short Kibat1[2];
extern signed short Ktbat[2];
//extern signed short bat_Ib[2];
short adc_buff_out_[3];
extern char kb_full_ver;
extern signed short Kuload;

signed short bat_ver_cnt=150;
extern signed short Isumm;
extern signed short Isumm_;
extern char ND_out[3];
//extern signed short tout[4];


short plazma_adc_cnt;
short plazma_sk;
extern char cntrl_plazma;

//extern const short ptr_bat_zar_cnt[2];

//***********************************************
//Управление вентилятором
signed char vent_stat=0;

//***********************************************
//Управление ШИМом
signed short cntrl_stat=600;
signed short cntrl_stat_old=600;
signed short cntrl_stat_new;
signed short Ibmax;
unsigned char unh_cnt0,unh_cnt1,b1Hz_unh;
unsigned char	ch_cnt0,b1Hz_ch,i,iiii;
unsigned char	ch_cnt1,b1_30Hz_ch;
unsigned char	ch_cnt2,b1_10Hz_ch;
unsigned short IZMAX_;
unsigned short IZMAX_70;
unsigned short IZMAX_130;
unsigned short Ubpsmax;


//***********************************************
//Самокалиброввка
signed short samokalibr_cnt;



//***********************************************
//Выравнивание токов
short avg_main_cnt=20;
signed int i_avg_max,i_avg_min,i_avg_summ,i_avg; 
signed int avg;
char bAVG;
char avg_cnt;  
char avg_num; 

//**********************************************
//Контроль наличия батарей
signed short 	main_kb_cnt;
signed short 	kb_cnt_1lev;
signed short 	kb_cnt_2lev;
char 		kb_full_ver;
char kb_start[2],kb_start_ips;

//**********************************************
//Работа с БПСами
char num_of_wrks_bps;
char bps_all_off_cnt,bps_mask_off_cnt,bps_mask_on_off_cnt;
char bps_hndl_2sec_cnt;
unsigned short bps_on_mask,bps_off_mask;
char num_necc_up,num_necc_down;
unsigned char sh_cnt0,b1Hz_sh;

//***********************************************
//Спецфункции
enum_spc_stat spc_stat;
char spc_bat;
char spc_phase;
unsigned short vz_cnt_s,vz_cnt_s_,vz_cnt_h,vz_cnt_h_;
char bAVZ;
enum_ke_start_stat ke_start_stat;
short cnt_end_ke;
unsigned long ke_date[2];
short __ee_vz_cnt;
short __ee_spc_stat;
short __ee_spc_bat;
short __ee_spc_phase;

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
//1бит	- контроль выходного напряжения


short cntrl_stat_blok_cnt,cntrl_stat_blok_cnt_,cntrl_stat_blok_cnt_plus[2],cntrl_stat_blok_cnt_minus[2];

//***********************************************
//Сухие контакты
const char sk_buff_KONTUR[4]={13,11,15,14};
const char sk_buff_RSTKM[4]={13,11,15,14};
const char sk_buff_GLONASS[4]={11,13,15,14};
const char sk_buff_3U[4]={11,13,15,14};
const char sk_buff_6U[4]={11,13,15,14};
const char sk_buff_220[4]={11,13,15,14};
const char sk_buff_TELECORE2015[4]={11,13,15,14};

char	plazma_inv[4];
char plazma_bat;
char plazma_cntrl_stat;

//***********************************************
//Ротация ведущего источника
char numOfForvardBps;
char numOfForvardBps_minCnt;
short numOfForvardBps_hourCnt;


//-----------------------------------------------
void ke_start(char in)
{          
ke_start_stat=(enum_ke_start_stat)0;		 

if(spc_stat==spcVZ)ke_start_stat=kssNOT_VZ;
else if(BAT_IS_ON[in]!=bisON)ke_start_stat=kssNOT_BAT;
else if(bat[in]._av&(1<<0))ke_start_stat=kssNOT_BAT_AV;
else if(bat[in]._temper_stat&(1<<1))ke_start_stat=kssNOT_BAT_AV_T;
else if(bat[in]._av&(1<<1))ke_start_stat=kssNOT_BAT_AV_ASS;
else if(bat[in]._Ib>IKB)ke_start_stat=kssNOT_BAT_ZAR;
else if(bat[in]._Ib<-IKB)ke_start_stat=kssNOT_BAT_RAZR;
else if((spc_stat==spcKE)&&(spc_bat==0))ke_start_stat=kssNOT_KE1;
else if((spc_stat==spcKE)&&(spc_bat==1))ke_start_stat=kssNOT_KE2;
else 
	{

	ke_start_stat=kssYES;

	spc_stat=spcKE;
	__ee_spc_stat=spcKE;
	//lc640_write_int(EE_SPC_STAT,__ee_spc_stat);
	
	spc_bat=in;
	__ee_spc_bat=in;
	//lc640_write_int(EE_SPC_BAT,__ee_spc_bat);

	bat[in]._zar_cnt_ke=0;
	//lc640_write_int(ADR_EE_BAT_ZAR_CNT_KE[in],0);
	
	spc_phase=0;
	__ee_spc_phase=0;
	//lc640_write_int(EE_SPC_PHASE,__ee_spc_phase);

	//ke_mem_hndl(in,//lc640_read_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat]));

		{					
		signed short temp_temp;
		signed char temp;
		temp_temp=bat[in]._u_old[((bat_u_old_cnt+1)&0x07)]; 
		    
		temp=LPC_RTC->YEAR;
		gran_char(&temp,1,99);
		*((char*)(&(ke_date[0])))=temp;
			
		temp=LPC_RTC->MONTH;
		gran_char(&temp,1,12);
		*(((char*)(&(ke_date[0])))+1)=temp;
		
		temp=LPC_RTC->DOM;
		gran_char(&temp,1,31);
		*(((char*)(&(ke_date[0])))+2)=temp;			
				
		*(((char*)(&(ke_date[0])))+3)=*((char*)&temp_temp);
		//lc640_write_long(EE_SPC_KE_DATE0,ke_date[0]);

		temp=LPC_RTC->HOUR;
		gran_char(&temp,0,23);
		*((char*)(&(ke_date[1])))=temp;
               
		temp=LPC_RTC->MIN;
		gran_char(&temp,0,59);
		*(((char*)(&(ke_date[1])))+1)=temp;
	          
		temp=LPC_RTC->SEC;
		gran_char(&temp,0,59);
		*(((char*)(&(ke_date[1])))+2)=temp;
			
		*(((char*)(&(ke_date[1])))+3)=*(((char*)&temp_temp)+1);
		//lc640_write_long(EE_SPC_KE_DATE1,ke_date[1]);
		}

	}
}

//-----------------------------------------------
void ke_drv(void)
{

if(spc_stat==spcKE)
	{
	if(spc_phase==0)
		{
		mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<(1-spc_bat)),20);
		mess_send(MESS2BPS_HNDL,PARAM_BPS_ALL_OFF_AFTER_2SEC,0xffff,20);

		bat[spc_bat]._zar_cnt_ke+=abs(bat[spc_bat]._Ib);
	    	
		if(bat[spc_bat]._zar_cnt_ke>=AH_CONSTANT)
			{
			bat[spc_bat]._zar_cnt_ke-=AH_CONSTANT;
			//lc640_write_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat],//lc640_read_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat])+1);
			}
		}

	else if(spc_phase==1)
		{
		mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<(1-spc_bat)),20);
		}

	if(bat[spc_bat]._Ub<(USIGN*10))
		{
		cnt_end_ke++;
		if(cnt_end_ke>=30)
			{
			
			if((spc_stat==spcKE)&&(spc_phase==0))
				{
				//lc640_write_int(ADR_EE_BAT_C_REAL[spc_bat],//lc640_read_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat]));
				//ke_mem_hndl(spc_bat,lc640_read_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat]));
				//lc640_write_int(ADR_EE_BAT_ZAR_CNT[spc_bat],0);
				cntrl_stat=50;
				cntrl_stat_old=50;
				}

			if((BAT_IS_ON[1-spc_bat]) == bisON)
				{
				spc_phase=1;
				__ee_spc_phase=1;
				//lc640_write_int(EE_SPC_PHASE,1);
				}			
			else
				{
				spc_stat=spcOFF;
				__ee_spc_stat=spcOFF;
				//lc640_write_int(EE_SPC_STAT,spcOFF);
				}
			}
		}
	else cnt_end_ke=0;

	if((bat[spc_bat]._Ub>=bat[1-spc_bat]._Ub)&&(spc_phase==1))
		{
		spc_stat=spcOFF;
		__ee_spc_stat=spcOFF;
		//lc640_write_int(EE_SPC_STAT,spcOFF);
		}
	}
			
}

//-----------------------------------------------
char vz_start(char hour)
{          
char out;
out=0;
if(spc_stat==spcOFF)
	{
	spc_stat=spcVZ;
	__ee_spc_stat=spcVZ; 
	//lc640_write_int(EE_SPC_STAT,__ee_spc_stat);   
	vz_cnt_h=hour;
	__ee_vz_cnt=hour*60;
	//lc640_write_int(EE_VZ_CNT,__ee_vz_cnt);
	//lc640_write_int(EE_SPC_VZ_LENGT,hour*60);	
	vz_cnt_h_=0;
	vz_cnt_s=0;
	out=1;
	vz_mem_hndl(1);
	}
//else if((spc_stat==spc_KE1p1)||(spc_stat==spc_KE1p2)) out=22; 
//else if((spc_stat==spc_KE2p1)||(spc_stat==spc_KE2p2)) out=33;
//plazma=out;	
return out;
}

//-----------------------------------------------
void vz_stop(void)
{
if(spc_stat==spcVZ)
     {
vz_mem_hndl(vz_cnt_h);          
vz_cnt_s=0;
vz_cnt_h=0;
vz_cnt_h_=0;
spc_stat=spcOFF;

		__ee_spc_stat=spcOFF;
		//lc640_write_int(EE_SPC_STAT,spcOFF);
     }

}

//-----------------------------------------------
void avz_next_date_hndl(void)
{
//if((LPC_RTC->MONTH+AVZ)>12)lc640_write_int(EE_YEAR_AVZ,LPC_RTC->YEAR+1);
//else lc640_write_int(EE_YEAR_AVZ,LPC_RTC->YEAR);

////lc640_write_int(EE_YEAR_AVZ,6);

//if((LPC_RTC->MONTH+AVZ)>12)lc640_write_int(EE_MONTH_AVZ,(LPC_RTC->MONTH+AVZ)-12);
//else lc640_write_int(EE_MONTH_AVZ,LPC_RTC->MONTH+AVZ);                                                 

////lc640_write_int(EE_MONTH_AVZ,5);

//if(LPC_RTC->DOM>28) lc640_write_int(EE_DATE_AVZ,28);
//else lc640_write_int(EE_DATE_AVZ,LPC_RTC->DOM);

////lc640_write_int(EE_DATE_AVZ,4);

//lc640_write_int(EE_HOUR_AVZ,LPC_RTC->HOUR);
//lc640_write_int(EE_MIN_AVZ,LPC_RTC->MIN);
//lc640_write_int(EE_SEC_AVZ,LPC_RTC->SEC);

}

//-----------------------------------------------
void avz_drv(void)                               
{                
if(AVZ!=AVZ_OFF)
	{
	if((LPC_RTC->YEAR==YEAR_AVZ)&&(LPC_RTC->MONTH==MONTH_AVZ)&&(LPC_RTC->DOM==DATE_AVZ)&&(LPC_RTC->HOUR==HOUR_AVZ)&&(LPC_RTC->MIN==MIN_AVZ)&&(LPC_RTC->SEC==SEC_AVZ))
		{
		bAVZ=1;
		}
	}
if(bAVZ)
	{
	if(vz_start(AVZ_TIME))
		{
		bAVZ=0;
		avz_next_date_hndl();
		}
	}	

}

//-----------------------------------------------
void vz_drv(void)
{ 
if(spc_stat==spcVZ)
	{
	if(vz_cnt_s_<3600)
		{
		vz_cnt_s_++;
		if(vz_cnt_s_>=3600)
			{
			vz_cnt_s_=0;
			if(vz_cnt_h)
				{
				vz_cnt_h--;
				vz_cnt_h_++;
				}
			}
		}


	if(vz_cnt_s<60)
		{
		vz_cnt_s++;
		if(vz_cnt_s>=60)
			{
			vz_cnt_s=0;
			
			__ee_vz_cnt--;
			//lc640_write_int(EE_VZ_CNT,__ee_vz_cnt);
			if(!__ee_vz_cnt)
				{
				spc_stat=spcOFF;
						__ee_spc_stat=spcOFF;
		//lc640_write_int(EE_SPC_STAT,spcOFF);
				vz_mem_hndl(0);
				}
			}
		}

	}


} 




//-----------------------------------------------
void kb_init(void)
{
main_kb_cnt=(TBAT*60)-60/*120*/;
}

//-----------------------------------------------
void kb_hndl(void)
{

static signed short ibat[2],ibat_[2],ibat_ips,ibat_ips_;
#ifdef UKU_TELECORE2015
if(((++main_kb_cnt>=TBAT*60)&&(TBAT))&&(BAT_TYPE==0))
#else 
if(((++main_kb_cnt>=TBAT*60)&&(TBAT)))
#endif
	{
	main_kb_cnt=0;
	
	kb_start[0]=0;
	kb_start[1]=0;
	kb_start_ips=0;

	if( (BAT_IS_ON[0]==bisON) && (bat[0]._Ub>80) && ( (abs(bat[0]._Ib)<IKB) || (bat[0]._av&1) ) ) kb_start[0]=1;
	if( (BAT_IS_ON[1]==bisON) && (bat[1]._Ub>80) && ( (abs(bat[1]._Ib)<IKB) || (bat[1]._av&1) ) ) kb_start[1]=1;
#ifdef UKU_220_IPS_TERMOKOMPENSAT
	if( (!ips_bat_av_vzvod)                      && ((abs(Ib_ips_termokompensat)<IKB) || (bat_ips._av&1) ) ) kb_start_ips=1;
#endif	
	if( (net_av) || (num_of_wrks_bps==0) || ( (spc_stat!=spcOFF) && (spc_stat!=spcVZ) ) ) 
		{
		kb_start[0]=0;
		kb_start[1]=0;
		kb_start_ips=0;
		}

	if((kb_start[0]==1)||(kb_start[1]==1)||(kb_start_ips==1))
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
		ibat_ips=abs(Ib_ips_termokompensat);
		}
	
	if(kb_cnt_1lev==0)
		{
		ibat_[0]=abs(bat[0]._Ib);
		ibat_[1]=abs(bat[1]._Ib);
		ibat_ips_=abs(Ib_ips_termokompensat);

		kb_cnt_2lev=0;


		if(( (ibat[0]+ibat_[0]) < IKB )&& (kb_start[0]==1))
			{
			kb_cnt_2lev=10;  
			}
		else if(bat[0]._Ub>200)
			{
			kb_start[0]=0;
			avar_bat_hndl(0,0);
			}
		
		if(( (ibat[1]+ibat_[1]) < IKB ) && (kb_start[1]==1))
			{
			kb_cnt_2lev=10;     
			}
		else  if(bat[1]._Ub>200)
			{
			kb_start[1]=0;
			avar_bat_hndl(1,0);
			}
#ifdef UKU_220_IPS_TERMOKOMPENSAT
		if(( (ibat_ips+ibat_ips_) < IKB ) && (kb_start_ips==1))
			{
			kb_cnt_2lev=10;     
			}
/*		else  if(bat[1]._Ub>200)
			{
			kb_start[1]=0;
			avar_bat_hndl(1,0);
			} */
#endif
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
		ibat_ips=abs(Ib_ips_termokompensat);
		}
	
	if(kb_cnt_2lev==0)
		{
		ibat_[0]=abs(bat[0]._Ib);
		ibat_[1]=abs(bat[1]._Ib);
		ibat_ips_=abs(Ib_ips_termokompensat);

		kb_full_ver=0;

		if(( (ibat[0]+ibat_[0]) < IKB ) && (kb_start[0]==1))
			{
			kb_full_ver=1;  
			}
		else if(bat[0]._Ub>200)			
			{
			kb_start[0]=0;
			avar_bat_hndl(0,0);
			}

		if(( (ibat[1]+ibat_[1]) < IKB ) && (kb_start[1]==1))
			{
			kb_full_ver=1;     
			}
		else	if(bat[1]._Ub>200)		
			{
			kb_start[1]=0;
			avar_bat_hndl(1,0);
			}
#ifdef UKU_220_IPS_TERMOKOMPENSAT
		if(( (ibat_ips+ibat_ips_) < IKB )  && (kb_start_ips==1))
			{
			kb_full_ver=1;     
			}
#endif
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
#ifdef UKU_220_IPS_TERMOKOMPENSAT
	if( abs(Ib_ips_termokompensat) > IKB ) 
		{
		if(kb_start_ips==1)
			{
			kb_start_ips=0;
			avar_bat_ips_hndl(0);
			}
		}
#endif

	if ((kb_start[0]==0) && (kb_start[1]==0) && (kb_start_ips==0)) 
		{
		kb_full_ver=0;
		}

	if(( (mess_find(MESS2KB_HNDL))	&& (mess_data[0]==PARAM_CNTRL_IS_DOWN) ) || (load_U<(USIGN*10)) )
		{
		kb_full_ver=0;
		if((kb_start[0]==1)&&((load_I>(2*IKB)/10))&&(!(bat[0]._av&0x01))) avar_bat_hndl(0,1);
		if((kb_start[1]==1)&&((load_I>(2*IKB)/10))&&(!(bat[1]._av&0x01))) avar_bat_hndl(1,1);
#ifdef UKU_220_IPS_TERMOKOMPENSAT
		if((kb_start_ips==1)&&((load_I>(2*IKB)/10))&&(!(bat_ips._av&0x01))) avar_bat_ips_hndl(1);
#endif
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
	mess_send(MESS2RELE_HNDL,PARAM_RELE_SAMOKALIBR,1,15);
	mess_send(MESS2IND_HNDL,PARAM_SAMOKALIBR,0,15);
	mess_send(MESS2MATEMAT,PARAM_SAMOKALIBR,0,15);
	} 

if(samokalibr_cnt==1799U)
	{
	//if((Kibat0[0]!=ad7705_buff_[0])&&(abs(bat[0]._Ib/10)<IZMAX)) lc640_write_int(ADR_KI0BAT[0],ad7705_buff_[0]);
	//if((Kibat0[1]!=ad7705_buff_[1])&&(abs(bat[0]._Ib/10)<IZMAX)) lc640_write_int(ADR_KI0BAT[1],ad7705_buff_[1]);
	
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
	if((unet_drv_cnt<10)&&(main_1Hz_cnt>15))
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
signed long temp_SL/*,temp_SL_*/;
char /*temp,*/i;
signed short temp_SS;

#ifdef UKU_MGTS
//напряжение сети
temp_SL=(signed long)net_buff_;
temp_SL*=Kunet;
temp_SL/=110000L;
net_U=(signed short)temp_SL;
#endif

#ifdef UKU_RSTKM
//напряжение сети
temp_SL=(signed long)net_buff_;
temp_SL*=Kunet;
temp_SL/=110000L;
net_U=(signed short)temp_SL;
#endif

#ifdef UKU_3U
//напряжение сети
temp_SL=(signed long)net_buff_;
temp_SL*=Kunet;
temp_SL/=36000L;
net_U=(signed short)temp_SL;
#endif

#ifdef UKU_6U
//напряжение сети

if((AUSW_MAIN%10)||(AUSW_MAIN==2400)||(AUSW_MAIN==4800)||(AUSW_MAIN==6000))
	{

	if(bps[11]._device==dNET_METR)
		{
		net_metr_buff_[0]=((signed short)bps[11]._buff[0])+(((signed short)bps[11]._buff[1])<<8);
		net_metr_buff_[1]=((signed short)bps[11]._buff[2])+(((signed short)bps[11]._buff[3])<<8);
		net_metr_buff_[2]=((signed short)bps[11]._buff[4])+(((signed short)bps[11]._buff[5])<<8);

		temp_SL=(signed long)net_metr_buff_[0];
		temp_SL*=KunetA;
		temp_SL/=6000L;
		net_Ua=(signed short)temp_SL;
	
		temp_SL=(signed long)net_metr_buff_[1];
		temp_SL*=KunetB;
		temp_SL/=6000L;
		net_Ub=(signed short)temp_SL;
	
		temp_SL=(signed long)net_metr_buff_[2];
		temp_SL*=KunetC;
		temp_SL/=6000L;
		net_Uc=(signed short)temp_SL;
		}
	else
		{
		temp_SL=(signed long)net_buff_;
		temp_SL*=KunetA;
		temp_SL/=110000L;
		net_Ua=(signed short)temp_SL;
	
		temp_SL=(signed long)adc_buff_[3];
		temp_SL*=KunetB;
		temp_SL/=6000L;
		net_Ub=(signed short)temp_SL;
	
		temp_SL=(signed long)adc_buff_[10];
		temp_SL*=KunetC;
		temp_SL/=6000L;
		net_Uc=(signed short)temp_SL;
		}

	net_U=net_Ua;
	if(net_Ub<net_U)net_U=net_Ub;
	if(net_Uc<net_U)net_U=net_Uc;
	}
else 
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=Kunet;
	temp_SL/=110000L;
	net_U=(signed short)temp_SL;
	}




#endif

#ifdef UKU_GLONASS
//напряжение сети
temp_SL=(signed long)net_buff_;
temp_SL*=Kunet;
temp_SL/=110000L;
net_U=(signed short)temp_SL;
#endif

#ifdef UKU_KONTUR
//напряжение сети
temp_SL=(signed long)net_buff_;
temp_SL*=Kunet;
temp_SL/=110000L;
net_U=(signed short)temp_SL;
#endif


#ifdef UKU_220_V2
//напряжение сети

if(AUSW_MAIN==22033)
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=KunetA;
	temp_SL/=6000L;
	net_Ua=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[3];
	temp_SL*=KunetB;
	temp_SL/=6000L;
	net_Ub=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[10];
	temp_SL*=KunetC;
	temp_SL/=6000L;
	net_Uc=(signed short)temp_SL;

	net_U=net_Ua;
	if(net_Ub<net_U)net_U=net_Ub;
	if(net_Uc<net_U)net_U=net_Uc;
	}
else
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=Kunet;
	temp_SL/=5000L;
	net_U=(signed short)temp_SL;
	}
#endif


#ifdef UKU_220
//напряжение сети

if(AUSW_MAIN==22035)
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=KunetA;
	temp_SL/=6000L;
	net_Ua=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[3];
	temp_SL*=KunetB;
	temp_SL/=6000L;
	net_Ub=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[10];
	temp_SL*=KunetC;
	temp_SL/=6000L;
	net_Uc=(signed short)temp_SL;

	net_U=net_Ua;
	if(net_Ub<net_U)net_U=net_Ub;
	if(net_Uc<net_U)net_U=net_Uc;
	}
else
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=Kunet;
	#ifdef _ACDC_
	temp_SL/=500L;
	#else
	temp_SL/=5000L;
	#endif
	net_U=(signed short)temp_SL;
	
	}
#endif

#ifdef UKU_220_IPS_TERMOKOMPENSAT
//напряжение сети


	if(bps[11]._device==dNET_METR)
		{
		net_metr_buff_[0]=((signed short)bps[11]._buff[0])+(((signed short)bps[11]._buff[1])<<8);
		net_metr_buff_[1]=((signed short)bps[11]._buff[2])+(((signed short)bps[11]._buff[3])<<8);
		net_metr_buff_[2]=((signed short)bps[11]._buff[4])+(((signed short)bps[11]._buff[5])<<8);

		temp_SL=(signed long)net_metr_buff_[2];
		temp_SL*=KunetA;
		temp_SL/=6000L;
		net_Ua=(signed short)temp_SL;
	
		temp_SL=(signed long)net_metr_buff_[1];
		temp_SL*=KunetB;
		temp_SL/=6000L;
		net_Ub=(signed short)temp_SL;
	
		temp_SL=(signed long)net_metr_buff_[0];
		temp_SL*=KunetC;
		temp_SL/=6000L;
		net_Uc=(signed short)temp_SL;

		net_F3=((signed short)bps[11]._buff[6])+(((signed short)bps[11]._buff[7])<<8);

		net_U=net_Ua;
		if(net_Ub<net_U)net_U=net_Ub;
		if(net_Uc<net_U)net_U=net_Uc;
		}
	  else if(AUSW_MAIN==22033)
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=KunetA;
	temp_SL/=4000L;
	net_Ua=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[3];
	temp_SL*=KunetB;
	temp_SL/=6000L;
	net_Ub=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[10];
	temp_SL*=KunetC;
	temp_SL/=6000L;
	net_Uc=(signed short)temp_SL;

	net_U=net_Ua;
	if(net_Ub<net_U)net_U=net_Ub;
	if(net_Uc<net_U)net_U=net_Uc;
	}
else if((AUSW_MAIN==22063)||(AUSW_MAIN==22023)||(AUSW_MAIN==22043))
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=KunetA;
	temp_SL/=40000L;
	net_Ua=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[3];
	temp_SL*=KunetB;
	temp_SL/=6000L;
	net_Ub=(signed short)temp_SL;

	temp_SL=(signed long)adc_buff_[10];
	temp_SL*=KunetC;
	temp_SL/=6000L;
	net_Uc=(signed short)temp_SL;

	net_U=net_Ua;
	if(net_Ub<net_U)net_U=net_Ub;
	if(net_Uc<net_U)net_U=net_Uc;
	}
else	if((AUSW_MAIN==22010)||(AUSW_MAIN==22011) )
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=Kunet;
	temp_SL/=35000L;
	net_U=(signed short)temp_SL;
	
	}
else
	{
	temp_SL=(signed long)net_buff_;
	temp_SL*=Kunet;
	#ifdef _ACDC_
	temp_SL/=500L;
	#else
	temp_SL/=5000L;
	#endif
	net_U=(signed short)temp_SL;
	
	}
if(bps[11]._device!=dNET_METR) net_F3=net_F;
#endif

#ifdef UKU_TELECORE2015
//напряжение сети
temp_SL=(signed long)net_buff_;
temp_SL*=Kunet;
temp_SL/=110000L;
net_U=(signed short)temp_SL;
#endif

//Напряжения батарей
temp_SL=(signed long)adc_buff_[0];
temp_SL*=Kubat[0];
temp_SL/=2000L;
bat[0]._Ub=(signed short)temp_SL;

#ifdef UKU_220
//Напряжения батарей
temp_SL=(signed long)adc_buff_[0];
temp_SL*=Kubat[0];
temp_SL/=400L;
bat[0]._Ub=(signed short)temp_SL;
#endif

#ifdef UKU_220_V2
//Напряжения батарей
temp_SL=(signed long)adc_buff_[0];
temp_SL*=Kubat[0];
temp_SL/=400L;
bat[0]._Ub=(signed short)temp_SL;
#endif

temp_SL=(signed long)adc_buff_[4];
temp_SL*=Kubatm[0];
temp_SL/=700L;
bat[0]._Ubm=(signed short)temp_SL;

#ifdef UKU_KONTUR
temp_SL=(signed long)adc_buff_[4];
temp_SL*=Kubatm[0];
temp_SL/=2000L;
bat[0]._Ubm=(signed short)temp_SL;
#endif

temp_SL=(signed long)adc_buff_[12];
temp_SL*=Kubat[1];
temp_SL/=2000L;
bat[1]._Ub=(signed short)temp_SL;

#ifdef UKU_220
temp_SL=(signed long)adc_buff_[12];
temp_SL*=Kubat[1];
temp_SL/=400L;
bat[1]._Ub=(signed short)temp_SL;
#endif

#ifdef UKU_220_V2
temp_SL=(signed long)adc_buff_[12];
temp_SL*=Kubat[1];
temp_SL/=400L;
bat[1]._Ub=(signed short)temp_SL;
#endif

temp_SL=(signed long)adc_buff_[1];
temp_SL*=Kubatm[1];
temp_SL/=700L;
bat[1]._Ubm=(signed short)temp_SL;
#ifdef UKU_KONTUR
temp_SL=(signed long)adc_buff_[1];
temp_SL*=Kubatm[1];
temp_SL/=2000L;
bat[1]._Ubm=(signed short)temp_SL;
#endif

#ifdef UKU_TELECORE2015
temp_SL=(signed long)adc_buff_[2];
temp_SL*=Kubat[0];
temp_SL/=2000L;
bat[0]._Ub=(signed short)temp_SL;
#endif

/*
//Токи батарей
if(!mess_find_unvol(MESS2MATEMAT))
	{
	temp_SL=(signed long)ad7705_buff_[0];
	temp_SL-=(signed long)Kibat0[0];
	temp_SL*=(signed long)Kibat1[0];
	if((AUSW_MAIN==24120)||(AUSW_MAIN==24210))temp_SL/=300L;
	else temp_SL/=1000L;
	bat[0]._Ib=(signed short)temp_SL;

	temp_SL=(signed long)ad7705_buff_[1];
	temp_SL-=(signed long)Kibat0[1];
	temp_SL*=(signed long)Kibat1[1];
	if((AUSW_MAIN==24120)||(AUSW_MAIN==24210))temp_SL/=300L;
	else temp_SL/=1000L;
	bat[1]._Ib=(signed short)temp_SL;
	}
*/


//Токи батарей






//Температуры батарей
if((adc_buff_[6]>800)&&(adc_buff_[6]<3800))bat[0]._nd=0;
else bat[0]._nd=1;
temp_SL=(signed long)adc_buff_[6];
temp_SL*=Ktbat[0];
temp_SL/=20000L;
temp_SL-=273L;
bat[0]._Tb=(signed short)temp_SL;

if((adc_buff_[7]>800)&&(adc_buff_[7]<3800))bat[1]._nd=0;
else bat[1]._nd=1;
temp_SL=(signed long)adc_buff_[7];
temp_SL*=Ktbat[1];
temp_SL/=20000L;
temp_SL-=273L;
bat[1]._Tb=(signed short)temp_SL;

#ifdef UKU_6U

if(NUMMAKB==2)
	{
	if(makb[0]._cnt<5)
		{
		if(makb[0]._T_nd[0]==0)
			{
			bat[0]._Tb=makb[0]._T[0];
			bat[0]._nd=0;
			}
		}

	if(makb[1]._cnt<5)
		{
		if(makb[1]._T_nd[0]==0)
			{
			bat[1]._Tb=makb[1]._T[0];
			bat[1]._nd=0;
			}
		}

	}
else if(NUMMAKB==4)
	{
	signed short temp_t;
	temp_t=-20;
	if(makb[0]._cnt<5)
		{
		if(makb[0]._T_nd[0]==0)
			{
			temp_t=makb[0]._T[0];
			bat[0]._nd=0;
			}
		}
	if(makb[1]._cnt<5)
		{
		if(makb[1]._T_nd[0]==0)
			{
			if(temp_t<makb[1]._T[0])
				{
				bat[0]._nd=0;
				temp_t=makb[1]._T[0];
				}
			}
		}
	if(temp_t!=-20)bat[0]._Tb = temp_t;

 	temp_t=-20;
	if(makb[2]._cnt<5)
		{
		if(makb[2]._T_nd[0]==0)
			{
			temp_t=makb[2]._T[0];
			bat[1]._nd=0;
			}
		}
	if(makb[3]._cnt<5)
		{
		if(makb[3]._T_nd[0]==0)
			{
			if(temp_t<makb[3]._T[0])
				{
				bat[1]._nd=0;
				temp_t=makb[3]._T[0];
				}
			}
		}
	if(temp_t!=-20)bat[1]._Tb = temp_t;
	}

#endif


//Напряжение нагрузки
temp_SL=(signed long)adc_buff_[2];
temp_SL*=Kuload;
temp_SL/=2000L;
load_U=(signed short)temp_SL;

#ifdef UKU_220 
//Напряжение нагрузки
temp_SL=(signed long)adc_buff_[2];
temp_SL*=Kuload;
temp_SL/=350L;
load_U=(signed short)temp_SL;
#endif

#ifdef UKU_220_V2 
//Напряжение нагрузки
temp_SL=(signed long)adc_buff_[2];
temp_SL*=Kuload;
temp_SL/=350L;
load_U=(signed short)temp_SL;
#endif

#ifdef UKU_220_IPS_TERMOKOMPENSAT
//Напряжение шины
temp_SL=(signed long)adc_buff_[1];
temp_SL*=Kuout;
if(AUSW_MAIN==22010)temp_SL/=400L;
else temp_SL/=500L;
out_U=(signed short)temp_SL;
load_U=out_U;

//Напряжение выпрямителей
temp_SL=(signed long)adc_buff_[2];
temp_SL*=Kubps;
if(AUSW_MAIN==22010)temp_SL/=400L;
else temp_SL/=500L;
bps_U=(signed short)temp_SL;

//Суммарный ток выпрямителей
temp_SL=0;
for (i=0;i<NUMIST;i++)
	{
	temp_SL+=((signed long)bps[i]._Ii);
	}
bps_I=(signed short)temp_SL;


#endif


#ifdef UKU_KONTUR
//Внешний датчик температуры №1(температура внешнего воздуха)
if((adc_buff_[5]>800)&&(adc_buff_[5]<3800))ND_EXT[0]=0;
else ND_EXT[0]=1;
temp_SL=(signed long)adc_buff_[5];
temp_SL*=Ktext[0];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[0]=(signed short)temp_SL;
#else 
//Внешний датчик температуры №1(температура внешнего воздуха)
if((adc_buff_[5]>800)&&(adc_buff_[5]<3800))ND_EXT[0]=0;
else ND_EXT[0]=1;
temp_SL=(signed long)adc_buff_[5];
temp_SL*=Ktext[0];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[0]=(signed short)temp_SL;
#endif

#ifdef UKU_220

//Внешний датчик температуры №2(температура отсека ЭПУ)
if((adc_buff_[3]>800)&&(adc_buff_[3]<3800))ND_EXT[1]=0;
else ND_EXT[1]=1;
temp_SL=(signed long)adc_buff_[3];
temp_SL*=Ktext[1];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[1]=(signed short)temp_SL;

//Внешний датчик температуры №3(температура отсека MSAN)
if((adc_buff_[10]>800)&&(adc_buff_[10]<3800))ND_EXT[2]=0;
else ND_EXT[2]=1;
temp_SL=(signed long)adc_buff_[10];
temp_SL*=Ktext[2];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[2]=(signed short)temp_SL;

#else


#ifdef UKU_220_IPS_TERMOKOMPENSAT

//Внешний датчик температуры 
if((adc_buff_[6]>800)&&(adc_buff_[6]<3800))ND_EXT[0]=0;
else ND_EXT[0]=1;
temp_SL=(signed long)adc_buff_[6];
temp_SL*=Ktext[0];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[0]=(signed short)temp_SL;

#else



//Внешний датчик температуры №2(температура отсека ЭПУ)
if((adc_buff_[10]>800)&&(adc_buff_[10]<3800))ND_EXT[1]=0;
else ND_EXT[1]=1;
temp_SL=(signed long)adc_buff_[10];
temp_SL*=Ktext[1];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[1]=(signed short)temp_SL;

//Внешний датчик температуры №3(температура отсека MSAN)
if((adc_buff_[3]>800)&&(adc_buff_[3]<3800))ND_EXT[2]=0;
else ND_EXT[2]=1;
temp_SL=(signed long)adc_buff_[3];
temp_SL*=Ktext[2];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[2]=(signed short)temp_SL;

#endif
#endif

#ifdef UKU_220_V2

//Внешний датчик температуры №2(температура отсека ЭПУ)
if((adc_buff_[3]>800)&&(adc_buff_[3]<3800))ND_EXT[1]=0;
else ND_EXT[1]=1;
temp_SL=(signed long)adc_buff_[3];
temp_SL*=Ktext[1];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[1]=(signed short)temp_SL;

//Внешний датчик температуры №3(температура отсека MSAN)
if((adc_buff_[10]>800)&&(adc_buff_[10]<3800))ND_EXT[2]=0;
else ND_EXT[2]=1;
temp_SL=(signed long)adc_buff_[10];
temp_SL*=Ktext[2];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[2]=(signed short)temp_SL;

#else

#ifdef UKU_220_IPS_TERMOKOMPENSAT
//Ток батареи
if(bps[8]._device==dIBAT_METR)
	{
	ibat_metr_buff_[0]=((signed long)bps[8]._buff[0])+(((signed long)bps[8]._buff[1])<<8);
	ibat_metr_buff_[1]=((signed long)bps[8]._buff[2])+(((signed long)bps[8]._buff[3])<<8);
	bIBAT_SMKLBR=((signed short)bps[8]._buff[4])+(((signed short)bps[8]._buff[5])<<8);

	if(!bIBAT_SMKLBR)
		{
		signed long temp_SL;
		temp_SL=(signed long)ibat_metr_buff_[0];
		temp_SL-=(signed long)ibat_metr_buff_[1];
		temp_SL*=(signed long)Kibat1[0];
		if((AUSW_MAIN==22010)||(AUSW_MAIN==22011)||(AUSW_MAIN==22035)||(AUSW_MAIN==22033)||(AUSW_MAIN==22063)||(AUSW_MAIN==22023)||(AUSW_MAIN==22043))temp_SL/=2000L;
	
		Ib_ips_termokompensat =(signed short)temp_SL;
		}
	}

bat[0]._Ub=load_U;
bat[0]._Ib=Ib_ips_termokompensat;

#endif
#endif


#ifdef UKU_TELECORE2015

//Внешний датчик температуры №1
if((adc_buff_[7]>800)&&(adc_buff_[7]<3800))ND_EXT[0]=0;
else ND_EXT[0]=1;
temp_SL=(signed long)adc_buff_[7];
temp_SL*=Ktext[0];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[0]=(signed short)temp_SL;


//Внешний датчик температуры №2
if((adc_buff_[6]>800)&&(adc_buff_[6]<3800))ND_EXT[1]=0;
else ND_EXT[1]=1;
temp_SL=(signed long)adc_buff_[6];
temp_SL*=Ktext[1];
temp_SL/=20000L;
temp_SL-=273L;
t_ext[1]=(signed short)temp_SL;

#endif

//напряжение ввода
temp_SL=(signed long)adc_buff_ext_[0];
temp_SL*=Kunet_ext[0];
temp_SL/=4000L;
Uvv[0]=(signed short)temp_SL;
if(Uvv[0]<100) Uvv0=Uvv[0];
else Uvv0=net_U;

//напряжение пэс
temp_SL=(signed long)adc_buff_ext_[1];
temp_SL*=Kunet_ext[1];
temp_SL/=4000L;
Uvv[1]=(signed short)temp_SL;


//напряжение ввода трехфазное
temp_SL=(signed long)eb2_data_short[0];
temp_SL*=Kvv_eb2[0];
temp_SL/=6000L;
Uvv_eb2[0]=(signed short)temp_SL;

temp_SL=(signed long)eb2_data_short[1];
temp_SL*=Kvv_eb2[1];
temp_SL/=6000L;
Uvv_eb2[1]=(signed short)temp_SL;

temp_SL=(signed long)eb2_data_short[2];
temp_SL*=Kvv_eb2[2];
temp_SL/=6000L;
Uvv_eb2[2]=(signed short)temp_SL;

//напряжение пэс трехфазное
temp_SL=(signed long)eb2_data_short[3];
temp_SL*=Kpes_eb2[0];
temp_SL/=6000L;
Upes_eb2[0]=(signed short)temp_SL;

temp_SL=(signed long)eb2_data_short[4];
temp_SL*=Kpes_eb2[1];
temp_SL/=6000L;
Upes_eb2[1]=(signed short)temp_SL;

temp_SL=(signed long)eb2_data_short[5];
temp_SL*=Kpes_eb2[2];
temp_SL/=6000L;
Upes_eb2[2]=(signed short)temp_SL;

//Вычисление температуры шкафа

ibt._T[0]=t_ext[1]+273;
ibt._T[1]=t_ext[2]+273;

ibt._nd[0]=ND_EXT[1];
ibt._nd[1]=ND_EXT[2];

#ifndef UKU_TELECORE2015
if((ibt._nd[0]==0) &&  (ibt._nd[1]==0))
	{
	t_box=((ibt._T[0]+ibt._T[1])/2)-273;
	}
else if((ibt._nd[0]==1) &&  (ibt._nd[1]==0))
	{
	t_box=ibt._T[1]-273;
	}
else if((ibt._nd[0]==0) &&  (ibt._nd[1]==1))
	{
	t_box=ibt._T[0]-273;
	}
else if((ibt._nd[0]==1) &&  (ibt._nd[1]==1))
	{
	if(t_ext_can_nd<5)t_box= t_ext_can;
	else t_box=20;
	}
#endif
/*
//Вычисление температуры шкафа

ibt._T[0]=bat[0]._Tb+273;
ibt._T[1]=bat[1]._Tb+273;
ibt._T[2]=t_ext[1]+273;
ibt._T[3]=t_ext[2]+273;

ibt._nd[0]=bat[0]._nd;
ibt._nd[1]=bat[1]._nd;
ibt._nd[2]=ND_EXT[1];
ibt._nd[3]=ND_EXT[2];

ibt._avg1=0;
ibt._avg_cnt=4;

if(ibt._nd[0]==0)
	{
	ibt._avg1+=ibt._T[0];
	}
else 
	{
	ibt._avg_cnt--;
	}

if(ibt._nd[1]==0)
	{
	ibt._avg1+=ibt._T[1];
	}
else 
	{
	ibt._avg_cnt--;
	}

if(ibt._nd[2]==0)
	{
	ibt._avg1+=ibt._T[2];
	}
else 
	{
	ibt._avg_cnt--;
	}

if(ibt._nd[3]==0)
	{
	ibt._avg1+=ibt._T[3];
	}
else 
	{
	ibt._avg_cnt--;
	}

if(ibt._avg_cnt==0)
	{
	}
else
	{
	ibt._avg1/=ibt._avg_cnt;
	}


if(ibt._nd[0]!=0)
	{
	ibt._T_dispers[0]=0;
	}
else 
	{
	ibt._T_dispers[0]=abs(ibt._T[0]-ibt._avg1);
	}

if(ibt._nd[1]!=0)
	{
	ibt._T_dispers[1]=0;
	}
else 
	{
	ibt._T_dispers[1]=abs(ibt._T[1]-ibt._avg1);
	}

if(ibt._nd[2]!=0)
	{
	ibt._T_dispers[2]=0;
	}
else 
	{
	ibt._T_dispers[2]=abs(ibt._T[2]-ibt._avg1);
	}

if(ibt._nd[3]!=0)
	{
	ibt._T_dispers[3]=0;
	}
else 
	{
	ibt._T_dispers[3]=abs(ibt._T[3]-ibt._avg1);
	}

if(	ibt._nd[0]&&
	ibt._nd[1]&&
	ibt._nd[2]&&
	ibt._nd[3]
	)
	{
	t_box=(bps[0]._Ti);
	}

else if(	ibt._nd[0]||
	ibt._nd[1]||
	ibt._nd[2]||
	ibt._nd[3]
	)
	{
	t_box=(ibt._avg1-273);
	}
else 
	{
	ibt._max_dispers_num=0;
	ibt._max_dispers=ibt._T_dispers[0];

	if(ibt._T_dispers[1]>ibt._max_dispers)
		{
		ibt._max_dispers_num=1;
		ibt._max_dispers=ibt._T_dispers[1];
		}
	if(ibt._T_dispers[2]>ibt._max_dispers)
		{
		ibt._max_dispers_num=2;
		ibt._max_dispers=ibt._T_dispers[2];
		}
	if(ibt._T_dispers[3]>ibt._max_dispers)
		{
		ibt._max_dispers_num=3;
		ibt._max_dispers=ibt._T_dispers[3];
		}

	ibt._avg2=0;

	if(ibt._max_dispers_num!=0)
		{
		ibt._avg2+=ibt._T[0];
		}
	if(ibt._max_dispers_num!=1)
		{
		ibt._avg2+=ibt._T[1];
		}
	if(ibt._max_dispers_num!=2)
		{
		ibt._avg2+=ibt._T[2];
		}
	if(ibt._max_dispers_num!=3)
		{
		ibt._avg2+=ibt._T[3];
		}

	t_box=(ibt._avg2/3)-273;

	}*/


//*********************************************

#ifndef TELECORE
if((BAT_IS_ON[0]==bisON)&&(bat[0]._Ub>200)) 
if((BAT_IS_ON[1]==bisON)&&(bat[1]._Ub>200)&&(bat[1]._Ib>bat[0]._Ib)) Ibmax=bat[1]._Ib;
#endif

#ifdef UKU_IP55
Ibmax=0;
if(NUMBAT_IP55>0)    						Ibmax=bat[0]._Ib/10;
if((NUMBAT_IP55>1)&&(bat[1]._Ib/10>Ibmax)) 	Ibmax=bat[1]._Ib/10;
#endif

for(i=0;i<NUMIST+2;i++)
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


#ifdef TELECORE
load_I=0;
for(i=0;i<NUMBAT_IP55;i++)
	{
	load_I-=lakb[i]._ch_curr/10;
	}
#else
load_I=-(bat[0]._Ib/10)-(bat[1]._Ib/10);
#endif
Isumm=0;

for(i=0;i<NUMIST;i++)
     {
     if(bps[i]._cnt<5)Isumm+=bps[i]._Ii;
     }  
     
load_I=load_I+Isumm;
if(load_I<0)load_I=0;

#ifdef UKU_220_IPS_TERMOKOMPENSAT
load_I=0;

Isumm=0;

for(i=0;i<NUMIST;i++)
     {
     if(bps[i]._cnt<5)Isumm+=bps[i]._Ii;
     }  
     
load_I=load_I+Isumm;
if(load_I<0)load_I=0;

#endif



#ifdef UKU_GLONASS
inv[0]._Uio=6;
if (NUMINV)
	{
	for(i=0;i<NUMINV;i++)
		{
		if(bps[i+first_inv_slot]._cnt<25)
     		{
     		inv[i]._Ii=bps[i+first_inv_slot]._buff[0]+(bps[i+first_inv_slot]._buff[1]*256);
     		inv[i]._Uin=bps[i+first_inv_slot]._buff[2]+(bps[i+first_inv_slot]._buff[3]*256);
     		inv[i]._Uio=bps[i+first_inv_slot]._buff[4]+(bps[i+first_inv_slot]._buff[5]*256);
     		inv[i]._Ti=(signed)(bps[i+first_inv_slot]._buff[6]);
     		inv[i]._flags_tm=bps[i+first_inv_slot]._buff[8];
	    	//	inv[i]._rotor=bps[i+first_inv_slot]._buff[10]+(bps[i+first_inv_slot]._buff[11]*256);
			inv[i]._cnt=0;    
     		} 
		else 
     		{
     		inv[i]._Uio=0; 
     		inv[i]._Ii=0;
     		inv[i]._Uin=0;
     		inv[i]._Ti=0;
     		inv[i]._flags_tm=0; 
//	     	inv[i]._rotor0;
			inv[i]._cnt=25;    
     		}
     	}
   	}
#endif

#ifndef UKU_GLONASS
if (NUMINV)
	{
	for(i=0;i<NUMINV;i++)
		{
		if(bps[i+20]._cnt<25)
     		{
     		inv[i]._Ii=bps[i+20]._buff[0]+(bps[i+20]._buff[1]*256);
     		inv[i]._Pio=bps[i+20]._buff[2]+(bps[i+20]._buff[3]*256);
     		inv[i]._Uio=bps[i+20]._buff[4]+(bps[i+20]._buff[5]*256);
     		inv[i]._Ti=(signed)(bps[i+20]._buff[6]);
     		inv[i]._flags_tm=bps[i+20]._buff[7];
     		inv[i]._Uin=bps[i+20]._buff[8]+(bps[i+20]._buff[9]*256);
     		inv[i]._Uil=bps[i+20]._buff[10]+(bps[i+20]._buff[11]*256);
			inv[i]._cnt=0;
			inv[i]._Uoutmin=bps[i+20]._buff[12]; 
			inv[i]._Uoutmax=bps[i+20]._buff[13]; 
			inv[i]._Pnom=bps[i+20]._buff[14]; 
			inv[i]._net_contr_en=bps[i+20]._buff[15];
			inv[i]._pwm_en=bps[i+20]._buff[16];  
			inv[i]._phase_mode=bps[i+20]._buff[17];  
     		} 
		else 
     		{
      		inv[i]._Ii=0;
			inv[i]._Pio=0;
			inv[i]._Uio=0;
     		inv[i]._Ti=0;
     		inv[i]._flags_tm=0; 
     		inv[i]._Uil=0;
     		inv[i]._Uin=0;
			inv[i]._cnt=25; 
			inv[i]._Uoutmin=0; 
			inv[i]._Uoutmax=0; 
			inv[i]._Pnom=0; 
			inv[i]._net_contr_en=0;
			inv[i]._pwm_en=0;   
			   
     		}
     	}
   	}
#endif

#ifdef GLADKOV
inv[0]._Ii=bps[4]._buff[0]+(bps[4]._buff[1]*256);
inv[0]._Pio=bps[4]._buff[2]+(bps[4]._buff[3]*256);
inv[0]._Uio=bps[4]._buff[4]+(bps[4]._buff[5]*256);
inv[0]._Ti=(signed)(bps[4]._buff[6]);
inv[0]._flags_tm=bps[4]._buff[7];
inv[0]._Uin=bps[4]._buff[8]+(bps[4]._buff[9]*256);
inv[0]._Uil=bps[4]._buff[10]+(bps[4]._buff[11]*256);
inv[0]._cnt=0;    

inv[1]._Ii=bps[21]._buff[0]+(bps[21]._buff[1]*256);
inv[1]._Pio=bps[21]._buff[2]+(bps[21]._buff[3]*256);
inv[1]._Uio=bps[21]._buff[4]+(bps[21]._buff[5]*256);
inv[1]._Ti=(signed)(bps[21]._buff[6]);
inv[1]._flags_tm=bps[21]._buff[7];
inv[1]._Uin=bps[21]._buff[8]+(bps[21]._buff[9]*256);
inv[1]._Uil=bps[21]._buff[10]+(bps[21]._buff[11]*256);
inv[1]._cnt=0;    
#endif

/*
if((BAT_IS_ON[0]==bisON)&&(BAT_TYPE==1))
	{
	lakb[0]._battCommState=0;
	if(lakb[0]._cnt>10)lakb[0]._battCommState=2;
	else if(lakb[0]._bRS485ERR==1)lakb[0]._battCommState=1;
	
	if(lakb[0]._battCommState==0)
		{	
		bat[0]._Ub=(signed short)((lakb[0]._tot_bat_volt+5)/10);
		bat[0]._Ib=(signed short)lakb[0]._ch_curr;
		if(lakb[0]._dsch_curr) bat[0]._Ib=(signed short) (-lakb[0]._dsch_curr);
		bat[0]._Tb=(signed short)lakb[0]._max_cell_temp;
		}
	}
*/

#ifdef UKU_TELECORE2015

	if(BAT_TYPE==2)
		{
/*		lakb[0]._ch_curr=((ascii2halFhex(liBatteryInBuff[113]))<<12)+
							((ascii2halFhex(liBatteryInBuff[114]))<<8)+
							((ascii2halFhex(liBatteryInBuff[115]))<<4)+
							((ascii2halFhex(liBatteryInBuff[116])));
		

		lakb[0]._tot_bat_volt=	(unsigned short)(((ascii2halFhex(liBatteryInBuff[117]))<<12)+
							((ascii2halFhex(liBatteryInBuff[118]))<<8)+
							((ascii2halFhex(liBatteryInBuff[119]))<<4)+
							((ascii2halFhex(liBatteryInBuff[120]))))/100;
	
		lakb[0]._max_cell_temp= 	(((ascii2halFhex(liBatteryInBuff[93]))<<12)+
							((ascii2halFhex(liBatteryInBuff[94]))<<8)+
							((ascii2halFhex(liBatteryInBuff[95]))<<4)+
							((ascii2halFhex(liBatteryInBuff[96]))))/10-273;
	
		lakb[0]._s_o_c_abs=		(unsigned short)((ascii2halFhex(liBatteryInBuff[121]))<<12)+
							((ascii2halFhex(liBatteryInBuff[122]))<<8)+
							((ascii2halFhex(liBatteryInBuff[123]))<<4)+
							((ascii2halFhex(liBatteryInBuff[124])));
	
		lakb[0]._rat_cap=		(unsigned short)((ascii2halFhex(liBatteryInBuff[127]))<<12)+
							((ascii2halFhex(liBatteryInBuff[128]))<<8)+
							((ascii2halFhex(liBatteryInBuff[129]))<<4)+
							((ascii2halFhex(liBatteryInBuff[130])));
	
		lakb[0]._s_o_c=		lakb[0]._s_o_c_abs/(lakb[0]._rat_cap/100); */
	
	
	/*	lakb[0]._rat_cap= (lakb_damp[i][13]*256)+ lakb_damp[i][14];
		lakb[0]._max_cell_volt= (lakb_damp[i][0]*256)+ lakb_damp[i][1];
		lakb[0]._min_cell_volt= (lakb_damp[i][2]*256)+ lakb_damp[i][3];
		lakb[0]._max_cell_temp= lakb_damp[i][4];
		lakb[0]._min_cell_temp= lakb_damp[i][5];
		lakb[0]._tot_bat_volt= (lakb_damp[i][6]*256)+ lakb_damp[i][7];
		lakb[0]._ch_curr= (lakb_damp[i][8]*256)+ lakb_damp[i][8];
		lakb[0]._dsch_curr= (lakb_damp[i][10]*256)+ lakb_damp[i][11];
		lakb[0]._s_o_c= lakb_damp[i][12];
		lakb[0]._r_b_t= lakb_damp[i][15];
		lakb[0]._c_c_l_v= (lakb_damp[i][16]*256)+ lakb_damp[i][17];
		lakb[0]._s_o_h= lakb_damp[i][18];
	
		if(lakb[i]._rat_cap==0)
			{
			if(lakb[i]._isOnCnt)
				{
				lakb[i]._isOnCnt--;
				if(lakb[i]._isOnCnt==0)
					{
					if(lakb[i]._battIsOn!=0) bLAKB_KONF_CH=1;
					}
				}
			}
		else 
			{
			if(lakb[i]._isOnCnt<50)
				{
				lakb[i]._isOnCnt++;
				if(lakb[i]._isOnCnt==50)
					{
					if(lakb[i]._battIsOn!=1) bLAKB_KONF_CH=1;
					}
				}
			}
		gran(&lakb[i]._isOnCnt,0,50);*/
		}
	else if(BAT_TYPE==3)
		{
		//short numOfPacks;
		//short numOfCells, numOfTemperCells, baseOfData;
		
		#ifndef UKU_TELECORE2016
/*		numOfCells=((ascii2halFhex(liBatteryInBuff[17]))<<4)+((ascii2halFhex(liBatteryInBuff[18])));
		numOfTemperCells=((ascii2halFhex(liBatteryInBuff[17+(numOfCells*4)+2]))<<4)+((ascii2halFhex(liBatteryInBuff[18+(numOfCells*4)+2])));
		numOfPacks=((ascii2halFhex(liBatteryInBuff[15]))<<4)+((ascii2halFhex(liBatteryInBuff[16])));
		if(numOfPacks)numOfPacks-=1;
		if((numOfPacks<0)||(numOfPacks>NUMBAT_TELECORE))numOfPacks=0;
		plazma_numOfCells=numOfCells;
		plazma_numOfTemperCells=numOfTemperCells;
		plazma_numOfPacks=numOfPacks;


		baseOfData=16+(numOfCells*4)+2+(numOfTemperCells*4)+2;

		lakb[numOfPacks]._ch_curr=(signed short)(
							((ascii2halFhex(liBatteryInBuff[1+baseOfData]))<<12)+
							((ascii2halFhex(liBatteryInBuff[2+baseOfData]))<<8)+
							((ascii2halFhex(liBatteryInBuff[3+baseOfData]))<<4)+
							((ascii2halFhex(liBatteryInBuff[4+baseOfData])))
							);	  

		lakb[numOfPacks]._tot_bat_volt=(signed short)(
							((ascii2halFhex(liBatteryInBuff[1+baseOfData+4]))<<12)+
							((ascii2halFhex(liBatteryInBuff[2+baseOfData+4]))<<8)+
							((ascii2halFhex(liBatteryInBuff[3+baseOfData+4]))<<4)+
							((ascii2halFhex(liBatteryInBuff[4+baseOfData+4])))
							)/10;

		lakb[numOfPacks]._max_cell_temp=(signed short)(
							((ascii2halFhex(liBatteryInBuff[1+baseOfData-4]))<<12)+
							((ascii2halFhex(liBatteryInBuff[2+baseOfData-4]))<<8)+
							((ascii2halFhex(liBatteryInBuff[3+baseOfData-4]))<<4)+
							((ascii2halFhex(liBatteryInBuff[4+baseOfData-4])))
							)-2730;

		lakb[numOfPacks]._s_o_c=(signed short)(
							((ascii2halFhex(liBatteryInBuff[1+baseOfData+8]))<<12)+
							((ascii2halFhex(liBatteryInBuff[2+baseOfData+8]))<<8)+
							((ascii2halFhex(liBatteryInBuff[3+baseOfData+8]))<<4)+
							((ascii2halFhex(liBatteryInBuff[4+baseOfData+8])))
							)/10;

		lakb[numOfPacks]._s_o_h=(signed short)(
							((ascii2halFhex(liBatteryInBuff[1+baseOfData+14]))<<12)+
							((ascii2halFhex(liBatteryInBuff[2+baseOfData+14]))<<8)+
							((ascii2halFhex(liBatteryInBuff[3+baseOfData+14]))<<4)+
							((ascii2halFhex(liBatteryInBuff[4+baseOfData+14])))
							)/10; */
		#endif								  
		}
/*	
if(sacredSunSilentCnt<3) 
	{
    	bat[0]._Ub=lakb[0]._tot_bat_volt;
    	bat[0]._Tb=lakb[0]._max_cell_temp;
   	bat[0]._Ib=lakb[0]._ch_curr/10;
	}
else 
	{
    	//bat[0]._Ub=0;
    	//bat[0]._Tb=0;
   	//bat[0]._Ib=0;
	} */

if(BAT_TYPE==1)
	{
	char i;
	for(i=0;i<1;i++)
		{
		lakb[i]._rat_cap= (lakb_damp[i][13]*256)+ lakb_damp[i][14];
		lakb[i]._max_cell_volt= (lakb_damp[i][0]*256)+ lakb_damp[i][1];
		lakb[i]._min_cell_volt= (lakb_damp[i][2]*256)+ lakb_damp[i][3];
		lakb[i]._max_cell_temp= lakb_damp[i][4];
		lakb[i]._min_cell_temp= lakb_damp[i][5];
		lakb[i]._tot_bat_volt= (lakb_damp[i][6]*256)+ lakb_damp[i][7];
		lakb[i]._ch_curr= (lakb_damp[i][8]*256)+ lakb_damp[i][9];
		lakb[i]._dsch_curr= (lakb_damp[i][10]*256)+ lakb_damp[i][11];
		lakb[i]._s_o_c= lakb_damp[i][12];
		lakb[i]._r_b_t= lakb_damp[i][15];
		lakb[i]._c_c_l_v= (lakb_damp[i][16]*256)+ lakb_damp[i][17];
		lakb[i]._s_o_h= lakb_damp[i][18];
		lakb[i]._flags1= lakb_damp[i][34];
		lakb[i]._flags2= lakb_damp[i][35];
		lakb[i]._b_p_ser_num= lakb_damp[i][36];

/*		if(lakb[i]._rat_cap==0)
			{
			if(lakb[i]._isOnCnt)
				{
				lakb[i]._isOnCnt--;
				if(lakb[i]._isOnCnt==0)
					{
					if(lakb[i]._battIsOn!=0) bLAKB_KONF_CH=1;
					}
				}
			}
		else 
			{
			if(lakb[i]._isOnCnt<50)
				{
				lakb[i]._isOnCnt++;
				if(lakb[i]._isOnCnt==50)
					{
					if(lakb[i]._battIsOn!=1) bLAKB_KONF_CH=1;
					}
				}
			} */
		gran(&lakb[i]._isOnCnt,0,50);
	 	}

	if(lakb_damp[0][41]==100)
		{
		li_bat._485Error=1;
		}
	if(lakb_damp[0][41]==0)
		{
		//if(bRS485ERR)bLAKB_KONF_CH=1;
		li_bat._485Error=0;
		}
	li_bat._485ErrorCnt=lakb_damp[0][41];


	}


#endif


#ifdef UKU_TELECORE2015
//вычисление параметров работы батареи
//TODO дописать для всех батарей все параметры и при отцепке батарей
li_bat._batStat=bsOK;
if(BAT_TYPE==1) //COSLIGHT
	{
	if(li_bat._batStat==bsOK)
		{
		li_bat._Ub=lakb[0]._tot_bat_volt/10;

		if(lakb[0]._ch_curr)li_bat._Ib=lakb[0]._ch_curr/10;
		else if(lakb[0]._dsch_curr) li_bat._Ib=bat[0]._Ib/10;//lakb[0]._dsch_curr/10;
	
		li_bat._ratCap=lakb[0]._rat_cap/100;
		li_bat._soc=lakb[0]._s_o_c;
		li_bat._soh=lakb[0]._s_o_h;
		li_bat._cclv=lakb[0]._c_c_l_v/10;
		li_bat._Tb=lakb[0]._max_cell_temp;
		li_bat._rbt=lakb[0]._r_b_t;
		}
	else 
		{
		li_bat._Ub=bat[0]._Ub;
		li_bat._Ib=bat[0]._Ib/10;
		li_bat._Tb=bat[0]._Tb;
		}

	if((li_bat._485Error)||(li_bat._canError))
		{
		li_bat._batStat=bsOFF;
		}
	else li_bat._batStat=bsOK;
	}
else if(BAT_TYPE==2) //SACRED SUN
	{
	}
else if(BAT_TYPE==3) //ZTT
	{
	if(li_bat._batStat==bsOK)
		{

		}
	}
#endif


/*
if((BAT_IS_ON[0]==bisON)&&(BAT_TYPE[0]==1)&&(BAT_LINK==0))
	{


	if(bat_drv_rx_buff[13]<=0x39)bbb[0]=bat_drv_rx_buff[13]-0x30;
	else bbb[0]=bat_drv_rx_buff[13]-55;
	if(bat_drv_rx_buff[14]<=0x39)bbb[1]=bat_drv_rx_buff[14]-0x30;
	else bbb[1]=bat_drv_rx_buff[14]-55;
	if(bat_drv_rx_buff[15]<=0x39)bbb[2]=bat_drv_rx_buff[15]-0x30;
	else bbb[2]=bat_drv_rx_buff[15]-55;
	if(bat_drv_rx_buff[16]<=0x39)bbb[3]=bat_drv_rx_buff[16]-0x30;
	else bbb[3]=bat_drv_rx_buff[16]-55;

	tempSS=0;
	tempSS=((bbb[0]*4096)+(bbb[1]*256)+(bbb[2]*16)+bbb[3]);

	bat[0]._max_cell_volt=(tempSS+5)/10;

	if(bat_drv_rx_buff[17]<=0x39)bbb[0]=bat_drv_rx_buff[17]-0x30;
	else bbb[0]=bat_drv_rx_buff[17]-55;
	if(bat_drv_rx_buff[18]<=0x39)bbb[1]=bat_drv_rx_buff[18]-0x30;
	else bbb[1]=bat_drv_rx_buff[18]-55;
	if(bat_drv_rx_buff[19]<=0x39)bbb[2]=bat_drv_rx_buff[19]-0x30;
	else bbb[2]=bat_drv_rx_buff[19]-55;
	if(bat_drv_rx_buff[20]<=0x39)bbb[3]=bat_drv_rx_buff[20]-0x30;
	else bbb[3]=bat_drv_rx_buff[20]-55;

	tempSS=0;
	tempSS=((bbb[0]*4096)+(bbb[1]*256)+(bbb[2]*16)+bbb[3]);

	bat[0]._min_cell_volt=(tempSS+5)/10;


	}*/



}

//-----------------------------------------------
void mnemo_hndl(void)
{
if(((ind==iMn_220)||(ind==iMn))&&(sub_ind==0)&&(MNEMO_ON==mnON))
	{
	if(mnemo_cnt)mnemo_cnt--;
	}
else mnemo_cnt=MNEMO_TIME;
}

//-----------------------------------------------
void adc_init(void)
{

SET_REG(LPC_PINCON->PINSEL1,1,(25-16)*2,2);
SET_REG(LPC_PINCON->PINSEL1,1,(24-16)*2,2);
SET_REG(LPC_PINCON->PINSEL1,1,(23-16)*2,2);


SET_REG(LPC_PINCON->PINMODE1,2,(25-16)*2,2);
SET_REG(LPC_PINCON->PINMODE1,2,(24-16)*2,2);
SET_REG(LPC_PINCON->PINMODE1,2,(23-16)*2,2);

SET_REG(LPC_ADC->ADCR,0,24,3);

SET_REG(LPC_ADC->ADCR,1,21,1);
SET_REG(LPC_ADC->ADCR,0,16,1);
SET_REG(LPC_ADC->ADCR,1,8,8);

//SET_REG(LPC_GPIO0->FIODIR,7,5,3);
//SET_REG(LPC_GPIO0->FIOPIN,4,5,3);
	
	/*if(adc_ch<=7)*///SET_REG(LPC_ADC->ADCR,1<<5,0,8);
     /*else if(adc_ch==8) SET_REG(LPC_ADC->ADCR,1<<2,0,8);
     else SET_REG(LPC_ADC->ADCR,1<<4,0,8);*/

LPC_ADC->ADINTEN     =  (1<< 8);      /* global enable interrupt            */

NVIC_EnableIRQ(ADC_IRQn);             /* enable ADC Interrupt               */


}

//-----------------------------------------------
void adc_drv7(void) //(Uсети - постоянка)
{
//int temp_S;
//char i;
//signed short temp_SS;

adc_self_ch_disp[0]=abs_pal(adc_self_ch_buff[1]-adc_self_ch_buff[0]);//adc_self_ch_buff[0]&0x0f80;
adc_self_ch_disp[1]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[1]);//adc_self_ch_buff[1]&0x0f80;
adc_self_ch_disp[2]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[0]);//adc_self_ch_buff[2]&0x0f80;

//adc_self_ch_disp[0]=adc_self_ch_buff[0]&0x0ff0;
//adc_self_ch_disp[1]=adc_self_ch_buff[1]&0x0ff0;
//adc_self_ch_disp[2]=adc_self_ch_buff[2]&0x0ff0;


if(adc_self_ch_disp[2]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[2];
	} 
else if(adc_self_ch_disp[1]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[1];
	}
else if(adc_self_ch_disp[0]<300)//==adc_self_ch_disp[1])
	{
	adc_result=adc_self_ch_buff[0];
	}
    //adc_result=92;

if(adc_ch_net)
	{

	main_power_buffer[0]+=(long)(adc_result);
	main_power_buffer[1]+=(long)(adc_result);
	main_power_buffer[2]+=(long)(adc_result);
	main_power_buffer[3]+=(long)(adc_result);

	adc_net_buff_cnt++;
	if(adc_net_buff_cnt>=0x1000)
		{
		adc_net_buff_cnt=0;
		}
	if((adc_net_buff_cnt&0x03ff)==0)
		{
		#ifdef UKU_220
		net_buff_=(short)((main_power_buffer[adc_net_buff_cnt>>10])>>11);
		#else
		#ifdef UKU_220_V2
		net_buff_=(short)((main_power_buffer[adc_net_buff_cnt>>10])>>11);
		#else
		net_buff_=(short)((main_power_buffer[adc_net_buff_cnt>>10])>>8);
		#endif
		#endif
		main_power_buffer[adc_net_buff_cnt>>10]=0;
		}


	} 
else if(!adc_ch_net)
	{
	adc_buff[adc_ch][adc_ch_cnt]=(long)adc_result;
	
	if((adc_ch_cnt&0x03)==0)
		{
		long temp_L;
		char i;
		temp_L=0;
		for(i=0;i<16;i++)
			{
			temp_L+=adc_buff[adc_ch][i];
			}
		adc_buff_[adc_ch]= (short)(temp_L>>4);

		//adc_buff_[3]=346;
		}
	if(++adc_ch>=16) 
		{
		adc_ch=0;
		adc_ch_cnt++;
		if(adc_ch_cnt>=16)adc_ch_cnt=0;
		}
	}

//adc_buff[adc_ch][adc_cnt1]=(adc_self_ch_buff[2]+adc_self_ch_buff[1])/2;

//if(adc_buff[adc_ch][adc_cnt1]<adc_buff_min[adc_ch])adc_buff_min[adc_ch]=adc_buff[adc_ch][adc_cnt1];
//if(adc_buff[adc_ch][adc_cnt1]>adc_buff_max[adc_ch])adc_buff_max[adc_ch]=adc_buff[adc_ch][adc_cnt1];
/*
	{
	if((adc_cnt1&0x03)==0)
		{
		temp_S=0;
		for(i=0;i<16;i++)
			{
			temp_S+=adc_buff[adc_ch][i];
			} 
         	adc_buff_[adc_ch]=temp_S>>4;
          }
	}*/


		  

adc_self_ch_cnt=0;

adc_ch_net++;
adc_ch_net&=1;

//SET_REG(LPC_GPIO0->FIODIR,7,5,3);
//SET_REG(LPC_GPIO0->FIOPIN,adc_ch,5,3);

if(adc_ch_net)
	{
	//LPC_GPIO2->FIODIR|=(1<<7);
	//LPC_GPIO2->FIOPIN|=(1<<7);
	SET_REG(LPC_ADC->ADCR,1<<2,0,8);
	}
else
	{
	//LPC_GPIO2->FIODIR|=(1<<7);
	//LPC_GPIO2->FIOPIN&=~(1<<7);
	if(!(adc_ch&(1<<3)))SET_REG(LPC_ADC->ADCR,1<<0,0,8);
	else 			SET_REG(LPC_ADC->ADCR,1<<1,0,8);


	SET_REG(LPC_GPIO0->FIODIR,1,28,1);
	SET_REG(LPC_GPIO1->FIODIR,1,30,1);
	SET_REG(LPC_GPIO3->FIODIR,1,26,1);

	if(!(adc_ch&(1<<0)))SET_REG(LPC_GPIO0->FIOPIN,0,28,1);
	else 			SET_REG(LPC_GPIO0->FIOPIN,1,28,1);

	if(!(adc_ch&(1<<1)))SET_REG(LPC_GPIO1->FIOPIN,0,30,1);
	else 			SET_REG(LPC_GPIO1->FIOPIN,1,30,1);

	if(!(adc_ch&(1<<2)))SET_REG(LPC_GPIO3->FIOPIN,0,26,1);
	else 			SET_REG(LPC_GPIO3->FIOPIN,1,26,1);
	}
	



LPC_ADC->ADCR |=  (1<<24);

}

//-----------------------------------------------
void adc_drv6(void) //(с попыткой измерять горбы)
{
//int temp_S;
//char i;
//signed short temp_SS;

adc_self_ch_disp[0]=abs_pal(adc_self_ch_buff[1]-adc_self_ch_buff[0]);//adc_self_ch_buff[0]&0x0f80;
adc_self_ch_disp[1]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[1]);//adc_self_ch_buff[1]&0x0f80;
adc_self_ch_disp[2]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[0]);//adc_self_ch_buff[2]&0x0f80;

//adc_self_ch_disp[0]=adc_self_ch_buff[0]&0x0ff0;
//adc_self_ch_disp[1]=adc_self_ch_buff[1]&0x0ff0;
//adc_self_ch_disp[2]=adc_self_ch_buff[2]&0x0ff0;


if(adc_self_ch_disp[2]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[2];
	} 
else if(adc_self_ch_disp[1]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[1];
	}
else if(adc_self_ch_disp[0]<300)//==adc_self_ch_disp[1])
	{
	adc_result=adc_self_ch_buff[0];
	}
    //adc_result=92;

if(adc_ch_net)
	{

	if(adc_window_flag)
		{
		main_power_buffer[0]+=(long)(adc_result>>2);
		main_power_buffer[1]+=(long)(adc_result>>2);
		main_power_buffer[2]+=(long)(adc_result>>2);
		main_power_buffer[3]+=(long)(adc_result>>2);
		}
//	main_power_buffer[4]+=(long)(adc_result>>2);
//	main_power_buffer[5]+=(long)(adc_result>>2);
//	main_power_buffer[6]+=(long)(adc_result>>2);
//	main_power_buffer[7]+=(long)(adc_result>>2);
//	main_power_buffer_cnt++;


	if(adc_result<100)
		{
		adc_zero_cnt++;
		}
	else adc_zero_cnt=0;

	if(adc_zero_cnt>=2000)
		{
		adc_zero_cnt=2000;
		main_power_buffer[0]=0;
		main_power_buffer[1]=0;
		main_power_buffer[2]=0;
		main_power_buffer[3]=0;
		net_buff_=0;
		}

	if(adc_zero_cnt==5)
		{
		
		if(adc_window_flag)
			{
			adc_gorb_cnt++;
			if(adc_gorb_cnt>=512)
				{
				adc_gorb_cnt=0;
				//net_buff_=main_power_buffer[0]>>8;
				//main_power_buffer[0]=0;
			   	}

			if((adc_gorb_cnt&0x007f)==0)
				{
				net_buff_=main_power_buffer[adc_gorb_cnt>>7]>>8;
				main_power_buffer[adc_gorb_cnt>>7]=0;
				}
			}

		//LPC_GPIO2->FIODIR|=(1<<8);
		//LPC_GPIO2->FIOPIN^=(1<<8);

		if((adc_window_cnt>150)&&(adc_window_flag))
			{
			adc_window_flag=0;

			
			}
		if((adc_window_cnt>30)&&(adc_window_cnt<70)&&(!adc_window_flag))
			{
			adc_window_flag=1;

			//LPC_GPIO2->FIODIR|=(1<<8);
			//LPC_GPIO2->FIOPIN|=(1<<8);
			}
		}
	} 
else if(!adc_ch_net)
	{
	adc_buff[adc_ch][adc_ch_cnt]=(long)adc_result;
	
	if((adc_ch_cnt&0x03)==0)
		{
		long temp_L;
		char i;
		temp_L=0;
		for(i=0;i<16;i++)
			{
			temp_L+=adc_buff[adc_ch][i];
			}
		adc_buff_[adc_ch]= (short)(temp_L>>4);

		//adc_buff_[3]=346;
		}
	if(++adc_ch>=16) 
		{
		adc_ch=0;
		adc_ch_cnt++;
		if(adc_ch_cnt>=16)adc_ch_cnt=0;
		}
	}

//adc_buff[adc_ch][adc_cnt1]=(adc_self_ch_buff[2]+adc_self_ch_buff[1])/2;

//if(adc_buff[adc_ch][adc_cnt1]<adc_buff_min[adc_ch])adc_buff_min[adc_ch]=adc_buff[adc_ch][adc_cnt1];
//if(adc_buff[adc_ch][adc_cnt1]>adc_buff_max[adc_ch])adc_buff_max[adc_ch]=adc_buff[adc_ch][adc_cnt1];
/*
	{
	if((adc_cnt1&0x03)==0)
		{
		temp_S=0;
		for(i=0;i<16;i++)
			{
			temp_S+=adc_buff[adc_ch][i];
			} 
         	adc_buff_[adc_ch]=temp_S>>4;
          }
	}*/


		  

adc_self_ch_cnt=0;

adc_ch_net++;
adc_ch_net&=1;

//SET_REG(LPC_GPIO0->FIODIR,7,5,3);
//SET_REG(LPC_GPIO0->FIOPIN,adc_ch,5,3);

if(adc_ch_net)
	{
	//LPC_GPIO2->FIODIR|=(1<<7);
	//LPC_GPIO2->FIOPIN|=(1<<7);
	SET_REG(LPC_ADC->ADCR,1<<2,0,8);
	}
else
	{
	//LPC_GPIO2->FIODIR|=(1<<7);
	//LPC_GPIO2->FIOPIN&=~(1<<7);
	if(!(adc_ch&(1<<3)))SET_REG(LPC_ADC->ADCR,1<<0,0,8);
	else 			SET_REG(LPC_ADC->ADCR,1<<1,0,8);


	SET_REG(LPC_GPIO0->FIODIR,1,28,1);
	SET_REG(LPC_GPIO1->FIODIR,1,30,1);
	SET_REG(LPC_GPIO3->FIODIR,1,26,1);

	if(!(adc_ch&(1<<0)))SET_REG(LPC_GPIO0->FIOPIN,0,28,1);
	else 			SET_REG(LPC_GPIO0->FIOPIN,1,28,1);

	if(!(adc_ch&(1<<1)))SET_REG(LPC_GPIO1->FIOPIN,0,30,1);
	else 			SET_REG(LPC_GPIO1->FIOPIN,1,30,1);

	if(!(adc_ch&(1<<2)))SET_REG(LPC_GPIO3->FIOPIN,0,26,1);
	else 			SET_REG(LPC_GPIO3->FIOPIN,1,26,1);
	}
	



LPC_ADC->ADCR |=  (1<<24);

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
//*************-----------------------------------------------
void rele_hndl(void)
{
//static char cnt_rel_sam;
//char temp;

//temp=0;


SET_REG(LPC_PINCON->PINSEL0,0,4*2,6*2);
SET_REG(LPC_GPIO0->FIODIR,63,4,6);
SET_REG(LPC_PINCON->PINSEL7,0,(25-16)*2,2);
SET_REG(LPC_GPIO3->FIODIR,1,25,1);
SET_REG(LPC_PINCON->PINSEL1,0,(29-16)*2,2);
SET_REG(LPC_GPIO0->FIODIR,1,29,1);






if((((bat[0]._rel_stat)  || (tbatdisable_stat!=tbdsON))&&(tbatdisable_cmnd))	&& (main_1Hz_cnt>5))
	{
	SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_BAT1,1);
	}
else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_BAT1,1);	  	

if((((bat[1]._rel_stat) || (tbatdisable_stat!=tbdsON))&&(tbatdisable_cmnd))	&& (main_1Hz_cnt>5))
	{
	SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_BAT2,1);
	}
else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_BAT2,1);


if(mess_find_unvol((MESS2RELE_HNDL))&&(mess_data[0]==PARAM_RELE_SAMOKALIBR)) 
	{
	if(mess_data[1]==1)SET_REG(LPC_GPIO0->FIOSET,1,29,1);
	else if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,29,1);
	}
else SET_REG(LPC_GPIO0->FIOCLR,1,29,1);


#ifndef UKU2071x
//Реле аварии сети
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
	{
	if(mess_data[1]==0) 			SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
	else 						SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
	}
else	if(!(avar_ind_stat&0x00000001)) 	SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
else 							SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
#endif
#ifdef UKU2071x
//Реле аварии сети
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
	{
	if(mess_data[1]==0)				SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1); 
	else 						SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
	}
else	if(!(avar_ind_stat&0x00000001))	SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
else 					  		SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
#endif

#ifdef UKU_3U
//Реле аварий батарей
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT1))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT1,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT1,1);
     }
else 
	{
	if(!(avar_ind_stat&0x00000002)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT1,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT1,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT2))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT2,1);
     }
else 
	{
	if(!(avar_ind_stat&0x00000004)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT2,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
     }
else 
	{
	if(!(avar_ind_stat&0x000007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
	} 

#endif


#ifdef UKU_GLONASS
//Реле аварий батарей
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT1))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT1,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT1,1);
     }
else 
	{
	if(!(avar_ind_stat&0x00000002)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT1,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT1,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT2))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT2,1);
     }
else 
	{
	if(!(avar_ind_stat&0x00000004)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT2,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
     }
else 
	{
	if(!(avar_ind_stat&0x000007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
	} 

#endif

#ifdef U /*



/*
//Реле аварии батарей
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
	{
	if(mess_data[1]==0) temp&=~(1<<SHIFT_REL_AV_BAT);
	else if(mess_data[1]==1) temp|=(1<<SHIFT_REL_AV_BAT);
     }
else 
	{
	if(!(avar_ind_stat&0x00000006)) temp&=~(1<<SHIFT_REL_AV_BAT);
     else temp|=(1<<SHIFT_REL_AV_BAT);
	} 
*/

#endif

#ifdef UKU_RSTKM

//Реле общей аварии
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_COMM))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_COMM,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_COMM,1);
	}
else 
	{
     if(  (!(avar_ind_stat&0x00007fff))/* &&
          ((!SK_REL_EN[0]) || (sk_av_stat[0]!=sasON))  &&
          ((!SK_REL_EN[1]) || (sk_av_stat[1]!=sasON))  &&
          ((!SK_REL_EN[2]) || (sk_av_stat[2]!=sasON))  &&
          ((!SK_REL_EN[3]) || (sk_av_stat[3]!=sasON))*/  )SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_COMM,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_COMM,1);
	}
	

//Реле освещения
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LIGHT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
     }
else 
	{
	if(sk_av_stat[0]!=sasON) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
	}


//Реле выключения нагрузки
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LOAD_OFF))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
     }
else if(tloaddisable_cmnd==0)
	{
	SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
	}
else if((tloaddisable_cmnd)&&(tloaddisable_cmnd<=11))
	{
	SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
	}

else 
	{
	if(!(tloaddisable_stat==tldsON)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
	} 

//Реле осевого вентилятора
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	}
else 
	{
	if(mixer_vent_stat==mvsOFF) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	} 

#endif

#ifdef UKU_KONTUR

//Реле общей аварии
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_COMM))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_COMM,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_COMM,1);
	}
else 
	{
     if(  (!(avar_ind_stat&0x00007fff)) &&
          ((!SK_REL_EN[0]) || (sk_av_stat[0]!=sasON))  &&
          ((!SK_REL_EN[1]) || (sk_av_stat[1]!=sasON))  &&
          ((!SK_REL_EN[2]) || (sk_av_stat[2]!=sasON))  /*&&
          ((!SK_REL_EN[3]) || (sk_av_stat[3]!=sasON))*/  )SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_COMM,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_COMM,1);
	}

	
//rel_warm_plazma=0;
//Реле освещения   
/*
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_WARM))
	{
	if(mess_data[1]==0)
		{
		SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=1;
		}
	else if(mess_data[1]==1) 
		{
		SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=2;
		}
     }
else 
	{
	if(warm_stat_k==wsOFF) 
		{
		SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=3;
		}
     else 
		{
		SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=4;
		}
	}
*/
//Реле освещения
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LIGHT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
     }
else 
	{
	if(sk_av_stat[0]!=sasON) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
	}



//Реле выключения нагрузки
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LOAD_OFF))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
     }
else if(tloaddisable_cmnd==0)
	{
	SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
	}
else if((tloaddisable_cmnd)&&(tloaddisable_cmnd<=11))
	{
	SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
	}

else 
	{
	if(!(tloaddisable_stat==tldsON)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
	} 

//Реле осевого вентилятора или отопителя
if(RELE_LOG)
	{
	if((mess_find_unvol(MESS2RELE_HNDL))&&(mess_data[0]==PARAM_RELE_VENT_WARM))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		}
	else 
		{
		if(warm_stat_k==wsOFF) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		} 

	}
else 
	{
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT_WARM))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		}
	else 
		{
		if(vent_stat_k==vsOFF) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		} 
	}
#endif

#ifdef UKU_6U
//Реле аварий батарей
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT1))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT1,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT1,1);
     }
else 
	{
	if(!(avar_ind_stat&0x00000002)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT1,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT1,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT2))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT2,1);
    }
else if(NPN_OUT==npnoRELEAVBAT2)
	{
	if(npn_stat==npnsOFF)//&&(mess_find_unvol(MESS2RELE_HNDL))&&(mess_data[0]==PARAM_RELE_NPN))
		{
		/*if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
		else if(mess_data[1]==1)*/ SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
     	}
	else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT2,1);
	}
else 
	{
	if(!(avar_ind_stat&0x00000004)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT2,1);
    else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT2,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
     }
else 
	{
	if(!(avar_ind_stat&0x000007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
	}
else if((NPN_OUT==npnoRELEVENT))
	{
	if(npn_stat==npnsOFF)//&&(mess_find_unvol(MESS2RELE_HNDL))&&(mess_data[0]==PARAM_RELE_NPN))
		{
		/*if(mess_data[1]==0)*/ SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
		//else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
    	}
	else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	}
else 
	{
	if(!vent_stat) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
	}

#endif

#ifdef UKU_220
//Реле аварий батарей
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT,1);
     }
else 
	{
	if(!(avar_ind_stat&0x00000002)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
     }
else 
	{
	if(!(avar_ind_stat&0x000007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
	}
else 
	{
	if((RELE_VENT_LOGIC==0)||(RELE_VENT_LOGIC==1))
		{
		if(vent_stat) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
		else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
		}
	else 
		{
		if((avar_ind_stat&0x00000004)) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
     	else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
		}
	}

#endif

#ifdef UKU_220_V2
//Реле аварий батарей
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT,1);
     }
else 
	{
	if(!(avar_ind_stat&0x00000002)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BAT,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BAT,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
     }
else 
	{
	if(!(avar_ind_stat&0x000007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
	} 

if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
	}
else 
	{
	if((RELE_VENT_LOGIC==0)||(RELE_VENT_LOGIC==1))
		{
		if(vent_stat) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
		else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
		}
	else 
		{
		if((avar_ind_stat&0x00000004)) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
     	else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
		}
	}

#endif

#ifdef UKU_220_IPS_TERMOKOMPENSAT

if((AUSW_MAIN==22010)||(AUSW_MAIN==22011))
	{
	#ifndef UKU2071x
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO3->FIOSET,1,25,1);
		else SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO3->FIOSET,1,25,1);
	else SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
	#endif
	#ifdef UKU2071x
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
		else SET_REG(LPC_GPIO3->FIOSET,1,25,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
	else SET_REG(LPC_GPIO3->FIOSET,1,25,1);
	#endif
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,7,1);
	     }
	else 
		{
		if(!(avar_ind_stat&0x100007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,7,1);
		} 

	//Реле аварий батарей
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,4,1);
     	}
	else 
		{
		if(!(ips_bat_av_stat)) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
     	else SET_REG(LPC_GPIO0->FIOSET,1,4,1);
		}
	}

else	if(AUSW_MAIN==22023)
	{

	//Реле аварий батарей
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,4,1);
     	}
	else 
		{
		if(!(ips_bat_av_stat)) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
     	else SET_REG(LPC_GPIO0->FIOSET,1,4,1);
		} 


	//Реле аварии сети ТУТ КАКАЯ то ЛАЖА с аварией сети. Обращение к разным портам
	#ifndef UKU2071x
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
		else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO1->FIOCLR,1,SHIFT_REL_AV_NET,1);
	else SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
	#endif
	#ifdef UKU2071x
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);
		else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO1->FIOSET,1,SHIFT_REL_AV_NET,1);
	else SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
	#endif

	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,7,1);
	     }
	else 
		{
		if(!(avar_ind_stat&0x100007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,7,1);
		} 
	}
else	if(AUSW_MAIN==22043)
	{
	//Реле аварий батарей
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,4,1);
     	}
	else 
		{
		if(!(ips_bat_av_stat)) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
     	else SET_REG(LPC_GPIO0->FIOSET,1,4,1);
		} 
	//Реле аварии сети ТУТ КАКАЯ то ЛАЖА с аварией сети. Обращение к разным портам
	#ifndef UKU2071x 
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
		else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO1->FIOCLR,1,SHIFT_REL_AV_NET,1);
	else SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
	#endif
	#ifdef UKU2071x 
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);
		else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO1->FIOSET,1,SHIFT_REL_AV_NET,1);
	else SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
	#endif

	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,7,1);
	     }
	else 
		{
		if(!(avar_ind_stat&0x100007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,7,1);
		}
	//Реле аварии БПС
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
     	}
	else 
		{
		if(!(avar_ind_stat&0x100007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
     	else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
		} 
	}
else	if(AUSW_MAIN==22033)
	{
	#ifndef UKU2071x 
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO3->FIOSET,1,25,1);
		else SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO3->FIOSET,1,25,1);
	else SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
	#endif
	#ifdef UKU2071x 
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
		else SET_REG(LPC_GPIO3->FIOSET,1,25,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO3->FIOCLR,1,25,1);
	else SET_REG(LPC_GPIO3->FIOSET,1,25,1);
	#endif
	
	
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,7,1);
	     }
	else 
		{
		if(!(avar_ind_stat&0x100007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,7,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,7,1);
		} 

	//Реле аварий батарей
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,4,1);
     	}
	else 
		{
		if(!(ips_bat_av_stat)) SET_REG(LPC_GPIO0->FIOCLR,1,4,1);
     	else SET_REG(LPC_GPIO0->FIOSET,1,4,1);
		} 
	} 	 
else	
	{
	//Реле аварии сети ТУТ КАКАЯ то ЛАЖА с аварией сети. Обращение к разным портам
	#ifndef UKU2071x 
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
		else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO1->FIOCLR,1,SHIFT_REL_AV_NET,1);
	else SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
	#endif
	#ifdef UKU2071x 
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);
		else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
		}
	else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO1->FIOSET,1,SHIFT_REL_AV_NET,1);
	else SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
	#endif

	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BPS))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
     	}
	else 
		{
		if(!(avar_ind_stat&0x100007f8)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_BPS,1);
     	else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_BPS,1);
		}
	}
//Дополнительное реле УКУ 
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_EXT))	 
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,9,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,9,1);
	}
else if(DOP_RELE_FUNC==0)	//если допреле подключено к ускоренному заряду
	{
	if(!speedChIsOn) SET_REG(LPC_GPIO0->FIOCLR,1,9,1);
	else SET_REG(LPC_GPIO0->FIOSET,1,9,1);
	}
else if(DOP_RELE_FUNC==1)  //если допреле подключено к индиказии разряженной батареи
	{
	if((mess_find_unvol(MESS2RELE_HNDL))&& (mess_data[0]==PARAM_RELE_BAT_IS_DISCHARGED)) SET_REG(LPC_GPIO0->FIOCLR,1,9,1);
	else SET_REG(LPC_GPIO0->FIOSET,1,9,1);
	}	 	
#endif

#ifdef UKU_KONTUR

//Реле общей аварии
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_COMM))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_COMM,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_COMM,1);
	}
else 
	{
     if(  (!(avar_ind_stat&0x00007fff)) &&
          ((!SK_REL_EN[0]) || (sk_av_stat[0]!=sasON))  &&
          ((!SK_REL_EN[1]) || (sk_av_stat[1]!=sasON))  &&
          ((!SK_REL_EN[2]) || (sk_av_stat[2]!=sasON))  /*&&
          ((!SK_REL_EN[3]) || (sk_av_stat[3]!=sasON))*/  )SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_COMM,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_COMM,1);
	}

	
//rel_warm_plazma=0;
//Реле освещения   
/*
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_WARM))
	{
	if(mess_data[1]==0)
		{
		SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=1;
		}
	else if(mess_data[1]==1) 
		{
		SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=2;
		}
     }
else 
	{
	if(warm_stat_k==wsOFF) 
		{
		SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=3;
		}
     else 
		{
		SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_WARM,1);
		rel_warm_plazma=4;
		}
	}
*/
//Реле освещения
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LIGHT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
     }
else 
	{
	if(sk_av_stat[0]!=sasON) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
	}



//Реле выключения нагрузки
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LOAD_OFF))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
     }
else if(tloaddisable_cmnd==0)
	{
	SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
	}
else if((tloaddisable_cmnd)&&(tloaddisable_cmnd<=11))
	{
	SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
	}

else 
	{
	if(!(tloaddisable_stat==tldsON)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LOAD_OFF,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LOAD_OFF,1);
	} 

//Реле осевого вентилятора или отопителя
if(RELE_LOG)
	{
	if((mess_find_unvol(MESS2RELE_HNDL))&&(mess_data[0]==PARAM_RELE_VENT_WARM))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		}
	else 
		{
		if(warm_stat_k==wsOFF) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		} 

	}
else 
	{
	if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT_WARM))
		{
		if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
		else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		}
	else 
		{
		if(vent_stat_k==vsOFF) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT_WARM,1);
	     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT_WARM,1);
		} 
	}
#endif


#ifdef UKU_TELECORE2015
//Реле аварии сети
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
	else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);
	}
else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_AV_NET,1);
else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_AV_NET,1);


//Реле освещения
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LIGHT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
     }
else 
	{
	if(sk_av_stat[0]!=sasON) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
     else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
	}

//Реле отопителя
if((mess_find_unvol(MESS2RELE_HNDL))&&(mess_data[0]==PARAM_RELE_WARM))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_WARM,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_WARM,1);
	}
else 
	{
	if(warm_stat_k==wsOFF) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_WARM,1);
     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_WARM,1);
	} 
//Реле вентилятора
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
	}
else 
	{
	if(vent_stat_k==vsOFF) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VENT,1);
     else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VENT,1);
	} 

//Реле внутреннего вентилятора
if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VVENT))
	{
	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VVENT,1);
	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VVENT,1);
	}
else 
	{
	if(vvent_stat_k==vsOFF) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_VVENT,1);
     else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_VVENT,1);
	} 

#endif

}

//-----------------------------------------------
void bps_hndl(void)
{
char ptr__,i;
unsigned short tempUS;

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
		char ii,iii;

		ii=(char)NUMIST;
		if(ii<0)ii=0;
		if(ii>32)ii=32;
		iii=numOfForvardBps;
		if(iii<0)iii=0;
		if(iii>=NUMIST)iii=0;
		iii+=i;
		iii=iii%ii;
		
  	     if((bps[iii]._state==bsRDY)||(bps[iii]._state==bsWRK))
  	         	{
  	         	bps[iii]._flags_tu=0;
  	         	ptr__++;
  	         	}
  	     }
	if(main_1Hz_cnt<60)
		{
     	for(i=0;i<=NUMIST;i++)
			{
	     	bps[i]._flags_tu=0;
	     	}	
		}
	if(ipsBlckStat)
		{
     	for(i=0;i<=NUMIST;i++)
			{
	     	bps[i]._flags_tu=1;
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

bps[2]._flags_tu=0;
bps[3]._flags_tu=0;


b1Hz_sh=0;


num_of_wrks_bps=0;
tempUS=0;
for(i=0;i<NUMIST;i++)
	{
	if(bps[i]._state==bsWRK)
		{
		num_of_wrks_bps++;
		if(bps[i]._Uii>tempUS)tempUS=bps[i]._Uii;
		}
	}
Ubpsmax=tempUS;

}

//биты аварий в приходящих сообщениях от источников и инверторов
#define AV_OVERLOAD	0
#define AV_T	1
#define AVUMAX	3
#define AVUMIN	4

//-----------------------------------------------
void powerAntiAliasingHndl(void)
{
if((power_summary_tempo/10UL)==(power_summary_tempo_old/10UL))
	{
	if(powerSummaryCnt<15)powerSummaryCnt++;
	if(powerSummaryCnt>=10)
		{
		power_summary=power_summary_tempo;
		}
	}
else powerSummaryCnt=0;
power_summary_tempo_old=power_summary_tempo;

if((power_current_tempo/10UL)==(power_current_tempo_old/10UL))
	{
	if(powerCurrentCnt<15)powerCurrentCnt++;
	if(powerCurrentCnt>=10)
		{
		power_current=power_current_tempo;
		}
	}
else powerCurrentCnt=0;
power_current_tempo_old=power_current_tempo;
}



//-----------------------------------------------
void ipsBlckHndl(char in)
{

ipsBlckStat=0;
if(ipsBlckSrc==1)
	{
	if(((ipsBlckLog==0)&&(adc_buff_[11]>2000)) || ((ipsBlckLog==1)&&(adc_buff_[11]<2000))) ipsBlckStat=1;
	}
else if(ipsBlckSrc==2)
	{
	if(((ipsBlckLog==0)&&(adc_buff_[13]>2000)) || ((ipsBlckLog==1)&&(adc_buff_[13]<2000))) ipsBlckStat=1;
	}
}

//-----------------------------------------------
void bps_drv(char in)
{
char temp;

if (bps[in]._device!=dSRC) return;
temp=bps[in]._flags_tm;
if(temp&(1<<AV_T))
	{
	if(bps[in]._temp_av_cnt<1200) 
		{
		bps[in]._temp_av_cnt++;
		if(bps[in]._temp_av_cnt>=1200)
			{
			bps[in]._temp_av_cnt=1200;
		   	if(!(bps[in]._av&(1<<0)))avar_bps_hndl(in,0,1);
			}
		}
	}

else if(!(temp&(1<<AV_T)))
	{
	if(bps[in]._temp_av_cnt) 
		{
		bps[in]._temp_av_cnt--;
		if(!bps[in]._temp_av_cnt)
			{
			if(bps[in]._av&(1<<0))avar_bps_hndl(in,0,0);
			}
		} 	

	}

if((temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt<10) 
		{
		bps[in]._umax_av_cnt++;
		if(bps[in]._umax_av_cnt>=10)
			{ 
			bps[in]._umax_av_cnt=10;
			if(!(bps[in]._av&(1<<1)))avar_bps_hndl(in,1,1);
		  	/*if((K[APV]!=ON)||((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afOFF)))avar_s_hndl(in,1,1);
			if((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afON))
				{
				apv_cnt[in,0]=APV_INIT;
				apv_cnt[in,1]=APV_INIT;
				apv_cnt[in,2]=APV_INIT;
				apv_flags[in]=afOFF;
				}				*/
						
			}
		} 
	}		
else if(!(temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt>0) 
		{
		bps[in]._umax_av_cnt--;
		if(bps[in]._umax_av_cnt==0)
			{
			bps[in]._umax_av_cnt=0;
			avar_bps_hndl(in,1,0);
	 //		apv_cnt[in,0]=0;
	//		apv_cnt[in,1]=0;
	 //		apv_cnt[in,2]=0;			
			}
		}
	else if(bps[in]._umax_av_cnt<0) bps[in]._umax_av_cnt=0;		 
	}

if(temp&(1<<AVUMIN))
	{
	if(bps[in]._umin_av_cnt<10) 
		{
		bps[in]._umin_av_cnt++;
		if(bps[in]._umin_av_cnt>=10)
			{ 
			bps[in]._umin_av_cnt=10;
			if(!(bps[in]._av&(1<<2)))avar_bps_hndl(in,2,1);
		  	/*	if((K[APV]!=ON)||((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afOFF)))avar_s_hndl(in,2,1);
			if((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afON))
				{
				apv_cnt[in,0]=APV_INIT;
				apv_cnt[in,1]=APV_INIT;
				apv_cnt[in,2]=APV_INIT;
				apv_flags[in]=afOFF;
				}*/				
			}
		} 
	}	
	
else if(!(temp&(1<<AVUMIN)))
	{
	if(bps[in]._umin_av_cnt) 
		{
		bps[in]._umin_av_cnt--;
		if(bps[in]._umin_av_cnt==0)
			{
			bps[in]._umin_av_cnt=0;
			avar_bps_hndl(in,2,0);
		//	apv_cnt[in,0]=0;
		//	apv_cnt[in,1]=0;
		//	apv_cnt[in,2]=0;
			}
		}
	else if(bps[in]._umin_av_cnt>10)bps[in]._umin_av_cnt--;	 
	}

//bps[in]._state=bsOFF;

if (bps[in]._av&0x0f)					bps[in]._state=bsAV;
else if ( (net_av) && (bps[in]._cnt>20)/*&& 
		(bps[in]._Uii<200)*/)				bps[in]._state=bsOFF_AV_NET;
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
bps[in]._vol_i=1000; 
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

#ifdef UKU_TELECORE2015
//-----------------------------------------------
void lakb_hndl(void)
{
/*
char i;
char temp;

//if()
temp=0;
for(i=0;i<3;i++)
	{
	if(i>=NUMBAT_TELECORE)lakb[i]._communicationFullErrorStat=0;
	else
		{
		if(lakbKanErrorStat)					lakb[i]._communicationFullErrorStat=1;
		if(lakb[i]._communication2lvlErrorStat)	lakb[i]._communicationFullErrorStat=2;
		else
			{
			 									lakb[i]._communicationFullErrorStat=0;
			temp++;
			}
		}
	}
lakbNotErrorNum=temp;





for(i=0;i<3;i++)
	{
	if((NUMBAT_TELECORE>i)&&(lakb[i]._communicationFullErrorStat==0))
		{
		signed short tempSS;
		tempSS=lakb[i]._s_o_c;
		tempSS*=100;
		tempSS/=lakb[i]._s_o_h;
		gran(&tempSS,0,100);
		lakb[i]._zar_percent=tempSS;
		}
	else 
		{
		lakb[i]._zar_percent=0;
		}
	}


for(i=0;i<3;i++)
	{
	if((i>NUMBAT_TELECORE)||(lakb[i]._communicationFullErrorStat))
		{
		lakb[i]._ch_curr=0;	  
		lakb[i]._tot_bat_volt=0;
		lakb[i]._max_cell_temp=0;
		lakb[i]._s_o_c=0;
		lakb[i]._s_o_h=0;
		}
	}*/
}

//-----------------------------------------------
void klimat_hndl_telecore2015(void)
{
char i;
char t_bps=20;
//t_box=25; 

if(TELECORE2015_KLIMAT_WARM_SIGNAL==0)
	{
	t_box_warm=t_ext[1];
	if(ND_EXT[1])t_box_warm=20;
	}
else if(TELECORE2015_KLIMAT_WARM_SIGNAL==1) 
	{
	t_box_warm=t_ext[0];
	if(ND_EXT[0])t_box_warm=20;
	}

if(TELECORE2015_KLIMAT_VENT_SIGNAL==0)
	{
	t_box_vent=t_ext[1];
	if(ND_EXT[1])t_box_vent=20;
	}
else if(TELECORE2015_KLIMAT_VENT_SIGNAL==1) 
	{
	t_box_vent=t_ext[0];
	if(ND_EXT[0])t_box_vent=20;
	}

TELECORE2015_KLIMAT_WARM_ON_temp=TELECORE2015_KLIMAT_WARM_ON;
if(
	(lakb_stat_comm_error)		//хотя бы у одной из литиевых батарей есть проблемы со связью 
	|| ((NUMBAT_IP55>0)&&(lakb[0]._zar_percent<TELECORE2015_KLIMAT_CAP)) //есть 1 батарея и ее заряд снизился ниже установленного порога
	|| ((NUMBAT_IP55>1)&&(lakb[1]._zar_percent<TELECORE2015_KLIMAT_CAP)) //есть 2-я батарея .....
	|| ((NUMBAT_IP55>2)&&(lakb[2]._zar_percent<TELECORE2015_KLIMAT_CAP)) //есть 3-я батарея	.....
  )	TELECORE2015_KLIMAT_WARM_ON_temp=10;

if(t_box_warm<TELECORE2015_KLIMAT_WARM_ON_temp) t_box_warm_on_cnt++;
else if(t_box_warm>TELECORE2015_KLIMAT_WARM_OFF) t_box_warm_on_cnt--;
gran(&t_box_warm_on_cnt,0,10);

if(t_box_warm_on_cnt>9) warm_stat_k=wsON;
else if(t_box_warm_on_cnt<1) warm_stat_k=wsOFF;


if(t_box_vent>TELECORE2015_KLIMAT_VENT_ON) t_box_vent_on_cnt++;
else if(t_box_vent<TELECORE2015_KLIMAT_VENT_OFF) t_box_vent_on_cnt--;
gran(&t_box_vent_on_cnt,0,10);

if(t_box_vent_on_cnt>9) vent_stat_k=vsON;
else if(t_box_vent_on_cnt<1) vent_stat_k=vsOFF;

for(i=0;i<NUMIST;i++)
	{
	if((bps[i]._Ti>t_bps)&&(bps[i]._cnt<10))t_bps=bps[i]._Ti;
	}

if(t_bps>TELECORE2015_KLIMAT_VVENT_ON) t_box_vvent_on_cnt++;
else if(t_bps<TELECORE2015_KLIMAT_VVENT_OFF) t_box_vvent_on_cnt--;
gran(&t_box_vvent_on_cnt,0,10);

if(t_box_vvent_on_cnt>9) vvent_stat_k=vsON;
else if(t_box_vvent_on_cnt<1) vvent_stat_k=vsOFF;

}
#endif


#ifndef UKU_KONTUR
//-----------------------------------------------
void klimat_hndl(void)
{


if(t_box>TBOXMAX)
	{
	av_tbox_cnt++;
	} 
else if(t_box<TBOXMAX)
	{
	av_tbox_cnt--;
	}
gran(&av_tbox_cnt,0,6);

if(av_tbox_cnt>5)
	{
	av_tbox_stat=atsON;
	}
if(av_tbox_cnt<1)
	{
	av_tbox_stat=atsOFF;
	}

if(t_box<(TBOXREG-2))
	{
	if(t_box_cnt<30)
		{
		t_box_cnt++;
		if(t_box_cnt>=30)
			{
			main_vent_pos--;
			t_box_cnt=0;
			}
		}
	}
else if(t_box>(TBOXREG))
	{
	if(t_box_cnt<30)
		{
		t_box_cnt++;
		if(t_box_cnt>=30)
			{
			main_vent_pos++;
			t_box_cnt=0;
			}
		}
	}
else
	{
	t_box_cnt=0;
	}

#ifndef UKU_KONTUR
if(t_box>TBOXVENTMAX)gran(&main_vent_pos,0,20); 
else gran(&main_vent_pos,0,pos_vent+9);

if((mess_find_unvol(MESS2VENT_HNDL))&&(mess_data[0]==PARAM_VENT_CB))
	{
	main_vent_pos=mess_data[1];
	}


if(main_vent_pos<=1)mixer_vent_stat=mvsON;
else mixer_vent_stat=mvsOFF;
#endif

#ifdef UKU_KONTUR

if(t_box>TBOXVENTON) t_box_vent_on_cnt++;
else if(t_box<TBOXVENTOFF) t_box_vent_on_cnt--;
gran(&t_box_vent_on_cnt,0,10);

if(t_box_vent_on_cnt>9) vent_stat_k=vsON;
else if(t_box_vent_on_cnt<1) vent_stat_k=vsOFF;

if(t_box<TBOXWARMON) t_box_warm_on_cnt++;
else if(t_box>TBOXWARMOFF) t_box_warm_on_cnt--;
gran(&t_box_warm_on_cnt,0,10);

if(t_box_warm_on_cnt>9) warm_stat_k=wsON;
else if(t_box_warm_on_cnt<1) warm_stat_k=wsOFF;

#endif

if((TBATDISABLE>=50) && (TBATDISABLE<=90))
	{
	if(t_box>TBATDISABLE)
		{
		tbatdisable_cnt++;
		}
	if(t_box<TBATENABLE)
		{
		tbatdisable_cnt--;
		}
	gran(&tbatdisable_cnt,0,6);

	if(tbatdisable_cnt>5)
		{
		tbatdisable_stat=tbdsOFF;
		}
	if(tbatdisable_cnt<1)
		{
		tbatdisable_stat=tbdsON;
		}
	}
else 
	{
	tbatdisable_stat=tbdsON;
	}

if((TLOADDISABLE>=50) && (TLOADDISABLE<=80))
	{
	if(t_box>TLOADDISABLE)
		{
		tloaddisable_cnt++;
		}
	if(t_box<TLOADENABLE)
		{
		tloaddisable_cnt--;
		}
	gran(&tloaddisable_cnt,0,6);

	if(tloaddisable_cnt>5)
		{
		tloaddisable_stat=tldsOFF;
		}
	if(tloaddisable_cnt<1)
		{
		tloaddisable_stat=tldsON;
		}
	}
else 
	{
	tloaddisable_stat=tldsON;
	}

}
#endif

#ifdef UKU_KONTUR
//-----------------------------------------------
void klimat_hndl(void)
{


if(t_box>TBOXMAX)
	{
	av_tbox_cnt++;
	} 
else if(t_box<TBOXMAX)
	{
	av_tbox_cnt--;
	}
gran(&av_tbox_cnt,0,6);

if(av_tbox_cnt>5)
	{
	av_tbox_stat=atsON;
	}
if(av_tbox_cnt<1)
	{
	av_tbox_stat=atsOFF;
	}

if(t_box<(TBOXREG-2))
	{
	if(t_box_cnt<30)
		{
		t_box_cnt++;
		if(t_box_cnt>=30)
			{
			main_vent_pos--;
			t_box_cnt=0;
			}
		}
	}
else if(t_box>(TBOXREG))
	{
	if(t_box_cnt<30)
		{
		t_box_cnt++;
		if(t_box_cnt>=30)
			{
			main_vent_pos++;
			t_box_cnt=0;
			}
		}
	}
else
	{
	t_box_cnt=0;
	}


if(t_box>TBOXVENTMAX)gran(&main_vent_pos,0,20); 
else gran(&main_vent_pos,0,pos_vent+9);

if((mess_find_unvol(MESS2VENT_HNDL))&&(mess_data[0]==PARAM_VENT_CB))
	{
	main_vent_pos=mess_data[1];
	}


if(main_vent_pos<=1)vent_stat_k=vsON;
else vent_stat_k=vsOFF;


if(t_box<TBOXWARMON) t_box_warm_on_cnt++;
else if(t_box>TBOXWARMOFF) t_box_warm_on_cnt--;
gran(&t_box_warm_on_cnt,0,10);

if(t_box_warm_on_cnt>9) warm_stat_k=wsON;
else if(t_box_warm_on_cnt<1) warm_stat_k=wsOFF;



if((TBATDISABLE>=50) && (TBATDISABLE<=90))
	{


	if(t_box>TBATDISABLE)
		{
		tbatdisable_cnt++;
		}
	if(t_box<TBATENABLE)
		{
		tbatdisable_cnt--;
		}
	gran(&tbatdisable_cnt,0,6);

	if(tbatdisable_cnt>5)
		{
		tbatdisable_stat=tbdsOFF;
		}
	if(tbatdisable_cnt<1)
		{
		tbatdisable_stat=tbdsON;
		}
	}
else 
	{
	tbatdisable_stat=tbdsON;
	}

if((TLOADDISABLE>=50) && (TLOADDISABLE<=80))
	{
	if(t_box>TLOADDISABLE)
		{
		tloaddisable_cnt++;
		}
	if(t_box<TLOADENABLE)
		{
		tloaddisable_cnt--;
		}
	gran(&tloaddisable_cnt,0,6);

	if(tloaddisable_cnt>5)
		{
		tloaddisable_stat=tldsOFF;
		}
	if(tloaddisable_cnt<1)
		{
		tloaddisable_stat=tldsON;
		}
	}
else 
	{
	tloaddisable_stat=tldsON;
	}

}
#endif

//-----------------------------------------------
void bat_drv(char in)
{
unsigned short /*tempUS,*/tempUS_;
unsigned long tempUL,tempUL_;
unsigned short b_zar;
//static unsigned short time_cnt[2];



if(cntrl_stat_blok_cnt_plus[in])cntrl_stat_blok_cnt_plus[in]--;
if(cntrl_stat_blok_cnt_minus[in])cntrl_stat_blok_cnt_minus[in]--;


if(bat[in]._Ib>IZMAX) cntrl_stat_blok_cnt_plus[in]=100;
if(bat[in]._Ib<0)     cntrl_stat_blok_cnt_minus[in]=100;

if(cntrl_stat_blok_cnt_plus[in] && cntrl_stat_blok_cnt_minus[in])
     {
     if(!cntrl_stat_blok_cnt_)
          {
          cntrl_stat_blok_cnt_=600; 
          cntrl_stat_blok_cnt_plus[in]=0;
          cntrl_stat_blok_cnt_minus[in]=0;
          }
     else cntrl_stat_blok_cnt=3000;
     }
cntrl_stat_blok_cnt=0;

if(++(bat[in]._time_cnt)>=10)
	{
	bat[in]._time_cnt=0;
	//bat[in]._zar_cnt++;
	}

if(main_10Hz_cnt==50)
	{
	if(!bat[in]._rel_stat)
		{
		
		if(bat[in]._Ub<80) 
			{
			
			if(!(bat[in]._av&1))
				{
				avar_bat_hndl(in,1);
				//if(in==0)plazma_bat++;
				}
			}				

		}
	}

if(main_10Hz_cnt>200)
	{
	if(abs(bat[in]._Ib)>IKB) 
		{
		if((bat[in]._av&1))avar_bat_hndl(in,0);
		}
	}



if(bat[in]._Ib>(-IKB))
	{
	if(bat[in]._cnt_wrk<10)
		{
		bat[in]._cnt_wrk++;
		if((bat[in]._cnt_wrk>=10)&&(bat[in]._wrk)) 
			{
			bat[in]._wrk=0;
			//beep_init(0x7L,'O');
			//wrk_mem_hndl(0);
			wrk_mem_hndl(in);
			//plazma++;
			}
		}
	else bat[in]._cnt_wrk=10;	
	}	

else if(bat[in]._Ib<(-IKB))
	{
	if(bat[in]._cnt_wrk)
		{
		bat[in]._cnt_wrk--;
		if((bat[in]._cnt_wrk==0)&&(bat[in]._wrk==0)) 
			{
			bat[in]._wrk=1;

				{
				char temp;
				signed short temp_temp;
				temp_temp=bat[in]._u_old[((bat_u_old_cnt+1)&0x07)];
			 
				temp=LPC_RTC->YEAR;
				gran_char((signed char*)&temp,1,99);
				*((char*)(&(bat[in]._wrk_date[0])))=temp;
			
				temp=LPC_RTC->MONTH;
				gran_char((signed char*)&temp,1,12);
				*(((char*)(&(bat[in]._wrk_date[0])))+1)=temp;
			
				temp=LPC_RTC->DOM;
				gran_char((signed char*)&temp,1,31);
				*(((char*)(&(bat[in]._wrk_date[0])))+2)=temp;			
				
				*(((char*)(&(bat[in]._wrk_date[0])))+3)=*((char*)&temp_temp);

				temp=LPC_RTC->HOUR;
				gran_char((signed char*)&temp,0,23);
				*((char*)(&(bat[in]._wrk_date[1])))=temp;
               	
				temp=LPC_RTC->MIN;
				gran_char((signed char*)&temp,0,59);
				*(((char*)(&(bat[in]._wrk_date[1])))+1)=temp;
	          
				temp=LPC_RTC->SEC;
				gran_char((signed char*)&temp,0,59);
				*(((char*)(&(bat[in]._wrk_date[1])))+2)=temp;
			
				*(((char*)(&(bat[in]._wrk_date[1])))+3)=*(((char*)&temp_temp)+1);
				bat[in]._Iintegr=0;		//Счетчик десятков милиамперсекунд
				bat[in]._Iintegr_=0;	//Счетчик сотен милиамперчасов
				}
	
			}

		}
	else bat[in]._cnt_wrk=0;	 
	
	}					

/*
if(Ibat>=(-IKB))
	{
	if(cnt_wrk<10)
		{
		cnt_wrk++;
		if((cnt_wrk>=10)&&(wrk!=wrkOFF)) 
			{
			wrk=wrkOFF;
			//beep_init(0x7L,'O');
			wrk_mem_hndl(ibat_integr);
			}
		}
	else cnt_wrk=10;	
	}	

else if((Ibat<(-IKB))&&(spc_stat!=spc_KE))
	{
	if(cnt_wrk)
		{
		cnt_wrk--;
		if((cnt_wrk==0)&&(wrk!=wrkON)) 
			{
			char temp;
			signed short temp_temp;
			temp_temp=ubat_old[((ubat_old_cnt+1)&0x07)];
			 
			wrk=wrkON;
			
			temp=_year;
			gran_char(&temp,1,99);
			*((char*)(&(wrk_date[0])))=temp;
			
			temp=_month;
			gran_char(&temp,1,12);
			*(((char*)(&(wrk_date[0])))+1)=temp;
			
			temp=_date;
			gran_char(&temp,1,31);
			*(((char*)(&(wrk_date[0])))+2)=temp;			
				
			*(((char*)(&(wrk_date[0])))+3)=*((char*)&temp_temp);

			temp=_hour;
			gran_char(&temp,0,23);
			*((char*)(&(wrk_date[1])))=temp;
               
			temp=_min;
			gran_char(&temp,0,59);
			*(((char*)(&(wrk_date[1])))+1)=temp;
	          
			temp=_sec;
			gran_char(&temp,0,59);
			*(((char*)(&(wrk_date[1])))+2)=temp;
			
			*(((char*)(&(wrk_date[1])))+3)=*(((char*)&temp_temp)+1);

			
			//beep_init(0xFL,'O'); 
			ibat_integr=0;
			ibat_integr_=0;
			}
		}
	else cnt_wrk=0;	 
	
	}
if(wrk==wrkON)
	{
	ibat_integr_+=-Ibat;
	if(ibat_integr_>=SEC_IN_HOUR*10L)
		{
		ibat_integr_-=SEC_IN_HOUR*10L;
		ibat_integr++;
		}
	}

*/


/*if(bat[in]._cnt_to_block)
	{
	bat[in]._cnt_to_block--;
	if(!(bat[in]._cnt_to_block))
		{
		//bat[in]._rel_stat=1;
		}
	}
*/




//unsigned int tempUI,tempUI_;
//unsigned int b_zar; 
//char i;
//Ibat[0]=5000;                     


                            
if(bat[in]._time_cnt==0)
	{
	bat[in]._zar_cnt+=(signed long)bat[in]._Ib;
	
	if(bat[in]._zar_cnt>=AH_CONSTANT)
		{
		if(BAT_C_REAL[in]==0x5555) tempUS_=BAT_C_NOM[in];
		else tempUS_=BAT_C_REAL[in];
		
		//b_zar=lc640_read_int(ADR_EE_BAT_ZAR_CNT[in]);

		if(b_zar<(tempUS_/**10*/))
			{
			bat[in]._zar_cnt-=AH_CONSTANT;

			//lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],b_zar+1);
			}
		else if(b_zar>(tempUS_/**10*/))  
			{
			//lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],tempUS_);
			bat[in]._zar_cnt=AH_CONSTANT;

			}

		}

	else if(bat[in]._zar_cnt<=-AH_CONSTANT)
		{
		if(BAT_C_REAL[in]==0x5555) tempUS_=BAT_C_NOM[in];
		else tempUS_=BAT_C_REAL[in];
		
		//b_zar=lc640_read_int(ADR_EE_BAT_ZAR_CNT[in]);

		if(b_zar>tempUS_)
			{
			//lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],tempUS_);
			b_zar=tempUS_;
			}
		if(b_zar)
			{
			bat[in]._zar_cnt+=AH_CONSTANT;

			//lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],b_zar-1);
			}
		else 
			{
			bat[in]._zar_cnt=-AH_CONSTANT;
			}

		}

			
	//tempUL=(unsigned long)lc640_read_int(ADR_EE_BAT_ZAR_CNT[in]);
	
	if(BAT_C_REAL[in]==0x5555) tempUL_=(unsigned long)BAT_C_NOM[in];
	else tempUL_=(unsigned long)BAT_C_REAL[in];
		           	
	tempUL*=1000L;


	if(tempUL_==0) tempUL=0;
	else tempUL/=tempUL_;

	tempUL/=10L;

	bat[in]._zar=(unsigned short)tempUL;

	if(BAT_TYPE==1)
		{
		bat[in]._zar=lakb[in]._s_o_c;
		}
	
	gran((signed short*)&bat[in]._zar,0,100);
     }


//Подсчет тока разряда батареи      
if(bat[in]._wrk==1)
	{
	if(bat[in]._Iintegr<36000)
		{          
		bat[in]._Iintegr+=abs(bat[in]._Ib);
		if(bat[in]._Iintegr>=36000)
			{
			bat[in]._Iintegr=0;		//Счетчик десятков милиамперсекунд
			bat[in]._Iintegr_++;	//Счетчик сотен милиамперчасов
			}
		}
	else 
		{
		bat[in]._Iintegr=0;
		}	
	} 
	    
//
if((bat[in]._Tb>TBATSIGN)&&(!bat[in]._nd))	
	{
	bat[in]._sign_temper_cnt++;
	}
else 
	{
	bat[in]._sign_temper_cnt--;
	}

gran(&bat[in]._sign_temper_cnt,0,600);
if(bat[in]._sign_temper_cnt>=590)	bat[in]._temper_stat|=(1<<0);
if(bat[in]._sign_temper_cnt<=10)	bat[in]._temper_stat&=~(1<<0);


if((bat[in]._Tb>TBATMAX)&&(!bat[in]._nd))	
	{
	bat[in]._max_temper_cnt++;
	}
else 
	{
	bat[in]._max_temper_cnt--;
	}

gran(&bat[in]._max_temper_cnt,0,600);
if(bat[in]._max_temper_cnt>=590)	bat[in]._temper_stat|=(1<<1);
if(bat[in]._max_temper_cnt<=10)	bat[in]._temper_stat&=~(1<<1);



//Подсчет наработки батареи
if(bat[in]._resurs_cnt<36000)
	{               
	bat[in]._resurs_cnt++;
	if(bat[in]._resurs_cnt>=36000)
		{
		bat[in]._resurs_cnt=0;
		//lc640_write_int(ADR_EE_BAT_RESURS[in],//lc640_read_int(ADR_EE_BAT_RESURS[in])+1);
		}
	}
else bat[in]._resurs_cnt=0;


#ifndef UKU_220_V2
#ifndef UKU_GLONASS
#ifndef UKU_6U
//#ifndef UKU_220
if(UBM_AV)
     {
     signed short temp_SS;
#ifdef UKU_220
temp_SS=bat[in]._Ub/2;
#else
     if(U0B<600)
          {
          temp_SS=bat[in]._Ub/4;
          }
     else temp_SS=bat[in]._Ub/5;
	
	temp_SS+=temp_SS;     
#endif
     temp_SS-=(bat[in]._Ubm);

     temp_SS=abs(temp_SS);

     temp_SS*=10;

     temp_SS/=12;

     bat[in]._dUbm=temp_SS;


     if(	(bat[in]._dUbm>UBM_AV) &&
		(abs(bat[in]._Ib)<(5*IKB)) &&
		(bat[in]._Ub>((short)(((long)USIGN*115)/100))) &&
		(!(bat[in]._av & 2))  )
		{
		bat[in]._cnt_as++;
		if(bat[in]._cnt_as==3000)
			{
			avar_bat_as_hndl(in,1);
			}
		if(bat[in]._cnt_as>=3005) bat[in]._cnt_as=3005;
		}
	else 
		{
		bat[in]._cnt_as=0;
		}
     
     }
#endif 
#endif 
#endif

}







//-----------------------------------------------
void u_necc_hndl(void)
{
signed long temp_L;
signed long temp_SL;
//signed short temp_SS;
signed short t[2];
char i;

//temp_SS=0;


#ifdef UKU_TELECORE2015

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
	b1Hz_unh=0;



		{
		u_necc=U0B;
		
		if(spc_stat==spcVZ)
			{
			u_necc=UVZ;
			}

		gran(&DU_LI_BAT,1,30);


		if(lakbNotErrorNum==0)
			{
			u_necc=U0B;
			}
		else 
			{
			signed short i;
			for(i=(NUMBAT_IP55-1);i>=0;i--)
				{
				/*if(lakb[i]._communicationFullErrorStat==0)*/u_necc=lakb[i]._tot_bat_volt+DU_LI_BAT;
				}
			}

		if(NUMBAT_IP55==0)	u_necc=UB0;

		gran(&u_necc,0,UB0);
		gran(&u_necc,0,UB20);
		gran(&u_necc,0,540);
		}
	}


#endif 

//u_necc=2356;
//#endif//gran(&u_necc,400,UMAX);

temp_L=(signed long) u_necc;
temp_L*=98L;
temp_L/=100L;
u_necc_dn=(signed short)temp_L;

temp_L=(signed long) u_necc;
temp_L*=102L;
temp_L/=100L;
u_necc_up=(signed short)temp_L;


}


//-----------------------------------------------
void num_necc_hndl(void)
{

static short num_necc_block_cnt;
if(num_necc_block_cnt) num_necc_block_cnt--;

Isumm_=Isumm;

if(bat[0]._Ib<0) Isumm_+=(abs(bat[0]._Ib))/10;
if(bat[1]._Ib<0) Isumm_+=(abs(bat[1]._Ib))/10;

num_necc_up=(Isumm_/((signed short)IMAX))+1;
////Isumm_+=(signed short)((IMAX*(10-KIMAX))/10);
////Isumm_+=(signed short)(IMAX-IMIN);

num_necc_down=(Isumm_/((signed short)IMIN))+1;

if(num_necc_up>num_necc)
	{
	num_necc=num_necc_up;
	num_necc_block_cnt=60;
	}
else if(num_necc_down<num_necc)
	{
	if(!num_necc_block_cnt)
		{
		num_necc=num_necc_down;
		num_necc_block_cnt=60;
		}
	}

if(PAR) num_necc=NUMIST;

gran(&num_necc,1,NUMIST);

}

//-----------------------------------------------
void cntrl_hndl_ip55(void)
{

gran(&LI_T4,1,10);



if(ch_cnt0<10)
	{
	ch_cnt0++;
	if(ch_cnt0>=10)
		{
		ch_cnt0=0;
		b1Hz_ch=1;

		if(ch_cnt1<LI_T4)
			{
			ch_cnt1++;
			if(ch_cnt1>=LI_T4)
				{
				ch_cnt1=0;
				b1_30Hz_ch=1;
				}
			}
		else ch_cnt1=0;

		if(ch_cnt2<10)
			{
			ch_cnt2++;
			if(ch_cnt2>=10)
				{
				ch_cnt2=0;
				b1_10Hz_ch=1;
				}
			}
		else ch_cnt2=0;
		}
	}
else ch_cnt0=0;

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

IZMAX_=LI_IZMAX1;

for(i=0;i<NUMBAT_IP55;i++)
	{
	if(lakb[i]._s_o_c_percent>=LI_Q)
		{
		IZMAX_=LI_IZMAX2;
		break;
		}
	}

IZMAX_130=IZMAX_+IZMAX_/10+IZMAX_/5;

IZMAX_70=IZMAX_-IZMAX_/10-IZMAX_/5;

if(b1Hz_ch)
	{
	cntrl_stat_new=cntrl_stat_old;


	LI_UNECC_=LI_UNECC;

	if(lakb[0]._voltage_event_code||lakb[1]._voltage_event_code/*||lakb[0]._balanced_event_code||lakb[1]._balanced_event_code*/)
		{
		if(LI_AVAR_CNT<209)LI_AVAR_CNT++;
		}
	else 
		{
		if(b1_10Hz_ch)
			{
			if(LI_AVAR_CNT)LI_AVAR_CNT--;
			}
		}
	if(LI_AVAR_CNT) LI_UNECC_=LI_UNECC-LI_AVAR_CNT/10;


	
	plazma_cntrl_stat=50;

	if(Ibmax>=IZMAX_130)
		{
		cntrl_stat_new-=10;
		plazma_cntrl_stat=51;
		}
	else if(Ubpsmax<(load_U-20))
		{
		cntrl_stat_new+=LI_K1;
		plazma_cntrl_stat=58;
		}
	else if((Ubpsmax>=(load_U-20))&&(Ibmax==0))
		{
		if(load_U>LI_UNECC_)
			{
			cntrl_stat_new-=LI_K2;
			plazma_cntrl_stat=57;
			}
		else if(load_U<LI_UNECC_)
			{
			cntrl_stat_new+=LI_K2;
			plazma_cntrl_stat=58;
			}
		}
	else if	(Ibmax>=IZMAX_)
		{
		plazma_cntrl_stat=60;
		if(b1_30Hz_ch)
			{
		//	if(load_U>TELECORE2017_ULINECC_)
		//		{
				cntrl_stat_new--;
				plazma_cntrl_stat=52;
		//		}
		//	else if(load_U<TELECORE2017_ULINECC_)
		//		{
		//		cntrl_stat_new++;
		//		plazma_cntrl_stat=53;
		//		}
			}
		}
	else if	(Ibmax>=IZMAX_70)
		{
		plazma_cntrl_stat=61;
		if(b1_30Hz_ch)
			{
			if(load_U>LI_UNECC_)
				{
				cntrl_stat_new--;
				plazma_cntrl_stat=54;
				}
			else if(load_U<LI_UNECC_)
				{
				cntrl_stat_new++;
				plazma_cntrl_stat=55;
				}
			}
		}
	else if((Ibmax)&&(Ibmax<IZMAX_70))
		{
		//cntrl_stat_new+=TELECORE2017_K3;
		if(load_U>LI_UNECC_)
			{
			cntrl_stat_new-=LI_K3;
			plazma_cntrl_stat=71;
			}
		else if(load_U<LI_UNECC_)
			{
			cntrl_stat_new+=LI_K3;
			plazma_cntrl_stat=72;
			}
		}
		
	gran(&cntrl_stat_new,10,1010);			
	cntrl_stat_old=cntrl_stat_new;
	cntrl_stat=cntrl_stat_new;
	}


iiii=0;
for(i=0;i<NUMIST;i++)
     {
     if(bps[i]._cnt<30)iiii=1;
     }

if(iiii==0)
     {
     cntrl_stat=0;	
     cntrl_stat_old=0;
     cntrl_stat_new=0;
	 plazma_cntrl_stat=20;
     }
gran(&cntrl_stat,10,1010); 
b1Hz_ch=0;
b1_30Hz_ch=0;
b1_10Hz_ch=0;
}

#ifndef TELECORE
//-----------------------------------------------
void cntrl_hndl(void)
{

IZMAX_=IZMAX;

if(speedChIsOn)IZMAX_=speedChrgCurr;

if(cntrl_stat_blok_cnt)cntrl_stat_blok_cnt--;
if(cntrl_stat_blok_cnt_)cntrl_stat_blok_cnt_--;

if((bat[0]._temper_stat&0x03)||(bat[1]._temper_stat&0x03))IZMAX_=IZMAX/10;


if(ch_cnt0<10)
	{
	ch_cnt0++;
	if(ch_cnt0>=10)
		{
		ch_cnt0=0;
		b1Hz_ch=1;
		}
	}




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
		#ifdef UKU_220_IPS_TERMOKOMPENSAT
		if(load_U>u_necc)
			{
			if(((bps_U-u_necc)>40)&&(cntrl_stat>0))cntrl_stat-=5;
			else if((cntrl_stat)&&b1Hz_ch)cntrl_stat--;
			}
		else if(bps_U<u_necc)
			{	
			if(((u_necc-bps_U)>40)&&(cntrl_stat<1015))cntrl_stat+=5;
			else	if((cntrl_stat<1020)&&b1Hz_ch)cntrl_stat++;
			}
		#elif defined(UKU_220)
		if(load_U>u_necc)
			{
			if(((load_U-u_necc)>40)&&(cntrl_stat>0))cntrl_stat-=5;
			else if((cntrl_stat)&&b1Hz_ch)cntrl_stat--;
			}
		else if(load_U<u_necc)
			{	
			if(((u_necc-load_U)>40)&&(cntrl_stat<1015))cntrl_stat+=5;
			else	if((cntrl_stat<1020)&&b1Hz_ch)cntrl_stat++;
			}
		#elif defined(UKU_220_V2)
		if(load_U>u_necc)
			{
			if(((load_U-u_necc)>40)&&(cntrl_stat>0))cntrl_stat-=5;
			else if((cntrl_stat)&&b1Hz_ch)cntrl_stat--;
			}
		else if(load_U<u_necc)
			{	
			if(((u_necc-load_U)>40)&&(cntrl_stat<1015))cntrl_stat+=5;
			else	if((cntrl_stat<1020)&&b1Hz_ch)cntrl_stat++;
			}
		#else

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
		#endif	
	 	}
	}

#ifdef UKU_220_IPS_TERMOKOMPENSAT
else if((b1Hz_ch)&&((!bIBAT_SMKLBR)||(bps[8]._cnt>40)))
	{
	cntrl_stat_new=cntrl_stat_old;
	
	if((Ibmax/10)>(2*IZMAX_))
		{
          if(cntrl_stat_blok_cnt)cntrl_stat_new--;
		else	cntrl_stat_new-=10;
		}		
	else if(((Ibmax/10)<(IZMAX_*2))&&(Ibmax>(IZMAX_*15)))
		{
          if(cntrl_stat_blok_cnt)cntrl_stat_new--;
          else	cntrl_stat_new-=3;
		}   
	else if((Ibmax<(IZMAX_*15))&&((Ibmax/10)>IZMAX_))
		{
		cntrl_stat_new--;
		}
		
	else if(bps_U<u_necc)
		{
		if(bps_U<(u_necc-(UB0-UB20)))
			{
			if(Ibmax<0)
				{
                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
				else cntrl_stat_new+=10;
				}
			else if(Ibmax<(IZMAX_*5))
				{
                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
				else	cntrl_stat_new+=2;
				}
			else if(Ibmax<((IZMAX_*95)/10))
				{
				cntrl_stat_new++;
				}					
			}
		else if(bps_U<(u_necc-((UB0-UB20)/4)))
			{
			if(Ibmax<(IZMAX_*5))
				{
                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
				else	cntrl_stat_new+=2;
				}
			else if(Ibmax<((IZMAX_*95)/10))
				{
				cntrl_stat_new++;
				}					
			}	
		else if(bps_U<(u_necc-1))
			{
			if(Ibmax<((IZMAX_*95)/10))
				{
				cntrl_stat_new++;
				}					
			}					
		}	
	else if((bps_U>u_necc)/*&&(!cntrl_blok)*/)
		{
		if(bps_U>(u_necc+(UB0-UB20)))
			{
               if(cntrl_stat_blok_cnt)cntrl_stat_new--;
			else	cntrl_stat_new-=10;
			}
		else if(bps_U>(u_necc+((UB0-UB20)/4)))
			{
               if(cntrl_stat_blok_cnt)cntrl_stat_new--;
			else cntrl_stat_new-=2;
			}	
		else if(bps_U>(u_necc+1))
			{
			cntrl_stat_new--;
			}					
		}

	gran(&cntrl_stat_new,10,1010);			
	cntrl_stat_old=cntrl_stat_new;
	cntrl_stat=cntrl_stat_new;	
	}
#else
else if((b1Hz_ch)&&((!bIBAT_SMKLBR)||(bps[8]._cnt>40)))
	{
	cntrl_stat_new=cntrl_stat_old;
	
	if((Ibmax/10)>(2*IZMAX_))
		{
          if(cntrl_stat_blok_cnt)cntrl_stat_new--;
		else	cntrl_stat_new-=10;
		}		
	else if(((Ibmax/10)<(IZMAX_*2))&&(Ibmax>(IZMAX_*15)))
		{
          if(cntrl_stat_blok_cnt)cntrl_stat_new--;
          else	cntrl_stat_new-=3;
		}   
	else if((Ibmax<(IZMAX_*15))&&((Ibmax/10)>IZMAX_))
		{
		cntrl_stat_new--;
		}
		
	else if(load_U<u_necc)
		{
		if(load_U<(u_necc-(UB0-UB20)))
			{
			if(Ibmax<0)
				{
                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
				else cntrl_stat_new+=10;
				}
			else if(Ibmax<(IZMAX_*5))
				{
                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
				else	cntrl_stat_new+=2;
				}
			else if(Ibmax<((IZMAX_*95)/10))
				{
				cntrl_stat_new++;
				}					
			}
		else if(load_U<(u_necc-((UB0-UB20)/4)))
			{
			if(Ibmax<(IZMAX_*5))
				{
                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
				else	cntrl_stat_new+=2;
				}
			else if(Ibmax<((IZMAX_*95)/10))
				{
				cntrl_stat_new++;
				}					
			}	
		else if(load_U<(u_necc-1))
			{
			if(Ibmax<((IZMAX_*95)/10))
				{
				cntrl_stat_new++;
				}					
			}					
		}	
	else if((load_U>u_necc)/*&&(!cntrl_blok)*/)
		{
		if(load_U>(u_necc+(UB0-UB20)))
			{
               if(cntrl_stat_blok_cnt)cntrl_stat_new--;
			else	cntrl_stat_new-=10;
			}
		else if(load_U>(u_necc+((UB0-UB20)/4)))
			{
               if(cntrl_stat_blok_cnt)cntrl_stat_new--;
			else cntrl_stat_new-=2;
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
#endif

iiii=0;
for(i=0;i<NUMIST;i++)
     {
     if(bps[i]._cnt<30)iiii=1;
     }

if(iiii==0)
     {
     cntrl_stat=600;	
     cntrl_stat_old=600;
     cntrl_stat_new=600;
	#ifdef UKU_TELECORE2015
	//cntrl_stat=0;
	//cntrl_stat_old=0;
	//cntrl_stat_new=0;
	#endif
     }
gran(&cntrl_stat,10,1010); 
b1Hz_ch=0;
}
#endif

#ifdef TELECORE
//-----------------------------------------------
void cntrl_hndl_telecore(void)
{

IZMAX_=IZMAX;

if(speedChIsOn)IZMAX_=speedChrgCurr;

if(cntrl_stat_blok_cnt)cntrl_stat_blok_cnt--;
if(cntrl_stat_blok_cnt_)cntrl_stat_blok_cnt_--;

//if((bat[0]._temper_stat&0x03)||(bat[1]._temper_stat&0x03))IZMAX_=IZMAX/10;


if(ch_cnt0<10)
	{
	ch_cnt0++;
	if(ch_cnt0>=10)
		{
		ch_cnt0=0;
		b1Hz_ch=1;

		if(ch_cnt1<30)
			{
			ch_cnt1++;
			if(ch_cnt1>=30)
				{
				ch_cnt1=0;
				b1_30Hz_ch=1;
				}
			}


		}
	}




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

else if((b1Hz_ch)&&(!bIBAT_SMKLBR))
	{
	cntrl_stat_new=cntrl_stat_old;
	plazma_cntrl_stat=11;
	if((NUMBAT_IP55==0)||(lakbNotErrorNum==0))
		{
		plazma_cntrl_stat=33;
		if(load_U<u_necc)
			{
			if((u_necc-load_U)>10)	cntrl_stat_new+=10;
			else 					cntrl_stat_new++;
			plazma_cntrl_stat=35;
			}
		else if(load_U>u_necc)
			{
			if((load_U>u_necc)>10)	cntrl_stat_new-=10;
			else 					cntrl_stat_new--;
			plazma_cntrl_stat=36;
			}
		}
	else 
		{
		plazma_cntrl_stat=40;
		if(Ibmax==IZMAX_)
			{
									
			}	
		else if(Ibmax>(IZMAX_*2))
			{
	        if(cntrl_stat_blok_cnt)	cntrl_stat_new--;
			else					cntrl_stat_new-=5;
			}
		else if((Ibmax<(IZMAX_*2))&&(Ibmax>IZMAX_))
			{
			if(b1_30Hz_ch)
				{
				b1_30Hz_ch=0;
									cntrl_stat_new--;
				}
			}
		else if((Ibmax>((IZMAX_*4)/5))&&(Ibmax<IZMAX_))
			{				
			if(load_U<u_necc)
				{
				if(b1_30Hz_ch)
					{
					b1_30Hz_ch=0;
									cntrl_stat_new++;
					}
				}
			else
				{
				if(b1_30Hz_ch)
					{
					b1_30Hz_ch=0;
									cntrl_stat_new--;
					}
				}
			}  		
							
		else if((Ibmax<((IZMAX_*4)/5)))
			{
			if(Ubpsmax<(u_necc-DU_LI_BAT))
				{
								   	cntrl_stat_new+=10;
				}				
			else if(load_U<u_necc)
				{
				if(b1_30Hz_ch)
					{
					b1_30Hz_ch=0;
									cntrl_stat_new+=10;
					}
				}
			else
				{
				if(b1_30Hz_ch)
					{
					b1_30Hz_ch=0;
									cntrl_stat_new-=10;
					}
				}
			}  
		//else if() 
		else if(load_U<u_necc)
			{
			if(load_U<(u_necc-DU_LI_BAT-5))
				{
									cntrl_stat_new+=1;
				}
	/*		else if(load_U<(u_necc-20))
				{
									cntrl_stat_new+=2;
				}*/
	/*		else if(load_U>(u_necc))
				{
				if(b1_30Hz_ch)
					{
					b1_30Hz_ch=0;
					if(Ibmax<(IZMAX_-5))cntrl_stat_new+=5;
					else				cntrl_stat_new++;
					}
				}*/				
			else 
				{
									cntrl_stat_new++;
				}					
			}	
		else if(load_U>u_necc)
			{
									cntrl_stat_new--;
			}
	
	
		}
	gran(&cntrl_stat_new,10,1010);			
	cntrl_stat_old=cntrl_stat_new;
	cntrl_stat=cntrl_stat_new;
	}


iiii=0;
for(i=0;i<NUMIST;i++)
     {
     if(bps[i]._cnt<30)iiii=1;
     }

if(iiii==0)
     {
     cntrl_stat=600;	
     cntrl_stat_old=600;
     cntrl_stat_new=600;
	#ifdef UKU_TELECORE2015
	//cntrl_stat=0;
	//cntrl_stat_old=0;
	//cntrl_stat_new=0;
	#endif
     }
gran(&cntrl_stat,10,1010); 
b1Hz_ch=0;


//cntrl_stat=800;
}
#endif

//-----------------------------------------------
void ext_drv(void)
{
char i;


for(i=0;i<NUMSK;i++)
	{
	#ifdef UKU_MGTS
	if(adc_buff_[sk_buff_RSTKM[i]]<2000)
	#endif
	#ifdef UKU_RSTKM
	if(adc_buff_[sk_buff_RSTKM[i]]<2000)
	#endif
	#ifdef UKU_3U
	if(adc_buff_[sk_buff_3U[i]]<2000)
	#endif
	#ifdef UKU_GLONASS
	if(adc_buff_[sk_buff_GLONASS[i]]<2000)
	#endif
	#ifdef UKU_KONTUR
	if(adc_buff_[sk_buff_KONTUR[i]]<2000)
	#endif
	#ifdef UKU_6U
	if(adc_buff_[sk_buff_6U[i]]<2000)
	#endif
	#ifdef UKU_220
	if(adc_buff_[sk_buff_220[i]]<2000)
	#endif
	#ifdef UKU_220_V2
	if(adc_buff_[sk_buff_220[i]]<2000)
	#endif
	#ifdef UKU_220_IPS_TERMOKOMPENSAT
	if(adc_buff_[sk_buff_220[i]]<2000)
	#endif
	#ifdef UKU_TELECORE2015
	if(adc_buff_[sk_buff_TELECORE2015[i]]<2000)	 //TODO
	#endif

		{
		if(sk_cnt[i]<10)
			{
			sk_cnt[i]++;
			if(sk_cnt[i]>=10)
				{
				sk_stat[i]=ssON;
				}
			}
		else 
			{
			sk_cnt[i]=10;
			}
               
		}
	else
		{
		if(sk_cnt[i]>0)
			{
			sk_cnt[i]--;
			if(sk_cnt[i]<=0)
				{
				sk_stat[i]=ssOFF;
				}
			}
		else 
			{
			sk_cnt[i]=0;
			}
		}
	}

for(i=0;i<NUMSK;i++)
	{
	if(((SK_SIGN[i]==0)&&(sk_stat[i]==ssON))||((SK_SIGN[i])&&(sk_stat[i]==ssOFF)) )
		{
		if(sk_av_cnt[i]<10)
			{
			sk_av_cnt[i]++;
			if(sk_av_cnt[i]>=10)
				{
				sk_av_stat[i]=sasON;
				}
			}
		else 
			{
			sk_av_cnt[i]=10;
			}
		}
	else
		{
		if(sk_av_cnt[i]>=0)
			{
			sk_av_cnt[i]--;
			if(sk_av_cnt[i]<=0)
				{
				sk_av_stat[i]=sasOFF;
				}
			}
		else 
			{
			sk_av_cnt[i]=0;
			}
		}




	sk_av_stat_old[i]=sk_av_stat[i];
	}
}


//-----------------------------------------------
void zar_superviser_drv(void)
{

if(((bat[0]._Ub>u_necc_up) || (bat[0]._Ub<u_necc_dn))&&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_U[0]=0;

if(((bat[0]._Ib>(2*IKB)) || (bat[0]._Ib<(-IKB*2))) &&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_I[0]=0;
																 
if((main_kb_cnt==((TBAT*60)-10)) &&(spc_stat==spcOFF))
	{
	//if((sign_U[0]==1) && (sign_I[0]==1) && (lc640_read_int(EE_BAT1_ZAR_CNT)!=BAT_C_REAL[0]) && (NUMBAT) && (!(bat[0]._av&1)))
		{
		//lc640_write_int(EE_BAT1_ZAR_CNT,BAT_C_REAL[0]);
		superviser_cnt++;
		}
	
	}

if(((bat[0]._Ub>u_necc_up) || (bat[1]._Ub<u_necc_dn))&&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_U[1]=0;

if(((bat[1]._Ib>(2*IKB)) || (bat[1]._Ib<(-IKB*2))) &&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_I[1]=0;
																 
if((main_kb_cnt==((TBAT*60)-10)) &&(spc_stat==spcOFF))
	{
	//if((sign_U[1]==1) && (sign_I[1]==1) && (lc640_read_int(EE_BAT2_ZAR_CNT)!=BAT_C_REAL[1]) && (NUMBAT==2) && (!(bat[1]._av&1)))
		{
		//lc640_write_int(EE_BAT2_ZAR_CNT,BAT_C_REAL[1]);
		superviser_cnt++;
		}
	
	}

if(main_kb_cnt==((TBAT*60)-2)) zar_superviser_start();
}

//-----------------------------------------------
void zar_superviser_start(void)
{
sign_U[0]=1;
sign_I[0]=1;
sign_U[1]=1;
sign_I[1]=1;

}

//-----------------------------------------------
void npn_hndl(void)
{
if(NPN_OUT!=npnoOFF)
	{
/*	if(NPN_SIGN==npnsAVNET)
		{
		if(net_av==1)
			{
			if(npn_tz_cnt<TZNPN)
				{
				npn_tz_cnt++;
				if(npn_tz_cnt==TZNPN)
					{
					npn_stat=npnsOFF;
					}
				}
			}
		else
			{
			if(npn_tz_cnt)
				{
				npn_tz_cnt--;
				if(npn_tz_cnt==0)
					{
					npn_stat=npnsON;
					}
				}
			}
		}*/
/*	if(NPN_SIGN==npnsULOAD)
		{
		if(load_U<UONPN)
			{
			if(npn_tz_cnt<TZNPN)
				{
				npn_tz_cnt++;
				if(npn_tz_cnt==TZNPN)
					{
					npn_stat=npnsOFF;
					}
				}
			}
		else if(load_U>UVNPN)
			{
			if(npn_tz_cnt)
				{
				npn_tz_cnt--;
				if(npn_tz_cnt==0)
					{
					npn_stat=npnsON;
					}
				}
			}
		}*/

	if((load_U<UONPN)&&((net_Ua<UMN)||(net_Ub<UMN)||(net_Uc<UMN)))
		{
		if(npn_tz_cnt<TZNPN)
			{
			npn_tz_cnt++;
			if(npn_tz_cnt==TZNPN)
				{
				npn_stat=npnsOFF;
				}
			}
		}
	else if((load_U>UVNPN)&&(net_Ua>UMN)&&(net_Ub>UMN)&&(net_Uc>UMN))
		{
		if(npn_tz_cnt)
			{
			npn_tz_cnt--;
			if(npn_tz_cnt==0)
				{
				npn_stat=npnsON;
				}
			}
		}
	}
else
	{
	npn_tz_cnt=0;
	npn_stat=npnsON;
	}

if(npn_stat==npnsOFF) mess_send(MESS2RELE_HNDL,PARAM_RELE_NPN,1,15);


}

//-----------------------------------------------
void speedChargeHndl(void)
{
if(speedChIsOn)
	{
	speedChTimeCnt++;
	if(speedChTimeCnt>=((signed long)speedChrgTimeInHour*3600L))
		{
		speedChIsOn=0;
		}
	if(speedChrgBlckStat)
		{
		speedChIsOn=0;
		speedChTimeCnt=0;
		}
	}



if(speedChrgAvtEn)
	{
	if(!speedChIsOn)
		{
		if((load_U<u_necc)&&((u_necc-load_U)>speedChrgDU)&&(abs(Ib_ips_termokompensat/10-IZMAX)<5)&&(!speedChrgBlckStat))
			{
			speedChIsOn=1;
			}
		}
	}



if((speedChrgBlckSrc!=1)&&(speedChrgBlckSrc!=2)) speedChrgBlckStat=0;
else
	{
	speedChrgBlckStat=0;
	if(speedChrgBlckSrc==1)
		{
		if(((speedChrgBlckLog==0)&&(adc_buff_[11]>2000)) || ((speedChrgBlckLog==1)&&(adc_buff_[11]<2000))) speedChrgBlckStat=1;
		}
	else if(speedChrgBlckSrc==2)
		{
		if(((speedChrgBlckLog==0)&&(adc_buff_[13]>2000)) || ((speedChrgBlckLog==1)&&(adc_buff_[13]<2000))) speedChrgBlckStat=1;
		}
	}


if(speedChrgBlckStat==1)
	{

	//speedChargeStartStop();

	speedChrgShowCnt++;
	if(speedChrgShowCnt>=30)	
		{
		speedChrgShowCnt=0;
		show_mess(	"     УСКОРЕННЫЙ     ",
					"       ЗАРЯД        ",
					"     ЗАПРЕЩЕН!!!    ",
					"                    ",
					5000);
		}
	}
else speedChrgShowCnt=0;


}

//-----------------------------------------------
void speedChargeStartStop(void)
{
if(speedChIsOn)
	{
	speedChIsOn=0;
	}

else
	{
	if(speedChrgBlckStat==0)
		{
		speedChIsOn=1;
		speedChTimeCnt=0;
		}
	else
		{
		show_mess(	"     Ускоренный     ",
	          		"       заряд        ",
	          		"    заблокирован!   ",
	          		"                    ",2000);	 
		}
	}
}

//-----------------------------------------------
void	numOfForvardBps_hndl(void)			//Программа смены первого источника для равномерного износа БПСов
{
numOfForvardBps=0;

//FORVARDBPSCHHOUR=10;

if((FORVARDBPSCHHOUR<=0)||(FORVARDBPSCHHOUR>500))
	{
	FORVARDBPSCHHOUR=0;
	return;
	}

numOfForvardBps_minCnt++;


if(numOfForvardBps_minCnt>=60)
	{
	numOfForvardBps_minCnt=0;
	numOfForvardBps_hourCnt=//lc640_read_int(EE_FORVBPSHOURCNT);
	numOfForvardBps_hourCnt++;
	if(numOfForvardBps_hourCnt>=(FORVARDBPSCHHOUR*NUMIST))
		{
		numOfForvardBps_hourCnt=0;
		}
	//lc640_write_int(EE_FORVBPSHOURCNT,numOfForvardBps_hourCnt);
	}

numOfForvardBps=numOfForvardBps_hourCnt/FORVARDBPSCHHOUR; 
}

//-----------------------------------------------
void	numOfForvardBps_init(void)			//Программа сброса системы смены первого источника для равномерного износа БПСов
{									//Должна вызываться при изменении кол-ва источников в структуре
//lc640_write_int(EE_FORVBPSHOURCNT,0);
numOfForvardBps_minCnt=0;
}

//-----------------------------------------------
void outVoltContrHndl(void)
{ 
if((load_U>U_OUT_KONTR_MAX)||(load_U<U_OUT_KONTR_MIN))
	{
	outVoltContrHndlCnt_=0;
	if(outVoltContrHndlCnt<U_OUT_KONTR_DELAY)
		{
		outVoltContrHndlCnt++;
		if(outVoltContrHndlCnt==U_OUT_KONTR_DELAY)
			{
			avar_uout_hndl(1);
			}
		}
	}
else
	{
	if(outVoltContrHndlCnt)
		{
		if(outVoltContrHndlCnt_<5)
			{
			outVoltContrHndlCnt_++;
			if(outVoltContrHndlCnt_>=5)
				{
				outVoltContrHndlCnt=0;
				if(uout_av)avar_uout_hndl(0);
				}
			}
		}
	}

if (load_U<(USIGN*10)) 
	{
	if(!bSILENT)
		{
		mess_send(MESS2RELE_HNDL,PARAM_RELE_BAT_IS_DISCHARGED,1,20);
		}

	//bU_BAT2REL_AV_BAT=1;
	}


}

//-----------------------------------------------
void vent_hndl(void)
{
if(RELEVENTSIGN==rvsAKB)
	{
	if(vent_stat==0)
		{
		if	(
			(BAT_IS_ON[0]==bisON)&&((bat[0]._Tb>TVENTON)||(bat[0]._nd))
			||
			(BAT_IS_ON[1]==bisON)&&((bat[1]._Tb>TVENTON)||(bat[1]._nd))
			)
			{
			vent_stat=1;
			}
		}
	else if(vent_stat==1)
		{
		if	(
			((BAT_IS_ON[0]!=bisON)||((BAT_IS_ON[0]==bisON)&&(bat[0]._Tb<TVENTOFF)&&(!bat[0]._nd)))
			&&
			((BAT_IS_ON[1]!=bisON)||((BAT_IS_ON[1]==bisON)&&(bat[1]._Tb<TVENTOFF)&&(!bat[1]._nd)))
			)
			{
			vent_stat=0;
			}
		}
	}
else if(RELEVENTSIGN==rvsBPS)
	{
/*	if	(
		(((bps[0]._flags_tm&0x06)||(bps[0]._cnt>=30)))||
		(((bps[1]._flags_tm&0x06)||(bps[1]._cnt>=30))&&(NUMIST>1))||
		(((bps[2]._flags_tm&0x06)||(bps[2]._cnt>=30))&&(NUMIST>2))||
		(((bps[3]._flags_tm&0x06)||(bps[3]._cnt>=30))&&(NUMIST>3))||
		(((bps[4]._flags_tm&0x06)||(bps[4]._cnt>=30))&&(NUMIST>4))||
		(((bps[5]._flags_tm&0x06)||(bps[5]._cnt>=30))&&(NUMIST>5))||
		(((bps[6]._flags_tm&0x06)||(bps[6]._cnt>=30))&&(NUMIST>6))
		)
		{
		vent_stat=1;
		}
	else vent_stat=0;
	*/

	if	(
		((NUMIST)&&((bps[0]._Ti>TVENTON)||(bps[0]._cnt>=30)))
		||
		((NUMIST>1)&&((bps[1]._Ti>TVENTON)||(bps[1]._cnt>=30)))
		||
		((NUMIST>2)&&((bps[2]._Ti>TVENTON)||(bps[2]._cnt>=30)))
		||
		((NUMIST>3)&&((bps[3]._Ti>TVENTON)||(bps[3]._cnt>=30)))
		||
		((NUMIST>4)&&((bps[4]._Ti>TVENTON)||(bps[4]._cnt>=30)))
		||
		((NUMIST>5)&&((bps[5]._Ti>TVENTON)||(bps[5]._cnt>=30)))
		||
		((NUMIST>6)&&((bps[6]._Ti>TVENTON)||(bps[6]._cnt>=30)))
		||
		((NUMIST>7)&&((bps[7]._Ti>TVENTON)||(bps[7]._cnt>=30)))
		)
		{
		vent_stat=1;
		}
	else if(vent_stat==1)
		{
		if	(
			((!NUMIST)||((NUMIST)&&(bps[0]._Ti<TVENTOFF)&&(bps[0]._cnt<10)))
			&&
			((NUMIST<2)||((NUMIST>=2)&&(bps[1]._Ti<TVENTOFF)&&(bps[1]._cnt<10)))
			&&
			((NUMIST<3)||((NUMIST>=3)&&(bps[2]._Ti<TVENTOFF)&&(bps[2]._cnt<10)))
			&&
			((NUMIST<4)||((NUMIST>=4)&&(bps[3]._Ti<TVENTOFF)&&(bps[3]._cnt<10)))
			&&
			((NUMIST<5)||((NUMIST>=5)&&(bps[4]._Ti<TVENTOFF)&&(bps[4]._cnt<10)))
			&&
			((NUMIST<6)||((NUMIST>=6)&&(bps[5]._Ti<TVENTOFF)&&(bps[5]._cnt<10)))
			&&
			((NUMIST<7)||((NUMIST>=7)&&(bps[6]._Ti<TVENTOFF)&&(bps[6]._cnt<10)))
			&&
			((NUMIST<8)||((NUMIST>=8)&&(bps[7]._Ti<TVENTOFF)&&(bps[7]._cnt<10)))
			)
			{
			vent_stat=0;
			}
		}
	}
else if(RELEVENTSIGN==rvsEXT)
	{
	if	(
		((NUMDT)&&((t_ext[0]>TVENTON)||(ND_EXT[0])))
		||
		((NUMDT>1)&&((t_ext[1]>TVENTON)||(ND_EXT[1])))
		||
		((NUMDT>2)&&((t_ext[2]>TVENTON)||(ND_EXT[2])))
		)
		{
		vent_stat=1;
		}
	else if(vent_stat==1)
		{
		if	(
			((!NUMDT)||((NUMDT)&&(t_ext[0]<TVENTOFF)&&(!ND_EXT[0])))
			&&
			((NUMDT<2)||((NUMDT>=2)&&(t_ext[1]<TVENTOFF)&&(!ND_EXT[1])))
			&&
			((NUMDT<3)||((NUMDT>=3)&&(t_ext[2]<TVENTOFF)&&(!ND_EXT[2])))
			)
			{
			vent_stat=0;
			}
		}
	}
else vent_stat=1;
}


