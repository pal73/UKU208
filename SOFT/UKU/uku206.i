#line 1 "uku206.c"
#line 1 "global_define.h"














typedef struct
     {
     enum {dSRC=3,dINV=5}_device;
	char _av;
	
	
	
	
     enum {bsAPV,bsWRK,bsRDY,bsBL,bsAV,bsOFF_AV_NET}_state;
     char _cnt;
     char _cnt_old;
     char _cnt_more2;
     char _buff[16]; 
     
     
     
     
     signed _Uii; 
     signed _Uin;
     signed _Ii;
     signed _Ti; 
     char _flags_tu;
     
     
     
     
     
     signed _vol_u;
     signed _vol_i;
     char _is_on_cnt;
     int _ist_blok_host_cnt_; 
     int _ist_blok_host_cnt;
     short _blok_cnt; 
     char _flags_tm;     
     
     signed short _temp_av_cnt;
     signed short _umax_av_cnt;
     signed short _umin_av_cnt;
     signed _rotor;
     signed  short _x_; 
     
     char _adr_ee;
	char _last_avar;
     } BPS_STAT; 



typedef struct
     {
	char 		_cnt_to_block;
	signed short	_Ub;
	signed short	_Ib;
	signed short	_Tb;
	char 		_nd;
	char 		_cnt_wrk;
	char 		_wrk;
	unsigned short _zar;
	char 		_full_ver;
	signed long 	_zar_cnt;
	unsigned short _Iintegr,_Iintegr_; 
	signed short 	_u_old[8];
	signed short	_u_old_cnt;
	unsigned long 	_wrk_date[2];
	char 		_rel_stat;
	char			_av;
	char			_time_cnt;
	char 		_temper_stat;
	
	
	signed short 	_sign_temper_cnt;
	signed short 	_max_temper_cnt;
     } BAT_STAT; 

















#line 138 "global_define.h"







		










#line 181 "global_define.h"


















#line 212 "global_define.h"

#line 226 "global_define.h"





  
#line 238 "global_define.h"





#line 2 "uku206.c"
#line 1 "uku206.h"












typedef struct  
{
enum {iMn,iSrv_sl,iNet,iSet,iBat,iBps,iS2,iSet_prl,iK_prl,iDnd,iK,
	iSpcprl,iSpc,k,Crash_0,Crash_1,iKednd,iAv_view_avt,iAKE,
	iLoad,iSpc_prl_vz,iSpc_prl_ke,iKe,iVz,iAvz,iAVAR,iStr,iVrs,iPrltst,iApv,
	iK_bps,iK_bps_sel,iK_bat,iK_bat_sel,iK_load,iK_net,iTst,iTst_klbr,iTst_BPS1,iTst_BPS2,
	iTst_BPS12,iDebug,iDef,iSet_st_prl,iK_pdp,iSet_T,iDeb,iJ_bat,iK_inv,iK_inv_sel,
	iPrl_bat_in_out,iPdp1,iJAv_sel,iJAv_net_sel,iJAv_net,iJAv_src1,
	 iAusw,iAusw_prl,iAusw_set,iK_t_out,iAv_view,
	iBatLogKe,iJ_bat_ke,iBatLogVz,iJ_bat_vz,iBatLogWrk ,iExtern,
	iExt_set,iExt_dt,iExt_sk, iSM,iLog,iLog_,iBatLog}i;

signed char s_i;
signed char s_i1;
signed char s_i2;
signed char i_s;
} stuct_ind_;







extern stuct_ind_ aa,b[10];


void bitmap_hndl(void);
void ind_hndl(void);
__irq void timer1_interrupt(void);
__irq void timer0_interrupt(void); 

#line 3 "uku206.c"




char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz;
short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7;
char bFL5,bFL2,bFL,bFL_;


 




char cnt_of_slave=3;





extern signed short net_U,net_Ustore;
extern char bFF,bFF_;
extern signed short net_F,hz_out,hz_out_cnt;
extern signed char unet_drv_cnt;
extern char net_av;



signed short tout[4];
char tout_max_cnt[4],tout_min_cnt[4];
enum {tNORM,tMAX,tMIN}tout_stat[4];

















 

BAT_STAT bat[2];

signed short		bat_u_old_cnt;




extern unsigned avar_stat;	 	
extern unsigned avar_ind_stat; 	










extern char beep_cnt;





BPS_STAT bps[12];



signed short load_U;
signed short load_I;



signed short Ktsrc[2];
signed short Kusrc[2];
signed short Kisrc[2];
signed short Ki0src[2];
signed short Kubat[2];
unsigned short Kibat0[2];
signed short Kibat1[2];
signed short Ktbat[2];
signed short Kunet;
signed short Ktout[3];
signed short Kuload;

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
signed short TBATMAX;
signed short TBATSIGN;

signed short NUMBAT;
signed short NUMIST;
signed short NUMINV;
signed short NUMDT;
signed short NUMSK;
signed short NUMEXT;

enum  {apvON=0x0055,apvOFF=0x00aa}APV_ON1,APV_ON2;
signed short APV_ON2_TIME;





 


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
enum {mnON=0x55,mnOFF=0xAA}MNEMO_ON;
unsigned short MNEMO_TIME;


extern const unsigned short ADR_EE_BAT_C_NOM[2];
extern const unsigned short ADR_EE_BAT_YEAR_OF_ON[2];
extern const unsigned short ADR_EE_BAT_IS_ON[2];
extern const unsigned short ADR_EE_BAT_DAY_OF_ON[2];
extern const unsigned short ADR_EE_BAT_MONTH_OF_ON[2];
extern const unsigned short ADR_EE_BAT_RESURS[2];
extern const unsigned short ADR_EE_BAT_C_REAL[2];
extern const unsigned short ADR_EE_BAT_ZAR[2];
extern const unsigned short ADR_EE_BAT_ZAR_KE[2];
extern const unsigned short ADR_KUBAT[2];
extern const unsigned short ADR_KI0BAT[2];
extern const unsigned short ADR_KI1BAT[2];
extern const unsigned short ADR_KTBAT[2];


extern const unsigned short ADR_TMAX_EXT_EN[3];
extern const unsigned short ADR_TMAX_EXT[3];
extern const unsigned short ADR_TMIN_EXT_EN[3];
extern const unsigned short ADR_TMIN_EXT[3];
extern const unsigned short ADR_T_EXT_REL_EN[3];
extern const unsigned short ADR_T_EXT_ZVUK_EN[3];
extern const unsigned short ADR_T_EXT_LCD_EN[3];
extern const unsigned short ADR_T_EXT_RS_EN[3];

extern const unsigned short ADR_SK_SIGN[4];
extern const unsigned short ADR_SK_REL_EN[4];
extern const unsigned short ADR_SK_ZVUK_EN[4];
extern const unsigned short ADR_SK_LCD_EN[4];
extern const unsigned short ADR_SK_RS_EN[4];

extern const unsigned short ADR_EE_BAT_ZAR_CNT[2];

signed short u_necc,u_necc_;
signed short main_cnt_5Hz;
signed short num_necc;
signed short num_necc_Imax;
signed short num_necc_Imin;
signed short cnt_num_necc;

signed mat_temper;



unsigned main_apv_cnt,hour_apv_cnt[2],reset_apv_cnt[2];
unsigned short apv_cnt_sec[2],apv_cnt[2];



const char sm_month[13][4]={"янв","янв","фев","мар","апр","май","июн","июл","авг","сен","окт","ноя","дек"};
extern const char sm_mont[12][4]; 
const char ABCDEF[]={"0123456789ABCDEF"};
const char sm_[]	={"                    "};
const char sm_exit[]={" Выход              "};
const char sm_time[]={" 0%:0^:0& 0</>  /0{ "};



stuct_ind_ aa,b[10];




char lcd_buffer[200]={"Hello World"};
signed char parol[3];
char phase;
char lcd_bitmap[1024];
char dig[5];
char zero_on;
char ptr_ind=0;
char mnemo_cnt=50;
char simax;



char but;                            
unsigned long but_n,but_s;
char but0_cnt;
char but1_cnt;
char but_onL_temp;



char cnt_net_drv;



extern char ptr_can1_tx_wr,ptr_can1_tx_rd;
extern char ptr_can2_tx_wr,ptr_can2_tx_rd;
extern unsigned short rotor_can[6];
extern char RXBUFF[40],TXBUFF[40];



extern signed char sec_bcd,sec__;
extern signed char min_bcd,min__;
extern signed char hour_bcd,hour__;
extern signed char day_bcd,day__;
extern signed char month_bcd,month__;
extern signed char year_bcd,year__;



extern unsigned short ad7705_res1,ad7705_res2;
extern unsigned short ad7705_buff[2][16],ad7705_buff_[2];
extern unsigned short ad7705_res;
extern char b7705ch,ad7705_wrk_cnt;
extern unsigned short cnt_ad7705_vis,cnt_ad7705_vis_wrk;




char speed,l_but,n_but;



enum {wrkON=0x55,wrkOFF=0xAA}wrk;
char cnt_wrk;
signed short ibat_integr;
unsigned short av_beep,av_rele,av_stat;
char default_temp;
enum {tstOFF,tstON,tstU} tst_state[10];
char ND_out[3];



extern short adc_buff[16][16],adc_buff_[16];
extern char adc_cnt,adc_cnt1,adc_ch;



char flag=0;


extern signed short bat_ver_cnt;
signed short Isumm;
signed short Isumm_;

#line 1 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"
 
 
 
 
 
 
 
 
 
 




 
#line 59 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 




 
#line 82 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 




 





 


 



 





 
#line 124 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 142 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 159 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 171 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 185 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 194 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 






 






 
#line 236 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 



 


 
#line 253 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 




 
#line 284 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 310 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 336 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 362 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 





#line 330 "uku206.c"

#line 1 "lcd_AGM1232_uku206.h"










#line 19 "lcd_AGM1232_uku206.h"




#line 32 "lcd_AGM1232_uku206.h"


void lcd1_chk(void);
void lcd1_wr(char in);
void lcd2_chk(void);
void lcd2_wr(char in);
char data1_wr(char in);
void data2_wr(char in);
void lcd_set_page(char in);
void lcd_set_col(char in);
void lcd_set_raw(char in);
void lcd_init(void);
void status(void);
void delay(void);
void ltstrobe(char in);
void lcd_init_(void);
void lcd_clear(void);
void lcd_on(void);
void lcd_off(void);
void lcd_out(char* adr);

#line 332 "uku206.c"
#line 333 "uku206.c"
#line 1 "simbol.h"



const char caracter[1536]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x3E,0x1C,0x08,0x00,0x00,0x08,0x0C,0x0E,0x0C,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x3E,0x14,0x3E,0x14,0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x3E,0x41,0x00,0x00,0x00,0x00,0x00,0x41,0x3E,0x00,0x00,0x14,0x08,0x3E,0x08,0x14,0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00,0x50,0x30,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x42,0x61,0x51,0x49,0x46,0x00,0x21,0x41,0x45,0x4B,0x31,0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x56,0x36,0x00,0x00,0x00,0x00,0x08,0x14,0x22,0x00,0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00,0x22,0x14,0x08,0x00,0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x7E,0x11,0x11,0x11,0x7E,0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00,0x41,0x7F,0x41,0x00,0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x46,0x49,0x49,0x49,0x31,0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x07,0x08,0x70,0x08,0x07,0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00,0x7F,0x41,0x00,0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x00,0x00,0x00,0x41,0x7F,0x00,0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x38,0x44,0x44,0x44,0x20,0x00,0x30,0x48,0x48,0x50,0x7E,0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x08,0x7E,0x09,0x01,0x02,0x00,0x08,0x54,0x54,0x54,0x3C,0x00,0x7F,0x10,0x08,0x08,0x70,0x00,0x00,0x44,0x7D,0x40,0x00,0x00,0x20,0x40,0x44,0x3D,0x00,0x00,0x7E,0x10,0x28,0x44,0x00,0x00,0x00,0x41,0x7F,0x40,0x00,0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x7C,0x08,0x04,0x04,0x78,0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x7C,0x14,0x14,0x14,0x08,0x00,0x08,0x14,0x14,0x14,0x7C,0x00,0x7C,0x08,0x04,0x04,0x08,0x00,0x48,0x54,0x54,0x54,0x20,0x00,0x04,0x3F,0x44,0x40,0x20,0x00,0x3C,0x40,0x40,0x20,0x7C,0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x0C,0x50,0x50,0x50,0x3C,0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x06,0x07,0x06,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x1C,0x3E,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x3E,0x1C,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x3E,0x3E,0x3E,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x55,0x54,0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x09,0x09,0x06,0x00,0x00,0x24,0x2E,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x55,0x54,0x55,0x18,0x00,0x7C,0x10,0x20,0x7B,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x11,0x11,0x11,0x7E,0x00,0x7F,0x49,0x49,0x49,0x31,0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x7F,0x01,0x01,0x01,0x03,0x00,0x60,0x3E,0x21,0x21,0x7F,0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x77,0x08,0x7F,0x08,0x77,0x00,0x41,0x49,0x49,0x49,0x36,0x00,0x7F,0x20,0x10,0x08,0x7F,0x00,0x7F,0x20,0x11,0x08,0x7F,0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x40,0x7E,0x01,0x01,0x7F,0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x7F,0x01,0x01,0x01,0x7F,0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x47,0x28,0x10,0x08,0x07,0x00,0x1C,0x22,0x7F,0x22,0x1C,0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x7F,0x40,0x40,0x40,0xFF,0x00,0x07,0x08,0x08,0x08,0x7F,0x00,0x7F,0x40,0x7F,0x40,0x7F,0x00,0x7F,0x40,0x7F,0x40,0xFF,0x00,0x01,0x7F,0x48,0x48,0x70,0x00,0x7F,0x44,0x38,0x00,0x7F,0x00,0x7F,0x48,0x48,0x48,0x30,0x00,0x22,0x41,0x49,0x49,0x3E,0x00,0x7F,0x08,0x3E,0x41,0x3E,0x00,0x46,0x29,0x19,0x09,0x7F,0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x3C,0x4A,0x4A,0x49,0x31,0x00,0x7C,0x54,0x54,0x28,0x00,0x00,0x7C,0x04,0x04,0x04,0x0C,0x00,0x60,0x38,0x24,0x24,0x7C,0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x6C,0x10,0x7C,0x10,0x6C,0x00,0x44,0x44,0x54,0x54,0x28,0x00,0x7C,0x20,0x10,0x08,0x7C,0x00,0x7C,0x20,0x12,0x08,0x7C,0x00,0x7C,0x10,0x28,0x44,0x00,0x00,0x40,0x38,0x04,0x04,0x7C,0x00,0x7C,0x08,0x10,0x08,0x7C,0x00,0x7C,0x10,0x10,0x10,0x7C,0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x7C,0x04,0x04,0x04,0x7C,0x00,0x7C,0x14,0x14,0x14,0x08,0x00,0x38,0x44,0x44,0x44,0x00,0x00,0x04,0x04,0x7C,0x04,0x04,0x00,0x0C,0x50,0x50,0x50,0x3C,0x00,0x18,0x24,0x7E,0x24,0x18,0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x7C,0x40,0x40,0x40,0xFC,0x00,0x00,0x1C,0x10,0x10,0x7C,0x00,0x7C,0x40,0x7C,0x40,0x7C,0x00,0x7C,0x40,0x7C,0x40,0xFC,0x00,0x04,0x7C,0x50,0x50,0x20,0x00,0x7C,0x50,0x20,0x00,0x7C,0x00,0x7C,0x50,0x50,0x50,0x20,0x00,0x28,0x44,0x54,0x54,0x38,0x00,0x7C,0x10,0x38,0x44,0x38,0x00,0x08,0x54,0x34,0x14,0x7C};
#line 334 "uku206.c"
#line 1 "25lc640.h"




char spi1(char in);
void spi1_config(void);
void spi1_unconfig(void);
void lc640_wren(void);
char lc640_rdsr(void);
int lc640_read(int ADR);
int lc640_read_int(int ADR);
long lc640_read_long(int ADR);
void lc640_read_long_ptr(int ADR,char* out_ptr);
void lc640_read_str(int ADR, char* ram_ptr, char num);
char lc640_write(int ADR,char in);
char lc640_write_int(short ADR,short in);
char lc640_write_long(int ADR,long in);
char lc640_write_long_ptr(int ADR,char* in);

#line 335 "uku206.c"
#line 1 "Timer.h"

void init_timer1 (void);
#line 336 "uku206.c"
#line 1 "gran.h"

void gran_ring_char(signed char *adr, signed char min, signed char max) ;
void gran_char(signed char *adr, signed char min, signed char max);
void gran(signed short *adr, signed short min, signed short max);
void gran_ring(signed short *adr, signed short min, signed short max);
void gran_long(signed long *adr, signed long min, signed long max); 
#line 337 "uku206.c"
#line 1 "uart0.h"





char crc_87(char* ptr,char num);
char crc_95(char* ptr,char num);
void putchar0(char c);
void uart_out0 (char num,char data0,char data1,char data2,char data3,char data4,char data5);
void uart_out_adr0 (char *ptr, char len);
void uart0_init(void);
char getchar0(void);
__irq void uart0_interrupt(void);
void uart_in_an0(void);
char index_offset0 (signed char index,signed char offset);
char control_check0(char index);
void uart_in0(void);



#line 338 "uku206.c"
#line 1 "cmd.h"


#line 339 "uku206.c"
#line 1 "ret.h"




void ret_ind(char r_i,char r_s,int r_c);
void ret_ind_hndl(void);
void ret_ind_sec(char r_i,int r_c);
void ret_ind_sec_hndl(void);
void ret(short duty);
void ret_hndl(void);








 

     
#line 340 "uku206.c"
#line 1 "eeprom_map.h"






#line 18 "eeprom_map.h"



#line 66 "eeprom_map.h"



#line 83 "eeprom_map.h"



#line 95 "eeprom_map.h"


#line 106 "eeprom_map.h"




#line 157 "eeprom_map.h"

#line 172 "eeprom_map.h"










































































































 







#line 341 "uku206.c"
#line 1 "common_func.h"




signed short abs(signed short in);
void clr_scrn(void);
char find(char xy);
void bin2bcd_int(unsigned int in);
void bcd2lcd_zero(char sig);
void int2lcd_m(signed short in,char xy,char des);
void int2lcd_mm(signed short in,char xy,char des);
void int2lcd_mmm(signed short in,char xy,char des);
void long2lcd_mmm(signed long in,char xy,char des);
void long2lcdyx_mmm(signed long in,char y,char x,char des);
void int2lcdyx(unsigned short in,char y,char x,char des);
void int2lcd(unsigned short in,char xy,char des);
void long2lcdhyx(unsigned long in,char y,char x);
void char2lcdh(char in,char yx);
void char2lcdhyx(char in,char y,char x);
void int2lcdhyx(unsigned short in,char y,char x);
void char2lcdbyx(char in,char y,char x);
void pointer_set(char num_of_first_row);
void tree_down(signed char offset_ind,signed char offset_sub_ind);
void tree_up(char tind, char tsub_ind, char tindex_set, char tsub_ind1);
void bgnd_par(char const *ptr0,char const *ptr1,char const *ptr2,char const *ptr3);
void sub_bgnd(char const *adr,char xy,signed char offset);
void show_mess(char* p1, char* p2, char* p3, char* p4,int m_sec);
void event2ind(char num, char simbol);
char ptr_carry(signed int in,unsigned char modul,signed int carry);
void event_data2ind(char num, char simbol);

#line 342 "uku206.c"
#line 1 "pcf8563.h"







void i2c_init_soft(void);
void i2c_start_soft(void);
void i2c_stop_soft(void);
void pcf8563_read_bytes_soft(char adr,char nums);
void pcf8563_read(char nums);
void pcf8563_write(char adr, char in);




#line 343 "uku206.c"

#line 1 "control.h"




char vz_start(char hour);
char vz_stop(void);
void vz_drv(void);
void samokalibr_init(void);
void samokalibr_hndl(void);
void kb_init(void);
void kb_hndl(void);
void ubat_old_drv(void);
void unet_drv(void);
void matemat(void);
void adc_init(void);
void adc_drv(void);
void adc_drv_(void);
void avg_hndl(void);


void rele_hndl(void);
void bps_hndl(void);
void bps_drv(char in);
void bat_hndl(void);
void bat_drv(char in);
void u_necc_hndl(void);
void cntrl_hndl(void);
void zar_drv(void);
void num_necc_hndl(void);
char ke_start(char in);
void avz_drv(void);




typedef enum {spcOFF=0,spcKE, spcVZ}enum_spc_stat;
extern enum_spc_stat spc_stat;

extern char spc_bat;
extern char spc_phase;
extern unsigned short vz_cnt_s,vz_cnt_h,vz_cnt_h_;







#line 345 "uku206.c"
#line 1 "mess.h"










		





void mess_hndl(void);
void mess_send(char _mess, short par0, short par1, char _time);
char mess_find(char _mess);
char mess_find_unvol(char _mess);

#line 346 "uku206.c"
#line 1 "full_can.h"


  
















  









 


char CRC1_in(void);
char CRC2_in(void);
char CRC1_out(void);
char CRC2_out(void);
void can1_out_adr(char* ptr,char num);
__irq void can_isr_err (void);
void can2_out(char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7);
void can_adr_hndl(void);
void can_in_an(void);
void can_in_an2(void);
__irq void can_isr_rx (void); 
__irq void can_isr_tx (void); 
short can1_init (unsigned short can_rx_vector, unsigned short can_tx_vector, unsigned int can_btr);
short can2_init (unsigned short can_rx_vector, unsigned short can_tx_vector, unsigned int can_btr);
short FullCAN_SetFilter (
  unsigned short can_port, 
  unsigned int CANID 
  );
#line 347 "uku206.c"
#line 1 "watchdog.h"

void watchdog_init(unsigned long f,unsigned long time_out);
void watchdog_reset(void);





#line 348 "uku206.c"
#line 1 "ad7705.h"


void spi1_ad7705_config(void);
void ad7705_reset(void);
void ad7705_write(char in);
void ad7705_read(char num);
void ad7705_drv(void);



#line 349 "uku206.c"
#line 1 "beep.h"


void beep_init(long zvuk,char fl);
void beep_hndl(void);
void beep_drv(void); 







#line 350 "uku206.c"
#line 1 "avar_hndl.h"


void avar_hndl(void);
void avar_unet_hndl(char in);
void reload_hndl(void);
void avar_bps_hndl(char bps, char v, char in);
void avar_bat_hndl(char bat, char in);



#line 351 "uku206.c"
#line 1 "memo.h"

void memo_read (void);






#line 352 "uku206.c"





 

extern short plazma_adc_cnt;
extern char net_buff_cnt;
extern unsigned short net_buff[32],net_buff_;
extern char rele_stat ;
extern char bRXIN0;

short av_j_si_max;
char cntrl_plazma;
extern char bOUT_FREE2;
extern char   av_bps[12],av_inv[6],av_dt[4],av_sk[4];

char content[63];



















extern signed short samokalibr_cnt;



extern char mess[10],mess_old[10],mess_cnt[10];
extern short mess_par0[10],mess_par1[10],mess_data[2];




extern signed short 	main_kb_cnt;
extern signed short 	kb_cnt_1lev;
extern signed short 	kb_cnt_2lev;
extern char 			kb_full_ver;
extern char 			kb_start[2];



extern signed short cntrl_stat;
extern signed short cntrl_stat_old;
extern signed short cntrl_stat_new;
extern signed short Ibmax;



extern char num_of_wrks_bps;



extern signed short main_10Hz_cnt;
extern signed short main_1Hz_cnt;



extern unsigned avar_stat;	 	
extern unsigned avar_ind_stat; 	
extern unsigned avar_stat_old;
extern unsigned avar_stat_new,avar_stat_offed;










extern signed char vent_stat;



extern char bps_hndl_2sec_cnt;






void def_set(int umax__,int ub0__,int ub20__,int usign__,int imax__,int uob__,int numi)
{
;
lc640_write_int(0x10+100+36,numi);
lc640_write_int(0x10+100+2,0);
lc640_write_int(0x10+100+4,umax__);
lc640_write_int(0x10+100+6,ub0__);
lc640_write_int(0x10+100+8,ub20__);
lc640_write_int(0x10+100+82,70);
lc640_write_int(0x10+100+10,80);

lc640_write_int(0x10+100+14,usign__);
lc640_write_int(0x10+100+16,187);
lc640_write_int(0x10+100+18,0xff);
lc640_write_int(0x10+100+20,5);
lc640_write_int(0x10+100+22,1030);
lc640_write_int(0x10+100+24,imax__);
lc640_write_int(0x10+100+26,8);
lc640_write_int(0x10+100+28,0xff);
lc640_write_int(0x10+100+30,20);
lc640_write_int(0x10+100+32,uob__);
lc640_write_int(0x10+100+34,3);

lc640_write_int(0x10+100+72,mnON);
lc640_write_int(0x10+100+74,30);	

lc640_write_int(0x10+100+12,1);
lc640_write_int(0x10+100+44,apvOFF);
}


void net_drv(void)
{ 


if(++cnt_net_drv>=16) cnt_net_drv=0; 

if(cnt_net_drv<=11) 
	{    
	can2_out(cnt_net_drv,cnt_net_drv,0xED,bps[cnt_net_drv]._flags_tu,*((char*)(&bps[cnt_net_drv]._vol_u)),*((char*)((&bps[cnt_net_drv]._vol_u))+1),*((char*)(&bps[cnt_net_drv]._vol_i)),*((char*)((&bps[cnt_net_drv]._vol_i))+1));
     
	if(cnt_net_drv<cnt_of_slave)
	     {
	     if(bps[cnt_net_drv]._cnt<60)
   	 		{    
   	 		bps[cnt_net_drv]._cnt++;
   	 		if( (bps[cnt_net_drv]._cnt>=60) && (!net_av) && (!(bps[cnt_net_drv]._av&0x08)) ) 
   	 			{
   	 			avar_bps_hndl(cnt_net_drv,3,1);
   	 			}
   	 		}
		else bps[cnt_net_drv]._cnt=60;
						
		if((bps[cnt_net_drv]._cnt>=3)&&(bps[cnt_net_drv]._cnt_old<3))bps[cnt_net_drv]._cnt_more2++;
		bps[cnt_net_drv]._cnt_old=bps[cnt_net_drv]._cnt;
	     }
	}
else if(cnt_net_drv==12)
	{
     can2_out(0xff,0xff,0x62,*((char*)(&UMAX)),*((char*)((&UMAX))+1),*((char*)(&DU)),*((char*)((&DU))+1),0);
     } 
     
else if(cnt_net_drv==13)
	{
     can2_out(0xff,0xff,0x26,*((char*)(&TMAX)),*((char*)((&TMAX))+1),*((char*)(&TSIGN)),*((char*)((&TSIGN))+1),(char)TZAS);
     } 
else if(cnt_net_drv==14)
	{                 

     } 
}




void parol_init(void)
{
parol[0]=0;
parol[1]=0;
parol[2]=0;
aa . s_i=0;
}


void bitmap_hndl(void)
{
short x,ii,i;
unsigned int ptr_bitmap;

for(ii=0;ii<488;ii++)
	{
	lcd_bitmap[ii]=0x00;
	}

if(!mnemo_cnt)
	{
		
	}
else
	{
	for(i=0;i<4;i++)
		{
		ptr_bitmap=122*(unsigned)i;
		for(x=(20*i);x<((20*i)+20);x++)
	 		{
			lcd_bitmap[ptr_bitmap++]=caracter[(unsigned)lcd_buffer[x]*6];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+1];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+2];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+3];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+4];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+5];
			} 
		}
	}	
}


void ind_hndl(void)
{

const char* ptrs[40];
const char* sub_ptrs[40];
static char sub_cnt,sub_cnt1;
char i,sub_cnt_max;
char ii_;
static char ii_cnt,cnt_ind_bat;


	 
sub_cnt_max=5;
i=0;

if(spc_stat==spcVZ)
	{
	sub_ptrs[i++]=		" Выравн.заряд  z:0Z ";
	sub_cnt_max++;
	}
if((spc_stat==spcKE))
	{
	sub_ptrs[i++]=		"Контроль емк. бат №q";
	sub_cnt_max++;
	}	
if(avar_stat&0x0001)
	{
	sub_ptrs[i++]=		"   Авария сети!!!   ";
	sub_cnt_max++;	
	}

for(ii_=0;ii_<2;ii_++)
	{
	if(avar_stat&(1<<(1+ii_)))
		{
		sub_ptrs[i++]=	" Авария батареи №w  ";
		sub_cnt_max++;	
		}
	}	

for(ii_=0;ii_<12;ii_++)
	{
	if(avar_stat&(1<<(3+ii_)))
		{
		sub_ptrs[i++]=	"   Авария БПС №W    ";
		sub_cnt_max++;	
		}
	}


cnt_of_slave=NUMIST+NUMINV;




 

  


sub_cnt1++;	
if(sub_cnt1>=20)
	{
	sub_cnt1=0;
	sub_cnt++;
	if(sub_cnt>=sub_cnt_max)
		{
		sub_cnt=0;
		}
	}


if(aa . i==iMn)
	{

	if(num_of_wrks_bps)	
		{
		ptrs[0]	=	"  В работе    rист. ";
		}
	else if((NUMBAT>1)&&(!bat[0]._av)&&(!bat[1]._av))
		{
		ptrs[0]	=	" Работа от батарей  ";
		}
	else if((BAT_IS_ON[0]==bisON)&&(!bat[0]._av) )
		{
		ptrs[0]	=	"Работа от батареи №1";
		}
	else if((BAT_IS_ON[1]==bisON)&&(!bat[1]._av))
		{
		ptrs[0]	=	"Работа от батареи №2";
		}

	 
     i=0;
 




 	
 	
 	ptrs[1]="Uб!=   ]В Iб!=    @А";
     ptrs[2]="Uн=    #В Iн=     $А";
     ptrs[3]=" 0%:0^:0& 0</>  /0{ ";
     
 	ptrs[4]=										" Батарея N1         ";
     ptrs[5]=										" Батарея N2         ";
     if((NUMBAT==1)&&(BAT_IS_ON[0]!=bisON))ptrs[4]=		" Батарея N2         ";
								
	ptrs[4+NUMBAT]=  								" БПС N1             ";
     ptrs[5+NUMBAT]=  								" БПС N2             ";
     ptrs[6+NUMBAT]=  								" БПС N3             ";
     ptrs[7+NUMBAT]=  								" БПС N4             ";
     ptrs[8+NUMBAT]= 								" БПС N5             ";
     ptrs[9+NUMBAT]= 								" БПС N6             ";
     ptrs[10+NUMBAT]= 								" БПС N7             ";
     ptrs[11+NUMBAT]= 								" БПС N8             ";
     ptrs[12+NUMBAT]= 								" БПС N9             ";
     ptrs[13+NUMBAT]= 								" БПС N10            ";
     ptrs[14+NUMBAT]= 								" БПС N11            ";
     ptrs[15+NUMBAT]= 								" БПС N12            ";

     
     ptrs[4+NUMIST+NUMBAT]=  							" Инвертор N1        ";
     ptrs[5+NUMIST+NUMBAT]=  							" Инвертор N2        ";
     ptrs[6+NUMIST+NUMBAT]=  							" Инвертор N3        ";
     ptrs[7+NUMIST+NUMBAT]=  							" Инвертор N4        ";

     ptrs[4+NUMIST+NUMBAT+NUMINV]= 					" Сеть               "; 
     ptrs[5+NUMIST+NUMBAT+NUMINV]= 					" Нагрузка           "; 
     ptrs[6+NUMIST+NUMBAT+NUMINV]= 					" Внешние датчики    "; 
 	ptrs[6+NUMIST+NUMBAT+NUMINV+(NUMEXT!=0)]= 			" Спецфункции    	 ";
     ptrs[7+NUMIST+NUMBAT+NUMINV+(NUMEXT!=0)]= 			" Установки          "; 
     ptrs[8+NUMIST+NUMBAT+NUMINV+(NUMEXT!=0)]= 			" Журнал событий     "; 
     ptrs[9+NUMIST+NUMBAT+NUMINV+(NUMEXT!=0)]= 			" Выход              "; 
     ptrs[10+NUMIST+NUMBAT+NUMINV+(NUMEXT!=0)]= 			" Журнал батареи N1  "; 
     ptrs[11+NUMIST+NUMBAT+NUMINV+(NUMEXT!=0)]= 			" Журнал батареи N2  "; 

     if(aa . s_i==0)aa . i_s=0;
	else if((aa . i_s-aa . s_i)>2)aa . i_s=aa . s_i+2;
	else if(aa . s_i>aa . i_s)aa . i_s=aa . s_i;
	





 
    



		
	if(sub_cnt<5)bgnd_par(ptrs[0],ptrs[aa . i_s+1],ptrs[aa . i_s+2],ptrs[aa . i_s+3]);
	else bgnd_par(sub_ptrs[sub_cnt-5],ptrs[aa . i_s+1],ptrs[aa . i_s+2],ptrs[aa . i_s+3]);
	
	if((ii_cnt<=80)||((spc_stat!=spcVZ)&&(spc_stat!=spcKE) )) 
		{
	if((ii_!=139)&&( num_of_wrks_bps!=0))
		{
		





 
		
		if(sub_cnt<5)int2lcdyx(num_of_wrks_bps,0,14,0);
		


 

          }
     }
 
  	int2lcd(load_U,'#',1);
 	int2lcd(load_I,'$',1);
 	
	int2lcd(hour__,'%',0);
	int2lcd(min__,'^',0);
	int2lcd(sec__,'&',0);
	int2lcd(day__,'<',0);
	int2lcd(year__,'{',0); 
	if(!((month__>=1)&&(month__<=12)))month__=1;
	sub_bgnd(sm_month[month__],'>',0);

 	if(bFL2)
 	     {
 	     lcd_buffer[find(':')]=' ';
 	     lcd_buffer[find(':')]=' ';
 	     lcd_buffer[find(':')]=' ';
 	     }

	if((aa . i_s)&&(aa . s_i))
	     {
	     if(aa . i_s==aa . s_i)lcd_buffer[60]=1;
	     else if((aa . i_s-aa . s_i)==1)lcd_buffer[40]=1;
	     else if((aa . i_s-aa . s_i)==2)lcd_buffer[20]=1;
	     }	
		
	cnt_ind_bat++;
	if(cnt_ind_bat>=(NUMBAT*20)) cnt_ind_bat=0;
	
	if(NUMBAT==0)sub_bgnd(" Работа без батарей ",'!',-2);
	else
		{
		int2lcd((cnt_ind_bat/20)+1+(!(BAT_IS_ON[0]==bisON)),'!',0);
		int2lcd((cnt_ind_bat/20)+1+(!(BAT_IS_ON[0]==bisON)),'!',0);
		int2lcd(bat[cnt_ind_bat/20]._Ub,']',1);
		if((mess_find_unvol(215))&&(mess_data[0]==216)) sub_bgnd("КЛБР. ",'@',-4);
		else int2lcd_mmm(bat[cnt_ind_bat/20]._Ib,'@',2);
		}

	int2lcd(vz_cnt_s/60,'z',0);
	int2lcd(vz_cnt_h,'Z',0);
		



 








 
		 
	}

else if (aa . i==iBat)
	{
	if(bat[aa . s_i1]._av )
		{
		if(bFL2)bgnd_par("       АВАРИЯ!        ",
		                 "     Батарея №#       ",
		                 "    не подключена     ",sm_);
		else bgnd_par(sm_,sm_,sm_,sm_);
		int2lcd(aa . s_i1+1,'#',0);
		}               
	else
		{
		if(bat[aa . s_i1]._Ib>0)
		     {
		     ptrs[1]="    заряжается      ";
		     ptrs[3]="   Iзар=     #А     ";
		     }
		else
		     {
		     ptrs[1]="   разряжается      ";
		     ptrs[3]="   Iразр=    #А     ";
		     }	
		ptrs[2]="   Uбат=     $В     ";
		
		if(bat[aa . s_i1]._nd)ptrs[4]="    ДТ. неисправен  ";
		else ptrs[4]="   tбат =   (°C     ";
		ptrs[5]="   Заряд=    w%     ";
		ptrs[6]="   Cбат=     QА*ч   ";
		ptrs[7]=sm_exit;
 
		bgnd_par("    БАТАРЕЯ N@      ",
		          ptrs[aa . s_i+1],ptrs[aa . s_i+2],ptrs[aa . s_i+3]);
	     
	     int2lcd(aa . s_i1+1,'@',0);
	     int2lcd(bat[aa . s_i1]._Ub,'$',1);
	     int2lcd_mmm(abs(bat[aa . s_i1]._Ib),'#',2);
	     int2lcd(bat[aa . s_i1]._Tb,'(',0);
	     int2lcd(bat[aa . s_i1]._zar,'w',0);
	     if(BAT_C_REAL[aa . s_i1]==0x5555)sub_bgnd("------",'Q',-1);
	     else int2lcd(BAT_C_REAL[aa . s_i1],'Q',1);
	     if(aa . s_i==4)lcd_buffer[60]=1;
		}

	int2lcdyx(lc640_read_int(ADR_EE_BAT_ZAR_CNT[aa . s_i1]),0,5,0);
	long2lcdyx_mmm(bat[aa . s_i1]._zar_cnt,1,8,0);
	int2lcdyx(bat[aa . s_i1]._time_cnt,0,19,0);
	int2lcdyx(lc640_read_int(ADR_EE_BAT_C_NOM[aa . s_i1]),3,5,0);


 
	} 

 else if(aa . i==iBps)
	{
	const char* ptr[8];
	const char* ptr1;


 
	simax=5;

	ptr[1]=			" Uист =        (В   ";
	ptr[2]=			" Iист =        [A   ";
	ptr[3]=			" tист =        ]°С  ";
	ptr[4]=			" Сброс аварий       ";
	ptr[5]=			sm_exit;

	if(bps[aa . s_i1]._state==bsWRK)
		{
		ptr[0]=		"      в работе      ";
		if((bps[aa . s_i1]._flags_tm&0x08)&&(bFL2))
		ptr[0]=		"  СИЛЬНЫЙ НАГРЕВ!!! ";	      
		}
 	 else if(bps[aa . s_i1]._state==bsRDY)
	 	{
		ptr[0]=		"      в резерве     ";	
		}

 	 else if(bps[aa . s_i1]._state==bsBL)
	 	{
		ptr[0]=		" заблокирован извне ";	
		}

	 else if(bps[aa . s_i1]._state==bsAPV)
	 	{
		ptr[0]=		"    Работает АПВ    ";
		}
	 
	 else if(bps[aa . s_i1]._state==bsAV)
	 	{
		if(bps[aa . s_i1]._av&(1<<0))
		ptr[0]=		" Авария - перегрев! ";
		else if(bps[aa . s_i1]._av&(1<<1))
		ptr[0]=		"Авария - завыш.Uвых!";
		else if(bps[aa . s_i1]._av&(1<<2))	 
		ptr[0]=		"Авария - заниж.Uвых!";
		else if(bps[aa . s_i1]._av&(1<<3))
			{
			ptr[0]=	"  Авария - потеряна ";
			ptr[1]=	"      связь!!!      ";
			ptr[2]=	"                    ";
			simax=0;
			}
		}

	 else if(bps[aa . s_i1]._state==bsOFF_AV_NET)
	 	{
		ptr[0]=		"      ВЫКЛЮЧЕН      ";
		ptr[1]=		"     Отсутствует    ";
		ptr[2]=		" первичное питание! ";
		simax=0;
		}

	bgnd_par(			"       БПС N&       ",
					ptr[aa . i_s],
					ptr[aa . i_s+1],
					ptr[aa . i_s+2]);

	if(aa . s_i-aa . i_s>2)aa . i_s=aa . s_i-2;
	else if (aa . s_i<aa . i_s)aa . i_s=aa . s_i;

	if(aa . s_i>=4)	pointer_set(1);


























































	int2lcd(aa . s_i1+1,'&',0);
	int2lcd(bps[aa . s_i1]._Uii,'(',1);
     int2lcd(bps[aa . s_i1]._Ii,'[',1);  
   	int2lcd_mmm(bps[aa . s_i1]._Ti,']',0); 
   			 
    
    
    

     }  

else if(aa . i==iNet)
	{
	bgnd_par(		"        СЕТЬ        ",
				" U   =     [В       ",
				" f   =     ]Гц      ",
				sm_exit);
	lcd_buffer[60]=1;
	     	
     int2lcd(net_U,'[',0);
     int2lcd(net_F,']',1);

     
                   	      	   	    		
     }

else if(aa . i==iLoad)
	{
	bgnd_par(		"      НАГРУЗКА      ",
				" Uнагр =     [В     ",
				" Iнагр =     ]А     ",
				sm_exit);
	lcd_buffer[60]=1;
	     	
     int2lcd(load_U,'[',1);
     int2lcd(load_I,']',1);

     
                   	      	   	    		
     }

else if(aa . i==iSpc)
	{

 	ptrs[0]=	" Выр.заряд          ";
 	ptrs[1]=	" Авт.выр.заряд      ";
 	ptrs[2]=	" К.Е. батареи N1    ";
 	ptrs[3]=	" К.Е. батареи N2    ";
 	ptrs[4]=	" А.К.Е.  бат. N1    ";
 	ptrs[5]=	" А.К.Е.  бат. N2    ";
 	ptrs[6]=	" Выход              ";
	
	if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
	else if((aa . s_i-aa . i_s)>2) aa . i_s=aa . s_i-2;
    	bgnd_par( "     СПЕЦФУНКЦИИ    ",
    	          ptrs[aa . i_s],
    	          ptrs[aa . i_s+1],
    	          ptrs[aa . i_s+2]);
	pointer_set(1);
	}    		


 else if(aa . i==iVz)
	{          
	if(aa . s_i==22) bgnd_par(	"ВЫРАВНИВАЮЩИЙ ЗАРЯД ",
							"    невозможен,     ",
							"  включен контроль  ",
							"   емкости бат.N1   "); 
	else if(aa . s_i==33) bgnd_par("ВЫРАВНИВАЮЩИЙ ЗАРЯД ",
							"    невозможен,     ",
							"  включен контроль  ",
							"   емкости бат.N2   ");
	else if(spc_stat==spcVZ)
		{
		bgnd_par(				"ВЫРАВНИВАЮЩИЙ ЗАРЯД ",
							" Длит.-сть     (ч.  ",
							" Включен            ",
							sm_exit);
		}
	else 
		{
		bgnd_par(				"ВЫРАВНИВАЮЩИЙ ЗАРЯД ",
							" Длит.-сть     (ч.  ",
							" Выключен           ",
							sm_exit);
		}	

	pointer_set(1);	

	int2lcd(VZ_HR,'(',0);
	} 
	
	
else if(aa . i==iKe)
	{    
	if((aa . s_i==0)||(aa . s_i==1))
		{
		if(spc_stat==spcKE)
			{
			bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
					"     БАТАРЕИ N{     ",
					" Включен            ",
					sm_exit);
			}
		else
			{
			bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
					"     БАТАРЕИ N{     ",
					" Выключен           ",
					sm_exit);

			}
		}

	else if(aa . s_i==11)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				" Выключен           ",
				sm_exit);
		}
	else if(aa . s_i==12)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"  контроль емкости  ",
				"    батареи   N)    ");
		int2lcd(2-aa . s_i1,')',0);
		}
	else if(aa . s_i==13)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"      батарея       ",
				"     не введена     ");
		}
	else if(aa . s_i==14)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"      авария        ",
				"      батареи       ");
		}				
	else if(aa . s_i==15)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"      батарея       ",
				"     заряжается     ");
		}
	else if(aa . s_i==16)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"      батарея       ",
				"    разряжается     ");
		}				
	else if(aa . s_i==17)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"  контроль заряда   ",
				"    батареи   N)    ");
		int2lcd(aa . s_i1+1,')',0);
		}
	else if(aa . s_i==18)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"      авария        ",
				"    батареи   N)    ");
		int2lcd(2-aa . s_i1,')',0);
		}				 
	else if(aa . s_i==19)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"     батарея N)     ",
				"     заряжается     ");
		int2lcd(2-aa . s_i1,')',0);
		}
	else if(aa . s_i==20)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"    разряжается     ",
				"     батарея N)     ");
		int2lcd(2-aa . s_i1,')',0);
		}				
	else if(aa . s_i==21)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"  контроль заряда   ",
				"    батареи   N)    ");
		int2lcd(2-aa . s_i1,')',0);
		}
	else if(aa . s_i==22)
		{
		bgnd_par(	"  КОНТРОЛЬ ЕМКОСТИ  ",
				"     БАТАРЕИ N{     ",
				"      авария        ",
				"       сети          ");
		}	
														
	if(aa . s_i==0) lcd_buffer[41]=1; 
	else if(aa . s_i==1) lcd_buffer[51]=1;
	int2lcd(aa . s_i1+1,'{',0);
	}	  



else if(aa . i==iLog)
	{
	


	av_j_si_max=lc640_read_int(1024+1024+512+1024+2);
	if(av_j_si_max>64)av_j_si_max=0;

	if(av_j_si_max==0)
		{
		bgnd_par("   ЖУРНАЛ СОБЫТИЙ   "," Журнал пуст        ",sm_exit,sm_);
		
		aa . s_i=1;
		aa . i_s=0;
		}       
		
	else if(av_j_si_max==1)
		{
		bgnd_par("   ЖУРНАЛ СОБЫТИЙ   "," (                  ",sm_exit," Очистить журнал    ");
		
		
		
		aa . i_s=0;
		}

	else if(av_j_si_max==2)
		{
		if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
		else if((aa . s_i-aa . i_s)>2) aa . i_s=aa . s_i-2;		
		if(aa . i_s==0) bgnd_par("   ЖУРНАЛ СОБЫТИЙ   "," (                  "," [                  ",sm_exit);
		else if(aa . i_s==1) bgnd_par("   ЖУРНАЛ СОБЫТИЙ   "," (                  ",sm_exit," Очистить журнал    ");
		
		
		
		
		}
		
	else if(av_j_si_max>2)
		{
		if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
		else if((aa . s_i-aa . i_s)>2) aa . i_s=aa . s_i-2;  
		if(aa . i_s==(av_j_si_max-1)) bgnd_par("   ЖУРНАЛ СОБЫТИЙ   "," (                  ",sm_exit," Очистить журнал    ");
		else if(aa . i_s==(av_j_si_max-2)) bgnd_par("   ЖУРНАЛ СОБЫТИЙ   "," (                  "," [                  ",sm_exit);
		else bgnd_par("   ЖУРНАЛ СОБЫТИЙ   "," (                  "," [                  "," {                  ");
		
		
		
		

		}
	pointer_set(1);
     event2ind(aa . i_s,'(');
     event2ind(aa . i_s+1,'[');	
     event2ind(aa . i_s+2,'{');	  
     
	}



else if(aa . i==iLog_)
	{	
	unsigned short tempUI,tempUI_;
	unsigned long tempUL;
	char av_head[4],av_data_on[8],av_data_off[8],av_data[4];
	char av_head_int[2];
	
	bgnd_par(sm_,sm_,sm_,sm_);
	tempUI=lc640_read_int(1024+1024+512+1024);
	tempUI=ptr_carry(tempUI,64,-1*((signed)aa . s_i1));
	tempUI*=32;
	tempUI+=1024;
     
     lc640_read_long_ptr(tempUI,av_head);
     lc640_read_long_ptr(tempUI+4,av_head_int);
     lc640_read_long_ptr(tempUI+8,av_data_on);
     lc640_read_long_ptr(tempUI+12,&(av_data_on[4])); 
     lc640_read_long_ptr(tempUI+16,av_data_off);
     lc640_read_long_ptr(tempUI+20,&(av_data_off[4]));      
	lc640_read_long_ptr(tempUI+24,av_data);  
	
	if((av_head[0]=='U')&&(av_head[2]=='R'))
		{
		bgnd_par(	"    Перезагрузка    ",
				"   или включение    ",
				"        ИБЭП        ",
				"  0%(  0^ 0@:0#:0$  ");
				
				  	
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]-1],'(',0);
		
		int2lcdyx(av_data_on[1],2,1,0);
		av_j_si_max=0;
		
		}

	else if((av_head[0]=='P')&&(av_head[2]=='A'))
		{  
		ptrs[0]="   Авария сети!!!   ";
		ptrs[1]="  0%(  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[2]="    не устранена    ";
			ptrs[3]="     Uсети=  +В     ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			int2lcd(net_U,'+',0);
			}
		else 
			{
			gran_char(&aa . i_s,0,1);
			ptrs[2]="      устранена     ";
			ptrs[3]="  0[]  0< 0>:0=:0)  ";
			ptrs[4]="     Uмин=  +В      ";
			bgnd_par(ptrs[aa . i_s],ptrs[1+aa . i_s],ptrs[2+aa . i_s],ptrs[3+aa . i_s]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]-1],']',0);
			
			int2lcd(av_data[0]+(av_data[1]*256),'+',0);			
			}	
		
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]-1],'(',0);
		
		av_j_si_max=1;
		}

	else if((av_head[0]=='B')&&(av_head[2]=='C'))
		{  
		ptrs[0]="       Авария       ";
		ptrs[1]="     батареи N+     ";
		ptrs[2]="  0%(  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[3]="    не устранена    ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			}
		else 
			{
			gran_char(&aa . i_s,0,1);
			ptrs[3]="      устранена     ";
			ptrs[4]="  0[]  0< 0>:0=:0)  ";
			bgnd_par(ptrs[aa . i_s],ptrs[1+aa . i_s],ptrs[2+aa . i_s],ptrs[3+aa . i_s]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]-1],']',0);
			
						
			}	
		int2lcd(av_head[1]+1,'+',0);
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]-1],'(',0);
		
		av_j_si_max=1;
		}

	else if((av_head[0]=='B')&&(av_head[2]=='Z'))
		{  
		ptrs[0]="   Выравнивающий    ";
		ptrs[1]="       заряд        ";
		ptrs[2]="  0%(  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[3]="    не завершен     ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			}
		else 
			{
			gran_char(&aa . i_s,0,1);
			ptrs[3]="      завершен      ";
			ptrs[4]="  0[]  0< 0>:0=:0)  ";
			bgnd_par(ptrs[aa . i_s],ptrs[1+aa . i_s],ptrs[2+aa . i_s],ptrs[3+aa . i_s]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]-1],']',0);
			
						
			}	
		int2lcd(av_head[1]+1,'+',0);
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]-1],'(',0);
		
		av_j_si_max=1;
		}



	else if((av_head[0]=='B')&&(av_head[2]=='W'))
		{  
		ptrs[0]="       Разряд       ";
		ptrs[1]="     батареи N!     ";
		ptrs[2]="   Начало           ";
		ptrs[3]="  0%(  0^ 0@:0#:0$  ";
		ptrs[4]="       Uбат=  <В";
		ptrs[5]="   Конец            ";
		ptrs[6]="  0qw  0r 0i:0l:0s  ";
		ptrs[7]="         Uбат=  >В  ";
		ptrs[8]="   Отдано    /а*ч.  ";
		
		bgnd_par(ptrs[aa . i_s],ptrs[1+aa . i_s],ptrs[2+aa . i_s],ptrs[3+aa . i_s]);
		
		int2lcd(av_head[1]+1,'!',0);

		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]-1],'(',0);
				
		int2lcd(av_data_off[4],'i',0);
		int2lcd(av_data_off[5],'l',0);
		int2lcd(av_data_off[6],'s',0);
		int2lcd(av_data_off[2],'q',0);
		int2lcd(av_data_off[0],'r',0); 
		if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
		sub_bgnd(sm_mont[av_data_off[1]-1],'w',0);
		
		
		int2lcd(av_head_int[0],'/',1);
		int2lcd(av_data_on[3]+(av_data_on[7]*256),'<',1);
		int2lcd(av_head_int[1],'>',1);	
		av_j_si_max=5;				

		
		}

	else if((av_head[0]=='B')&&(av_head[2]=='K'))
		{  
		ptrs[0]="  Контроль емкости  ";
		ptrs[1]="       батареи      ";
		ptrs[2]="   Начало           ";
		ptrs[3]="  0%(  0^ 0@:0#:0$  ";
		ptrs[4]="         Uбат=  <В  ";
		ptrs[5]="   Конец            ";
		ptrs[6]="  0qw  0r 0i:0l:0s  ";
		ptrs[7]="         Uбат=  >В  ";
		ptrs[8]="   Ёмкость   /а*ч.  ";
		
		bgnd_par(ptrs[aa . i_s],ptrs[1+aa . i_s],ptrs[2+aa . i_s],ptrs[3+aa . i_s]);
		
		int2lcd(av_head[1]+1,'!',0);

		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]-1],'(',0);
				
		int2lcd(av_data_off[4],'i',0);
		int2lcd(av_data_off[5],'l',0);
		int2lcd(av_data_off[6],'s',0);
		int2lcd(av_data_off[2],'q',0);
		int2lcd(av_data_off[0],'r',0); 
		if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
		sub_bgnd(sm_mont[av_data_off[1]-1],'w',0);
		
		
		int2lcd(av_head_int[0],'/',0);
		int2lcd(av_data_on[3]+(av_data_on[7]*256),'<',1);
		int2lcd(av_head_int[1],'>',1);	
		av_j_si_max=5;				

		
		}



	else if(av_head[0]=='S')
		{  
		ptrs[0]="   Авария БПС N+    ";
		
		if(av_head[2]=='L')
			{
			ptrs[1]="     отключился     ";
			}
		else if(av_head[2]=='T')
			{
			ptrs[1]="      перегрев      ";
			}		
		else if(av_head[2]=='U')
			{
			ptrs[1]="   завышено Uвых.   ";
			}		
		else if(av_head[2]=='u')
			{
			ptrs[1]="   занижено Uвых.   ";
			}								
		
		
		ptrs[2]="  0%(  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[3]="    не устранена    ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			}
		else 
			{
			gran_char(&aa . i_s,0,1);
			ptrs[3]="      устранена     ";
			ptrs[4]="  0[]  0< 0>:0=:0)  ";
			bgnd_par(ptrs[aa . i_s],ptrs[1+aa . i_s],ptrs[2+aa . i_s],ptrs[3+aa . i_s]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]-1],']',0);
			
						
			}	
		int2lcd(av_head[1]+1,'+',0);
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]-1],'(',0);
		
		}

	
	}
		 
else if(aa . i==iBatLog)
	{
	if(BAT_IS_ON[aa . s_i1]==bisON)ptrs[0]=" Введена  0!/@  /0# ";
	else ptrs[0]=" Выведена 0!/@  /0# ";
     ptrs[1]=" Номин.емк.     $A*ч";
     ptrs[2]=" Наработка      %ч. ";
     ptrs[3]=" Контроль емкости   ";
     ptrs[4]=" Выравнивающий заряд";
     ptrs[5]=" Разряды            ";
     ptrs[6]=sm_exit;	
	if((aa . s_i-aa . i_s)>1)aa . i_s=aa . s_i-1;
	else if(aa . s_i<aa . i_s)aa . i_s=aa . s_i;
	bgnd_par(	" БАТАРЕЙНЫЙ ЖУРНАЛ  ",
			"     БАТАРЕЯ N^     ",
			ptrs[aa . i_s],
			ptrs[aa . i_s+1]);
	pointer_set(2);	

	int2lcd(aa . s_i1+1,'^',0); 
	int2lcd(BAT_DAY_OF_ON[aa . s_i1],'!',0);
	sub_bgnd(sm_month[BAT_MONTH_OF_ON[aa . s_i1]],'@',0);
	int2lcd(BAT_YEAR_OF_ON[aa . s_i1],'#',0); 
	int2lcd(BAT_C_NOM[aa . s_i1],'$',0);
	int2lcd(BAT_RESURS[aa . s_i1],'%',0);
	}

else if(aa . i==iBatLogKe)
	{             
	if(av_j_si_max==0)
		{
		bgnd_par(	"  КОНТРОЛИ ЕМКОСТИ  ",
				"     БАТАРЕИ N!     ",
				" Журнал пуст        ",
				sm_exit);
		pointer_set(3);
		aa . s_i=0;
		aa . i_s=0;
		} 
	else if(av_j_si_max==1)
		{
		bgnd_par(	"  КОНТРОЛИ ЕМКОСТИ  ",
				"     БАТАРЕИ N!     ",
				" (                  ",sm_exit);
		aa . i_s=0;
		pointer_set(2);
		}	
	else
		{
		if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
		else if((aa . s_i-aa . i_s)>1) aa . i_s=aa . s_i-1;
		if(aa . i_s==(av_j_si_max-1)) 
			{
			bgnd_par( "  КОНТРОЛИ ЕМКОСТИ  ",
					"     БАТАРЕИ N!     ",
					" (                  ",
					sm_exit);
			}
		else
			{
			bgnd_par(	"  КОНТРОЛИ ЕМКОСТИ  ",
					"     БАТАРЕИ N!     ",
					" (                  ",
					" [                  ");
			}
		pointer_set(2);			 
		}
		
   	int2lcd(aa . s_i1+1,'!',0);
 	event_data2ind(content[aa . i_s],'(');
 	event_data2ind(content[aa . i_s+1],'[');
	}

else if(aa . i==iBatLogVz)
	{
	if(av_j_si_max==0)
		{
		bgnd_par(	"ВЫРАВНИВАЮЩИЕ ЗАРЯДЫ",
				"     БАТАРЕИ N!     ",
				" Журнал пуст        ",
				sm_exit);
		aa . s_i=0;
		aa . i_s=0;
		pointer_set(3);
		} 
	else if(av_j_si_max==1)
		{
		bgnd_par(	"ВЫРАВНИВАЮЩИЕ ЗАРЯДЫ",
				"     БАТАРЕИ N!     ",
				" (                  ",
				sm_exit);
		aa . i_s=0;
		pointer_set(2);
		}	
	else
		{
		if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
		else if((aa . s_i-aa . i_s)>1) aa . i_s=aa . s_i-1;
		if(aa . i_s==(av_j_si_max-1)) 
			{
			bgnd_par(	"ВЫРАВНИВАЮЩИЕ ЗАРЯДЫ",
					"     БАТАРЕИ N!     ",
					" (                  ",
					sm_exit);
			}

		else bgnd_par(	"ВЫРАВНИВАЮЩИЕ ЗАРЯДЫ",
					"     БАТАРЕИ N!     ",
					" (                  ",
					" [                  "); 
		pointer_set(2);			        
		}
   	int2lcd(aa . s_i1+1,'!',0);
 	event_data2ind(content[aa . i_s],'(');
 	event_data2ind(content[aa . i_s+1],'[');
	
	}
   
else if(aa . i==iBatLogWrk)
	{
	if(av_j_si_max==0)
		{
		bgnd_par(	"      РАЗРЯДЫ       ",
				"     БАТАРЕИ N!     ",
				" Журнал пуст        ",
				sm_exit);
		aa . s_i=0;
		aa . i_s=0;
		pointer_set(3);
		} 
	else if(av_j_si_max==1)
		{
		bgnd_par(	"      РАЗРЯДЫ       ",
				"     БАТАРЕИ N!     ",
				" (                  ",
				sm_exit);
		aa . i_s=0;
		pointer_set(2);
		}	

	else
		{
		if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
		else if((aa . s_i-aa . i_s)>1) aa . i_s=aa . s_i-1;
		if(aa . i_s==(av_j_si_max-1))
			{
			bgnd_par(	"      РАЗРЯДЫ       ",
					"     БАТАРЕИ N!     ",
					" (                  ",
					sm_exit);
			}
		else bgnd_par(	"      РАЗРЯДЫ       ",
					"     БАТАРЕИ N!     ",
					" (                  ",
					" [                  ");

		pointer_set(2);
		}

   	int2lcd(aa . s_i1+1,'!',0);
 	event_data2ind(content[aa . i_s],'(');
 	event_data2ind(content[aa . i_s+1],'[');

	

	} 
	
else if((aa . i==iSet_prl)||(aa . i==iK_prl)||(aa . i==iSpc_prl_vz)
	||(aa . i==iSpc_prl_ke)||(aa . i==iAusw_prl)||(aa . i==iPrltst))
	{
	bgnd_par("  Введите  пароль   ",sm_,sm_,sm_);
	int2lcdyx(parol[0],1,8,0);
     int2lcdyx(parol[1],1,9,0);
     int2lcdyx(parol[2],1,10,0);
     lcd_buffer[48+aa . s_i]='¤';
	}	
		
else if(aa . i==iPrl_bat_in_out)
	{
	if(BAT_IS_ON[aa . s_i1]==bisON)ptrs[0]="Для выведения бат.-и";
	else  ptrs[0]="Для введения батареи";
	bgnd_par(ptrs[0],"  наберите пароль   ",sm_,sm_);
	
     int2lcdyx(parol[0],2,8,0);
     int2lcdyx(parol[1],2,9,0);
     int2lcdyx(parol[2],2,10,0);
     lcd_buffer[68+aa . s_i]='¤';	
	}
	
else if(aa . i==iSet)
	{
     ptrs[0]=		" Стандартные        ";
	ptrs[1]=		" Время и дата       ";
     ptrs[2]=		" Структура          ";
     ptrs[3]=		" Мнемоника         y";
	ptrs[4]=		" Зв.сигн.   (       ";
	ptrs[5]=		" Отключение сигнала ";
	ptrs[6]=		"  аварии    )       ";
	ptrs[7]=		" АПВ источников     ";
	ptrs[8]=		" Паралл.работа z    ";
	ptrs[9]=		" T проверки   цепи  ";
     ptrs[10]=		" батареи     qмин.  ";
     ptrs[11]=		" Umax=       !В     ";
     ptrs[12]=		" dU=         ZВ     ";
     ptrs[13]=		" Uб0°=       @В     ";
     ptrs[14]=		" Uб20°=      #В     ";
     ptrs[15]=		" Uсигн=      ^В     ";
     ptrs[16]=		" Umin.сети=  &В     ";
	ptrs[17]=		" U0б=        >В     ";
	ptrs[18]=		" Iбк.=       jА     ";
     ptrs[19]=		" Iз.мах.=    JА     ";
     ptrs[20]=		" Imax=       ]A     ";
     ptrs[21]=		" Kimax=      {      ";
     ptrs[22]=		" Kвыр.зар.=    [    ";
     ptrs[23]=		" Tз.вкл.а.с. !с     ";
	ptrs[24]=		" tи.max=     $°C    ";
	ptrs[25]=		" tи.сигн=    z°C    ";
	ptrs[26]=		" tбат.max=   b°C    ";
	ptrs[27]=		" tбат.сигн=  X°C    ";
     ptrs[28]=		" Внешние датчики    ";
     ptrs[29]=		" Выход              ";
     ptrs[30]=		" Калибровки         "; 
     ptrs[31]=		" Тест               ";        
	
	if((aa . s_i-aa . i_s)>2)aa . i_s=aa . s_i-2;
	else if(aa . s_i<aa . i_s)aa . i_s=aa . s_i;
	bgnd_par("     УСТАНОВКИ      ",
			ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);

	pointer_set(1);	
	
	if(aa . i_s<18)
	     {
	     if(ZV_ON)sub_bgnd("ВКЛ.",'(',0);
	     else sub_bgnd("ВЫК.",'(',0);
	     if(AV_OFF_AVT)sub_bgnd("автом.",')',0);
	     else sub_bgnd("ручн.",')',0);
		if(PAR)sub_bgnd("ВКЛ.",'z',0);
	     else sub_bgnd("ВЫК.",'z',0);
	     if(MNEMO_ON==mnON)
	     	{
	     	sub_bgnd("через yс.",'y',-8);
	     	int2lcd(MNEMO_TIME,'y',0);
	     	}
	     else sub_bgnd("выкл.",'y',-4);
	     int2lcd(UMAX,'!',1);
	     int2lcd(DU,'Z',1);
	     int2lcd(UB0,'@',1);
	     int2lcd(UB20,'#',1);
	     int2lcd(USIGN,'^',0);
	     int2lcd(UMN,'&',0);
	     int2lcd(U0B,'>',1);
	     } 
	int2lcd(TMAX,'$',0);
	int2lcd(IKB,'j',2);
	int2lcd(KVZ,'[',3);
	int2lcd(IMAX,']',1);
	int2lcd(KIMAX,'{',1);
	int2lcd(IZMAX,'J',1); 
	int2lcd(TZAS,'!',0);
	int2lcd(TBAT,'q',0);
	int2lcd(TSIGN,'z',0); 
	int2lcd(TBATMAX,'b',0); 
	int2lcd(TBATSIGN,'X',0); 
	}

else if (aa . i==iDef)
	{ 
	ptrs[0]=" ИБЭП220/48-80А     ";
	ptrs[1]=" ИБЭП220/60-80А     ";
	ptrs[2]=" ИБЭП220/48-100А    ";
	ptrs[3]=" ИБЭП220/60-100А    ";
	ptrs[4]=" ИБЭП220/48-120А    ";
	ptrs[5]=" ИБЭП220/60-120А    ";
	ptrs[6]=sm_exit;
	if(bFL5)ptrs[default_temp]=sm_;
	
	if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
	else if((aa . s_i-aa . i_s)>2) aa . i_s=aa . s_i-2;

     bgnd_par("СТАНДАРТНЫЕ УСТ.-КИ ",ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);
	
	pointer_set(1);
	} 	
	        



else if(aa . i==iSet_T)
	{
	static char phase_cnt;
	if(++phase_cnt>=15)
	     {
	     phase_cnt=0;
	     if(++phase>=3)phase=0;
	     }
	ptrs[0]=sm_time;
	ptrs[1]=sm_;
	if(phase==0)ptrs[2]="     <> - выбор     ";
     if(phase==1)ptrs[2]="   ^v - установка   ";
     if(phase==2)ptrs[2]="     0  - выход     ";
	
	bgnd_par(" УСТАНОВКА  ВРЕМЕНИ ",ptrs[0],ptrs[1],ptrs[2]);
     if(aa . s_i==0)lcd_buffer[42]='^';
     else if(aa . s_i==1)lcd_buffer[45]='^';
     else if(aa . s_i==2)lcd_buffer[48]='^';
     else if(aa . s_i==3)lcd_buffer[51]='^';
     else if(aa . s_i==4)lcd_buffer[54]='^';
     else if(aa . s_i==5)lcd_buffer[58]='^';
  
 	int2lcd(sec__,'&',0);
 	int2lcd(min__,'^',0);
 	int2lcd(hour__,'%',0);
 	
 	int2lcd(day__,'<',0);
 	sub_bgnd(sm_month[month__],'>',0);
 	int2lcd(year__,'{',0);
 	if(bFL2)
 	     {
 	     lcd_buffer[find(':')]=' ';
 	     lcd_buffer[find(':')]=' ';
 	     }  
	}  

else if(aa . i==iStr)
	{
	ptrs[0]=" Батарей           @";
	ptrs[1]=" Источников        !";
	ptrs[2]=" Инверторов        ^";	
	ptrs[3]=" Датчиков темпер.  #";
	ptrs[4]=" Сухих контактов   $";
	ptrs[5]=" Выход                   ";
	
	if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
	else if((aa . s_i-aa . i_s)>2) aa . i_s=aa . s_i-2;
	bgnd_par("      СТРУКТУРА     ",ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);
	
	pointer_set(1);

	int2lcd(NUMBAT,'@',0);		
	int2lcd(NUMIST,'!',0); 
	int2lcd(NUMINV,'^',0);
	int2lcd(NUMDT,'#',0);
	int2lcd(NUMSK,'$',0);
	}    

else if (aa . i==iApv)
	{ 
	ptrs[0]=			" АПВ 1й уровень !   ";
	if(APV_ON1!=apvON)
	     {
	     ptrs[1]=		" Выход              ";
	     ptrs[2]=sm_;
	     ptrs[3]=sm_;
	     ptrs[4]=sm_;
	     simax=1;
	     }
	else
	     {
	     if(APV_ON2!=apvON)
	          {
	          ptrs[1]=" АПВ 2й уровень @   ";
	          ptrs[2]=" Выход              ";
	          ptrs[3]=sm_;
	          ptrs[4]=sm_;
	          simax=2;
	          }
	     else 
	          {
               ptrs[1]=" АПВ 2й уровень @   ";
	          ptrs[2]=" Период АПВ2     #ч.";
	          ptrs[3]=" Выход              ";
	          ptrs[4]=sm_;
	          simax=3;	          
	          }     
	     }     
	
	if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
	else if((aa . s_i-aa . i_s)>2) aa . i_s=aa . s_i-2;	
     bgnd_par("   АПВ ИСТОЧНИКОВ   ",ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);
	
	pointer_set(1);
	if(APV_ON1==apvON)sub_bgnd("ВКЛ.",'!',0);
	else sub_bgnd("ВЫКЛ.",'!',-1);
	
	if(APV_ON2==apvON)
	     {
	     sub_bgnd("ВКЛ.",'@',0);
	     int2lcd(APV_ON2_TIME,'#',0);
	     }
	else sub_bgnd("ВЫКЛ.",'@',-1);	
     
 	} 


else if(aa . i==iK)
	{
	char i;
	i=0;
	
	ptrs[i++]=" Сеть               ";
	if(NUMBAT)
     ptrs[i++]=" Батареи            ";
	if(NUMIST)
	ptrs[i++]=" БПС                ";
	if(NUMINV)
     ptrs[i++]=" Инверторы          ";
	ptrs[i++]=" Нагрузка           ";
     if(NUMDT)
     ptrs[i++]=" Внешние датчики    ";
     ptrs[i++]=" Выход              ";
     ptrs[i++]="                    ";
     ptrs[i++]="                    ";

	if((aa . s_i-aa . i_s)>2)aa . i_s=aa . s_i-2;
	else if(aa . s_i<aa . i_s)aa . i_s=aa . s_i;
	bgnd_par("     КАЛИБРОВКА     ",
			ptrs[aa . i_s],
			ptrs[aa . i_s+1],
			ptrs[aa . i_s+2]);

	pointer_set(1);	 
	}    	

else if(aa . i==iK_net)
	{
	ptrs[0]=" U =     @В         ";
     ptrs[1]=" Выход              ";
	ptrs[2]="                    ";
	
	if((aa . s_i-aa . i_s)>2)aa . i_s=aa . s_i-2;
	else if(aa . s_i<aa . i_s)aa . i_s=aa . s_i;
	bgnd_par("   КАЛИБРОВКА СЕТИ  ",ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);

	pointer_set(1);	
	int2lcd(net_U,'@',0);
	
	
	
     }


else if(aa . i==iK_load)
	{
	ptrs[0]=" U =     @В         ";
     ptrs[1]=" Выход              ";
	ptrs[2]="                    ";
	
	if((aa . s_i-aa . i_s)>2)aa . i_s=aa . s_i-2;
	else if(aa . s_i<aa . i_s)aa . i_s=aa . s_i;
	bgnd_par(		" КАЛИБРОВКА НАГРУЗКИ",
				ptrs[aa . i_s],
				ptrs[aa . i_s+1],
				ptrs[aa . i_s+2]);

	pointer_set(1);	
	int2lcd(load_U,'@',1);
     }

     
else if(aa . i==iK_bat_sel)
	{
	ptrs[0]=						" Батарея N1         ";
     ptrs[1]=						" Батарея N2         ";
     if(BAT_IS_ON[0]!=bisON)ptrs[0]=	" Батарея N2         ";
	ptrs[0+NUMBAT]=				" Выход              ";
	ptrs[1+NUMBAT]=				"                    ";
	ptrs[2+NUMBAT]=				"                    ";

	if((aa . s_i-aa . i_s)>2)aa . i_s=aa . s_i-2;
	else if(aa . s_i<aa . i_s)aa . i_s=aa . s_i;
	bgnd_par(" КАЛИБРОВКА БАТАРЕЙ ",ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);
	pointer_set(1);
	
     }     

else if(aa . i==iK_bat)
	{
	ptrs[0]=		" Uбат =     @В      ";
	ptrs[1]=		" откалибруйте Uбат  ";
	ptrs[2]=		"  нажатием љ или њ  ";
     ptrs[3]=		" Iбат =     #А      ";
     if(phase==0)
          {
          ptrs[4]=	"   нажмите ¤ для    ";
          ptrs[5]=	"калибровки нуля Iбат";
          }
     else          
          {
          ptrs[4]=	" откалибруйте Iбат  ";
          ptrs[5]=	"  нажатием љ или њ  ";
          }
     if(bat[aa . s_i1]._nd)
     	{
     	ptrs[6]=		" Датчик температуры ";
     	ptrs[7]=		"     неисправен     ";
     	ptrs[8]=		"  или неподключен.  ";
     	}
     else
     	{	     
     	ptrs[6]=		" tбат =    $°C      ";
     	ptrs[7]=		" откалибруйте tбат  ";
     	ptrs[8]=		"  нажатием љ или њ  ";
     	}
     ptrs[9]=		" Выход              ";
     ptrs[10]=		"                    ";
     ptrs[11]=		"                    ";

	bgnd_par(		" КАЛИБРОВКА БАТ. N! ",
				ptrs[aa . i_s],
				ptrs[aa . i_s+1],
				ptrs[aa . i_s+2]);
     
     if(aa . s_i==0)
     	{
     	mess_send(205,206,0xffff,10);
     	mess_send(200,202,(1<<(1-aa . s_i1)),10);
     	
     	}
     
     if(aa . s_i==3)
     	{
     	if(phase==0)
     		{
     		mess_send(210,100,0,10);
			mess_send(200,202,(1<<aa . s_i1),10);
     		
     		}
     	else if(phase==1)
     		{
			mess_send(205,206,0xffff,10);
			mess_send(200,202,(1<<(1-aa . s_i1)),10);
     		
   			}
     		
     	}

     if(aa . s_i==6)
     	{
   		
    		
     		
     	}
	
	if((aa . s_i==0)||(aa . s_i==1)||(aa . s_i==2))aa . i_s=0;
	else if((aa . s_i==3)||(aa . s_i==4)||(aa . s_i==5))aa . i_s=3;
	else if((aa . s_i==6)||(aa . s_i==7)||(aa . s_i==8))aa . i_s=6;
	else aa . i_s=9;
	


	pointer_set(1);	
	int2lcd(aa . s_i1+1,'!',0);
	int2lcd(bat[aa . s_i1]._Ub,'@',1);
	int2lcd_mmm(bat[aa . s_i1]._Ib,'#',2);
	int2lcd_mmm(bat[aa . s_i1]._Tb,'$',0);
	
	
	   
 
		    
         
	
	

	
	
	
	
 

	
	
	}  	

else if(aa . i==iK_bps_sel)
	{
	ptrs[0]=						" БПС N1             ";
     ptrs[1]=						" БПС N2             ";
     ptrs[2]=						" БПС N3             ";
	ptrs[3]=						" БПС N4             ";
     ptrs[4]=						" БПС N5             ";
     ptrs[5]=						" БПС N6             ";
	ptrs[6]=						" БПС N7             ";
     ptrs[7]=						" БПС N8             ";
     ptrs[8]=						" БПС N9             ";
	ptrs[9]=						" БПС N10            ";
     ptrs[10]=						" БПС N11            ";
     ptrs[11]=						" БПС N12            ";               
	ptrs[NUMIST]=					" Выход              ";
	ptrs[1+NUMIST]=				"                    ";
	ptrs[2+NUMIST]=				"                    ";

	if((aa . s_i-aa . i_s)>2)aa . i_s=aa . s_i-2;
	else if(aa . s_i<aa . i_s)aa . i_s=aa . s_i;
	bgnd_par("  КАЛИБРОВКА БПСов  ",ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);
	pointer_set(1);
	
     }     

else if(aa . i==iK_bps)
	{
	
	ptrs[0]=" Uист =    @В       ";
     ptrs[1]=" откалибруйте Uист  ";
     ptrs[2]="  нажатием љ или њ  "; 
	ptrs[3]=" Uнагр =   #В       ";
     ptrs[4]=" откалибруйте Uнагр ";
     ptrs[5]="  нажатием љ или њ  ";
	ptrs[6]=" Uавтон =   $В      ";
	if(bFL_)
		{
		ptrs[7]=" установите Uавтон  ";
     	ptrs[8]="  нажатием љ или њ  ";
     	}
     else 
     	{
		ptrs[7]=" удерживайте ¤ для  ";
     	ptrs[8]="    запоминания     ";     	
     	}	
	ptrs[9]=" Iист =     %А      ";
	if(phase==0)
          {
          ptrs[10]=	"   нажмите ¤ для    ";
          ptrs[11]=	"калибровки нуля Iист";
          }
     else
     	{
          ptrs[10]=" откалибруйте Iист  ";
          ptrs[11]="  нажатием љ или њ  ";     	
     	} 
     	
     ptrs[12]=" tист =   ^°C       ";    
	ptrs[13]=" откалибруйте tист  ";
     ptrs[14]="  нажатием љ или њ  ";
     ptrs[15]=sm_exit;
     ptrs[16]=sm_;
     ptrs[17]=sm_;     	     	    
	

     if((aa . s_i==0)||(aa . s_i==1)||(aa . s_i==2))aa . i_s=0;
	else if((aa . s_i==3)||(aa . s_i==4)||(aa . s_i==5))aa . i_s=3;
	else if((aa . s_i==6)||(aa . s_i==7)||(aa . s_i==8))aa . i_s=6;
	else if((aa . s_i==9)||(aa . s_i==10)||(aa . s_i==11))aa . i_s=9;
	else if((aa . s_i==12)||(aa . s_i==13)||(aa . s_i==14))aa . i_s=12;	
	else aa . i_s=15;
	
	bgnd_par(" КАЛИБРОВКА БПС N! ",ptrs[aa . i_s],ptrs[aa . i_s+1],ptrs[aa . i_s+2]);

	pointer_set(1);	
	int2lcd(aa . s_i1+1,'!',0);
	int2lcd(bps[aa . s_i1]._Uii,'@',1);
	int2lcd(bps[aa . s_i1]._Uin,'#',1);
	int2lcd(U_AVT,'$',1);
	int2lcd(bps[aa . s_i1]._Ii,'%',1);
	int2lcd(bps[aa . s_i1]._Ti,'^',0); 
	 
	
     if((aa . s_i==0)||(aa . s_i==3))
		{
		mess_send(205,208,(1<<aa . s_i1),10);
		mess_send(200,201,0,10);
	    	mess_send(225,229,1000,10);
          }
     if(aa . s_i==6)
		{
          mess_send(205,208,(1<<aa . s_i1),10);
          mess_send(200,201,0,40);
          mess_send(190,191,U_AVT,10);
	    	mess_send(225,230,0,10);

          }

     if(aa . s_i==9)
		{
		if(phase==0)
			{
          	mess_send(205,208,~(1<<aa . s_i1),10);
          	}
      	else if(phase==1)
			{
          	mess_send(205,208,(1<<aa . s_i1),10);
			mess_send(200,201,0,10);
          	}
          mess_send(225,229,1000,10);
          }
	
    	if(aa . s_i==12)
		{
          }	
          
          
	if(mess_find( (215)) && (mess_data[0]==217) )
		{
		show_mess("     Установка      ",
	          	"    напряжения      ",
	          	" автономной работы  ",
	          	"    произведена     ",3000);
		}	     
	     
	
	






 


int2lcdyx(load_U,0,5,0); 
int2lcdyx(cntrl_stat,0,10,0); 

int2lcdyx(u_necc,0,19,0);  
	 }			
if(aa . i==iDeb)
     {
     if(aa . s_i==0)
     	{
     	bgnd_par("     Источники      ",
     	         "                    ",
     	         "                    ",
     	         "                    ");
		int2lcdyx(( ((*((volatile unsigned long *) 0xE0048008)) & ((0xffffffff>>(32-8))<<16)) >> 16),0,15,0);
		int2lcdyx(( ((*((volatile unsigned long *) 0xE0048008)) & ((0xffffffff>>(32-8))<<24)) >> 24),0,19,0);
		
		int2lcdyx(cntrl_stat,0,3,0);

		int2lcdyx(aa . s_i1+1,1,0,0);
		int2lcdyx(aa . s_i1+2,2,0,0);
		int2lcdyx(aa . s_i1+3,3,0,0);
		
		
		int2lcdyx(bps[aa . s_i1  ]._cnt,1,2,0);
		int2lcdyx(bps[aa . s_i1+1]._cnt,2,2,0);
		int2lcdyx(bps[aa . s_i1+2]._cnt,3,2,0);		
		
	

 			
		
		char2lcdhyx(bps[aa . s_i1  ]._flags_tu,1,8);
		char2lcdhyx(bps[aa . s_i1+1]._flags_tu,2,8);
		char2lcdhyx(bps[aa . s_i1+2]._flags_tu,3,8);

		int2lcdyx(bps[aa . s_i1  ]._vol_u,1,12,0);
		int2lcdyx(bps[aa . s_i1+1]._vol_u,2,12,0);
		int2lcdyx(bps[aa . s_i1+2]._vol_u,3,12,0);		


		char2lcdhyx(bps[aa . s_i1]._flags_tm,1,15);
		char2lcdhyx(bps[aa . s_i1+1]._flags_tm,2,15);
		char2lcdhyx(bps[aa . s_i1+2]._flags_tm,3,15);	

		char2lcdhyx(bps[aa . s_i1]._Ii,1,19);
		char2lcdhyx(bps[aa . s_i1+1]._Ii,2,19);
		char2lcdhyx(bps[aa . s_i1+2]._Ii,3,19);
	






 



     	}     

    	else if(aa . s_i==1) 
     	{
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");
      













 


      	int2lcdyx(net_buff[0],0,5,0);
   		int2lcdyx(net_buff[3],0,12,0);
   		int2lcdyx(net_buff[6],0,19,0);
   
      	int2lcdyx(net_buff[9],1,5,0);
   		int2lcdyx(net_buff[12],1,12,0);
   		int2lcdyx(net_buff[15],1,19,0);
   		
      	int2lcdyx(net_buff[18],2,5,0);
   		int2lcdyx(net_buff[21],2,12,0);
   		int2lcdyx(net_buff[24],2,19,0);

      	int2lcdyx(net_buff[27],3,5,0);
   		int2lcdyx(net_buff[30],3,12,0);
   		int2lcdyx(net_buff[31],3,19,0);


     	}
 
 

 

    else if(aa . s_i==2)
     	{
     	bgnd_par("КБ                  ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     		    
     	int2lcdyx(TBAT*60,0,6,0);
    		int2lcdyx(main_kb_cnt,0,11,0);
     	
		
		int2lcdyx(cntrl_stat,0,19,0);
		int2lcdyx(cntrl_stat_old,0,15,0);

		int2lcdyx(kb_cnt_1lev,1,2,0);
     	int2lcdyx(kb_cnt_2lev,1,5,0);
		int2lcdyx(kb_full_ver,1,8,0);

		int2lcdyx(num_of_wrks_bps,1,19,0);

		lcd_buffer[45]='a';
		int2lcd_mmm(bat[0]._Ib,'a',0);
		int2lcdyx(kb_start[0],2,9,0);
		int2lcdyx(bat[0]._av,2,15,0);
		lcd_buffer[65]='a';
		int2lcd_mmm(bat[1]._Ib,'a',0);
		int2lcdyx(kb_start[1],3,9,0);
		int2lcdyx(bat[1]._av,3,15,0);
    
    











 
    	}  

	else if(aa . s_i==3)
     	{
     	bgnd_par("*                   ",
     	         "                    ",
     	         "                    ",
     	         "                    ");
		int2lcdyx(load_U,0,4,0);
		int2lcdyx(load_I,1,4,0);
		lcd_buffer[44]='a';
		int2lcd_mmm((bat[0]._Ib)/10,'a',1);
		lcd_buffer[64]='a';
		int2lcd_mmm((bat[1]._Ib)/10,'a',1);

 		int2lcdyx(u_necc,0,8,0);

		
		
		lcd_buffer[14]='.';
		lcd_buffer[34]='.';
		int2lcdyx(Isumm,0,15,1);		
		int2lcdyx(Isumm_,1,15,1);


		int2lcdyx(cntrl_stat,0,19,0);
		int2lcdyx(num_necc,1,19,0);
		
		
		  

		 
		
		
		
 

	



 

	
 

	
		
		

	

		
		


 
 
 
 
 
     	

     	
     	
     	
     	
    
    
 
 
 
		}

	else if(aa . s_i==4)
     	{
     	bgnd_par(" АВАРИИ             ",
     	         "                    ",
     	         "                    ",
     	         "                    ");

		int2lcdyx(main_10Hz_cnt,0,7,0);
		int2lcdyx(bat[0]._av,0,10,0);
		int2lcdyx(bat[1]._av,0,12,0);
		char2lcdhyx(rele_stat,0,19);

 		long2lcdhyx(avar_stat,1,7);
		long2lcdhyx(avar_stat_old,2,7);
		long2lcdhyx(avar_ind_stat,3,7);

		long2lcdhyx(avar_stat_new,2,19);
		long2lcdhyx(avar_stat_offed,3,19);



	
	









 

		}
   else if(aa . s_i==5)
     	{
     	bgnd_par("                    ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     		    
     	int2lcdyx(ad7705_buff_[0],1,5,0);
     	int2lcdyx(Kibat0[0],1,12,0);
     	int2lcdyx(Kibat1[0],1,17,0);
 
     	int2lcdyx(ad7705_buff_[1],2,5,0);
     	int2lcdyx(Kibat0[1],2,12,0);
     	int2lcdyx(Kibat1[1],2,17,0);


		lcd_buffer[70]='a';
		int2lcd_mmm(bat[0]._Ib,'a',0);

		
		lcd_buffer[78]='a';
		int2lcd_mmm(bat[1]._Ib,'a',0);

		int2lcdyx(samokalibr_cnt,3,4,0);

    		}
    else if(aa . s_i==6)
     	{
     	bgnd_par("                    ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     		    
     	int2lcdyx(ad7705_buff[0][0],0,4,0);
     	int2lcdyx(ad7705_buff[0][1],0,9,0);
     	int2lcdyx(ad7705_buff[0][2],0,14,0);
     	int2lcdyx(ad7705_buff[0][3],0,19,0);
     	int2lcdyx(ad7705_buff[0][4],1,4,0);
     	int2lcdyx(ad7705_buff[0][5],1,9,0);
     	int2lcdyx(ad7705_buff[0][6],1,14,0);
     	int2lcdyx(ad7705_buff[0][7],1,19,0);
     	int2lcdyx(ad7705_buff[0][8],2,4,0);
     	int2lcdyx(ad7705_buff[0][9],2,9,0);
     	int2lcdyx(ad7705_buff[0][10],2,14,0);
     	int2lcdyx(ad7705_buff[0][11],2,19,0);
     	int2lcdyx(ad7705_buff[0][12],3,4,0);
     	int2lcdyx(ad7705_buff[0][13],3,9,0);
     	int2lcdyx(ad7705_buff[0][14],3,14,0);
     	int2lcdyx(ad7705_buff[0][15],3,19,0);
    	}  		  		
		     	
  















 


 























 



 

















 

     	
     	


 
		   
     	







 
     	
     	
     	
     	










 
     	
     	
     	
     	
     	









 
      


 
  
 
 
  











 
     	


 
  
 
  
  
 
    
   	
     	
 











        	
     		



 
     		    
     








 
    









































    	    	  	
 
 
 
 
 
 










 
	    	       	
		
















   	       			
     }

else if((aa . i==iAv_view)||(aa . i==iAv_view_avt))
	{
	unsigned short tempUI,tempUI_;
    	unsigned long tempUL;
	
	bgnd_par(sm_,sm_,sm_,sm_);
	if(aa . s_i==0)
		{	
		if(avar_stat&0x00000001)
			{
			bgnd_par(	"    Авария  сети    ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			int2lcd(net_U,']',0);
			}
    		else 
			{
	    		bgnd_par(	"    Авария  сети    ",
	    				"     устранена      ",
					sm_,sm_); 
			}
		}
	else if((aa . s_i==1)||(aa . s_i==2))
		{
		if(avar_stat&(1<<aa . s_i))
			{
			bgnd_par(	"   Авария бат. N!   ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			}
    		else 
			{
	    		bgnd_par(	"   Авария бат. N!   ",
	    				"     устранена      ",
					sm_,sm_); 
		
		     }
		int2lcd(aa . s_i,'!',0);
		} 
     
	else if((aa . s_i>=3)&&(aa . s_i<=14))
		{
		if((aa . s_i-2)<=9)					ptrs[0]=	"   Авария БПС N+    ";
		else 							ptrs[0]=	"   Авария БПС N +   ";
		if(bps[aa . s_i-3]._last_avar==0)		ptrs[1]=	"     перегрев!!!    ";
		else if(bps[aa . s_i-3]._last_avar==1)	ptrs[1]=	"  завышено Uвых!!!  ";	
		else if(bps[aa . s_i-3]._last_avar==2)	ptrs[1]=	"  занижено Uвых!!!  ";	
		else if(bps[aa . s_i-3]._last_avar==3)	ptrs[1]=	"    отключился!!!   ";
		if(avar_stat&(1<<aa . s_i)) 			ptrs[2]=	"    не устранена    ";
		else								ptrs[2]=	"     устранена      ";	
										ptrs[3]=	"                    ";

		bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
		int2lcd((aa . s_i-2),'+',0);
          
		

		} 
		
	else if(aa . s_i==4)
		{ 

		}

	else if(aa . s_i==5)
		{

		}

	else if(aa . s_i==6)
		{

		}

	else if(aa . s_i==7)
		{

		} 
		
	else if(aa . s_i==8)
		{

		}

	else if(aa . s_i==9)
		{

		}

	else if(aa . s_i==10)
		{

		}
	    		     
	else if(aa . s_i==11)
		{

		} 
		
	else if(aa . s_i==12)
		{

		}

	else if(aa . s_i==13)
		{

		}

	else if(aa . s_i==14)
		{

		}

	else if(aa . s_i==15)
		{

		} 
					
	} 
	
else if(aa . i==iAvz)
	{
	
 	if(AVZ==AVZ_1) 		ptrs[0]=	" раз в месяц        ";
	else if(AVZ==AVZ_2) 	ptrs[0]=	" раз в 2 месяца     ";
	else if(AVZ==AVZ_3) 	ptrs[0]=	" раз в 3 месяца     "; 
	else if(AVZ==AVZ_6) 	ptrs[0]=	" раз в полгода      ";
	else if(AVZ==AVZ_12) 	ptrs[0]=	" раз в год          ";
	else 				ptrs[0]=	" выключен           "; 
	
	ptrs[1]=						" Длительность    (ч.";
	if(AVZ!=AVZ_OFF)
		{
		ptrs[2]=					" очередное включение";
		ptrs[3]=					"  0%  &0^  0@:0#:0$ ";
		ptrs[4]=					sm_exit;
		}
	else ptrs[2]=						sm_exit;

	if(aa . s_i<aa . i_s) aa . i_s=aa . s_i;
	else if((aa . s_i-aa . i_s)>1) aa . i_s=aa . s_i-1;
	if((aa . s_i==2)&&(AVZ!=AVZ_OFF)) aa . i_s=2;
	
	bgnd_par(	"   АВТОМАТИЧЕСКИЙ   ",
			"ВЫРАВНИВАЮЩИЙ ЗАРЯД ",
			ptrs[aa . i_s],
			ptrs[aa . i_s+1]);

	pointer_set(2);
		
	int2lcd(HOUR_AVZ,'@',0);
	int2lcd(MIN_AVZ,'#',0);
	int2lcd(SEC_AVZ,'$',0);
	int2lcd(DATE_AVZ,'%',0);
	int2lcd(YEAR_AVZ,'^',0);

	sub_bgnd(sm_month[MONTH_AVZ],'&',-2);

	int2lcd(AVZ_TIME,'(',0);
	
	}
	        	
	 









 





















}


#line 3029 "uku206.c"




#line 3045 "uku206.c"


void but_drv(void)
{

but_n=(*((volatile unsigned long *) 0xE0028010))|(0xFFFFFFFFUL&(~(1UL<<16))&(~(1UL<<17))&(~(1UL<<18))&(~(1UL<<19))&(~(1UL<<20)));
if((but_n==0xffffffffUL)||(but_n!=but_s))
 	{
 	speed=0;
 
   	if (((but0_cnt>=4)||(but1_cnt!=0))&&(!l_but))
  		{
   	     n_but=1;
          but=*(((char*)&but_s)+2);

          }
   	if (but1_cnt>=but_onL_temp)
  		{
   	     n_but=1;
 
          but=*(((char*)&but_s)+2)&0x7f;
          }
    	l_but=0;
   	but_onL_temp=20;
    	but0_cnt=0;
  	but1_cnt=0;          
     goto but_drv_out;
  	}
if(but_n==but_s)
 	{
  	but0_cnt++;
  	if(but0_cnt>=4)
  		{
   		but0_cnt=0;
   		but1_cnt++;
   		if(but1_cnt>=but_onL_temp)
   			{              
    			but=*(((char*)&but_s)+2)&0x7f;;
    			but1_cnt=0;
    			n_but=1;
    			     
    			l_but=1;
			if(speed)
				{
    				but_onL_temp=but_onL_temp>>1;
        			if(but_onL_temp<=2) but_onL_temp=2;
				}    
   			}
  		}
 	}
but_drv_out: 
but_s=but_n;



(*((volatile unsigned long *) 0xE002C014))&=~(1UL<<((16-16)*2))&~(1UL<<(((16-16)*2)+1))
	   &~(1UL<<((17-16)*2))&~(1UL<<(((17-16)*2)+1))
	   &~(1UL<<((18-16)*2))&~(1UL<<(((18-16)*2)+1))
	   &~(1UL<<((19-16)*2))&~(1UL<<(((19-16)*2)+1))
	   &~(1UL<<((20-16)*2))&~(1UL<<(((20-16)*2)+1));
(*((volatile unsigned long *) 0xE0028018))&=~(1UL<<16)&~(1UL<<17)&~(1UL<<18)&~(1UL<<19)&~(1UL<<20);
	   
}



void but_an(void)
{
signed short temp_SS;
signed short deep,i,cap,ptr;
char av_head[4];
if(!n_but)goto but_an_end;

av_beep=0x0000;
av_rele=0x0000;


























































 

if(but==252)
     {
     if(aa . i!=iDeb)
          {
          b[ptr_ind++]=aa;
          aa . i=iDeb;
          aa . s_i=0;
          }
     else 
          {
          aa=b[--ptr_ind];
          }     
     }

else if(aa . i==iDeb)
	{
	if(but==247)
		{
		aa . s_i++;
		aa . i_s=0;
		gran_ring_char(&aa . s_i,0,7);
		}
	else if(but==251)
		{
		aa . s_i--;
		aa . i_s=0;
		gran_ring_char(&aa . s_i,0,7);
		}
		
	else if(aa . s_i==0)
		{
		if(but==254)
	     	{
	     	aa . s_i1--;
	     	gran_char(&aa . s_i1,0,NUMIST);
	     	}
		if(but==253)
	     	{
	     	aa . s_i1++;
	     	gran_char(&aa . s_i1,0,NUMIST);
	     	}
	     
		if(but==239)
	     	{
	     	(*((volatile unsigned long *) 0xE0048008)) = ( ((*((volatile unsigned long *) 0xE0048008)) & ~((0xffffffff>>(32-8))<<24)) | (3 << 24) );
			(*((volatile unsigned long *) 0xE0048000))=0;
			 bOUT_FREE2=1;
	     	}
			
		}	
     else if(but==254)
	     {
	     aa . i_s--;
	     gran_char(&aa . i_s,0,4);
	     
	     }	
     else if(but==253)
	     {
	     aa . i_s++;
	     gran_char(&aa . i_s,0,4); 
	     
	     }	
     else if(but==239)
         	{
          
          can2_out(1,2,3,4,5,6,7,8);
          }   
          
     else if(but==111)
         	{
          
          can1_out_adr(TXBUFF,3);
          }                      				
	}

else if(aa . i==iMn)
	{
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,8+NUMBAT+NUMIST+NUMINV+(NUMEXT!=0));
		}
		
	else if(but==125)
		{
		
	     
	     
		}

	else if(but==126)
		{
		
	     
	     
		}
		
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,8+NUMBAT+NUMIST+NUMINV+(NUMEXT!=0));
		}	

	else if(but==251)
		{
		aa . i=iMn;
		aa . s_i=0;
		}
		
	else if(but==239)
		{
		if(aa . s_i==0)
			{
			if(avar_ind_stat)
				{
				
				
				tree_up(iAv_view,0,0,0);
				while(!(avar_ind_stat&(1<<aa . s_i)))
					{
					aa . s_i++;
					if(aa . s_i>=32)
						{
						tree_down(0,0);
						avar_ind_stat=0;
						}
					}
















 
				}																							
			}
		else if((aa . s_i>0)&&(aa . s_i<=NUMBAT))
		    	{
		    	if(BAT_IS_ON[0]!=bisON)tree_up(iBat,0,0,1);
		    	else tree_up(iBat,0,0,aa . s_i-1);
		    	}
		else if((aa . s_i>NUMBAT)&&(aa . s_i<=(NUMBAT+NUMIST)))
		    	{
		    	tree_up(iBps,0,0,aa . s_i-(1+NUMBAT));
		    	}
		else if((aa . s_i>(NUMBAT+NUMIST))&&(aa . s_i<=(NUMBAT+NUMIST+NUMINV)))
		    	{
		    	tree_up(iBps,0,0,aa . s_i-(1+NUMBAT+NUMIST));
		    	}
		else if(aa . s_i==(1+NUMBAT+NUMIST+NUMINV))
			{
			tree_up(iNet,0,0,0);
		     ret(1000);
			}
		else if(aa . s_i==(2+NUMBAT+NUMIST+NUMINV))
			{
			tree_up(iLoad,0,0,0);
		     ret(1000);
			}
		else if((aa . s_i==(3+NUMBAT+NUMIST+NUMINV))&&(NUMEXT))
			{
			tree_up(iExtern,0,0,0);
		     ret(1000);
			}

		else if(aa . s_i==(3+NUMBAT+NUMIST+NUMINV+(NUMEXT!=0)))
			{
			tree_up(iSpc,0,0,0);
		     ret(1000);
			}

		else if(aa . s_i==(4+NUMBAT+NUMIST+NUMINV+(NUMEXT!=0)))
			{
			tree_up(iSet_prl,0,0,0);
		     ret(50);
		     parol_init();
			}
		else if(aa . s_i==(5+NUMBAT+NUMIST+NUMINV+(NUMEXT!=0)))
			{
			tree_up(iLog,0,0,0);
		     ret(1000);
			}
		else if(aa . s_i==(7+NUMBAT+NUMIST+NUMINV+(NUMEXT!=0)))
			{
			tree_up(iBatLog,0,0,0);
		     ret(1000);
			}
		else if(aa . s_i==(8+NUMBAT+NUMIST+NUMINV+(NUMEXT!=0)))
			{
			tree_up(iBatLog,0,0,1);
		     ret(1000);
			}
		}
    	
     	
	else if(but==247)
		{
		aa . i=iBat;
		aa . s_i=0;
		}		
		
				
	else if(aa . s_i==100)
		{
		if(but==239)
		     {
		     tree_up(iBat,0,0,0);
		     ret(1000);
		     }
		}
     else if(aa . s_i==20)
		{
		if(but==239)
		     {
		     tree_up(iBps,0,0,0);
		     ret(1000);
		     }
		}
     else if(aa . s_i==30)
		{
		if(but==239)
		     {
		     tree_up(iBps,0,0,1);
		     ret(1000);
		     }
		}		

     else if(aa . s_i==40)
		{
		if(but==239)
		     {
		     tree_up(iLoad,0,0,0);
		     ret(1000);
		     }
		}		

     else if(aa . s_i==50)
		{
		if(but==239)
		     {
		     tree_up(iNet,0,0,0);
		     ret(1000);
		     }
		}	

     else if(aa . s_i==60)
		{
		if(but==239)
		     {

		     tree_up(iSpc,0,0,0);
		     ret(1000);
		     }
		}	

     else if(aa . s_i==70)
		{
		if(but==239)
		     {
		     tree_up(iJAv_sel,0,0,0);
		     ret(1000);
		     }
		}	



    	else if(aa . s_i==90)
		{
		if(but==239)
		     {
			tree_up(iAusw,0,0,0);
		     ret(1000);
			}
		}	

 
     else if(aa . s_i==110)
		{
		if(but==239)
		     {
	
	
			}
		}		
     else if(aa . s_i==7+NUMBAT+NUMIST+NUMINV)
		{
		if(but==239)
		     {
			aa . s_i=0;
			}
		}	
		
	else if(aa . s_i==8+NUMBAT+NUMIST+NUMINV)
		{
		if(but==239)
		     {
			tree_up(iJ_bat,0,0,0);
		     ret(1000);
			}
		}		
     else if(aa . s_i==9+NUMBAT+NUMIST+NUMINV)
		{
		if(but==239)
		     {
			tree_up(iJ_bat,0,0,1);
		     ret(1000);
			}
		}			
				
	}

else if(aa . i==iBat)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,4);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,4);
		}
	else if((but==251)||((aa . s_i==4)&&(but==239)))
	     {
	     tree_down(0,0);
	     ret(0);
	     }
	else if(but==125)
		{
		aa . s_i=4;
		}		     
     }

else if(aa . i==iBps)
	{
	ret_ind(0,0,0);
	if (but==254)
		{      
		aa . s_i--;
		if(aa . s_i==3)aa . s_i=1;
		else if(aa . s_i==1)aa . s_i=0;
		gran_char(&aa . s_i,0,simax);
		}
		
	else if (but==253)
		{
		aa . s_i++;
		if(aa . s_i<3)aa . s_i=3;
		gran_char(&aa . s_i,0,simax);
		}
		
	else if((but==239)&&(aa . s_i==4))
		{
		can2_out(aa . s_i1,aa . s_i1,0x16,0x63,0,0,0,0);
		}
				
	else if(((but==239)&&(aa . s_i==5))||(but))
		{
	     tree_down(0,0);
	     ret(0);
		}	
		
	}		
else if(aa . i==iNet)
	{
	ret(1000);
	if((but==251)||(but==239))
	     {
	     tree_down(0,0);
	     ret(0);
	     }
	}
else if(aa . i==iLoad)
	{
	ret(1000);
	if((but==251)||(but==239))
	     {
	     tree_down(0,0);
	     ret(0);
	     }
	}	

else if((aa . i==iPrl_bat_in_out)||(aa . i==iSet_prl)||(aa . i==iK_prl)
	||(aa . i==iSpc_prl_vz)||(aa . i==iSpc_prl_ke)||(aa . i==iAusw_prl)
	||(aa . i==iPrltst))
	{
	ret(50);
	if(but==247)
		{
		aa . s_i++;
		gran_ring_char(&aa . s_i,0,2);
		}
	else if(but==251)
		{
		aa . s_i--;
		gran_ring_char(&aa . s_i,0,2);
		}	
	else if(but==254)
		{
		parol[aa . s_i]++;
		gran_ring_char(&parol[aa . s_i],0,9);
		}	
	else if(but==253)
		{
		parol[aa . s_i]--;
		gran_ring_char(&parol[aa . s_i],0,9);
		}	
	else if(but==239)
		{
		unsigned short tempU;
		tempU=parol[2]+(parol[1]*10U)+(parol[0]*100U);
		
		if(aa . i==iPrl_bat_in_out)
		     {
		     if(BAT_IS_ON[aa . s_i1]!=bisON)
		          {
		          if(tempU==0)
		               {
		               lc640_write_int(ADR_EE_BAT_IS_ON[aa . s_i1],bisON);
		               lc640_write_int(ADR_EE_BAT_DAY_OF_ON[aa . s_i1],day__);
		               lc640_write_int(ADR_EE_BAT_MONTH_OF_ON[aa . s_i1],month__);
		               lc640_write_int(ADR_EE_BAT_YEAR_OF_ON[aa . s_i1],year__);
		               lc640_write_int(ADR_EE_BAT_C_REAL[aa . s_i1],0x5555);
		               lc640_write_int(ADR_EE_BAT_RESURS[aa . s_i1],0);
					lc640_write_int(ADR_EE_BAT_ZAR_CNT[aa . s_i1],0);
		               
		               lc640_write(996,0);
					lc640_write(1016,0);
					lc640_write(1020,0);
					lc640_write(998,0);
					lc640_write(1018,0);
					lc640_write(1022,0);
					lc640_write(1014,0);
					lc640_write(1012,0);					
		               
                         tree_down(0,0);
                         ret(0);
		               }
		          else
		               {
		               tree_down(0,0);
	    	               show_mess("                    ",
	          				"       Пароль       ",
	          				"    не верный!!!    ",
	          				"                    ",1000);
     	               }
		          }      
               else		          
		          {
		          if(tempU==0)
		               {
		               lc640_write_int(ADR_EE_BAT_IS_ON[aa . s_i1],bisOFF);
		               lc640_write_int(ADR_EE_BAT_DAY_OF_ON[aa . s_i1],day__);
		               lc640_write_int(ADR_EE_BAT_MONTH_OF_ON[aa . s_i1],month__);
		               lc640_write_int(ADR_EE_BAT_YEAR_OF_ON[aa . s_i1],year__);

		               tree_down(0,0);
		               ret(0);
		               
		               }
	               else
		               {
		               tree_down(0,0);
	    	               show_mess("                    ",
	          				"       Пароль       ",
	          				"    не верный!!!    ",
	          				"                    ",1000);
		               }		               
		          }     
               }
		
		else if(aa . i==iSet_prl)
			{
	     	if(tempU==0) 
				{
				tree_down(0,0);
				tree_up(iSet,0,0,0);
				ret(1000);
				}
			else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"    не верный!!!    ",
	          			"                    ",1000);
				}
			}
		else	if(aa . i==iK_prl)
			{
	     	if(tempU==0) 
				{
				tree_down(0,0);
				tree_up(iK,0,0,0);
				show_mess(	"Включите авт-ты СЕТЬ",
 							"  БАТАРЕЯ,НАГРУЗКА  ",
 							"   Установите ток   ",
 							"   нагрузки 4-10А   ",3000);
				
				}
			else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"    не верный!!!    ",
	          			"                    ",1000);
				}
			} 
	
		else	if(aa . i==iAusw_prl)
			{
	     	if(tempU==0) 
				{
				tree_up(iAusw_set,1,0,0);
				default_temp=10;
				ret(0);
				}
			else 
				{
				aa . i=iDnd;
				ret(15);
				}
			} 	
			
		else	if(aa . i==iSet_st_prl)
			{
	     	if(tempU==0) 
				{
	
				aa . s_i=1;
				aa . i_s=0;
				default_temp=10;
				}
			else 
				{
				aa . i=iDnd;
				ret_ind(iSet,0,10);
				}
			} 
						
		else if(aa . i==iPrltst)
			{
			if(tempU==0) 
				{
				aa . i=iTst;
				aa . s_i=0;
				aa . i_s=0;
				tst_state[0]=tstOFF;
				tst_state[1]=tstOFF;
				tst_state[2]=tstOFF;
				tst_state[3]=tstOFF;
				tst_state[4]=tstOFF;
				tst_state[5]=tstOFF;
				}
	  		else 
				{
				aa . i=iDnd;
				}
			}
		else if(aa . i==iSpc_prl_ke)
			{
			if(tempU==0) 
				{
				aa . i=iKe;
				aa . s_i=0;
				aa . i_s=0;
				}
	  		else 
				{	
				aa . i=iDnd;
				ret_ind(b[--ptr_ind].i,b[ptr_ind].s_i,5);
				}
			}
		else if(aa . i==iSpc_prl_vz)
			{
			if(tempU==0) 
				{
				tree_down(0,0);
				tree_up(iVz,0,0,0);
				ret(1000);
				}
	  		else 
				{
				tree_down(0,0);
				tree_up(iDnd,0,0,0);
				ret(10);
				}     	          
			}
		}
	}

else if(aa . i==iSpc)
	{
	ret_ind(0,0,0);
	ret_ind_sec(iMn,60);
	if (but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,6);
		}
	else if (but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,6);
		}
	else if(but==239)
		{
		if(aa . s_i==0)
			{   
			ret_ind_sec(iMn,10);
               tree_up(iSpc_prl_vz,0,0,0);
               parol_init();
			}
		else if(aa . s_i==1)
			{
               tree_up(iAvz,0,0,0);
               aa . s_i=0;
			}			
		else if((aa . s_i==2)||(aa . s_i==3))
			{
               tree_up(iSpc_prl_vz,0,0,aa . s_i-2);
               parol_init();
			} 
		else if(aa . s_i==4)
			{
			tree_up(iAKE,0,0,0);
               

 
			}	
		else if(aa . s_i==5)
			{
			tree_up(iAKE,0,0,1);
               

 
			}						
		else if(aa . s_i==6)
			{
			tree_down(0,0);
			

 
			}	
		}
	else if(but==251)
		{
		tree_down(0,0);
		

 
		}			
	}

else if(aa . i==iVz)
	{
	ret_ind(0,0,0);
	ret_ind_sec(0,0);
	if (but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,2);
		}
	else if (but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,2);
		}
	else if(aa . s_i==0)
		{
		if(spc_stat!=spcVZ)
			{
			if(but==247)
				{
				VZ_HR++;
				}
			else if(but==251)
				{
				VZ_HR--;
				}
			gran(&VZ_HR,1,10);
			lc640_write_int(0x10+100+76,VZ_HR);
			}			
          }
	else if(aa . s_i==1)
		{
          if(spc_stat!=spcVZ)
          	{
          	char temp;
          	temp=vz_start(VZ_HR);
          	if(temp==22) 
          		{
          		aa . s_i=22;
          		ret_ind(iVz,1,5);
          		} 
			else if(temp==33) 
          		{
          		aa . s_i=33;
          		ret_ind(iVz,1,5);
          		}          		
          	}    
         	else if(spc_stat==spcVZ)
          	{
          	vz_stop();
          	}             	 
		}			
	else if(aa . s_i==2)
		{                 
		if(but==239)
			{
			aa . i=iSpc;
			aa . s_i=0;
			ret_ind_sec(iMn,60);
			}
          } 
	}

else if(aa . i==iKe)
	{
	ret_ind(0,0,0);
	ret_ind_sec(0,0);
	if (but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,1);
		}
	else if (but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,1);
		}
	else if(aa . s_i==0)
		{
		if(but==239)
			{
			if((spc_stat==spcKE)&&(spc_bat==aa . s_i1))
				{
				spc_stat=spcOFF;
				}
			else
				{
				if(ke_start(aa . s_i1)==1)
					{
					aa . s_i=11;
					ret_ind(iKe,0,10);
					}
				else if(ke_start(aa . s_i1)==2)
					{
					aa . s_i=12;
					ret_ind(iKe,0,10);
					}			
				else if(ke_start(aa . s_i1)==3)
					{
					aa . s_i=13;
					ret_ind(iKe,0,10);
					}     
				else if(ke_start(aa . s_i1)==4)
					{
					aa . s_i=14;
					ret_ind(iKe,0,10);
					}     			
				else if(ke_start(aa . s_i1)==5)
					{
					aa . s_i=15;
					ret_ind(iKe,0,10);
					}			
				else if(ke_start(aa . s_i1)==6)
					{
					aa . s_i=16;
					ret_ind(iKe,0,10);
					}     
				else if(ke_start(aa . s_i1)==7)
					{
					aa . s_i=17;
					ret_ind(iKe,0,10);
					}  
				else if(ke_start(aa . s_i1)==8)
					{
					aa . s_i=18;
					ret_ind(iKe,0,10);
					}     			
				else if(ke_start(aa . s_i1)==9)
					{
					aa . s_i=19;
					ret_ind(iKe,0,10);
					}			
				else if(ke_start(aa . s_i1)==10)
					{
					aa . s_i=20;
					ret_ind(iKe,0,10);
					}     
				else if(ke_start(aa . s_i1)==11)
					{
					aa . s_i=21;
					ret_ind(iKe,0,10);
					}   
				else if(ke_start(aa . s_i1)==12)
					{
					aa . s_i=22;
					ret_ind(iKe,0,10);
					}  					  								   										
				}
			}						
          }
	
	else if(aa . s_i==1)
		{                 
		if(but==239)
			{
			aa . i=iSpc;
			aa . s_i=2+aa . s_i1;
			ret_ind_sec(iMn,600);
			}
          } 
     else aa . s_i=0;     
	}


else if(aa . i==iLog)
	{
	ret_ind_sec(0,0);
	ret_ind(0,0,0);
	if (but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,av_j_si_max+1);
		}
	else if (but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,av_j_si_max+1);
          
		}  

	else if (but==125)
		{
		aa . s_i=av_j_si_max;
		} 
		 
	else if (but==251)
		{
		tree_down(0,0);
		}  
		
	else if(but==239)
		{  
		if(aa . s_i==av_j_si_max+1)
			{
			lc640_write(1024+1024+512+1024+2,0);
			lc640_write(1024+1024+512+1024,0);
			
			
			
			tree_down(0,0);				
			}
					
		else if(aa . s_i==av_j_si_max)
			{
			

 
			tree_down(0,0);
			}
			
		else 
			{
			aa . i=iLog_;
			aa . s_i1=aa . s_i;
			aa . i_s=0;
			aa . s_i=0;
			}	
			
		} 






 		
		

	else if(but==247)
		{
	    
		}
	else if(but==119)
		{
	    	
		}		
	else if(but==251)
		{
	    	
		}
				
	else if(but==123)
		{           
					lc640_write(1024+1024+512+1024+2,0);
			lc640_write(1024+1024+512+1024,0);
			aa . i=iMn;
			aa . s_i=cnt_of_slave+10;
			aa . i_s=0;				
	
		}	 		
		






 		
	







 


































 													
	}

else if(aa . i==iLog_)
	{          
	if(but==254)
		{
		aa . i_s--;
		gran_char(&aa . i_s,0,av_j_si_max);
		}
	else if(but==253)
		{
		aa . i_s++;
		gran_char(&aa . i_s,0,av_j_si_max);
		}
	else 
		{
		aa . i=iLog;
		aa . s_i=aa . s_i1;
		}		
	}	

else if(aa . i==iSet)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		if(aa . s_i==5)aa . i_s=4;
		if(aa . s_i==6)aa . s_i=8;
		if(aa . s_i==9)aa . i_s=8;
		if(aa . s_i==10)aa . s_i=11;
		
		gran_char(&aa . s_i,0,30);
		}
	else if(but==254)
		{
		aa . s_i--;
		if(aa . s_i==6)aa . s_i=5;
		if(aa . s_i==10)aa . s_i=9;
		
		gran_char(&aa . s_i,0,30);
		}
	else if(but==125)
		{
		aa . s_i=29;
		}
		
	else if(aa . s_i==0)
	     {
	     if(but==239)
	          {
	          tree_up(iDef,0,0,0);
	          ret(1000);
	          default_temp=10;
	          }
	     }	
	
     else if(aa . s_i==1)
		{
		if(but==239)
		     {
		     tree_up(iSet_T,0,0,0);
		     ret(1000);
		     phase=0;
		     }
		}	
					 
     else if(aa . s_i==2)
		{
		if(but==239)
		     {
		     tree_up(iStr,0,0,0);
		     ret(1000);
		     aa . i_s=0;
		     }
		}	
	
	else if(aa . s_i==3)
	     {
	     if(but==247)MNEMO_TIME++;
	     else if(but==119)MNEMO_TIME+=10;
	     else if(but==251)MNEMO_TIME--;
	     else if(but==123)MNEMO_TIME-=10;

	     if(((MNEMO_TIME<5)||(MNEMO_TIME>60))&&(MNEMO_ON!=mnOFF))lc640_write_int(0x10+100+72,mnOFF);	
	     if(((MNEMO_TIME>=5)&&(MNEMO_TIME<=60))&&(MNEMO_ON!=mnON))lc640_write_int(0x10+100+72,mnON);
	     gran((signed short*)&MNEMO_TIME,4,61);
	     lc640_write_int(0x10+100+74,MNEMO_TIME);
	     speed=1;
	     }
				     		
	else if(aa . s_i==4)
	     {
		if(ZV_ON)ZV_ON=0;
		else ZV_ON=1;
	     lc640_write_int(0x10+100+18,ZV_ON);
	     speed=1;
	     }	
	
	else if(aa . s_i==5)
	     {
		if(AV_OFF_AVT)AV_OFF_AVT=0;
		else AV_OFF_AVT=1;
	     lc640_write_int(0x10+100+12,AV_OFF_AVT);
	     speed=1;
	     }	

	else if(aa . s_i==7)
	     {
	     if(but==239)
	          {
	          tree_up(iApv,0,0,0);
	          ret(1000);
	          }
	     }	

	else if(aa . s_i==8)
	     {
		if(PAR)PAR=0;
		else PAR=1;
	     lc640_write_int(0x10+100+86,PAR);
	     speed=1;
	     }

	else if(aa . s_i==9)
	     {
	     if(but==247)TBAT++;
	     else if(but==119)TBAT+=10;
	     else if(but==251)TBAT--;
	     else if(but==123)TBAT-=10;
	     gran(&TBAT,5,60);
	     lc640_write_int(0x10+100+78,TBAT);
	     speed=1;
	     }	
	                    	     	
	else if(aa . s_i==11)
	     {
	     if(but==247)UMAX++;
	     else if(but==119)UMAX+=10;
	     else if(but==251)UMAX--;
	     else if(but==123)UMAX-=10;
	     gran(&UMAX,10,1000);
	     lc640_write_int(0x10+100+4,UMAX);
	     speed=1;
	     }
	else if(aa . s_i==12)
	     {
	     if(but==247)DU++;
	     else if(but==119)DU+=10;
	     else if(but==251)DU--;
	     else if(but==123)DU-=10;
	     gran(&DU,10,1000);
	     lc640_write_int(0x10+100+84,DU);
	     speed=1;
	     }	     
	else if(aa . s_i==13)
	     {
	     if(but==247)UB0++;
	     else if(but==119)UB0+=10;
	     else if(but==251)UB0--;
	     else if(but==123)UB0-=10;
	     gran(&UB0,10,1000);
	     lc640_write_int(0x10+100+6,UB0);
	     speed=1;
	     }
	     
	else if(aa . s_i==14)
	     {
	     if(but==247)UB20++;
	     else if(but==119)UB20+=10;
	     else if(but==251)UB20--;
	     else if(but==123)UB20-=10;
	     gran(&UB20,10,1000);
	     lc640_write_int(0x10+100+8,UB20);
	     speed=1;
	     }	

	else if(aa . s_i==15)
	     {
	     if(but==247)USIGN++;
	     else if(but==119)USIGN+=10;
	     else if(but==251)USIGN--;
	     else if(but==123)USIGN-=10;
	     gran(&USIGN,1,500);
	     lc640_write_int(0x10+100+14,USIGN);
	     speed=1;
	     }	
	else if(aa . s_i==16)
	     {
	     if(but==247)UMN++;
	     else if(but==119)UMN+=10;
	     else if(but==251)UMN--;
	     else if(but==123)UMN-=10;
	     gran(&UMN,1,220);
	     lc640_write_int(0x10+100+16,UMN);
	     speed=1;
	     }	

	else if(aa . s_i==17)
	     {
	     if(but==247)U0B++;
	     else if(but==119)U0B+=10;
	     else if(but==251)U0B--;
	     else if(but==123)U0B-=10;
	     gran(&U0B,10,1000);
	     lc640_write_int(0x10+100+32,U0B);
	     speed=1;
	     }	
	     
	else if(aa . s_i==18)
	     {
	     if(but==247)IKB++;
	     else if(but==119)IKB+=10;
	     else if(but==251)IKB--;
	     else if(but==123)IKB-=10;
	     gran(&IKB,1,500);
	     lc640_write_int(0x10+100+20,IKB);
	     speed=1;
	     }		
            
	else if(aa . s_i==19)
	     {
	     if(but==247)IZMAX++;
	     else if(but==119)IZMAX+=10;
	     else if(but==251)IZMAX--;
	     else if(but==123)IZMAX-=10;
	     gran(&IZMAX,10,1000);
	     lc640_write_int(0x10+100+30,IZMAX);
	     speed=1;
	     }   

	else if(aa . s_i==20)
	     {
	     if(but==247)IMAX++;
	     else if(but==119)IMAX+=10;
	     else if(but==251)IMAX--;
	     else if(but==123)IMAX-=10;
	     gran(&IMAX,1,120);
	     lc640_write_int(0x10+100+24,IMAX);
	     speed=1;
	     }		
	     
	else if(aa . s_i==21)
	     {
	     if(but==247)KIMAX++;
	     else if(but==119)KIMAX+=10;
	     else if(but==251)KIMAX--;
	     else if(but==123)KIMAX-=10;
	     gran(&KIMAX,5,10);
	     lc640_write_int(0x10+100+26,KIMAX);
	     speed=1;
	     }
	
	else if(aa . s_i==22)
	     {
	     if ((but==247)||(but==119))KVZ+=5;
		if ((but==251)||(but==123))KVZ-=5;
		gran(&KVZ,1005,1030); 	          
		lc640_write_int(0x10+100+22,KVZ);
	     speed=1;
	     }
	     
	else if(aa . s_i==23)
		{
		if ((but==247)||(but==119))TZAS++;
		if ((but==251)||(but==123))TZAS--;
		gran(&TZAS,0,3);
		lc640_write_int(0x10+100+34,TZAS);
		speed=1; 
		}	
			       	        
	else if(aa . s_i==24)
	     {
	     if(but==247)TMAX++;
	     else if(but==119)TMAX+=2;
	     else if(but==251)TMAX--;
	     else if(but==123)TMAX-=2;
	     gran(&TMAX,10,100);
	     lc640_write_int(0x10+100+10,TMAX);
	     speed=1;
	     }	
	
	else if(aa . s_i==25)
	     {
	     if(but==247)TSIGN++;
	     else if(but==119)TSIGN+=2;
	     else if(but==251)TSIGN--;
	     else if(but==123)TSIGN-=2;
	     gran(&TSIGN,10,100);
	     lc640_write_int(0x10+100+82,TSIGN);
	     speed=1;
	     }	     
	else if(aa . s_i==26)
	     {
	     if(but==247)TBATMAX++;
	     else if(but==119)TBATMAX+=2;
	     else if(but==251)TBATMAX--;
	     else if(but==123)TBATMAX-=2;
	     gran(&TBATMAX,10,100);
	     lc640_write_int(0x10+100+88,TBATMAX);
	     speed=1;
	     }	
	
	else if(aa . s_i==27)
	     {
	     if(but==247)TBATSIGN++;
	     else if(but==119)TBATSIGN+=2;
	     else if(but==251)TBATSIGN--;
	     else if(but==123)TBATSIGN-=2;
	     gran(&TBATSIGN,10,100);
	     lc640_write_int(0x10+100+90,TBATSIGN);
	     speed=1;
	     }	
     	     	     		     	     
    else if(aa . s_i==28)
		{
		if(but==239)
		     {
		     
		     
		     }
		}		
     else if(aa . s_i==29)
		{
		if(but==239)
		     {
		     tree_down(0,0);
		     ret(0);
		     }
		}		
	else if(aa . s_i==30)
		{
		if(but==239)
		     {		
			tree_up(iK_prl,0,0,0);
			parol_init();
			ret(50);
			}						
		}			
	else if(aa . s_i==31)
		{
		if(but==239)
		     {
		     tree_up(iPrltst,0,0,0);
		     parol_init();
		     }
		}			
     }

else if(aa . i==iDef)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,6);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,6);
		}
	else if(but==125)
		{
		aa . s_i=6;
		}
	
	else if(but==239)
		{
		if(aa . s_i==0)
			{
			def_set(600,564,545,44,100,480,4);
			

			}
		else if(aa . s_i==1)
			{
			def_set(750,705,681,55,100,600,4);
			
			}	
		else if(aa . s_i==2)
			{
			def_set(600,564,545,44,1600,480,5);
			

			}
		else if(aa . s_i==3)
			{
			def_set(750,705,681,55,100,600,5);
			
			}
		else if(aa . s_i==4)
			{
			def_set(600,564,545,44,100,480,6);
			

			}
		else if(aa . s_i==5)
			{
			def_set(750,705,681,55,100,600,6);
			
			}

		else if(aa . s_i==6)
			{
			tree_down(0,0);
			}
		default_temp=aa . s_i;	
		}
     }
else if(aa . i==iSet_T)
	{
	signed char temp;
	if(but==247)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,5);
		}
	else if(but==251)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,5);
		}
	else if(but==239)
		{
		aa=b[--ptr_ind];
		}	
	else if(aa . s_i==0)
	     {
	     temp=hour__;
	     if((but==254)||(but==126))
	          {
	          temp++;
	          gran_ring_char(&temp,0,23);
	          hour__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x04,temp);
	          }
          else if((but==253)||(but==125))
	          {
	          temp--;
	          gran_ring_char(&temp,0,23);
	          hour__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x04,temp);
	          }	
	     speed=1;               
	     }
     else if(aa . s_i==1)
	     {
	     temp=min__;
	     if((but==254)||(but==126))
	          {
	          temp++;
	          gran_ring_char(&temp,0,59);
	          min__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x03,temp);
	          }
          else if((but==253)||(but==125))
	          {
	          temp--;
	          gran_ring_char(&temp,0,59);
	          min__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x03,temp);
	          }	
	     speed=1;               
	     }
     else if(aa . s_i==2)
	     {
	     temp=sec__;
	     if((but==254)||(but==126))
	          {
	          temp=0;
	          gran_ring_char(&temp,0,59);
	          sec__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x02,temp);
	          }
          else if((but==253)||(but==125))
	          {
	          temp=0;
	          gran_ring_char(&temp,0,59);
	          sec__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x02,temp);
	          }	
	     speed=1;               
	     }

     else if(aa . s_i==3)
	     {
	     temp=day__;
	     if((but==254)||(but==126))
	          {
	          temp++;
	          gran_ring_char(&temp,1,31);
	          day__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x05,temp);
	          }
          else if((but==253)||(but==125))
	          {
	          temp--;
	          gran_ring_char(&temp,1,31);
	          day__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x05,temp);
	          }	
	     speed=1;               
	     }
     else if(aa . s_i==4)
	     {
	     temp=month__;
	     if((but==254)||(but==126))
	          {
	          temp++;
	          gran_ring_char(&temp,1,12);
	          month__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x07,temp);
	          }
          else if((but==253)||(but==125))
	          {
	          temp--;
	          gran_ring_char(&temp,1,12);
	          month__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x07,temp);
	          }	
	     speed=1;               
	     }	  
     else if(aa . s_i==5)
	     {
	     temp=year__;
	     if((but==254)||(but==126))
	          {
	          temp++;
	          gran_ring_char(&temp,0,99);
	          year__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x08,temp);
	          }
          else if((but==253)||(but==125))
	          {
	          temp--;
	          gran_ring_char(&temp,0,99);
	          year__=temp;
	          temp=((temp/10)<<4)+(temp%10);
	          pcf8563_write(0x08,temp);
	          }	
	     speed=1;               
	     }		        
	}  
	   	
else if(aa . i==iStr)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,1,5);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,1,5);
		}
	else if(but==125)
		{
		aa . s_i=4;
		}				
     else if(aa . s_i==1)
	     {
	     if((but==247)||(but==119))
	     	{
	     	NUMIST++;
	     	gran(&NUMIST,0,12);
	     	lc640_write_int(0x10+100+36,NUMIST);
	     	}
	     
	     else if((but==251)||(but==123))
	     	{
	     	NUMIST--;
	     	gran(&NUMIST,0,12);
	     	lc640_write_int(0x10+100+36,NUMIST);
	     	}
          }	
          
     else if(aa . s_i==2)
	     {
	     if((but==247)||(but==119))
	     	{
	     	NUMINV++;
	     	gran(&NUMINV,0,4);
	     	lc640_write_int(0x10+100+38,NUMINV);
	     	}
	     
	     else if((but==251)||(but==123))
	     	{
	     	NUMINV--;
	     	gran(&NUMINV,0,4);
	     	lc640_write_int(0x10+100+38,NUMINV);
	     	}
          }	          
     else if(aa . s_i==3)
	     {
	     if((but==247)||(but==119))
	     	{
	     	NUMDT++;
	     	gran(&NUMDT,0,3);
	     	lc640_write_int(0x10+500+90,NUMDT);
	     	}
	     
	     else if((but==251)||(but==123))
	     	{
	     	NUMDT--;
	     	gran(&NUMDT,0,3);
	     	lc640_write_int(0x10+500+90,NUMDT);
	     	}
          }	
     else if(aa . s_i==4)
	     {
	     if((but==247)||(but==119))
	     	{
	     	NUMSK++;
	     	gran(&NUMSK,0,4);
	     	lc640_write_int(0x10+500+88,NUMSK);
	     	}
	     
	     else if((but==251)||(but==123))
	     	{
	     	NUMSK--;
	     	gran(&NUMSK,0,4);
	     	lc640_write_int(0x10+500+88,NUMSK);
	     	}
          }	                 
    else if(aa . s_i==5)
	     {
	     if(but==239)
	          {
			tree_down(0,0);
	          }
          }	          
	}     

else if (aa . i==iApv)
	{
     ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,simax);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,simax);
		}
	else if(but==125)
		{
		aa . s_i=simax;
		}			
	else if(but==239)
	     {
	     if(aa . s_i==simax)
	          {
	          
	          tree_down(0,0);
	          }
	     else if(aa . s_i==0)   
	          {
	          if(APV_ON1==apvON)lc640_write_int(0x10+100+44,apvOFF);
	          else lc640_write_int(0x10+100+44,apvON);
	          }
          else if((aa . s_i==1)&&(APV_ON1==apvON))   
	          {
	          if(APV_ON2==apvON)lc640_write_int(0x10+100+46,apvOFF);
	          else lc640_write_int(0x10+100+46,apvON);
	          }	 
          }
     
     else if((aa . s_i==2)&&(APV_ON2==apvON))   
          {
	     if((but==247)||(but==119))
	          {
	          signed short tempSS;
	          tempSS=APV_ON2_TIME;
	          tempSS++;
	          gran(&tempSS,1,24);
	          lc640_write_int(0x10+100+48,tempSS);
	          }
          else if((but==251)||(but==123))
	          {
	          signed short tempSS;
	          tempSS=APV_ON2_TIME;
	          tempSS--;
	          gran(&tempSS,1,24);
	          lc640_write_int(0x10+100+48,tempSS);
	          }	          
	     speed=1;
	     }	 
  	} 
		     
else if(aa . i==iK)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,2+(NUMBAT!=0)+(NUMIST!=0)+(NUMINV!=0)+(NUMDT!=0));
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,2+(NUMBAT!=0)+(NUMIST!=0)+(NUMINV!=0)+(NUMDT!=0));
		}
	else if(but==125)
		{
		aa . s_i=2+(NUMBAT!=0)+(NUMIST!=0)+(NUMINV!=0)+(NUMDT!=0);
		}				
	else if(but==239)
		{
		if(aa . s_i==0)
			{
			tree_up(iK_net,0,0,0);	
			ret(1000);		
			}
		else if((NUMBAT)&&(aa . s_i==1))
			{
			tree_up(iK_bat_sel,0,0,0);	
			ret(1000);
			}
		else if((NUMIST)&&(aa . s_i==(1+(NUMBAT!=0))))
			{
			tree_up(iK_bps_sel,0,0,0);	
			ret(1000);
			}
		else if((NUMINV)&&(aa . s_i==(1+(NUMBAT!=0)+(NUMIST!=0))))
			{
			tree_up(iK_inv_sel,0,0,1);	
			ret(1000);
			}		

		else if((aa . s_i==(1+(NUMBAT!=0)+(NUMIST!=0)+(NUMINV!=0))))
			{
			tree_up(iK_load,0,0,0);	
			ret(1000);
			}
          
         	else if((NUMDT)&&(aa . s_i==(2+(NUMBAT!=0)+(NUMIST!=0)+(NUMINV!=0))))
			{
			tree_up(iK_t_out,0,0,0);	
			ret(1000);			
			}				
          else if(aa . s_i==(2+(NUMBAT!=0)+(NUMIST!=0)+(NUMINV!=0)+(NUMDT!=0)))
			{
	          tree_down(0,0);
	          ret(0);
               }	               			
		}			
	}

else if(aa . i==iK_net)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,1);
		phase=0;
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,1);
		phase=0;
		}
	else if(but==125)
		{
		aa . s_i=1;
		}				
	else if(aa . s_i==0)
		{
		temp_SS=lc640_read_int(0x10+16);
		if(but==247)
			{
			temp_SS++;
			}
		else if(but==119)
			{
			
			temp_SS+=10;
			
			}	
		else if(but==251)
			{
			
			temp_SS--;
			
			}
		else if(but==123)
			{
			
			temp_SS-=10;
			
			}				
		speed=1;
		gran(&temp_SS,450,550);
		lc640_write_int(0x10+16,temp_SS);
					
		}
	else if(aa . s_i==1)
		{
		if(but==239)
			{
			tree_down(0,1);
			ret(0);
			}
		}			
	}

else if(aa . i==iK_bat_sel)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,NUMBAT);
		phase=0;
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,NUMBAT);
		phase=0;
		}
	else if(but==125)
		{
		aa . s_i=1+NUMBAT;
		}	
	else if((but==239)&&(NUMBAT)&&(BAT_IS_ON[0]==bisON)&&(aa . s_i==0))
		{
		tree_up(iK_bat,0,0,0);	
		
		
     	

		ret(1000);
		}	
	else if((but==239)&&(NUMBAT)&&(BAT_IS_ON[1]==bisON)&&(aa . s_i==((BAT_IS_ON[0]==bisON))))
		{
		tree_up(iK_bat,0,0,1);
		
		
     	
     		
		ret(1000);
		}	
	else if(aa . s_i==(NUMBAT))
		{
		if(but==239)
			{
			tree_down(0,0);
			ret(0);
			}
		}				
	}

else if(aa . i==iK_bat)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		if((aa . s_i==1)||(aa . s_i==2))
			{
			aa . s_i=3;
			
			}
     		
		else if((aa . s_i==4)||(aa . s_i==5))aa . s_i=6;
		else if((aa . s_i==7)||(aa . s_i==8))aa . s_i=9;
		gran_char(&aa . s_i,0,9);
		phase=0;
		}
	else if(but==254)
		{
		aa . s_i--;
		if((aa . s_i==1)||(aa . s_i==2))
			{
			aa . s_i=0;
			
     		
     		}
		else if((aa . s_i==4)||(aa . s_i==5))aa . s_i=3;
		else if((aa . s_i==7)||(aa . s_i==8))
			{
			aa . s_i=6;
			
		gran_char(&aa . s_i,0,9);
		phase=0;
			}
		}
	else if(but==125)
		{
		aa . s_i=9;
		}			
	else if(aa . s_i==0)
		{
		temp_SS=lc640_read_int(ADR_KUBAT[aa . s_i1]);
	     if(but==247)
	     	{
	     	
		     temp_SS++;
		    
		    
	     	}
	     else if(but==119)
	     	{
	     	
	     	temp_SS+=2;
	     	
	     	
	     	}	
	     else if(but==251)
	     	{
	     	
	     	temp_SS--;
	     	
	     	
	     	}
	     else if(but==123)
	     	{
	     	
	     	temp_SS-=2;
	     	
	     	
	     	}
	     gran(&temp_SS,500,650);
		lc640_write_int(ADR_KUBAT[aa . s_i1],temp_SS);					
		speed=1;			
		}
					
	else if(aa . s_i==3)
		{
		if(but==239)
		     {
		     if(phase==0)
		          {
		          lc640_write_int(ADR_KI0BAT[aa . s_i1],ad7705_buff_[aa . s_i1]);
		          phase=1;
		          }
		     }	
		else
			{
			temp_SS=lc640_read_int(ADR_KI1BAT[aa . s_i1]);
			if(but==247)temp_SS++;
			else if(but==119)temp_SS+=2;
			else if(but==251)temp_SS--;
			else if(but==123)temp_SS-=2;
						
			gran(&temp_SS,600,700);
			lc640_write_int(ADR_KI1BAT[aa . s_i1],temp_SS);
			phase=1;
			}
				
		speed=1;			
		}					
	else if(aa . s_i==6)
		{
		temp_SS=lc640_read_int(ADR_KTBAT[aa . s_i1]);
		if(but==247)temp_SS++;
		else if(but==119)temp_SS+=3;
		else if(but==251)temp_SS--;
		else if(but==123)temp_SS-=3;
		gran(&temp_SS,1900,2100);
		lc640_write_int(ADR_KTBAT[aa . s_i1],temp_SS);				
		speed=1;			
		}	
	else if(aa . s_i==9)
		{
		if(but==239)
			{
			
			
			tree_down(0,1);
			ret(0);
			}
		}			
	}		

else if(aa . i==iK_bps_sel)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,NUMIST);
		phase=0;
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,NUMIST);
		phase=0;
		}
	else if(but==125)
		{
		aa . s_i=1+NUMIST;
		}	
	else if((but==239)&&(NUMIST)&&(aa . s_i<NUMIST))
		{
		tree_up(iK_bps,0,0,aa . s_i);	
		
		
     	

		ret(1000);
		}	
	else if(aa . s_i==(NUMIST))
		{
		if(but==239)
			{
			tree_down(0,0);
			ret(0);
			}
		}				
	}

else if(aa . i==iK_bps)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i++;
		if((aa . s_i==1)||(aa . s_i==2))aa . s_i=3;
		else if((aa . s_i==4)||(aa . s_i==5))aa . s_i=6;
		else if((aa . s_i==7)||(aa . s_i==8))aa . s_i=9;
		else if((aa . s_i==10)||(aa . s_i==11))aa . s_i=12;
		else if((aa . s_i==13)||(aa . s_i==14))aa . s_i=15;
		gran_char(&aa . s_i,0,15);
		phase=0;
		}
	else if(but==254)
		{
		aa . s_i--;
		if((aa . s_i==1)||(aa . s_i==2))aa . s_i=0;
		else if((aa . s_i==4)||(aa . s_i==5))aa . s_i=3;
		else if((aa . s_i==7)||(aa . s_i==8))aa . s_i=6;
		else if((aa . s_i==10)||(aa . s_i==11))aa . s_i=9;
		else if((aa . s_i==13)||(aa . s_i==14))aa . s_i=12;		
		gran_char(&aa . s_i,0,15);
		phase=0;
		}
	else if(but==125)
		{
		aa . s_i=15;
		}
	else if (aa . s_i == 0)
		{
		if(but==243) can2_out(aa . s_i1,aa . s_i1,0xEE,(0*16)+1,(0*16)+1,0,0,0);
	     else if(but==247) can2_out(aa . s_i1,aa . s_i1,0xEE,(0*16)+2,(0*16)+2,0,0,0);
		else if(but==119)	can2_out(aa . s_i1,aa . s_i1,0xEE,(0*16)+3,(0*16)+3,0,0,0);
    		else if(but==251) can2_out(aa . s_i1,aa . s_i1,0xEE,(0*16)+4,(0*16)+4,0,0,0); 
		else if(but==123) can2_out(aa . s_i1,aa . s_i1,0xEE,(0*16)+5,(0*16)+5,0,0,0);
		speed=1;
		}	
		
	else if (aa . s_i == 3)
		{
		if(but==243) can2_out(aa . s_i1,aa . s_i1,0xEE,(1*16)+1,(1*16)+1,0,0,0);
	     else if(but==247) can2_out(aa . s_i1,aa . s_i1,0xEE,(1*16)+2,(1*16)+2,0,0,0);
		else if(but==119)	can2_out(aa . s_i1,aa . s_i1,0xEE,(1*16)+3,(1*16)+3,0,0,0);
    		else if(but==251) can2_out(aa . s_i1,aa . s_i1,0xEE,(1*16)+4,(1*16)+4,0,0,0); 
		else if(but==123) can2_out(aa . s_i1,aa . s_i1,0xEE,(1*16)+5,(1*16)+5,0,0,0);
		speed=1;
		}		
		
	else if (aa . s_i == 6)
		{
		temp_SS=lc640_read_int(0x10+100+80);
		if(but==247)temp_SS++;
		else if(but==119)temp_SS+=2;
		else if(but==251)temp_SS--;
		else if(but==123)temp_SS-=2;
		else if(but==111)can2_out(aa . s_i1,aa . s_i1,0x16,0xee,0xee,0,0,0);   
						
		gran(&temp_SS,400,800);
		lc640_write_int(0x10+100+80,temp_SS);
		
		speed=1;
		}	
		
	else if (aa . s_i == 9)
		{
		if(but==239)
			{
			can2_out(aa . s_i1,aa . s_i1,0xEE,(2*16)+1,(2*16)+1,0,0,0);
			phase=1;
			}
	     else if(but==247) can2_out(aa . s_i1,aa . s_i1,0xEE,(2*16)+2,(2*16)+2,0,0,0);
		else if(but==119)	can2_out(aa . s_i1,aa . s_i1,0xEE,(2*16)+3,(2*16)+3,0,0,0);
    		else if(but==251) can2_out(aa . s_i1,aa . s_i1,0xEE,(2*16)+4,(2*16)+4,0,0,0); 
		else if(but==123) can2_out(aa . s_i1,aa . s_i1,0xEE,(2*16)+5,(2*16)+5,0,0,0);
		speed=1;
		}		
		
	else if (aa . s_i == 12)
		{
		if(but==247) can2_out(aa . s_i1,aa . s_i1,0xEE,(3*16)+2,(3*16)+2,0,0,0);
		else if(but==119)	can2_out(aa . s_i1,aa . s_i1,0xEE,(3*16)+3,(3*16)+3,0,0,0);
    		else if(but==251) can2_out(aa . s_i1,aa . s_i1,0xEE,(3*16)+4,(3*16)+4,0,0,0); 
		else if(but==123) can2_out(aa . s_i1,aa . s_i1,0xEE,(3*16)+5,(3*16)+5,0,0,0);
		speed=1;
		}								
	
























































 	
		
				
			
	else if(aa . s_i==0)
		{
		if(phase==0)
		     {
		     if(but==239)
		          {




                    if(aa . s_i1==0)temp_SS=adc_buff_[2];
		          if(aa . s_i1==1)temp_SS=adc_buff_[3];

		          
		     	phase=1;
		          }
		     else phase=1;     
		     }
		else if(phase==2)
		     {
		     if(but==247)
		     	{
		     	
		     	temp_SS++;
		     	
	     		}
	     	else if(but==119)
	     		{
	     		
	     		temp_SS+=2;
	     		
	     		}	
	     	else if(but==251)
	     		{
	     		
	     		temp_SS--;
	     		
	     		}
	     	else if(but==123)
	     		{
	     		
	     		temp_SS-=2;
	     		
	     		}				
	     	speed=1;			
	     	}
	     }	
					
	else if(aa . s_i==3)
		{
	     if(but==247)
			{
			
			temp_SS++;
			
			}
		else if(but==119)
			{
			
			temp_SS+=2;
			
			}	
		else if(but==251)
			{
			
			temp_SS--;
			
			}
		else if(but==123)
			{
			
			temp_SS-=2;
			
			}				
		speed=1;			
		}					
	else if(aa . s_i==6)
		{
		if(but==247)
			{
			
			temp_SS++;
			
			}
		else if(but==119)
			{
			
			temp_SS+=3;
			
			}	
		else if(but==251)
			{
			
			temp_SS--;
			
			}
		else if(but==123)
			{
			
			temp_SS-=3;
			
			}				
		speed=1;			
		}	
	else if(aa . s_i==15)
		{
		if(but==239)
			{
			
			
			tree_down(0,1);
			ret(0);
			}
		}			
	}		

else if(aa . i==iK_load)
	{
	ret(1000);
	if(but==253)
		{
		aa . s_i=1;
		}
	else if(but==254)
		{
		aa . s_i=0;
		}
	else if(aa . s_i==0)
		{
		temp_SS=lc640_read_int(0x10+20);
	     if(but==247)
	     	{
		     temp_SS++;
	     	}
	     else if(but==119)
	     	{
	     	temp_SS+=2;
	     	}	
	     else if(but==251)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==123)
	     	{
	     	temp_SS-=2;
	     	}
	     gran(&temp_SS,500,600);
		lc640_write_int(0x10+20,temp_SS);					
		speed=1;	
					
		}
	else if(aa . s_i==1)
		{
		if(but==239)
			{
			tree_down(0,1);
			ret(0);
			}
		}			
	}
			
else if(aa . i==iBatLog)
	{
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,6);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,6);
		}
	else if(but==125)
		{
		aa . s_i=6;
		}				
	else if((but==251)&&((aa . s_i==0)||(aa . s_i==3)||(aa . s_i==4)))
		{
		tree_down(0,0);
		}		
	else if(aa . s_i==0)
	     {
	     if(but==239)
	          {
	          
	          
	          
	               
	               
	               
	               
	          tree_up(iPrl_bat_in_out,0,0,aa . s_i1);
	          if(BAT_IS_ON[aa . s_i1]!=bisON) show_mess("  Введение батареи  ",
	          								 "    уничтожит все   ",
	          								 "   предшествующие   ",
	          								 "      данные!!!     ",2000);     
	          parol_init();
	          }
	     }
	else if(aa . s_i==1)
	     {
	     if(but==247)BAT_C_NOM[aa . s_i1]++;
	     else if(but==119)BAT_C_NOM[aa . s_i1]+=10;
	     else if(but==251)BAT_C_NOM[aa . s_i1]--;
	     else if(but==123)BAT_C_NOM[aa . s_i1]-=10;
	     gran(&BAT_C_NOM[aa . s_i1],0,200);
	     lc640_write_int(ADR_EE_BAT_C_NOM[aa . s_i1],BAT_C_NOM[aa . s_i1]);
	     speed=1;
	     }		     




















 
		
		
	else if(aa . s_i==3)
		{
		if(but==239)
			{ 
               cap=0;
			deep=lc640_read_int(1024+1024+512+1024+2);
			ptr=lc640_read_int(1024+1024+512+1024);
			
			if(deep>63)
				{
				deep=0;
			     ptr=0;
			     }
			     			
			for(i=0;i<deep;i++)
				{
				lc640_read_long_ptr(1024+(32*ptr),av_head);
				
				if((av_head[0]=='B')&&(av_head[1]==aa . s_i1)&&(av_head[2]=='K')) 	
					{
					cap++;
					content[cap-1]=ptr;
					}
					
				ptr=ptr_carry(ptr,64,-1); 
	
				} 
				
			
 
			tree_up(iBatLogKe,0,0,aa . s_i1);
			
			av_j_si_max=cap;
			if(av_j_si_max>63)av_j_si_max=0;
			} 
		}




	else if(aa . s_i==4)
		{
		if(but==239)
			{ 
               cap=0;
			deep=lc640_read_int(1024+1024+512+1024+2);
			ptr=lc640_read_int(1024+1024+512+1024);
			
			if(deep>63)
				{
				deep=0;
			     ptr=0;
			     }
			     
			for(i=0;i<deep;i++)
				{
				lc640_read_long_ptr(1024+(32*ptr),av_head);
				
				if((av_head[0]=='B') &&(av_head[2]=='Z')) 	
					{
					cap++;
					content[cap-1]=ptr;
					}
					
				ptr=ptr_carry(ptr,64,-1); 
				} 
				
			
 
			tree_up(iBatLogVz,0,0,aa . s_i1);   
			
			av_j_si_max=cap;
			if(av_j_si_max>63)av_j_si_max=0;
			} 
		else if(but==247)
			{
			
			
			} 
		}

	else if(aa . s_i==5)
		{
		if(but==239)
			{ 
               cap=0;
			deep=lc640_read_int(1024+1024+512+1024+2);
			ptr=lc640_read_int(1024+1024+512+1024);

			if(deep>63)
				{
				deep=0;
			     ptr=0;
			     }
			
			
			
			for(i=0;i<deep;i++)
				{
				lc640_read_long_ptr(1024+(32*ptr),av_head);
				
				if((av_head[0]=='B')&&(av_head[1]==aa . s_i1)&&(av_head[2]=='W')) 	
					{
					cap++;
					content[cap-1]=ptr;
					}
					
		   	


 
				ptr=ptr_carry(ptr,64,-1); 
				} 
				
			
 

			tree_up(iBatLogWrk,0,0,aa . s_i1);
			
			av_j_si_max=cap;
			if(av_j_si_max>63)av_j_si_max=0;
			} 
		else if(but==247)
			{
			
			
			} 
		}		
		 	         	
     else if(aa . s_i==6)
	     {
	     if(but==239)
	          {
	          tree_down(0,0);
	          }
	     }		     
		
	} 

else if(aa . i==iBatLogVz)
	{
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,av_j_si_max);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,av_j_si_max);
		}
	else if(but==239)
		{
		if(aa . s_i==av_j_si_max)
			{
			tree_down(0,0);
			}
		} 
	else if(but==251)
		{
		tree_down(0,0);
		}		
    
	
		
	}

else if(aa . i==iBatLogKe)
	{
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,av_j_si_max);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,av_j_si_max);
		}
	else if(but==239)
		{
		if(aa . s_i==av_j_si_max)
			{
			tree_down(0,0);
			}
		} 
	else if(but==251)
		{
		tree_down(0,0);
		}		
    
	}

else if(aa . i==iBatLogWrk)
	{
	if(but==253)
		{
		aa . s_i++;
		gran_char(&aa . s_i,0,av_j_si_max);
		}
	else if(but==254)
		{
		aa . s_i--;
		gran_char(&aa . s_i,0,av_j_si_max);
		}
	else if(but==239)
		{
		if(aa . s_i==av_j_si_max)
			{
			tree_down(0,0);
			}
		else if(aa . s_i<=av_j_si_max)
			{
			
			
			aa . i_s=0;
			
			}	
		} 
	else if(but==251)
		{
		tree_down(0,0);
		}		
	else if(but==247)
		{
	    

		} 
	}

else if(aa . i==iAv_view)
	{
	if(but==239)
		{
		avar_ind_stat&=~(1L<<aa . s_i);
		if(avar_ind_stat)
			{
			while(!(avar_ind_stat&(1<<aa . s_i)))
				{
				aa . s_i++;
				if(aa . s_i>=32)
					{
					tree_down(0,0);
					avar_ind_stat=0;
					}
				}
		 	}
	 	else 
			{
			tree_down(0,0);
			avar_ind_stat=0;
			}
		}
 	}

else if(aa . i==iAvz)
	{
	if(AVZ!=AVZ_OFF)
		{
		if(but==254)
			{
			aa . s_i--;
			if(aa . s_i==3)aa . s_i--;
			}
		else if(but==253)
			{
			aa . s_i++;
			if(aa . s_i==3)aa . s_i++;
			}
		else if(aa . s_i==0)
			{
			if(but==251)
				{
				if(AVZ==AVZ_1)AVZ=AVZ_OFF;
				else if(AVZ==AVZ_2)AVZ=AVZ_1;
				else if(AVZ==AVZ_3)AVZ=AVZ_2; 
				else if(AVZ==AVZ_6)AVZ=AVZ_3;
				else if(AVZ==AVZ_12)AVZ=AVZ_6;			
				else AVZ=AVZ_12;
				}
			else if((but==247)||(but==239))
				{
				if(AVZ==AVZ_1)AVZ=AVZ_2;
				else if(AVZ==AVZ_2)AVZ=AVZ_3;
				else if(AVZ==AVZ_3)AVZ=AVZ_6; 
				else if(AVZ==AVZ_6)AVZ=AVZ_12;
				else if(AVZ==AVZ_12)AVZ=AVZ_OFF;			
				else AVZ=AVZ_1;
				} 
			lc640_write_int(0x10+100+70,AVZ);
			if(AVZ!=AVZ_OFF)avz_next_date_hndl();		
			}      
		else if(aa . s_i==1)
			{
			if((but==247)||(but==119))
				{
				speed=1;
				AVZ_TIME++;
				} 
			else if((but==251)||(but==123))
				{
				speed=1;
				AVZ_TIME--;
				}			
			gran(&AVZ_TIME,1,20);
			lc640_write_int(0x10+100+56,AVZ_TIME);
			}	
		else if(aa . s_i==4)
			{
			if((but==239))
				{
				aa . i=iSpc;
				aa . s_i=1;
				}	
			}        
		gran_char(&aa . s_i,0,4);						               
		} 
	else if(AVZ==AVZ_OFF)
		{
		if(but==254)
			{
			aa . s_i--;
			}
		else if(but==253)
			{
			aa . s_i++;
			}
		else if(aa . s_i==0)
			{
			if(but==251)
				{
				if(AVZ==AVZ_1)AVZ=AVZ_OFF;
				else if(AVZ==AVZ_2)AVZ=AVZ_1;
				else if(AVZ==AVZ_3)AVZ=AVZ_2; 
				else if(AVZ==AVZ_6)AVZ=AVZ_3;
				else if(AVZ==AVZ_12)AVZ=AVZ_6;			
				else AVZ=AVZ_12;
				}
			else if((but==247)||(but==239))
				{
				if(AVZ==AVZ_1)AVZ=AVZ_2;
				else if(AVZ==AVZ_2)AVZ=AVZ_3;
				else if(AVZ==AVZ_3)AVZ=AVZ_6; 
				else if(AVZ==AVZ_6)AVZ=AVZ_12;
				else if(AVZ==AVZ_12)AVZ=AVZ_OFF;			
				else AVZ=AVZ_1;
				}   
			lc640_write_int(0x10+100+70,AVZ);
			if(AVZ!=AVZ_OFF)avz_next_date_hndl();		
			}      
		else if(aa . s_i==1)
			{
			if((but==247)||(but==119))
				{
				speed=1;
				AVZ_TIME++;
				} 
			else if((but==251)||(but==123))
				{
				speed=1;
				AVZ_TIME--;
				}			
			gran(&AVZ_TIME,1,20);
			lc640_write_int(0x10+100+56,AVZ_TIME);
			}	
		else if(aa . s_i==2)
			{
			if((but==239))
				{
				tree_down(0,0);
				}	
			}        
		gran_char(&aa . s_i,0,2);						               
		} 
     }	
	
but_an_end:
n_but=0;
}








__irq void timer1_interrupt(void) 
{
(*((volatile unsigned long *) 0xE0008000)) = 0xff; 

adc_drv();

if(++t0cnt4>=10)
     {
     t0cnt4=0;
     b1000Hz=1;

	bFF=(char)(( ((*((volatile unsigned long *) 0xE0028000)) & ((0xffffffff>>(32-1))<<22)) >> 22));
	if(bFF!=bFF_) hz_out++;
	bFF_=bFF;
	

     }

if(++t0cnt5>=200)
     {
     t0cnt5=0;
     b50Hz=1;
     }
     
if(++t0cnt>=100)
     {
     t0cnt=0;
     b100Hz=1;

	if(beep_cnt)
		{
		beep_cnt--;
		if(beep_cnt==0)(*((volatile unsigned long *) 0xE002801C)) = ( ((*((volatile unsigned long *) 0xE002801C)) & ~((0xffffffff>>(32-1))<<27)) | (1 << 27) );
		} 

     hz_out_cnt++;
     if(hz_out_cnt>=500)
	     {	
	     hz_out_cnt=0;
	     net_F=hz_out;
	     hz_out=0;
	     }

     if(++t0cnt0>=10)
	     {
	     t0cnt0=0;
	     b10Hz=1;
	     beep_drv();
		if(main_10Hz_cnt<10000) main_10Hz_cnt++;
	     }

     if(t0cnt0==5)
	     {
	     
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

		if(main_1Hz_cnt<10000) main_1Hz_cnt++;

	     }
     }

(*((volatile unsigned long *) 0xFFFFF030)) = 0;

}


__irq void timer0_interrupt(void) 
{	




 
}





int main (void) 
{


(*((volatile unsigned long *) 0xE0028018)) |= (1<<21);                         

(*((volatile unsigned long *) 0xE0028008)) |= (1<<21);
(*((volatile unsigned long *) 0xE0028004)) |= (1<<21);


lcd_init();
lcd_on();
lcd_clear(); 


ad7705_reset();
{long xx; xx=(unsigned long)20 * 12000UL; while(xx)xx--;};

ad7705_write(0x20);
ad7705_write((((0x1101) | 0x1101>>3 | 0x1101>>6 | 0x1101>>9) & 0xf | ((0x1101) | 0x1101>>3 | 0x1101>>6 | 0x1101>>9)>>12 & 0xf0)); 
ad7705_write(0x10);
ad7705_write(0x44);

ad7705_reset();
{long xx; xx=(unsigned long)20 * 12000UL; while(xx)xx--;};

ad7705_write(0x20);
ad7705_write((((0x1101) | 0x1101>>3 | 0x1101>>6 | 0x1101>>9) & 0xf | ((0x1101) | 0x1101>>3 | 0x1101>>6 | 0x1101>>9)>>12 & 0xf0)); 
ad7705_write(0x10);
ad7705_write(0x44);

ad7705_reset();
{long xx; xx=(unsigned long)20 * 12000UL; while(xx)xx--;};  

ad7705_write(0x20);
ad7705_write((((0x1101) | 0x1101>>3 | 0x1101>>6 | 0x1101>>9) & 0xf | ((0x1101) | 0x1101>>3 | 0x1101>>6 | 0x1101>>9)>>12 & 0xf0)); 
ad7705_write(0x10);
ad7705_write(0x44); 










can2_init(7,8,0x009C000E);


FullCAN_SetFilter(2,0x18e);

memo_read();

uart0_init();
init_timer1();
adc_init();

pcf8563_read(1);
reload_hndl();
watchdog_init(60000000UL,1000UL);
samokalibr_init();
kb_init();

b1Hz=1;
while (1)  
	{ 
	if(bRXIN0) 
		{
		bRXIN0=0;
	
		uart_in0();
		} 

	if(b1000Hz)
		{
		b1000Hz=0;


		}
	
	if(b100Hz)
		{
		b100Hz=0;

		but_drv();
		but_an();
		}
		 
	if(b50Hz)
		{
		b50Hz=0;

		net_drv();
		}

	if(b10Hz)
		{
		char i;

		b10Hz=0;
				
		u_necc_hndl();
		
		for(i=0;i<NUMIST;i++)bps_drv(i);
		bps_hndl();
		
		if(BAT_IS_ON[0])bat_drv(0);
		if(BAT_IS_ON[1])bat_drv(1);
		bat_hndl();
				
		unet_drv();

		
		
		ind_hndl(); 

		bitmap_hndl();
		lcd_out(lcd_bitmap);

		ad7705_drv();
		
		ret_hndl();
		mess_hndl();
		
		cntrl_hndl();

		}

	if(b5Hz)
		{
		b5Hz=0;

		watchdog_reset();
		memo_read();
		matemat();
		rele_hndl();
		avar_hndl();
		
  		}

	if(b2Hz)
		{
		b2Hz=0;

		pcf8563_read(1);
  		}

	if(b1Hz)
		{
		b1Hz=0;
		
		samokalibr_hndl();
		num_necc_hndl();

		
		ubat_old_drv();

		kb_hndl();

		beep_hndl();

		avg_hndl();
		vz_drv();
		avz_drv();

	

	
 

		
		}
	}
}
