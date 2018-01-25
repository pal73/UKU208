#line 1 "full_can.c"
#line 1 "main.h"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"









 




 

 


#line 27 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"







 typedef unsigned int   size_t;


typedef signed char     S8;
typedef unsigned char   U8;
typedef short           S16;
typedef unsigned short  U16;
typedef int             S32;
typedef unsigned int    U32;
typedef long long       S64;
typedef unsigned long long U64;
typedef unsigned char   BIT;
typedef unsigned int    BOOL;

#line 54 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"

#line 66 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"



 





 
typedef U32 OS_SEM[2];

 

typedef U32 OS_MBX[];

 
typedef U32 OS_MUT[3];

 
typedef U32 OS_TID;

 
typedef void *OS_ID;

 
typedef U32 OS_RESULT;

 












 




#line 194 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"



 



 
extern void      os_set_env    (void);
extern void      rt_sys_init   (void (*task)(void), U8 priority, void *stk);
extern void      rt_tsk_pass   (void);
extern OS_TID    rt_tsk_self   (void);
extern OS_RESULT rt_tsk_prio   (OS_TID task_id, U8 new_prio);
extern OS_TID    rt_tsk_create (void (*task)(void), U8 priority, void *stk, void *argv);
extern OS_RESULT rt_tsk_delete (OS_TID task_id);

#line 230 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"

extern void      _os_sys_init(U32 p, void (*task)(void), U32 prio_stksz,
                                     void *stk)                        __svc_indirect(0);
extern OS_TID    _os_tsk_create (U32 p, void (*task)(void), U32 prio_stksz,
                                        void *stk, void *argv)         __svc_indirect(0);
extern OS_TID    _os_tsk_create_ex (U32 p, void (*task)(void *), U32 prio_stksz,
                                           void *stk, void *argv)      __svc_indirect(0);
extern OS_TID    _os_tsk_self (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_pass (U32 p)                                  __svc_indirect(0);
extern OS_RESULT _os_tsk_prio (U32 p, OS_TID task_id, U8 new_prio)     __svc_indirect(0);
extern OS_RESULT _os_tsk_delete (U32 p, OS_TID task_id)                __svc_indirect(0);

 
extern OS_RESULT rt_evt_wait (U16 wait_flags,  U16 timeout, BOOL and_wait);
extern void      rt_evt_set  (U16 event_flags, OS_TID task_id);
extern void      rt_evt_clr  (U16 clear_flags, OS_TID task_id);
extern U16       rt_evt_get  (void);







extern OS_RESULT _os_evt_wait(U32 p, U16 wait_flags, U16 timeout,
                                     BOOL and_wait)                    __svc_indirect(0);
extern void      _os_evt_set (U32 p, U16 event_flags, OS_TID task_id)  __svc_indirect(0);
extern void      _os_evt_clr (U32 p, U16 clear_flags, OS_TID task_id)  __svc_indirect(0);
extern U16       _os_evt_get (U32 p)                                   __svc_indirect(0);
extern void      isr_evt_set (U16 event_flags, OS_TID task_id);

 
extern void      rt_sem_init (OS_ID semaphore, U16 token_count);
extern OS_RESULT rt_sem_send (OS_ID semaphore);
extern OS_RESULT rt_sem_wait (OS_ID semaphore, U16 timeout);





extern void      _os_sem_init (U32 p, OS_ID semaphore, 
                                      U16 token_count)                 __svc_indirect(0);
extern OS_RESULT _os_sem_send (U32 p, OS_ID semaphore)                 __svc_indirect(0);
extern OS_RESULT _os_sem_wait (U32 p, OS_ID semaphore, U16 timeout)    __svc_indirect(0);
extern void      isr_sem_send (OS_ID semaphore);

 
extern void      rt_mbx_init  (OS_ID mailbox, U16 mbx_size);
extern OS_RESULT rt_mbx_send  (OS_ID mailbox, void *p_msg,    U16 timeout);
extern OS_RESULT rt_mbx_wait  (OS_ID mailbox, void **message, U16 timeout);
extern OS_RESULT rt_mbx_check (OS_ID mailbox);







extern void      _os_mbx_init (U32 p, OS_ID mailbox, U16 mbx_size)     __svc_indirect(0);
extern OS_RESULT _os_mbx_send (U32 p, OS_ID mailbox, void *message_ptr,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_wait (U32 p, OS_ID mailbox, void  **message,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_check (U32 p, OS_ID mailbox)                  __svc_indirect(0);
extern void      isr_mbx_send (OS_ID mailbox, void *message_ptr);
extern OS_RESULT isr_mbx_receive (OS_ID mailbox, void **message);

 
extern void      rt_mut_init    (OS_ID mutex);
extern OS_RESULT rt_mut_release (OS_ID mutex);
extern OS_RESULT rt_mut_wait    (OS_ID mutex, U16 timeout);





extern void      _os_mut_init (U32 p, OS_ID mutex)                     __svc_indirect(0);
extern OS_RESULT _os_mut_release (U32 p, OS_ID mutex)                  __svc_indirect(0);
extern OS_RESULT _os_mut_wait (U32 p, OS_ID mutex, U16 timeout)        __svc_indirect(0);

 
extern void      rt_dly_wait (U16 delay_time);
extern void      rt_itv_set  (U16 interval_time);
extern void      rt_itv_wait (void);





extern void      _os_dly_wait (U32 p, U16 delay_time)                  __svc_indirect(0);
extern void      _os_itv_set (U32 p, U16 interval_time)                __svc_indirect(0);
extern void      _os_itv_wait (U32 p)                                  __svc_indirect(0);

 
extern OS_ID     rt_tmr_create (U16 tcnt, U16 info);
extern OS_ID     rt_tmr_kill   (OS_ID timer);




extern OS_ID     _os_tmr_create (U32 p, U16 tcnt, U16 info)            __svc_indirect(0);
extern OS_ID     _os_tmr_kill (U32 p, OS_ID timer)                     __svc_indirect(0);

 
extern void      rt_tsk_lock   (void);
extern void      rt_tsk_unlock (void);




extern void      _os_tsk_lock (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_unlock (U32 p)                                __svc_indirect(0);

 
extern int       _init_box (void *box_mem, U32 box_size, U32 blk_size);
extern void     *_alloc_box (void *box_mem);
extern void     *_calloc_box (void *box_mem);
extern int       _free_box (void *box_mem, void *box);








 




 

typedef struct {                         
  U8  hr;                                
  U8  min;                               
  U8  sec;                               
  U8  day;                               
  U8  mon;                               
  U16 year;                              
} RL_TIME;

typedef struct {                         
  S8  name[256];                         
  U32 size;                              
  U16 fileID;                            
  U8  attrib;                            
  RL_TIME time;                          
} FINFO;

extern int finit (void);
extern int fdelete (const char *filename);
extern int frename (const char *oldname, const char *newname);
extern int ffind (const char *pattern, FINFO *info);
extern U64 ffree (const char *drive);
extern int fformat (const char *drive);
extern int fanalyse (const char *drive);
extern int fcheck (const char *drive);
extern int fdefrag (const char *drive);

 




 

 



 






 
#line 415 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"

 
#line 428 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"

 





 
#line 442 "C:\\Keil\\ARM\\RV31\\INC\\rtl.h"

 




 



extern void init_TcpNet (void);
extern void main_TcpNet (void);
extern void timer_tick (void);
extern U8   udp_get_socket (U8 tos, U8 opt, 
                            U16 (*listener)(U8 socket, U8 *remip, U16 port, U8 *buf, U16 len));
extern BOOL udp_release_socket (U8 socket);
extern BOOL udp_open (U8 socket, U16 locport);
extern BOOL udp_close (U8 socket);
extern BOOL udp_mcast_ttl (U8 socket, U8 ttl);
extern U8  *udp_get_buf (U16 size);
extern BOOL udp_send (U8 socket, U8 *remip, U16 remport, U8 *buf, U16 dlen);
extern U8   tcp_get_socket (U8 type, U8 tos, U16 tout,
                            U16 (*listener)(U8 socket, U8 event, U8 *buf, U16 len));
extern BOOL tcp_release_socket (U8 socket);
extern BOOL tcp_listen (U8 socket, U16 locport);
extern BOOL tcp_connect (U8 socket, U8 *remip, U16 remport, U16 locport);
extern U8  *tcp_get_buf (U16 size);
extern U16  tcp_max_dsize (U8 socket);
extern BOOL tcp_check_send (U8 socket);
extern U8   tcp_get_state (U8 socket);
extern BOOL tcp_send (U8 socket, U8 *buf, U16 dlen);
extern BOOL tcp_close (U8 socket);
extern BOOL tcp_abort (U8 socket);
extern void tcp_reset_window (U8 socket);
extern BOOL arp_cache_ip (U8 *ipadr, U8 type);
extern void ppp_listen (char const *user, char const *passw);
extern void ppp_connect (char const *dialnum, char const *user, char const *passw);
extern void ppp_close (void);
extern BOOL ppp_is_up (void);
extern void slip_listen (void);
extern void slip_connect (char const *dialnum);
extern void slip_close (void);
extern BOOL slip_is_up (void);
extern U8   get_host_by_name (U8 *hostn, void (*cbfunc)(U8 event, U8 *host_ip));
extern BOOL smtp_connect (U8 *ipadr, U16 port, void (*cbfunc)(U8 event));
extern void dhcp_disable (void);
extern BOOL igmp_join (U8 *group_ip);
extern BOOL igmp_leave (U8 *group_ip);
extern BOOL snmp_trap (U8 *manager_ip, U8 gen_trap, U8 spec_trap, U16 *obj_list);
extern BOOL snmp_set_community (const char *community);






 
  

 
#line 2 "main.h"

































#line 41 "main.h"





#line 58 "main.h"

#line 67 "main.h"






#line 79 "main.h"

#line 88 "main.h"











#line 105 "main.h"







#line 135 "main.h"





#line 149 "main.h"













#line 180 "main.h"

#line 203 "main.h"

































#line 383 "main.h"








































#line 451 "main.h"







		










#line 482 "main.h"

#line 494 "main.h"

#line 510 "main.h"





















#line 544 "main.h"

#line 558 "main.h"









 


#line 579 "main.h"

#line 589 "main.h"

#line 598 "main.h"

#line 607 "main.h"

#line 619 "main.h"

#line 629 "main.h"

#line 638 "main.h"

#line 646 "main.h"

#line 655 "main.h"

#line 667 "main.h"



extern char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz;
extern short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7;
extern char bFL5,bFL2,bFL,bFL_;
extern signed short main_10Hz_cnt;
extern signed short main_1Hz_cnt;



extern char cnt_of_slave;







typedef enum {

	iMn_220_IPS_TERMOKOMPENSAT,
#line 708 "main.h"
	iMn,iMn_3U,iMn_RSTKM,




	iMn_220,


	iMn_KONTUR,


	iMn_6U,


	iMn_GLONASS,


	iMn_220_V2,


	iMn_TELECORE2015,

	iSrv_sl,iNet,iNet3,iNetEM,
	iSet,iSet_3U,iSet_RSTKM,iSet_GLONASS,iSet_KONTUR,iSet_6U,iSet_220,iSet_220_IPS_TERMOKOMPENSAT,iSet_220_V2,iInv_set_sel,
	iBat,iBat_simple,iBat_li,iBat_SacredSun,iBat_universe,iInv_set,iSet_TELECORE2015,
	iMakb,
	iBps,iS2,iSet_prl,iK_prl,iDnd,
	iK,iK_3U,iK_RSTKM,iK_GLONASS,iK_KONTUR,iK_6U,iK_220,iK_220_380,iK_220_IPS_TERMOKOMPENSAT,iK_220_IPS_TERMOKOMPENSAT_IB,iK_TELECORE,
	iSpcprl,iSpc,k,Crash_0,Crash_1,iKednd,iAv_view_avt,iAKE,iSpc_termocompensat,
	iLoad,iSpc_prl_vz,iSpc_prl_ke,iKe,iVz,iAvz,iAVAR,
	iStr,iStr_3U,iStr_RSTKM,iStr_GLONASS,iStr_KONTUR,iStr_6U,iStr_220_IPS_TERMOKOMPENSAT,iStr_TELECORE2015,
	iVrs,iPrltst,iApv,
	iK_bps,iK_bps_sel,iK_bat,iK_bat_simple,iK_bat_ips_termokompensat_ib,iK_bat_sel,iK_bat_sel_TELECORE,iK_load,iK_net,iK_net3,
	iK_makb_sel,iK_makb,iK_out,
	iTst,iTst_3U,iTst_RSTKM,iTst_GLONASS,iTst_KONTUR,iTst_6U,iTst_220,iTst_220_380,iTst_220_IPS_TERMOKOMPENSAT,
	iTst_TELECORE2015,
	iTst_klbr,iTst_BPS1,iTst_BPS2,iTst_BPS12,iDebug,
	iDef,iDef_3U,iDef_RSTKM,iDef_GLONASS,iDef_KONTUR,iDef_6U,iDef_220,iDef_220_IPS_TERMOKOMPENSAT,iDef_220_V2,
	iSet_st_prl,iK_pdp,iSet_T,
	iDeb,iBat_link_set,iK_inv,iK_inv_sel,iK_byps,
	iPrl_bat_in_out,iPrl_bat_in_sel,iPdp1,iJAv_sel,iJAv_net_sel,iJAv_net,iJAv_src1,
	iTst_bps, iAusw,iAusw_prl,iAusw_set,
	iK_t_ext,iK_t_3U,iK_t_ext_6U,
	iAv_view,
	iBatLogKe,iJ_bat_ke,iBatLogVz,iJ_bat_vz,iBatLogWrk,
	iExtern,iExtern_3U,iExtern_GLONASS,iExtern_KONTUR,iExtern_6U,iExtern_220,
	iK_power_net,
	iExt_set,iExt_set_3U,iExt_set_GLONASS,iExt_set_TELECORE2015,
	iExt_dt,
	iExt_sk,iExt_sk_3U,iExt_sk_GLONASS,
	iExt_ddv,iExt_ddi,iExt_dud,iExt_dp,iSM,iLog,iLog_,iBatLog,iKlimat,iKlimat_kontur,iKlimat_TELECORE2015,
	iEnerg3,iEnerg,
	iExtern_TELECORE2015,
	iVent,
	iK_power_net3,
	iAvt,iLan_set,
	iInv,iInv_v2,
	iNpn_set,
	iByps,iInv_tabl,iSet_bat_sel,
	iBps_list,
	iSpch_set,
	iAvt_set_sel,iAvt_set,
	iOut_volt_contr,iDop_rele_set,iBlok_ips_set}i_enum;

typedef struct  
{

i_enum i;
signed char s_i;
signed char s_i1;
signed char s_i2;
signed char i_s;
} stuct_ind;







extern stuct_ind a_ind,b_ind[10],c_ind;
extern signed short ptr_ind;
extern char lcd_buffer[200+100];
extern signed char parol[3];
extern char phase;
extern char lcd_bitmap[1024];
extern char dig[5];
extern signed short ind_pointer;
extern char zero_on;
extern char mnemo_cnt;
extern char simax;
extern short av_j_si_max;
extern const char ABCDEF[];
extern const char sm_mont[13][4]; 




extern signed short Ktsrc[2];
extern signed short Kusrc[2];
extern signed short Kisrc[2];
extern signed short Ki0src[2];
extern signed short Kubat[2];
extern signed short Kubatm[2];
extern unsigned short Kibat0[2];
extern signed short Kibat1[2];
extern signed short Ktbat[2];
extern signed short Kunet;
extern signed short Ktext[3];
extern signed short Kuload;
extern signed short Kunet_ext[3];
extern signed short KunetA;
extern signed short KunetB;
extern signed short KunetC;
extern signed short Kubps;
extern signed short Kuout;

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
extern signed short UVZ;
extern signed short IMAX;
extern signed short IMIN;
extern signed short APV_ON;
extern signed short IZMAX;
extern signed short U0B;
extern signed short TZAS;
extern signed short VZ_HR;
extern signed short TBAT;
extern signed short U_AVT;
extern signed short DU;
extern signed short PAR;
extern signed short TBATMAX;
extern signed short TBATSIGN;
extern signed short UBM_AV;
extern signed short RELE_LOG;
extern signed short TBOXMAX;
extern signed short TBOXREG;
extern signed short TBOXVENTMAX;
extern signed short TLOADDISABLE;
extern signed short TLOADENABLE;
extern signed short TBATDISABLE;
extern signed short TBATENABLE;
extern signed short TBOXMAX;
extern signed short TBOXREG;
extern signed short TBOXVENTMAX;
extern signed short TLOADDISABLE;
extern signed short TLOADENABLE;
extern signed short TBATDISABLE;
extern signed short TBATENABLE;
extern signed short TVENTON;
extern signed short TVENTOFF;
extern signed short TWARMON;
extern signed short TWARMOFF;
typedef enum {rvsAKB=0,rvsEXT,rvsBPS} enum_releventsign;
extern enum_releventsign RELEVENTSIGN;
extern signed short TZNPN;
extern signed short UONPN;
extern signed short UVNPN;
typedef enum {npnoOFF=0,npnoRELEVENT,npnoRELEAVBAT2} enum_npn_out;
extern enum_npn_out NPN_OUT;
typedef enum {npnsULOAD=0,npnsAVNET} enum_npn_sign;
extern enum_npn_sign NPN_SIGN;
extern signed short TERMOKOMPENS;
extern signed short TBOXVENTON; 
extern signed short TBOXVENTOFF;
extern signed short TBOXWARMON; 
extern signed short TBOXWARMOFF;
extern signed short BAT_TYPE;	
extern signed short DU_LI_BAT;	
extern signed short FORVARDBPSCHHOUR;	
extern signed short NUMBAT;
extern signed short NUMBAT_TELECORE;
extern signed short NUMIST;
extern signed short NUMINV;
extern signed short NUMDT;
extern signed short NUMSK;
extern signed short NUMEXT;
extern signed short NUMAVT;
extern signed short NUMMAKB;
extern signed short NUMBYPASS;
extern signed short U_OUT_KONTR_MAX;
extern signed short U_OUT_KONTR_MIN;
extern signed short U_OUT_KONTR_DELAY;
extern signed short DOP_RELE_FUNC;

typedef enum {apvON=0x01,apvOFF=0x00}enum_apv_on;
extern enum_apv_on APV_ON1,APV_ON2;

extern signed short APV_ON2_TIME;

typedef enum {bisON=0x0055,bisOFF=0x00aa}enum_bat_is_on;
extern enum_bat_is_on BAT_IS_ON[2];

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

typedef enum {AVZ_1=1,AVZ_2=2,AVZ_3=3,AVZ_6=6,AVZ_12=12,AVZ_OFF=0}enum_avz;
extern enum_avz AVZ;

extern unsigned short HOUR_AVZ;
extern unsigned short MIN_AVZ;
extern unsigned short SEC_AVZ;
extern unsigned short DATE_AVZ;
extern unsigned short MONTH_AVZ;
extern unsigned short YEAR_AVZ;
extern unsigned short AVZ_TIME;
typedef enum {mnON=0x55,mnOFF=0xAA}enum_mnemo_on;
extern enum_mnemo_on MNEMO_ON;
extern unsigned short MNEMO_TIME;
extern signed short POWER_CNT_ADRESS;

extern signed short ETH_IS_ON;
extern signed short ETH_DHCP_ON;
extern signed short ETH_IP_1;
extern signed short ETH_IP_2;
extern signed short ETH_IP_3;
extern signed short ETH_IP_4;
extern signed short ETH_MASK_1;
extern signed short ETH_MASK_2;
extern signed short ETH_MASK_3;
extern signed short ETH_MASK_4;
extern signed short ETH_TRAP1_IP_1;
extern signed short ETH_TRAP1_IP_2;
extern signed short ETH_TRAP1_IP_3;
extern signed short ETH_TRAP1_IP_4;
extern signed short ETH_TRAP2_IP_1;
extern signed short ETH_TRAP2_IP_2;
extern signed short ETH_TRAP2_IP_3;
extern signed short ETH_TRAP2_IP_4;
extern signed short ETH_TRAP3_IP_1;
extern signed short ETH_TRAP3_IP_2;
extern signed short ETH_TRAP3_IP_3;
extern signed short ETH_TRAP3_IP_4;
extern signed short ETH_TRAP4_IP_1;
extern signed short ETH_TRAP4_IP_2;
extern signed short ETH_TRAP4_IP_3;
extern signed short ETH_TRAP4_IP_4;
extern signed short ETH_TRAP5_IP_1;
extern signed short ETH_TRAP5_IP_2;
extern signed short ETH_TRAP5_IP_3;
extern signed short ETH_TRAP5_IP_4;
extern signed short ETH_SNMP_PORT_READ;
extern signed short ETH_SNMP_PORT_WRITE;
extern signed short ETH_GW_1;
extern signed short ETH_GW_2;
extern signed short ETH_GW_3;
extern signed short ETH_GW_4;

extern signed short RELE_VENT_LOGIC;

extern signed short MODBUS_ADRESS;
extern signed short MODBUS_BAUDRATE;
extern signed short BAT_LINK;



typedef struct
     {
	char 		_cnt_to_block;
	signed short	_Ub;
     signed short	_Ubm;
     signed short	_dUbm;
	signed short	_Ib;
	signed short	_Tb;
	char 		_nd;
	char 		_cnt_wrk;
	char 		_wrk;
	unsigned short _zar;
	char 		_full_ver;
	signed long 	_zar_cnt;
	signed long 	_zar_cnt_ke;
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
	signed long 	_resurs_cnt;
	signed short 	_cnt_as; 	
     
	
	} BAT_STAT; 
extern BAT_STAT bat[2],bat_ips;
extern signed short		bat_u_old_cnt;
extern signed short 	Ib_ips_termokompensat;


typedef enum {bsOFF=0,bsCOMM_ON,bsOK} enum_batStat;


typedef struct
     {
	
	signed short	_Ub;
     
     
	signed short	_Ib;
	signed short	_Tb;
	char 		_nd;
	char   		_soh;
	char 		_soc;
	signed short   _ratCap;
	char 		_comErrStat;	
	enum_batStat	_batStat;
	signed short 	_cclv;
	char 		_rbt;
	short 		_canErrorCnt;
	char			_canError;
	char 		_485Error;
	short 		_485ErrorCnt;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
     
	
	} LI_BAT_STAT; 
extern LI_BAT_STAT li_bat;



typedef struct
     {
	signed short 	_Iout;
	signed short 	_Uout;
	signed short 	_Pout;
	signed short 	_Unet; 	
	signed short 	_Uin;
	char			_T;
	char 		_flags;
	char			_cnt;
	char 		_adress;
	} BYPS_STAT; 
extern BYPS_STAT byps;



typedef struct
     {
	signed short	_U[5];
	signed short	_Ub[5];
	signed short	_T[5];
	signed short	_T_nd[5];
	signed short 	_cnt; 	
	} MAKB_STAT; 
extern MAKB_STAT makb[4];



typedef struct
     {
	signed short	_max_cell_volt;
	signed short	_min_cell_volt;
	signed short	_max_cell_temp;
	signed short	_min_cell_temp;
	signed short	_tot_bat_volt;
	signed short	_ch_curr;
	signed short	_dsch_curr;
	signed short	_rat_cap;
	signed short	_s_o_h;
	signed short	_s_o_c;
	signed short	_c_c_l_v;
	signed short	_r_b_t;
	signed short	_b_p_ser_num;
	signed short   _flags1;
	signed short 	_flags2;
	signed short 	_communication2lvlErrorStat; 	
	signed short	_communication2lvlErrorCnt;  	
	signed short 	_cnt;
	signed short 	_communicationFullErrorStat;	
	signed short   _battIsOn;		
	char 		_plazma[8];		
	signed short 	_isOnCnt;
	signed short	_s_o_c_abs;		
	signed short	_plazma_ss;
	signed short	_zar_percent;	
	signed char		_cell_temp_1;	
	signed char		_cell_temp_2;	
	signed char		_cell_temp_3;	
	signed char		_cell_temp_4;	
	signed char		_cell_temp_ambient;	
	signed char		_cell_temp_power;	
	} LAKB_STAT; 
extern LAKB_STAT lakb[3];
extern char lakb_damp[1][42];
extern char bLAKB_KONF_CH;
extern char bLAKB_KONF_CH_old;
extern char lakb_ison_mass[7];
extern short lakb_mn_ind_cnt;
extern char bLAKB_KONF_CH_EN;
extern char bRS485ERR;
extern short LBAT_STRUKT;
extern char lakb_error_cnt;	
extern short numOfPacks,numOfPacks_;
extern short numOfCells, numOfTemperCells, baseOfData;
extern short lakb_stat_comm_error;	
extern short lakbNotErrorNum;		
extern short lakbKanErrorCnt;		
extern short lakbKanErrorStat;		





extern char can_slot[12][16];
extern char plazma_can_inv[3];





typedef struct
     {
     enum {dSRC=3,dINV=5,dNET_METR=7,dIBAT_METR=9,dMAKB=11}_device;
	char _av;
	
	
	
	
     enum {bsAPV,bsWRK,bsRDY,bsBL,bsAV,bsOFF_AV_NET}_state;
     char _cnt;
     char _cnt_old;
     char _cnt_more2;
     char _buff[20]; 
     
     
     
     
     signed _Uii; 
     signed _Uin;
     signed _Ii;
     signed _Ti; 
     char _flags_tu;
     
     
     
     
     
     signed _vol_u;
     signed _vol_i;
     char _is_on_cnt;
     
     int _ist_blok_host_cnt;
     short _blok_cnt; 
     char _flags_tm;
	signed short _overload_av_cnt;     
     signed short _temp_av_cnt;
     signed short _umax_av_cnt;
     signed short _umin_av_cnt;
     signed _rotor;
     signed  short _x_; 
     char _adr_ee;
	char _last_avar;
     } BPS_STAT; 
extern BPS_STAT bps[32];



typedef struct
     {
	char _av;
	
	
	
	
     enum {isAPV,isWRK,isRDY,isBL,isAV,isOFF_AV_NET}_state;
     char _cnt;
     char _cnt_old;
     char _cnt_more2;
     char _buff[16]; 
     signed _Uio; 
     signed _Ii;
     signed _Ti; 
	signed _Uil;
	signed _Uin;
	signed _Pio;
     char _flags_tu;
     signed _vol_u;
     signed _vol_i;
     char _is_on_cnt;
     
     int _ist_blok_host_cnt;
     short _blok_cnt; 
     char _flags_tm;
	char _flags_tm_old;
	signed short _overload_av_cnt;     
     signed short _temp_av_cnt;
     signed short _umax_av_cnt;
     signed short _umin_av_cnt;
     signed _rotor;
     signed  short _x_; 
     char _adr_ee;
	char _last_avar;
	char _Pnom;
	char _Uoutmin;
	char _Uoutmax;
	char _net_contr_en;
	char _pwm_en;
	char _phase_mode;
     } INV_STAT; 




extern INV_STAT inv[20];

extern char first_inv_slot;



extern signed short load_U;
extern signed short load_I;



extern signed short bps_U;
extern signed short out_U;
extern signed short bps_I;



extern signed short net_U,net_Ustore,net_Ua,net_Ub,net_Uc;
extern char bFF,bFF_;
extern signed short net_F,hz_out,hz_out_cnt,net_F3;
extern signed char unet_drv_cnt;
extern char net_av;


extern char plazma_plazma_plazma;

void bitmap_hndl(void);
void ind_hndl(void);
__irq void timer1_interrupt(void);
__irq void timer0_interrupt(void); 





extern char tout_max_cnt[4],tout_min_cnt[4];
typedef enum {tNORM,tMAX,tMIN}enum_tout_stat;
extern enum_tout_stat tout_stat[4];
extern signed short t_ext[3];
extern BOOL ND_EXT[3];
extern signed char sk_cnt[4],sk_av_cnt[4];
typedef enum  {ssOFF,ssON} enum_sk_stat;
extern enum_sk_stat sk_stat[4];
typedef enum  {sasOFF,sasON} enum_sk_av_stat;
extern enum_sk_av_stat sk_av_stat[4],sk_av_stat_old[4];
extern signed short t_box,t_box_warm,t_box_vent;



extern BOOL bSILENT;



typedef enum {tstOFF,tst1,tst2} enum_tst_state;
extern enum_tst_state tst_state[15];



extern char sign_U[2],sign_I[2];
extern char superviser_cnt;



extern unsigned short adc_buff_ext_[3];
extern unsigned short Uvv[3];
extern unsigned short Uvv0;
extern short pos_vent;
extern short t_ext_can;
extern char t_ext_can_nd;



extern char eb2_data[30];
extern short eb2_data_short[10];
extern short Uvv_eb2[3],Upes_eb2[3];
extern short Kvv_eb2[3],Kpes_eb2[3];



extern signed short vvod_pos;



extern signed long power_summary;
extern signed short power_current;
extern signed long power_summary_tempo,power_summary_tempo_old;
extern signed short power_current_tempo,power_current_tempo_old;
extern char powerSummaryCnt;
extern char powerCurrentCnt;


extern char bRESET;
extern char bRESET_EXT;
extern char bRESET_INT_WDT;
extern char bRESET_EXT_WDT;



extern signed short main_vent_pos;
extern signed char t_box_cnt;
typedef enum  {mvsOFF,mvsON} enum_mixer_vent_stat;
extern enum_mixer_vent_stat mixer_vent_stat;
typedef struct
     {
	signed short _T[4];
	char _nd[4];
	signed short _T_dispers[4];
	char _max_dispers_num;
	signed short _max_dispers;
    	signed short _avg1;
	signed short _avg2;
	char _avg_cnt;
     } INT_BOX_TEMPER;
extern INT_BOX_TEMPER ibt;
typedef enum {tbdsON,tbdsOFF,tbdsMNL} enum_tbatdisable_stat;
extern enum_tbatdisable_stat tbatdisable_stat;
typedef enum {tldsON,tldsOFF,tldsMNL} enum_tloaddisable_stat;
extern enum_tloaddisable_stat tloaddisable_stat;
typedef enum {atsOFF,atsON} enum_av_tbox_stat;
extern enum_av_tbox_stat av_tbox_stat;
extern signed short av_tbox_cnt;
extern char tbatdisable_cmnd,tloaddisable_cmnd;
extern short tbatdisable_cnt,tloaddisable_cnt;
#line 1406 "main.h"

#line 1417 "main.h"



extern char ext_can_cnt;


signed short abs_pal(signed short in);
void ADC_IRQHandler(void);




typedef enum  {avtOFF,avtON} enum_avt_stat;
extern enum_avt_stat avt_stat[12],avt_stat_old[12]; 



extern signed long ibat_metr_buff_[2];
extern short bIBAT_SMKLBR;



extern signed short npn_tz_cnt;
typedef enum {npnsOFF=0,npnsON} enum_npn_stat;
extern enum_npn_stat npn_stat;

extern char snmp_plazma;


extern char ips_bat_av_vzvod;
extern char ips_bat_av_stat;

extern char rel_warm_plazma;
extern char can_byps_plazma0,can_byps_plazma1;

extern short plazma_bat_drv0,plazma_bat_drv1,bat_drv_cnt_cnt;
extern unsigned short bat_drv_rx_cnt;
extern char bat_drv_rx_buff[512];
extern char bat_drv_rx_in;

extern short can_plazma;




extern signed short TELECORE2015_KLIMAT_WARM_SIGNAL;
extern signed short TELECORE2015_KLIMAT_VENT_SIGNAL;
extern signed short TELECORE2015_KLIMAT_WARM_ON;
extern signed short TELECORE2015_KLIMAT_WARM_OFF;
extern signed short TELECORE2015_KLIMAT_CAP;
extern signed short TELECORE2015_KLIMAT_VENT_ON;
extern signed short TELECORE2015_KLIMAT_VENT_OFF;
extern signed short TELECORE2015_KLIMAT_VVENT_ON;
extern signed short TELECORE2015_KLIMAT_VVENT_OFF;














extern signed short speedChrgCurr;			
extern signed short speedChrgVolt;			
extern signed short speedChrgTimeInHour; 	
extern signed short speedChrgAvtEn;	 	
extern signed short speedChrgDU;	    		
extern signed short speedChIsOn;			
extern signed long  speedChTimeCnt;		
extern signed short speedChrgBlckSrc;		
extern signed short speedChrgBlckLog;		
extern signed short speedChrgBlckStat;		
extern char  		speedChrgShowCnt;		



extern signed short ipsBlckSrc;
extern signed short ipsBlckLog;
extern signed short ipsBlckStat;



extern signed short outVoltContrHndlCnt;		
extern signed short outVoltContrHndlCnt_;		
extern char uout_av;


extern short plazma_numOfCells;
extern short plazma_numOfTemperCells;
extern short plazma_numOfPacks;

extern char plazma_ztt[2];



 
#line 2 "full_can.c"
#line 1 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"




















 









 

typedef enum IRQn
{
 
  NonMaskableInt_IRQn           = -14,       
  MemoryManagement_IRQn         = -12,       
  BusFault_IRQn                 = -11,       
  UsageFault_IRQn               = -10,       
  SVCall_IRQn                   = -5,        
  DebugMonitor_IRQn             = -4,        
  PendSV_IRQn                   = -2,        
  SysTick_IRQn                  = -1,        

 
  WDT_IRQn                      = 0,         
  TIMER0_IRQn                   = 1,         
  TIMER1_IRQn                   = 2,         
  TIMER2_IRQn                   = 3,         
  TIMER3_IRQn                   = 4,         
  UART0_IRQn                    = 5,         
  UART1_IRQn                    = 6,         
  UART2_IRQn                    = 7,         
  UART3_IRQn                    = 8,         
  PWM1_IRQn                     = 9,         
  I2C0_IRQn                     = 10,        
  I2C1_IRQn                     = 11,        
  I2C2_IRQn                     = 12,        
  SPI_IRQn                      = 13,        
  SSP0_IRQn                     = 14,        
  SSP1_IRQn                     = 15,        
  PLL0_IRQn                     = 16,        
  RTC_IRQn                      = 17,        
  EINT0_IRQn                    = 18,        
  EINT1_IRQn                    = 19,        
  EINT2_IRQn                    = 20,        
  EINT3_IRQn                    = 21,        
  ADC_IRQn                      = 22,        
  BOD_IRQn                      = 23,        
  USB_IRQn                      = 24,        
  CAN_IRQn                      = 25,        
  DMA_IRQn                      = 26,        
  I2S_IRQn                      = 27,        
  ENET_IRQn                     = 28,        
  RIT_IRQn                      = 29,        
  MCPWM_IRQn                    = 30,        
  QEI_IRQn                      = 31,        
  PLL1_IRQn                     = 32,        
  USBActivity_IRQn              = 33,        
  CANActivity_IRQn              = 34,        
} IRQn_Type;






 

 





#line 1 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"



















 




















































 

 
 
 
 
 
 
 
 


#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"
 
 





 









#line 25 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"

     







     










     











#line 260 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"



 


#line 86 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"

















 

#line 112 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"





 


 





 






 
typedef struct
{
  volatile uint32_t ISER[8];                       
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                       
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                       
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                       
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                       
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                       
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                          
}  NVIC_Type;


 
typedef struct
{
  volatile const  uint32_t CPUID;                         
  volatile uint32_t ICSR;                          
  volatile uint32_t VTOR;                          
  volatile uint32_t AIRCR;                         
  volatile uint32_t SCR;                           
  volatile uint32_t CCR;                           
  volatile uint8_t  SHP[12];                       
  volatile uint32_t SHCSR;                         
  volatile uint32_t CFSR;                          
  volatile uint32_t HFSR;                          
  volatile uint32_t DFSR;                          
  volatile uint32_t MMFAR;                         
  volatile uint32_t BFAR;                          
  volatile uint32_t AFSR;                          
  volatile const  uint32_t PFR[2];                        
  volatile const  uint32_t DFR;                           
  volatile const  uint32_t ADR;                           
  volatile const  uint32_t MMFR[4];                       
  volatile const  uint32_t ISAR[5];                       
} SCB_Type;


 
typedef struct
{
  volatile uint32_t CTRL;                          
  volatile uint32_t LOAD;                          
  volatile uint32_t VAL;                           
  volatile const  uint32_t CALIB;                         
} SysTick_Type;


 
typedef struct
{
  volatile  union  
  {
    volatile  uint8_t    u8;                        
    volatile  uint16_t   u16;                       
    volatile  uint32_t   u32;                       
  }  PORT [32];                                
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                           
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                           
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                           
       uint32_t RESERVED3[29];
  volatile uint32_t IWR;                           
  volatile uint32_t IRR;                           
  volatile uint32_t IMCR;                          
       uint32_t RESERVED4[43];
  volatile uint32_t LAR;                           
  volatile uint32_t LSR;                           
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                          
  volatile const  uint32_t PID5;
  volatile const  uint32_t PID6;
  volatile const  uint32_t PID7;
  volatile const  uint32_t PID0;
  volatile const  uint32_t PID1;
  volatile const  uint32_t PID2;
  volatile const  uint32_t PID3;
  volatile const  uint32_t CID0;
  volatile const  uint32_t CID1;
  volatile const  uint32_t CID2;
  volatile const  uint32_t CID3;
} ITM_Type;


 
typedef struct
{
       uint32_t RESERVED0;
  volatile const  uint32_t ICTR;                          



       uint32_t RESERVED1;

} InterruptType_Type;


 

typedef struct
{
  volatile const  uint32_t TYPE;                          
  volatile uint32_t CTRL;                          
  volatile uint32_t RNR;                           
  volatile uint32_t RBAR;                          
  volatile uint32_t RASR;                          
  volatile uint32_t RBAR_A1;                       
  volatile uint32_t RASR_A1;                       
  volatile uint32_t RBAR_A2;                       
  volatile uint32_t RASR_A2;                       
  volatile uint32_t RBAR_A3;                       
  volatile uint32_t RASR_A3;                       
} MPU_Type;



 
typedef struct
{
  volatile uint32_t DHCSR;                         
  volatile  uint32_t DCRSR;                         
  volatile uint32_t DCRDR;                         
  volatile uint32_t DEMCR;                         
} CoreDebug_Type;


 
#line 274 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"

#line 281 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"










 






#line 311 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"


 


 




#line 336 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"


 
 
 
 









 
extern uint32_t __get_PSP(void);









 
extern void __set_PSP(uint32_t topOfProcStack);









 
extern uint32_t __get_MSP(void);









 
extern void __set_MSP(uint32_t topOfMainStack);








 
extern uint32_t __REV16(uint16_t value);








 
extern int32_t __REVSH(int16_t value);


#line 502 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"









 









 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}








 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0x1ff);
}









 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}








 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}








 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}








 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}








 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}








 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}





#line 1044 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"



 













 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  
  reg_value  = ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                     
  reg_value &= ~((0xFFFFU << 16) | (0x0F << 8));                               
  reg_value  = ((reg_value | (0x5FA << 16) | (PriorityGroupTmp << 8)));   
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR = reg_value;
}









 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR >> 8) & 0x07);                                           
}









 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}









 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000) + 0x0100))->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}













 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 5)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)] = ((priority << (8 - 5)) & 0xff);    }         
}















 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 5)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)]           >> (8 - 5)));  }  
}
















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
 
  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}

















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
  
  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}



 



 














 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > ((1<<24) -1))  return (1);                                              

  ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD  =  (ticks & ((1<<24) -1)) - 1;                                       
  NVIC_SetPriority (SysTick_IRQn, (1<<5) - 1);                             
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL   =  (0x00);                                                               
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL = (1 << 2) | (1<<0) | (1<<1);  
  return (0);                                                                             
}







 








 
static __inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16) | (((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (0x700)) | (1<<2));  
  __dsb(0);                                                                                            
  while(1);                                                                             
}


 











 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (ch == '\n') ITM_SendChar('\r');
  
  if ((((CoreDebug_Type *) (0xE000EDF0))->DEMCR & (1 << 24))  &&
      (((ITM_Type *) (0xE0000000))->TCR & 1)                  &&
      (((ITM_Type *) (0xE0000000))->TER & (1UL << 0))  ) 
  {
    while (((ITM_Type *) (0xE0000000))->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000))->PORT[0].u8 = (uint8_t) ch;
  }  
  return (ch);
}







 
#line 97 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"
#line 1 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\system_LPC17xx.h"




















 









extern uint32_t SystemFrequency;     










 
extern void SystemInit (void);





#line 98 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"


 
 
 


#pragma anon_unions


 
typedef struct
{
  volatile uint32_t FLASHCFG;                
       uint32_t RESERVED0[31];
  volatile uint32_t PLL0CON;                 
  volatile uint32_t PLL0CFG;
  volatile const  uint32_t PLL0STAT;
  volatile  uint32_t PLL0FEED;
       uint32_t RESERVED1[4];
  volatile uint32_t PLL1CON;
  volatile uint32_t PLL1CFG;
  volatile const  uint32_t PLL1STAT;
  volatile  uint32_t PLL1FEED;
       uint32_t RESERVED2[4];
  volatile uint32_t PCON;
  volatile uint32_t PCONP;
       uint32_t RESERVED3[15];
  volatile uint32_t CCLKCFG;
  volatile uint32_t USBCLKCFG;
  volatile uint32_t CLKSRCSEL;
  volatile uint32_t	CANSLEEPCLR;
  volatile uint32_t	CANWAKEFLAGS;
       uint32_t RESERVED4[10];
  volatile uint32_t EXTINT;                  
       uint32_t RESERVED5;
  volatile uint32_t EXTMODE;
  volatile uint32_t EXTPOLAR;
       uint32_t RESERVED6[12];
  volatile uint32_t RSID;                    
       uint32_t RESERVED7[7];
  volatile uint32_t SCS;                     
  volatile uint32_t IRCTRIM;                 
  volatile uint32_t PCLKSEL0;
  volatile uint32_t PCLKSEL1;
       uint32_t RESERVED8[4];
  volatile uint32_t USBIntSt;                
  volatile uint32_t DMAREQSEL;
  volatile uint32_t CLKOUTCFG;               
 } LPC_SC_TypeDef;

 
typedef struct
{
  volatile uint32_t PINSEL0;
  volatile uint32_t PINSEL1;
  volatile uint32_t PINSEL2;
  volatile uint32_t PINSEL3;
  volatile uint32_t PINSEL4;
  volatile uint32_t PINSEL5;
  volatile uint32_t PINSEL6;
  volatile uint32_t PINSEL7;
  volatile uint32_t PINSEL8;
  volatile uint32_t PINSEL9;
  volatile uint32_t PINSEL10;
       uint32_t RESERVED0[5];
  volatile uint32_t PINMODE0;
  volatile uint32_t PINMODE1;
  volatile uint32_t PINMODE2;
  volatile uint32_t PINMODE3;
  volatile uint32_t PINMODE4;
  volatile uint32_t PINMODE5;
  volatile uint32_t PINMODE6;
  volatile uint32_t PINMODE7;
  volatile uint32_t PINMODE8;
  volatile uint32_t PINMODE9;
  volatile uint32_t PINMODE_OD0;
  volatile uint32_t PINMODE_OD1;
  volatile uint32_t PINMODE_OD2;
  volatile uint32_t PINMODE_OD3;
  volatile uint32_t PINMODE_OD4;
  volatile uint32_t I2CPADCFG;
} LPC_PINCON_TypeDef;

 
typedef struct
{
  union {
    volatile uint32_t FIODIR;
    struct {
      volatile uint16_t FIODIRL;
      volatile uint16_t FIODIRH;
    };
    struct {
      volatile uint8_t  FIODIR0;
      volatile uint8_t  FIODIR1;
      volatile uint8_t  FIODIR2;
      volatile uint8_t  FIODIR3;
    };
  };
  uint32_t RESERVED0[3];
  union {
    volatile uint32_t FIOMASK;
    struct {
      volatile uint16_t FIOMASKL;
      volatile uint16_t FIOMASKH;
    };
    struct {
      volatile uint8_t  FIOMASK0;
      volatile uint8_t  FIOMASK1;
      volatile uint8_t  FIOMASK2;
      volatile uint8_t  FIOMASK3;
    };
  };
  union {
    volatile uint32_t FIOPIN;
    struct {
      volatile uint16_t FIOPINL;
      volatile uint16_t FIOPINH;
    };
    struct {
      volatile uint8_t  FIOPIN0;
      volatile uint8_t  FIOPIN1;
      volatile uint8_t  FIOPIN2;
      volatile uint8_t  FIOPIN3;
    };
  };
  union {
    volatile uint32_t FIOSET;
    struct {
      volatile uint16_t FIOSETL;
      volatile uint16_t FIOSETH;
    };
    struct {
      volatile uint8_t  FIOSET0;
      volatile uint8_t  FIOSET1;
      volatile uint8_t  FIOSET2;
      volatile uint8_t  FIOSET3;
    };
  };
  union {
    volatile  uint32_t FIOCLR;
    struct {
      volatile  uint16_t FIOCLRL;
      volatile  uint16_t FIOCLRH;
    };
    struct {
      volatile  uint8_t  FIOCLR0;
      volatile  uint8_t  FIOCLR1;
      volatile  uint8_t  FIOCLR2;
      volatile  uint8_t  FIOCLR3;
    };
  };
} LPC_GPIO_TypeDef;

typedef struct
{
  volatile const  uint32_t IntStatus;
  volatile const  uint32_t IO0IntStatR;
  volatile const  uint32_t IO0IntStatF;
  volatile  uint32_t IO0IntClr;
  volatile uint32_t IO0IntEnR;
  volatile uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  volatile const  uint32_t IO2IntStatR;
  volatile const  uint32_t IO2IntStatF;
  volatile  uint32_t IO2IntClr;
  volatile uint32_t IO2IntEnR;
  volatile uint32_t IO2IntEnF;
} LPC_GPIOINT_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
       uint32_t RESERVED0[2];
  volatile uint32_t EMR;
       uint32_t RESERVED1[12];
  volatile uint32_t CTCR;
} LPC_TIM_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
  volatile const  uint32_t CR2;
  volatile const  uint32_t CR3;
       uint32_t RESERVED0;
  volatile uint32_t MR4;
  volatile uint32_t MR5;
  volatile uint32_t MR6;
  volatile uint32_t PCR;
  volatile uint32_t LER;
       uint32_t RESERVED1[7];
  volatile uint32_t CTCR;
} LPC_PWM_TypeDef;

 
typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[7];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  volatile uint8_t  SCR;
       uint8_t  RESERVED3[3];
  volatile uint32_t ACR;
  volatile uint8_t  ICR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  FDR;
       uint8_t  RESERVED5[7];
  volatile uint8_t  TER;
       uint8_t  RESERVED6[39];
  volatile uint32_t FIFOLVL;
} LPC_UART_TypeDef;

typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[7];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  volatile uint8_t  SCR;
       uint8_t  RESERVED3[3];
  volatile uint32_t ACR;
  volatile uint8_t  ICR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  FDR;
       uint8_t  RESERVED5[7];
  volatile uint8_t  TER;
       uint8_t  RESERVED6[39];
  volatile uint32_t FIFOLVL;
} LPC_UART0_TypeDef;

typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  MCR;
       uint8_t  RESERVED2[3];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED3[3];
  volatile const  uint8_t  MSR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  SCR;
       uint8_t  RESERVED5[3];
  volatile uint32_t ACR;
       uint32_t RESERVED6;
  volatile uint32_t FDR;
       uint32_t RESERVED7;
  volatile uint8_t  TER;
       uint8_t  RESERVED8[27];
  volatile uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  volatile uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  volatile uint8_t  RS485DLY;
       uint8_t  RESERVED11[3];
  volatile uint32_t FIFOLVL;
} LPC_UART1_TypeDef;

 
typedef struct
{
  volatile uint32_t SPCR;
  volatile const  uint32_t SPSR;
  volatile uint32_t SPDR;
  volatile uint32_t SPCCR;
       uint32_t RESERVED0[3];
  volatile uint32_t SPINT;
} LPC_SPI_TypeDef;

 
typedef struct
{
  volatile uint32_t CR0;
  volatile uint32_t CR1;
  volatile uint32_t DR;
  volatile const  uint32_t SR;
  volatile uint32_t CPSR;
  volatile uint32_t IMSC;
  volatile uint32_t RIS;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t DMACR;
} LPC_SSP_TypeDef;

 
typedef struct
{
  volatile uint32_t I2CONSET;
  volatile const  uint32_t I2STAT;
  volatile uint32_t I2DAT;
  volatile uint32_t I2ADR0;
  volatile uint32_t I2SCLH;
  volatile uint32_t I2SCLL;
  volatile  uint32_t I2CONCLR;
  volatile uint32_t MMCTRL;
  volatile uint32_t I2ADR1;
  volatile uint32_t I2ADR2;
  volatile uint32_t I2ADR3;
  volatile const  uint32_t I2DATA_BUFFER;
  volatile uint32_t I2MASK0;
  volatile uint32_t I2MASK1;
  volatile uint32_t I2MASK2;
  volatile uint32_t I2MASK3;
} LPC_I2C_TypeDef;

 
typedef struct
{
  volatile uint32_t I2SDAO;
  volatile uint32_t I2SDAI;
  volatile  uint32_t I2STXFIFO;
  volatile const  uint32_t I2SRXFIFO;
  volatile const  uint32_t I2SSTATE;
  volatile uint32_t I2SDMA1;
  volatile uint32_t I2SDMA2;
  volatile uint32_t I2SIRQ;
  volatile uint32_t I2STXRATE;
  volatile uint32_t I2SRXRATE;
  volatile uint32_t I2STXBITRATE;
  volatile uint32_t I2SRXBITRATE;
  volatile uint32_t I2STXMODE;
  volatile uint32_t I2SRXMODE;
} LPC_I2S_TypeDef;

 
typedef struct
{
  volatile uint32_t RICOMPVAL;
  volatile uint32_t RIMASK;
  volatile uint8_t  RICTRL;
       uint8_t  RESERVED0[3];
  volatile uint32_t RICOUNTER;
} LPC_RIT_TypeDef;

 
typedef struct
{
  volatile uint8_t  ILR;
       uint8_t  RESERVED0[7];
  volatile uint8_t  CCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  CIIR;
       uint8_t  RESERVED2[3];
  volatile uint8_t  AMR;
       uint8_t  RESERVED3[3];
  volatile const  uint32_t CTIME0;
  volatile const  uint32_t CTIME1;
  volatile const  uint32_t CTIME2;
  volatile uint8_t  SEC;
       uint8_t  RESERVED4[3];
  volatile uint8_t  MIN;
       uint8_t  RESERVED5[3];
  volatile uint8_t  HOUR;
       uint8_t  RESERVED6[3];
  volatile uint8_t  DOM;
       uint8_t  RESERVED7[3];
  volatile uint8_t  DOW;
       uint8_t  RESERVED8[3];
  volatile uint16_t DOY;
       uint16_t RESERVED9;
  volatile uint8_t  MONTH;
       uint8_t  RESERVED10[3];
  volatile uint16_t YEAR;
       uint16_t RESERVED11;
  volatile uint32_t CALIBRATION;
  volatile uint32_t GPREG0;
  volatile uint32_t GPREG1;
  volatile uint32_t GPREG2;
  volatile uint32_t GPREG3;
  volatile uint32_t GPREG4;
  volatile uint8_t  RTC_AUXEN;
       uint8_t  RESERVED12[3];
  volatile uint8_t  RTC_AUX;
       uint8_t  RESERVED13[3];
  volatile uint8_t  ALSEC;
       uint8_t  RESERVED14[3];
  volatile uint8_t  ALMIN;
       uint8_t  RESERVED15[3];
  volatile uint8_t  ALHOUR;
       uint8_t  RESERVED16[3];
  volatile uint8_t  ALDOM;
       uint8_t  RESERVED17[3];
  volatile uint8_t  ALDOW;
       uint8_t  RESERVED18[3];
  volatile uint16_t ALDOY;
       uint16_t RESERVED19;
  volatile uint8_t  ALMON;
       uint8_t  RESERVED20[3];
  volatile uint16_t ALYEAR;
       uint16_t RESERVED21;
} LPC_RTC_TypeDef;

 
typedef struct
{
  volatile uint8_t  WDMOD;
       uint8_t  RESERVED0[3];
  volatile uint32_t WDTC;
  volatile  uint8_t  WDFEED;
       uint8_t  RESERVED1[3];
  volatile const  uint32_t WDTV;
  volatile uint32_t WDCLKSEL;
} LPC_WDT_TypeDef;

 
typedef struct
{
  volatile uint32_t ADCR;
  volatile uint32_t ADGDR;
       uint32_t RESERVED0;
  volatile uint32_t ADINTEN;
  volatile const  uint32_t ADDR0;
  volatile const  uint32_t ADDR1;
  volatile const  uint32_t ADDR2;
  volatile const  uint32_t ADDR3;
  volatile const  uint32_t ADDR4;
  volatile const  uint32_t ADDR5;
  volatile const  uint32_t ADDR6;
  volatile const  uint32_t ADDR7;
  volatile const  uint32_t ADSTAT;
  volatile uint32_t ADTRM;
} LPC_ADC_TypeDef;

 
typedef struct
{
  volatile uint32_t DACR;
  volatile uint32_t DACCTRL;
  volatile uint16_t DACCNTVAL;
} LPC_DAC_TypeDef;

 
typedef struct
{
  volatile const  uint32_t MCCON;
  volatile  uint32_t MCCON_SET;
  volatile  uint32_t MCCON_CLR;
  volatile const  uint32_t MCCAPCON;
  volatile  uint32_t MCCAPCON_SET;
  volatile  uint32_t MCCAPCON_CLR;
  volatile uint32_t MCTIM0;
  volatile uint32_t MCTIM1;
  volatile uint32_t MCTIM2;
  volatile uint32_t MCPER0;
  volatile uint32_t MCPER1;
  volatile uint32_t MCPER2;
  volatile uint32_t MCPW0;
  volatile uint32_t MCPW1;
  volatile uint32_t MCPW2;
  volatile uint32_t MCDEADTIME;
  volatile uint32_t MCCCP;
  volatile uint32_t MCCR0;
  volatile uint32_t MCCR1;
  volatile uint32_t MCCR2;
  volatile const  uint32_t MCINTEN;
  volatile  uint32_t MCINTEN_SET;
  volatile  uint32_t MCINTEN_CLR;
  volatile const  uint32_t MCCNTCON;
  volatile  uint32_t MCCNTCON_SET;
  volatile  uint32_t MCCNTCON_CLR;
  volatile const  uint32_t MCINTFLAG;
  volatile  uint32_t MCINTFLAG_SET;
  volatile  uint32_t MCINTFLAG_CLR;
  volatile  uint32_t MCCAP_CLR;
} LPC_MCPWM_TypeDef;

 
typedef struct
{
  volatile  uint32_t QEICON;
  volatile const  uint32_t QEISTAT;
  volatile uint32_t QEICONF;
  volatile const  uint32_t QEIPOS;
  volatile uint32_t QEIMAXPOS;
  volatile uint32_t CMPOS0;
  volatile uint32_t CMPOS1;
  volatile uint32_t CMPOS2;
  volatile const  uint32_t INXCNT;
  volatile uint32_t INXCMP;
  volatile uint32_t QEILOAD;
  volatile const  uint32_t QEITIME;
  volatile const  uint32_t QEIVEL;
  volatile const  uint32_t QEICAP;
  volatile uint32_t VELCOMP;
  volatile uint32_t FILTER;
       uint32_t RESERVED0[998];
  volatile  uint32_t QEIIEC;
  volatile  uint32_t QEIIES;
  volatile const  uint32_t QEIINTSTAT;
  volatile const  uint32_t QEIIE;
  volatile  uint32_t QEICLR;
  volatile  uint32_t QEISET;
} LPC_QEI_TypeDef;

 
typedef struct
{
  volatile uint32_t mask[512];               
} LPC_CANAF_RAM_TypeDef;

typedef struct                           
{
  volatile uint32_t AFMR;
  volatile uint32_t SFF_sa;
  volatile uint32_t SFF_GRP_sa;
  volatile uint32_t EFF_sa;
  volatile uint32_t EFF_GRP_sa;
  volatile uint32_t ENDofTable;
  volatile const  uint32_t LUTerrAd;
  volatile const  uint32_t LUTerr;
  volatile uint32_t FCANIE;
  volatile uint32_t FCANIC0;
  volatile uint32_t FCANIC1;
} LPC_CANAF_TypeDef;

typedef struct                           
{
  volatile const  uint32_t CANTxSR;
  volatile const  uint32_t CANRxSR;
  volatile const  uint32_t CANMSR;
} LPC_CANCR_TypeDef;

typedef struct                           
{
  volatile uint32_t MOD;
  volatile  uint32_t CMR;
  volatile uint32_t GSR;
  volatile const  uint32_t ICR;
  volatile uint32_t IER;
  volatile uint32_t BTR;
  volatile uint32_t EWL;
  volatile const  uint32_t SR;
  volatile uint32_t RFS;
  volatile uint32_t RID;
  volatile uint32_t RDA;
  volatile uint32_t RDB;
  volatile uint32_t TFI1;
  volatile uint32_t TID1;
  volatile uint32_t TDA1;
  volatile uint32_t TDB1;
  volatile uint32_t TFI2;
  volatile uint32_t TID2;
  volatile uint32_t TDA2;
  volatile uint32_t TDB2;
  volatile uint32_t TFI3;
  volatile uint32_t TID3;
  volatile uint32_t TDA3;
  volatile uint32_t TDB3;
} LPC_CAN_TypeDef;

 
typedef struct                           
{
  volatile const  uint32_t DMACIntStat;
  volatile const  uint32_t DMACIntTCStat;
  volatile  uint32_t DMACIntTCClear;
  volatile const  uint32_t DMACIntErrStat;
  volatile  uint32_t DMACIntErrClr;
  volatile const  uint32_t DMACRawIntTCStat;
  volatile const  uint32_t DMACRawIntErrStat;
  volatile const  uint32_t DMACEnbldChns;
  volatile uint32_t DMACSoftBReq;
  volatile uint32_t DMACSoftSReq;
  volatile uint32_t DMACSoftLBReq;
  volatile uint32_t DMACSoftLSReq;
  volatile uint32_t DMACConfig;
  volatile uint32_t DMACSync;
} LPC_GPDMA_TypeDef;

typedef struct                           
{
  volatile uint32_t DMACCSrcAddr;
  volatile uint32_t DMACCDestAddr;
  volatile uint32_t DMACCLLI;
  volatile uint32_t DMACCControl;
  volatile uint32_t DMACCConfig;
} LPC_GPDMACH_TypeDef;

 
typedef struct
{
  volatile const  uint32_t HcRevision;              
  volatile uint32_t HcControl;
  volatile uint32_t HcCommandStatus;
  volatile uint32_t HcInterruptStatus;
  volatile uint32_t HcInterruptEnable;
  volatile uint32_t HcInterruptDisable;
  volatile uint32_t HcHCCA;
  volatile const  uint32_t HcPeriodCurrentED;
  volatile uint32_t HcControlHeadED;
  volatile uint32_t HcControlCurrentED;
  volatile uint32_t HcBulkHeadED;
  volatile uint32_t HcBulkCurrentED;
  volatile const  uint32_t HcDoneHead;
  volatile uint32_t HcFmInterval;
  volatile const  uint32_t HcFmRemaining;
  volatile const  uint32_t HcFmNumber;
  volatile uint32_t HcPeriodicStart;
  volatile uint32_t HcLSTreshold;
  volatile uint32_t HcRhDescriptorA;
  volatile uint32_t HcRhDescriptorB;
  volatile uint32_t HcRhStatus;
  volatile uint32_t HcRhPortStatus1;
  volatile uint32_t HcRhPortStatus2;
       uint32_t RESERVED0[40];
  volatile const  uint32_t Module_ID;

  volatile const  uint32_t OTGIntSt;                
  volatile uint32_t OTGIntEn;
  volatile  uint32_t OTGIntSet;
  volatile  uint32_t OTGIntClr;
  volatile uint32_t OTGStCtrl;
  volatile uint32_t OTGTmr;
       uint32_t RESERVED1[58];

  volatile const  uint32_t USBDevIntSt;             
  volatile uint32_t USBDevIntEn;
  volatile  uint32_t USBDevIntClr;
  volatile  uint32_t USBDevIntSet;

  volatile  uint32_t USBCmdCode;              
  volatile const  uint32_t USBCmdData;

  volatile const  uint32_t USBRxData;               
  volatile  uint32_t USBTxData;
  volatile const  uint32_t USBRxPLen;
  volatile  uint32_t USBTxPLen;
  volatile uint32_t USBCtrl;
  volatile  uint32_t USBDevIntPri;

  volatile const  uint32_t USBEpIntSt;              
  volatile uint32_t USBEpIntEn;
  volatile  uint32_t USBEpIntClr;
  volatile  uint32_t USBEpIntSet;
  volatile  uint32_t USBEpIntPri;

  volatile uint32_t USBReEp;                 
  volatile  uint32_t USBEpInd;
  volatile uint32_t USBMaxPSize;

  volatile const  uint32_t USBDMARSt;               
  volatile  uint32_t USBDMARClr;
  volatile  uint32_t USBDMARSet;
       uint32_t RESERVED2[9];
  volatile uint32_t USBUDCAH;
  volatile const  uint32_t USBEpDMASt;
  volatile  uint32_t USBEpDMAEn;
  volatile  uint32_t USBEpDMADis;
  volatile const  uint32_t USBDMAIntSt;
  volatile uint32_t USBDMAIntEn;
       uint32_t RESERVED3[2];
  volatile const  uint32_t USBEoTIntSt;
  volatile  uint32_t USBEoTIntClr;
  volatile  uint32_t USBEoTIntSet;
  volatile const  uint32_t USBNDDRIntSt;
  volatile  uint32_t USBNDDRIntClr;
  volatile  uint32_t USBNDDRIntSet;
  volatile const  uint32_t USBSysErrIntSt;
  volatile  uint32_t USBSysErrIntClr;
  volatile  uint32_t USBSysErrIntSet;
       uint32_t RESERVED4[15];

  union {
  volatile const  uint32_t I2C_RX;                  
  volatile  uint32_t I2C_TX;
  };
  volatile const  uint32_t I2C_STS;
  volatile uint32_t I2C_CTL;
  volatile uint32_t I2C_CLKHI;
  volatile  uint32_t I2C_CLKLO;
       uint32_t RESERVED5[824];

  union {
  volatile uint32_t USBClkCtrl;              
  volatile uint32_t OTGClkCtrl;
  };
  union {
  volatile const  uint32_t USBClkSt;
  volatile const  uint32_t OTGClkSt;
  };
} LPC_USB_TypeDef;

 
typedef struct
{
  volatile uint32_t MAC1;                    
  volatile uint32_t MAC2;
  volatile uint32_t IPGT;
  volatile uint32_t IPGR;
  volatile uint32_t CLRT;
  volatile uint32_t MAXF;
  volatile uint32_t SUPP;
  volatile uint32_t TEST;
  volatile uint32_t MCFG;
  volatile uint32_t MCMD;
  volatile uint32_t MADR;
  volatile  uint32_t MWTD;
  volatile const  uint32_t MRDD;
  volatile const  uint32_t MIND;
       uint32_t RESERVED0[2];
  volatile uint32_t SA0;
  volatile uint32_t SA1;
  volatile uint32_t SA2;
       uint32_t RESERVED1[45];
  volatile uint32_t Command;                 
  volatile const  uint32_t Status;
  volatile uint32_t RxDescriptor;
  volatile uint32_t RxStatus;
  volatile uint32_t RxDescriptorNumber;
  volatile const  uint32_t RxProduceIndex;
  volatile uint32_t RxConsumeIndex;
  volatile uint32_t TxDescriptor;
  volatile uint32_t TxStatus;
  volatile uint32_t TxDescriptorNumber;
  volatile uint32_t TxProduceIndex;
  volatile const  uint32_t TxConsumeIndex;
       uint32_t RESERVED2[10];
  volatile const  uint32_t TSV0;
  volatile const  uint32_t TSV1;
  volatile const  uint32_t RSV;
       uint32_t RESERVED3[3];
  volatile uint32_t FlowControlCounter;
  volatile const  uint32_t FlowControlStatus;
       uint32_t RESERVED4[34];
  volatile uint32_t RxFilterCtrl;            
  volatile uint32_t RxFilterWoLStatus;
  volatile uint32_t RxFilterWoLClear;
       uint32_t RESERVED5;
  volatile uint32_t HashFilterL;
  volatile uint32_t HashFilterH;
       uint32_t RESERVED6[882];
  volatile const  uint32_t IntStatus;               
  volatile uint32_t IntEnable;
  volatile  uint32_t IntClear;
  volatile  uint32_t IntSet;
       uint32_t RESERVED7;
  volatile uint32_t PowerDown;
       uint32_t RESERVED8;
  volatile uint32_t Module_ID;
} LPC_EMAC_TypeDef;


#pragma no_anon_unions



 
 
 
 
#line 924 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"

 
#line 945 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"

 
#line 959 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"

 
#line 972 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"

 







 
 
 
#line 1031 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.H"

#line 3 "full_can.c"
#line 1 "full_can.h"


  








#line 19 "full_can.h"



  
















extern char ptr_can1_tx_wr,ptr_can1_tx_rd;
extern long can1_info[8];
extern long can1_id[8];
extern long can1_data[8];
extern long can1_datb[8];
																							 
extern char ptr_can2_tx_wr,ptr_can2_tx_rd;

extern long can2_info[8];
extern long can2_id[8];
extern long can2_data[8];
extern long can2_datb[8];

extern unsigned short rotor_can[6];



extern char bR;
extern char RXBUFF[40],TXBUFF[40];
extern char bIN,bIN2;
extern char bd_dumm[25];
extern char bd[25];
extern char TX_len;

extern char RXBUFF2[40],TXBUFF2[40];
extern char can_tx_cnt;
extern char can_tx_cnt2;


extern char rotor_rotor_rotor[2];
extern char can_tx_cnt;

extern const char Table87[];
extern const char Table95[];

extern char can_debug_plazma[2][10];
extern char bOUT_FREE;
extern char can_rotor[10];
extern char plazma_can;
extern char plazma_can1,plazma_can2,plazma_can3,plazma_can4;



typedef struct
{
  unsigned int Dat1; 
                     
                     
                     
  unsigned int DatA; 
  unsigned int DatB; 
} FULLCAN_MSG; 
extern short volatile gCANFilter;
extern FULLCAN_MSG volatile gFullCANList[2];
extern char can_reset_cnt;



char CRC1_in(void);
char CRC2_in(void);
char CRC1_out(void);
char CRC2_out(void);
void can1_out_adr(char* ptr,char num);
__irq void can_isr_err (void);
void can1_out(char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7);
void can_adr_hndl(void);
void can_in_an(void);
void can_in_an2(void);
__irq void can_isr_rx (void); 
__irq void can_isr_tx (void); 
short can1_init ( unsigned int can_btr);
short can2_init ( unsigned int can_btr);
short FullCAN_SetFilter (
  unsigned short can_port, 
  unsigned int CANID 
  );

void CAN_IRQHandler(void);
void CAN_ISR_Rx1( void );

extern char can_debug_plazma[2][10];
extern char ccc_plazma[20];

#line 4 "full_can.c"
#line 1 "cmd.h"


#line 5 "full_can.c"
#line 1 "mess.h"










		





void mess_hndl(void);
void mess_send(char _mess, short par0, short par1, char _time);
char mess_find(char _mess);
char mess_find_unvol(char _mess);

#line 6 "full_can.c"
#line 1 "global_define.h"






#line 7 "full_can.c"
#line 1 "avar_hndl.h"




extern unsigned avar_stat;	 	
extern unsigned avar_ind_stat; 	
extern unsigned avar_stat_old;
extern unsigned avar_stat_new,avar_stat_offed;









void avar_hndl(void);
void avar_unet_hndl(char in);
void avar_uout_hndl(char in);
void reload_hndl(void);
void avar_bps_hndl(char bps, char v, char in);
void avar_bat_hndl(char bat, char in);
void avar_bat_as_hndl(char b, char in);
void ke_mem_hndl(char b,unsigned short in);
void vz_mem_hndl(unsigned short in);
void wrk_mem_hndl(char b);



#line 8 "full_can.c"
#line 1 "eeprom_map.h"






#line 34 "eeprom_map.h"



#line 134 "eeprom_map.h"



#line 151 "eeprom_map.h"



#line 163 "eeprom_map.h"


#line 174 "eeprom_map.h"



#line 185 "eeprom_map.h"



#line 241 "eeprom_map.h"


#line 283 "eeprom_map.h"








#line 305 "eeprom_map.h"







































































































extern const unsigned short ADR_EE_BAT_ZAR_CNT[2];
extern const unsigned short ADR_EE_BAT_ZAR_CNT_KE[2];
extern const unsigned short ADR_EE_BAT_C_NOM[2];
extern const unsigned short ADR_EE_BAT_YEAR_OF_ON[2];
extern const unsigned short ADR_EE_BAT_IS_ON[2];
extern const unsigned short ADR_EE_BAT_DAY_OF_ON[2];
extern const unsigned short ADR_EE_BAT_MONTH_OF_ON[2];
extern const unsigned short ADR_EE_BAT_RESURS[2];
extern const unsigned short ADR_EE_BAT_C_REAL[2];
extern const unsigned short ADR_EE_BAT_TYPE[2];
extern const unsigned short ADR_KUBAT[2];
extern const unsigned short ADR_KUBATM[2];
extern const unsigned short ADR_KI0BAT[2];
extern const unsigned short ADR_KI1BAT[2];
extern const unsigned short ADR_KTBAT[2];
extern const unsigned short ADR_EE_BAT_TYPE[2];


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

#line 9 "full_can.c"
#line 1 "control.h"







extern char num_of_wrks_bps;
extern char bps_all_off_cnt,bps_mask_off_cnt,bps_mask_on_off_cnt;
extern char bps_hndl_2sec_cnt;
extern unsigned short bps_on_mask,bps_off_mask;
extern char num_necc_up,num_necc_down;
extern unsigned char sh_cnt0,b1Hz_sh;


extern short cntrl_stat_blok_cnt,cntrl_stat_blok_cnt_,cntrl_stat_blok_cnt_plus[2],cntrl_stat_blok_cnt_minus[2];



extern long adc_buff[16][16];
extern signed short adc_buff_max[12],adc_buff_min[12],unet_buff_max,unet_buff_min;
extern short adc_buff_[16];
extern char adc_self_ch_cnt,adc_ch_net;
extern char adc_cnt,adc_cnt1,adc_ch,adc_ch_cnt;
extern short zero_cnt;
typedef enum {asCH=1,asNET_WAIT=2,asNET_RDY=3,asNET=4} enum_adc_stat;
extern enum_adc_stat adc_stat;
extern unsigned short net_buff[32],net_buff_,net_metr_buff_[3];
extern char net_buff_cnt;
extern short ADWR,period_cnt,non_zero_cnt;
extern char rele_stat;
extern char bRELE_OUT;
extern short plazma_adc_cnt;
extern signed short adc_self_ch_buff[3],adc_self_ch_disp[3];
extern long main_power_buffer[8],main_power_buffer_;
extern short main_power_buffer_cnt;
extern short adc_gorb_cnt,adc_zero_cnt;
extern char adc_window_flag;
extern short adc_window_cnt;
extern short adc_net_buff_cnt;


char vz_start(char hour);
void vz_stop(void);
void vz_drv(void);
void samokalibr_init(void);
void samokalibr_hndl(void);
void kb_init(void);
void kb_hndl(void);
void ubat_old_drv(void);
void unet_drv(void);
void matemat(void);
void adc_init(void);
void adc_drv5(void);
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
void ke_start(char in);
void ke_drv(void);
void avz_drv(void);
void zar_drv(void);
void vent_hndl(void);
void avz_next_date_hndl(void);
void klimat_hndl(void);
void ext_drv(void);
void adc_drv7(void);
void avt_hndl(void);




typedef enum {spcOFF=0,spcKE, spcVZ}enum_spc_stat;
typedef enum {kssNOT=0,kssNOT_VZ,kssYES=100,kssNOT_BAT,kssNOT_BAT_AV,kssNOT_BAT_AV_T,kssNOT_BAT_AV_ASS,kssNOT_BAT_ZAR,kssNOT_BAT_RAZR,kssNOT_KE1,kssNOT_KE2}enum_ke_start_stat;
extern enum_spc_stat spc_stat;
extern enum_ke_start_stat ke_start_stat;
extern char spc_bat;
extern char spc_phase;
extern unsigned short vz_cnt_s,vz_cnt_s_,vz_cnt_h,vz_cnt_h_;
extern short cnt_end_ke;
extern unsigned long ke_date[2];
extern short __ee_vz_cnt;
extern short __ee_spc_stat;
extern short __ee_spc_bat;
extern short __ee_spc_phase;



extern signed short cntrl_stat;
extern signed short cntrl_stat_old;
extern signed short cntrl_stat_new;
extern signed short Ibmax;
extern unsigned char unh_cnt0,unh_cnt1,b1Hz_unh;
extern unsigned char	ch_cnt0,b1Hz_ch,i,iiii;
extern unsigned char	ch_cnt1,b1_30Hz_ch;
extern unsigned short IZMAX_;
extern unsigned short Ubpsmax;

extern short plazma_sk;
extern char	plazma_inv[4];
extern char plazma_bat;


extern signed int i_avg_max,i_avg_min,i_avg_summ,i_avg; 
extern signed int avg;
extern char bAVG;
extern const char sk_buff_TELECORE2015[4];



extern char numOfForvardBps;
extern char numOfForvardBps_minCnt;
extern short numOfForvardBps_hourCnt;


void zar_superviser_drv(void);
void zar_superviser_start(void);
void vent_hndl(void);
void speedChargeHndl(void);
void speedChargeStartStop(void);


#line 10 "full_can.c"
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
#line 11 "full_can.c"


short volatile gCANFilter = 0;

char ptr_can1_tx_wr,ptr_can1_tx_rd;
long can1_info[8];
long can1_id[8];
long can1_data[8];
long can1_datb[8];
																							 
char ptr_can2_tx_wr,ptr_can2_tx_rd;

long can2_info[8];
long can2_id[8];
long can2_data[8];
long can2_datb[8];

unsigned short rotor_can[6];





FULLCAN_MSG volatile gFullCANList[2];

char bR;
char RXBUFF[40],TXBUFF[40];
char bIN,bIN2;
char bd_dumm[25];
char bd[25];
char TX_len;

char RXBUFF2[40],TXBUFF2[40];
extern char can_tx_cnt;
extern char can_tx_cnt2;
char bOUT_FREE=1;
char bOUT_FREE2=1;
char rotor_rotor_rotor[2];
char can_tx_cnt;
char can_rotor[10];

const char Table87[]={
0x00, 0x0E, 0x1C, 0x12, 0x38, 0x36, 0x24, 0x2A, 0x70, 0x7E, 0x6C, 0x62, 0x48, 0x46, 0x54, 0x5A,
0xE0, 0xEE, 0xFC, 0xF2, 0xD8, 0xD6, 0xC4, 0xCA, 0x90, 0x9E, 0x8C, 0x82, 0xA8, 0xA6, 0xB4, 0xBA,
0xCE, 0xC0, 0xD2, 0xDC, 0xF6, 0xF8, 0xEA, 0xE4, 0xBE, 0xB0, 0xA2, 0xAC, 0x86, 0x88, 0x9A, 0x94,
0x2E, 0x20, 0x32, 0x3C, 0x16, 0x18, 0x0A, 0x04, 0x5E, 0x50, 0x42, 0x4C, 0x66, 0x68, 0x7A, 0x74,
0x92, 0x9C, 0x8E, 0x80, 0xAA, 0xA4, 0xB6, 0xB8, 0xE2, 0xEC, 0xFE, 0xF0, 0xDA, 0xD4, 0xC6, 0xC8,
0x72, 0x7C, 0x6E, 0x60, 0x4A, 0x44, 0x56, 0x58, 0x02, 0x0C, 0x1E, 0x10, 0x3A, 0x34, 0x26, 0x28,
0x5C, 0x52, 0x40, 0x4E, 0x64, 0x6A, 0x78, 0x76, 0x2C, 0x22, 0x30, 0x3E, 0x14, 0x1A, 0x08, 0x06,
0xBC, 0xB2, 0xA0, 0xAE, 0x84, 0x8A, 0x98, 0x96, 0xCC, 0xC2, 0xD0, 0xDE, 0xF4, 0xFA, 0xE8, 0xE6,
0x2A, 0x24, 0x36, 0x38, 0x12, 0x1C, 0x0E, 0x00, 0x5A, 0x54, 0x46, 0x48, 0x62, 0x6C, 0x7E, 0x70,
0xCA, 0xC4, 0xD6, 0xD8, 0xF2, 0xFC, 0xEE, 0xE0, 0xBA, 0xB4, 0xA6, 0xA8, 0x82, 0x8C, 0x9E, 0x90,
0xE4, 0xEA, 0xF8, 0xF6, 0xDC, 0xD2, 0xC0, 0xCE, 0x94, 0x9A, 0x88, 0x86, 0xAC, 0xA2, 0xB0, 0xBE,
0x04, 0x0A, 0x18, 0x16, 0x3C, 0x32, 0x20, 0x2E, 0x74, 0x7A, 0x68, 0x66, 0x4C, 0x42, 0x50, 0x5E,
0xB8, 0xB6, 0xA4, 0xAA, 0x80, 0x8E, 0x9C, 0x92, 0xC8, 0xC6, 0xD4, 0xDA, 0xF0, 0xFE, 0xEC, 0xE2,
0x58, 0x56, 0x44, 0x4A, 0x60, 0x6E, 0x7C, 0x72, 0x28, 0x26, 0x34, 0x3A, 0x10, 0x1E, 0x0C, 0x02,
0x76, 0x78, 0x6A, 0x64, 0x4E, 0x40, 0x52, 0x5C, 0x06, 0x08, 0x1A, 0x14, 0x3E, 0x30, 0x22, 0x2C,
0x96, 0x98, 0x8A, 0x84, 0xAE, 0xA0, 0xB2, 0xBC, 0xE6, 0xE8, 0xFA, 0xF4, 0xDE, 0xD0, 0xC2, 0xCC};



const char Table95[]={
0x00, 0x2A, 0x54, 0x7E, 0xA8, 0x82, 0xFC, 0xD6, 0x7A, 0x50, 0x2E, 0x04, 0xD2, 0xF8, 0x86, 0xAC,
0xF4, 0xDE, 0xA0, 0x8A, 0x5C, 0x76, 0x08, 0x22, 0x8E, 0xA4, 0xDA, 0xF0, 0x26, 0x0C, 0x72, 0x58,
0xC2, 0xE8, 0x96, 0xBC, 0x6A, 0x40, 0x3E, 0x14, 0xB8, 0x92, 0xEC, 0xC6, 0x10, 0x3A, 0x44, 0x6E,
0x36, 0x1C, 0x62, 0x48, 0x9E, 0xB4, 0xCA, 0xE0, 0x4C, 0x66, 0x18, 0x32, 0xE4, 0xCE, 0xB0, 0x9A,
0xAE, 0x84, 0xFA, 0xD0, 0x06, 0x2C, 0x52, 0x78, 0xD4, 0xFE, 0x80, 0xAA, 0x7C, 0x56, 0x28, 0x02,
0x5A, 0x70, 0x0E, 0x24, 0xF2, 0xD8, 0xA6, 0x8C, 0x20, 0x0A, 0x74, 0x5E, 0x88, 0xA2, 0xDC, 0xF6,
0x6C, 0x46, 0x38, 0x12, 0xC4, 0xEE, 0x90, 0xBA, 0x16, 0x3C, 0x42, 0x68, 0xBE, 0x94, 0xEA, 0xC0,
0x98, 0xB2, 0xCC, 0xE6, 0x30, 0x1A, 0x64, 0x4E, 0xE2, 0xC8, 0xB6, 0x9C, 0x4A, 0x60, 0x1E, 0x34,
0x76, 0x5C, 0x22, 0x08, 0xDE, 0xF4, 0x8A, 0xA0, 0x0C, 0x26, 0x58, 0x72, 0xA4, 0x8E, 0xF0, 0xDA,
0x82, 0xA8, 0xD6, 0xFC, 0x2A, 0x00, 0x7E, 0x54, 0xF8, 0xD2, 0xAC, 0x86, 0x50, 0x7A, 0x04, 0x2E,
0xB4, 0x9E, 0xE0, 0xCA, 0x1C, 0x36, 0x48, 0x62, 0xCE, 0xE4, 0x9A, 0xB0, 0x66, 0x4C, 0x32, 0x18,
0x40, 0x6A, 0x14, 0x3E, 0xE8, 0xC2, 0xBC, 0x96, 0x3A, 0x10, 0x6E, 0x44, 0x92, 0xB8, 0xC6, 0xEC, 
0xD8, 0xF2, 0x8C, 0xA6, 0x70, 0x5A, 0x24, 0x0E, 0xA2, 0x88, 0xF6, 0xDC, 0x0A, 0x20, 0x5E, 0x74, 
0x2C, 0x06, 0x78, 0x52, 0x84, 0xAE, 0xD0, 0xFA, 0x56, 0x7C, 0x02, 0x28, 0xFE, 0xD4, 0xAA, 0x80, 
0x1A, 0x30, 0x4E, 0x64, 0xB2, 0x98, 0xE6, 0xCC, 0x60, 0x4A, 0x34, 0x1E, 0xC8, 0xE2, 0x9C, 0xB6, 
0xEE, 0xC4, 0xBA, 0x90, 0x46, 0x6C, 0x12, 0x38, 0x94, 0xBE, 0xC0, 0xEA, 0x3C, 0x16, 0x68, 0x42};



char can_debug_plazma[2][10];
volatile uint32_t CANStatus;

char can_reset_cnt=0;

char plazma_can_pal[20];
char cnt_can_pal;
char plazma_can_pal_index;


char plazma_can;
char plazma_can1,plazma_can2,plazma_can3,plazma_can4;
short can2_tx_cnt;
char ccc_plazma[20];


char CRC1_in(void)
{
char r,j,lb;
lb=(RXBUFF[1]&0x1f)+0x04;
r=RXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(RXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 


char CRC2_in(void)
{
char r,j,lb;
lb=(RXBUFF[1]&0x1f)+0x04;
r=RXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(RXBUFF[j]^Table95[r]);
	}
if(r==0)r=0xFF;
return r;	
}  


char CRC1_out(void)
{
char r,j,lb;
lb=(TXBUFF[1]&0x1f)+0x04;
r=TXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(TXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 


char CRC2_out(void)
{
char r,j,lb;
lb=(TXBUFF[1]&0x1f)+0x04;
r=TXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(TXBUFF[j]^Table95[r]);
	}
if(r==0)r=0xFF;
return r;	
}


void can1_out_adr(char* ptr,char num)
{

if(num<=8)
	{
	can1_info[ptr_can1_tx_wr]=(((long)num)<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	}
	
else if(num<=16)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-8))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	

else if(num<=24)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;

	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-16))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[17];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[18];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[19];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[20];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[21];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[22];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[23];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	

else if(num<=32)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;

	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[17];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[18];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[19];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[20];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[21];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[22];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[23];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-24))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[24];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[25];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[26];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[27];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[28];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[29];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[30];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[31];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	


if(bOUT_FREE)
	{
	((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TFI1=can1_info[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TID1=can1_id[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TDA1=can1_data[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TDB1=can1_datb[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}

}	


void can2_out_adr(char* ptr,char num)
{

if(num<=8)
	{
	can2_info[ptr_can2_tx_wr]=(((long)num)<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	}
	
else if(num<=16)
	{
	
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(((long)(num-8))<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[8];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[9];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[10];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[11];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[12];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[13];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[14];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[15];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
		
	}	

else if(num<=24)
	{
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;

	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[8];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[9];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[10];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[11];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[12];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[13];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[14];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[15];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(((long)(num-16))<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[16];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[17];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[18];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[19];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[20];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[21];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[22];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[23];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;	
	}	

else if(num<=32)
	{
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;

	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[8];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[9];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[10];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[11];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[12];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[13];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[14];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[15];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[16];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[17];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[18];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[19];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[20];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[21];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[22];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[23];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(((long)(num-24))<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[24];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[25];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[26];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[27];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[28];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[29];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[30];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[31];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;	
	}	


if(bOUT_FREE2)
	{
	((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TFI1=can2_info[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TID1=can2_id[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TDA1=can2_data[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TDB1=can2_datb[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->CMR=0x00000021;
     ptr_can2_tx_rd++;
     if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
     bOUT_FREE2=0;	
	}

}


void paking(char* data_ptr,char data_len)
{
char i,ii,iii;
for(i=0;i<data_len;i++)
	{
	ii=data_len+(i/7);
	iii=i-(7*(i/7)); 
	if(iii==0) data_ptr[ii]=0;
	data_ptr[ii]<<=1;
	if(data_ptr[i]&0x01)
		{
		data_ptr[ii]|=0x01;
		}                      
	else 
		{
		data_ptr[ii]&=0xfe;
		}              
	data_ptr[i]>>=1;	        
	data_ptr[i]|=0x80;	
	}                       
for(i=data_len;i<(data_len+(data_len/7)+1);i++)
	{
	data_ptr[i]|=0x80;
	}	
}


void can1_out(char dat0,char dat1,char dat2,char dat3,char dat4,char dat5,char dat6,char dat7)
{

can1_info[ptr_can1_tx_wr]=((8UL)<<16)&0x000f0000UL;
can1_id[ptr_can1_tx_wr]=0x0000009eUL;
*((char*)&can1_data[ptr_can1_tx_wr])=dat0;
*(((char*)&can1_data[ptr_can1_tx_wr])+1)=dat1;
*(((char*)&can1_data[ptr_can1_tx_wr])+2)=dat2;
*(((char*)&can1_data[ptr_can1_tx_wr])+3)=dat3;
*((char*)&can1_datb[ptr_can1_tx_wr])=dat4;
*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=dat5;
*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=dat6;
*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=dat7;	
ptr_can1_tx_wr++;
if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;


if(bOUT_FREE)
	{
	

	((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TFI1=can1_info[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TID1=can1_id[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TDA1=can1_data[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TDB1=can1_datb[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}
}	


void can2_out(char dat0,char dat1,char dat2,char dat3,char dat4,char dat5,char dat6,char dat7)
{


can2_info[ptr_can2_tx_wr]=((8UL)<<16)&0x000f0000UL;
can2_id[ptr_can2_tx_wr]=0x0000018eUL;
*((char*)&can2_data[ptr_can2_tx_wr])=dat0;
*(((char*)&can2_data[ptr_can2_tx_wr])+1)=dat1;
*(((char*)&can2_data[ptr_can2_tx_wr])+2)=dat2;
*(((char*)&can2_data[ptr_can2_tx_wr])+3)=dat3;
*((char*)&can2_datb[ptr_can2_tx_wr])=dat4;
*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=dat5;
*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=dat6;
*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=dat7;	
ptr_can2_tx_wr++;
if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;


if(bOUT_FREE2)
	{
	

	((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TFI1=can2_info[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TID1=can2_id[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TDA1=can2_data[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TDB1=can2_datb[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->CMR=0x00000021;
     ptr_can2_tx_rd++;
     if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
     bOUT_FREE2=0;	
	}
}	
	


void can_adr_hndl(void)
{
	TXBUFF[2]=RXBUFF[3];
	TXBUFF[3]=RXBUFF[2];
	TXBUFF[4]=((RXBUFF[4]&0xF0)>>4)|((RXBUFF[4]&0x0f)<<4);
	TXBUFF[5]=((RXBUFF[5]&0xF0)>>4)|((RXBUFF[5]&0x0f)<<4);	
}	


void can_in_an2(void)
{
if(!bIN) goto CAN_IN_AN_end; 
can_debug_plazma[0][1]++;
 


if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x01))
	{ 
     

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+4;
	can_adr_hndl();
	TXBUFF[6]=0x01;
	TXBUFF[7]=3;
	TXBUFF[8]=5;
	TXBUFF[9]=CRC1_out();
	TXBUFF[10]=CRC2_out();
	TX_len=11;

	can2_out_adr(TXBUFF,11);  
	}

else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB0))
	{ 
	can_debug_plazma[0][2]++;
    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+13;
	can_adr_hndl(); 
	
	TXBUFF[6]=0xB0;
	
	
	

	if(net_U>=254)TXBUFF[7]=0xff;
	else TXBUFF[7]=net_U;
	
	if(net_F<400) TXBUFF[8]=1;
	else if(net_F>654) TXBUFF[8]=0xff;
	else TXBUFF[8]=(unsigned char)((net_F-400)+1);
	
	TXBUFF[9]=*((char*)(&load_U));
	TXBUFF[10]=*(((char*)(&load_U))+1);
	TXBUFF[11]=*((char*)(&load_I));
	TXBUFF[12]=*(((char*)(&load_I))+1);
	
	TXBUFF[13]=0xcc;
	TXBUFF[13]|=4;(NUMIST&0x07);
	TXBUFF[13]|=((NUMBAT&0x03)<<4);
	

	TXBUFF[14]=0x80;
	if(avar_stat&0x00000001)TXBUFF[14]|=0x01;
	if(PAR)TXBUFF[14]|=0x40;
	
	TXBUFF[15]=25;
     
	paking(&TXBUFF[6],10);
	
	TXBUFF[18]=CRC1_out();
	TXBUFF[19]=CRC2_out();
	TX_len=20;
				
	can2_out_adr(TXBUFF,20);  
	} 


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB1)&&(RXBUFF[7]==0x01))
	{ 
	signed short temp_S;

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+14;
	can_adr_hndl();
	TXBUFF[6]=0xB1;
	TXBUFF[7]=1;
	
	if(BAT_IS_ON[0]!=bisON) TXBUFF[8]=0xFF;
	else if(bat[0]._av)TXBUFF[8]=0xF7;
	else TXBUFF[8]=0xF0;
	
	if((spc_stat==spcKE))TXBUFF[9]=0xF9;
	else if(spc_stat==spcVZ)TXBUFF[9]=0xF8;                      
	else TXBUFF[9]=0xF0;
	
	
	temp_S=(bat[0]._Ib/10)+10000;
			
	TXBUFF[10]=*((char*)(&bat[0]._Ub));
	TXBUFF[11]=*(((char*)(&bat[0]._Ub))+1);
	TXBUFF[12]=*((char*)(&temp_S));
	TXBUFF[13]=*(((char*)(&temp_S))+1);
	TXBUFF[14]=bat[0]._Tb;
	TXBUFF[15]=bat[0]._zar; 
	
	if(BAT_C_REAL[0]==0x5555)TXBUFF[16]=BAT_C_NOM[0];
	else TXBUFF[16]=BAT_C_REAL[0]/10;	
	
    	paking(&TXBUFF[6],11);
    
	TXBUFF[19]=CRC1_out();
	TXBUFF[20]=CRC2_out();
	TX_len=21; 
 
	can2_out_adr(TXBUFF,21);  
	}	


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB1)&&(RXBUFF[7]==0x02))
	{ 
	signed short temp_S;

    TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+14;
	can_adr_hndl();
	TXBUFF[6]=0xB1;
	TXBUFF[7]=2;
	
	if(BAT_IS_ON[1]!=bisON) TXBUFF[8]=0xFF;
	else if(bat[1]._av)TXBUFF[8]=0xF7;
	else TXBUFF[8]=0xF0;

	if((spc_stat==spcKE))TXBUFF[9]=0xF9;
	else if(spc_stat==spcVZ)TXBUFF[9]=0xF8;                      
	else TXBUFF[9]=0xF0;
	
	
	temp_S=(bat[1]._Ib/10)+10000;
			
	TXBUFF[10]=*((char*)(&bat[1]._Ub));
	TXBUFF[11]=*(((char*)(&bat[1]._Ub))+1);
	TXBUFF[12]=*((char*)(&temp_S));
	TXBUFF[13]=*(((char*)(&temp_S))+1);
	TXBUFF[14]=bat[1]._Tb;
	TXBUFF[15]=bat[1]._zar; 
	
	if(BAT_C_REAL[1]==0x5555)TXBUFF[16]=BAT_C_NOM[1];
	else TXBUFF[16]=BAT_C_REAL[1]/10;	
	
    	paking(&TXBUFF[6],11);
    
	TXBUFF[19]=CRC1_out();
	TXBUFF[20]=CRC2_out();
	TX_len=21; 
 
	can2_out_adr(TXBUFF,21);  
	}		
		



	
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x01))
	{ 
    

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=1;
		
	
	if(NUMIST<1)TXBUFF[8]=0xff;	
	else if(bps[0]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[0]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[0]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[0]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[0]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[0]._Uii));
	TXBUFF[10]=*(((char*)(&bps[0]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[0]._Ii));
	TXBUFF[12]=*(((char*)(&bps[0]._Ii))+1);
	TXBUFF[13]=bps[0]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}	
	
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x02))
	{ 
    

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=2;
		
	
	if(NUMIST<3)TXBUFF[8]=0xff;	
	else if(bps[1]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[1]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[1]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[1]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[1]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[1]._Uii));
	TXBUFF[10]=*(((char*)(&bps[1]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[1]._Ii));
	TXBUFF[12]=*(((char*)(&bps[1]._Ii))+1);
	TXBUFF[13]=bps[1]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}	


	
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x03))
	{ 
    

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=3;
		
	
	if(NUMIST<3)TXBUFF[8]=0xff;	
	else if(bps[2]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[2]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[2]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[2]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[2]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[2]._Uii));
	TXBUFF[10]=*(((char*)(&bps[2]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[2]._Ii));
	TXBUFF[12]=*(((char*)(&bps[2]._Ii))+1);
	TXBUFF[13]=bps[2]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}	

	
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x04))
	{ 
    

    TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=4;
		
	
	if(NUMIST<4)TXBUFF[8]=0xff;	
	else if(bps[3]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[3]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[3]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[3]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[3]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[3]._Uii));
	TXBUFF[10]=*(((char*)(&bps[3]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[3]._Ii));
	TXBUFF[12]=*(((char*)(&bps[3]._Ii))+1);
	TXBUFF[13]=bps[3]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x03)
	&&((RXBUFF[7])&&(RXBUFF[7]<25)))
 	  
	{ 
     char temp;      		

	temp=vz_start(RXBUFF[7]);

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x03;
	TXBUFF[7]=0x01;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);
	}


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x08))
 	  
	{ 
	if(spc_stat==spcVZ) spc_stat=spcOFF;

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
	can_adr_hndl();
	TXBUFF[6]=0x08;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;
	can2_out_adr(TXBUFF,9);
	}



else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x04)
	&&(RXBUFF[7]==0x01))
	  
	{
	ke_start(0);

	if(ke_start_stat==kssYES)TXBUFF[7]=0xff;
	else TXBUFF[7]=0x01;

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x04;
	TXBUFF[7]=0x01;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);
	} 
	

else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x04)
	&&(RXBUFF[7]==0x02))
	  
	{
	ke_start(1);

	if(ke_start_stat==kssYES)TXBUFF[7]=0xff;
	else TXBUFF[7]=0x01;

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x04;
	TXBUFF[7]=0x02;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);
	}	
	
	
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x07))
	  
	{
   	
	if(spc_stat==spcKE)spc_stat=spcOFF;
	
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
	can_adr_hndl();
	TXBUFF[6]=0x07;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;
	can2_out_adr(TXBUFF,9);
	}




if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x01))
	  
	{
	bps[0]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x01;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);

	}


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x02))
	  
	{                  
	bps[1]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
 	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x02;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;     

	can2_out_adr(TXBUFF,10);

	}


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x03))
	  
	{                  
	bps[2]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
 	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x03;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;     

	can2_out_adr(TXBUFF,10);

	}



else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x04))
	  
	{                  
	bps[3]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
 	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x03;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;     

	can2_out_adr(TXBUFF,10);

	}



else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x06))
	  
	{                  
	bps[0]._ist_blok_host_cnt=0;
	bps[1]._ist_blok_host_cnt=0;
	bps[2]._ist_blok_host_cnt=0;
	bps[3]._ist_blok_host_cnt=0;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
 	can_adr_hndl();
	TXBUFF[6]=0x05;

	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;     

	can2_out_adr(TXBUFF,9);

	}


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x0a))
	  
	{                  
	PAR=1;
	lc640_write_int(0x10+100+86,PAR);
	
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
 	can_adr_hndl();
	TXBUFF[6]=0x0a;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();

	can2_out_adr(TXBUFF,9);    

	}


else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x0b))
	  
	{                  
	PAR=0;
	lc640_write_int(0x10+100+86,PAR);
	
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
 	can_adr_hndl();
	TXBUFF[6]=0x0b;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;     

	can2_out_adr(TXBUFF,9);

	}

CAN_IN_AN_end:
bIN=0;
}

void can_in_an1(void)
{


char slave_num;




can_rotor[1]++;

if((RXBUFF[0]==a_ind . s_i1)&&(RXBUFF[1]==0x91)&&(RXBUFF[2]==0xdd)&&(RXBUFF[3]==0xdd) )
	{
	mess_send(215,217,0,10);
	can_reset_cnt=0;
	}


if((RXBUFF[1]==0xDA)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
     {
	
     slave_num=RXBUFF[0]&0x1f;
     
    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     	
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];









 
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10;
	
 	if((bps[slave_num]._cnt==0)&&(bps[slave_num]._av&(1<<3))) avar_bps_hndl(slave_num,3,0);

	can_reset_cnt=0;
     }

if((RXBUFF[1]==0xDB)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
     slave_num=RXBUFF[0]&0x1f;  

    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     
	bps[slave_num]._buff[6]=RXBUFF[2]; 
	bps[slave_num]._buff[7]=RXBUFF[3];
	bps[slave_num]._buff[8]=RXBUFF[4];
	bps[slave_num]._buff[9]=RXBUFF[5];
	bps[slave_num]._buff[10]=RXBUFF[6];
	bps[slave_num]._buff[11]=RXBUFF[7];	









 
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==0xDD)&&((RXBUFF[0]&0x1f)>=20)&&((RXBUFF[0]&0x1f)<20+NUMINV))
     {
	
     slave_num=RXBUFF[0]&0x1f;

	plazma_can_inv[0]++;
     
    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     	
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];









 
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10;
	
 	if((bps[slave_num]._cnt==0)&&(bps[slave_num]._av&(1<<3))) avar_bps_hndl(slave_num,3,0);

	can_reset_cnt=0;
     }

if((RXBUFF[1]==0xDE)&&((RXBUFF[0]&0x1f)>=20)&&((RXBUFF[0]&0x1f)<20+NUMINV))
 	{
     slave_num=RXBUFF[0]&0x1f;
	
	plazma_can_inv[1]++;  

    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     
	bps[slave_num]._buff[6]=RXBUFF[2]; 
	bps[slave_num]._buff[7]=RXBUFF[3];
	bps[slave_num]._buff[8]=RXBUFF[4];
	bps[slave_num]._buff[9]=RXBUFF[5];
	bps[slave_num]._buff[10]=RXBUFF[6];
	bps[slave_num]._buff[11]=RXBUFF[7];	









 
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==0xDf)&&((RXBUFF[0]&0x1f)>=20)&&((RXBUFF[0]&0x1f)<20+NUMINV))
 	{
     slave_num=RXBUFF[0]&0x1f; 

	plazma_can_inv[2]++; 

    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     
	bps[slave_num]._buff[12]=RXBUFF[2]; 
	bps[slave_num]._buff[13]=RXBUFF[3];
	bps[slave_num]._buff[14]=RXBUFF[4];
	bps[slave_num]._buff[15]=RXBUFF[5];
	bps[slave_num]._buff[16]=RXBUFF[6];
	bps[slave_num]._buff[17]=RXBUFF[7];	









 
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==0xD8))
     {
	
     byps._adress=RXBUFF[0]&0x1f;
     
     	
	byps._Iout=(signed short)RXBUFF[2]+(((signed short)RXBUFF[3])*256);
	byps._Pout=(signed short)RXBUFF[4]+(((signed short)RXBUFF[5])*256);
	byps._Uout=(signed short)RXBUFF[6]+(((signed short)RXBUFF[7])*256);
	
	byps._cnt=0;
     }

if((RXBUFF[1]==0xD9))
 	{
	byps._T=(char)RXBUFF[2];
	byps._flags=(char)RXBUFF[3];
	byps._Unet=(signed short)RXBUFF[4]+(((signed short)RXBUFF[5])*256);
	byps._Uin=(signed short)RXBUFF[6]+(((signed short)RXBUFF[7])*256);

	byps._cnt=0;
   	}

if((RXBUFF[1]==0xD1)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
    slave_num=RXBUFF[0]&0x1f;  

    bps[slave_num]._device=dIBAT_METR;
         
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];	









 
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==0xEA)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
    slave_num=RXBUFF[0]&0x1f;  

    bps[slave_num]._device=dNET_METR;
         
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];	









 
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	
	can_reset_cnt=0;
   	}


if((RXBUFF[1]==0xEB)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
    slave_num=RXBUFF[0]&0x1f;  

    bps[slave_num]._device=dNET_METR;
         
	bps[slave_num]._buff[6]=RXBUFF[2]; 
	bps[slave_num]._buff[7]=RXBUFF[3];
	
	

	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	
	can_reset_cnt=0;
   	}

if( (RXBUFF[0]==0x62)&&(RXBUFF[1]==1)&&(RXBUFF[2]==1))
     {
     power_summary_tempo=*((signed short*)&RXBUFF[3]);
     power_current_tempo=*((signed short*)&RXBUFF[5]);
	
	can_reset_cnt=0;
     }


if( ((RXBUFF[0]&0x1f)==8)&&((RXBUFF[1])==0xDE) )
     {
     adc_buff_ext_[0]=*((short*)&RXBUFF[2]);
     adc_buff_ext_[1]=*((short*)&RXBUFF[4]);
     adc_buff_ext_[2]=*((short*)&RXBUFF[6]);
	if((adc_buff_ext_[2]>=-50) && (adc_buff_ext_[2]<=100))
		{
		t_ext_can=adc_buff_ext_[2];
		t_ext_can_nd=0;
		}
		t_ext_can=adc_buff_ext_[2];
	
	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==9)&&((RXBUFF[1])==0xDE) )
     {
     vvod_pos=RXBUFF[2];
	ext_can_cnt=RXBUFF[3];
	if(ext_can_cnt<10)bRESET_EXT=0;
	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==10)&&((RXBUFF[1])==0xDE) )
     {
     power_current=*((signed short*)&RXBUFF[2]);
     power_summary=*((signed long*)&RXBUFF[4]);
	
	can_reset_cnt=0;
     }


if( ((RXBUFF[0]&0x1f)==20)&&((RXBUFF[1])==0xDE) )
     {
     eb2_data[0]=RXBUFF[2];
	eb2_data[1]=RXBUFF[3];
     eb2_data[2]=RXBUFF[4];
	eb2_data[3]=RXBUFF[5];
	eb2_data[4]=RXBUFF[6];
	eb2_data[5]=RXBUFF[7];
     power_current=*((signed short*)&RXBUFF[2]);
     power_summary=*((signed long*)&RXBUFF[4]);

	 can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==21)&&((RXBUFF[1])==0xDE) )
     {
     eb2_data[6]=RXBUFF[2];
	eb2_data[7]=RXBUFF[3];
     eb2_data[8]=RXBUFF[4];
	eb2_data[9]=RXBUFF[5];
	eb2_data[10]=RXBUFF[6];
	eb2_data[11]=RXBUFF[7];
	eb2_data_short[6]=*((short*)&eb2_data[6]);

	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==22)&&((RXBUFF[1])==0xDE) )
     {
     eb2_data[12]=RXBUFF[2];
	eb2_data[13]=RXBUFF[3];
     eb2_data[14]=RXBUFF[4];
	eb2_data[15]=RXBUFF[5];
	eb2_data[16]=RXBUFF[6];
	eb2_data[17]=RXBUFF[7];
	eb2_data_short[0]=*((short*)&eb2_data[12]);
	eb2_data_short[1]=*((short*)&eb2_data[14]);
	eb2_data_short[2]=*((short*)&eb2_data[16]);

	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==23)&&((RXBUFF[1])==0xDE) )
     {
     eb2_data[18]=RXBUFF[2];
	eb2_data[19]=RXBUFF[3];
     eb2_data[20]=RXBUFF[4];
	eb2_data[21]=RXBUFF[5];
	eb2_data[22]=RXBUFF[6];
	eb2_data[23]=RXBUFF[7];
	eb2_data_short[3]=*((short*)&eb2_data[18]);
	eb2_data_short[4]=*((short*)&eb2_data[20]);
	eb2_data_short[5]=*((short*)&eb2_data[22]);

	can_reset_cnt=0;
     }

if( (RXBUFF[1]==0xE2)&&(RXBUFF[0]>=0)&&(RXBUFF[0]<=3))
     {
	makb[RXBUFF[0]]._U[0]=*((short*)&RXBUFF[2]);
	makb[RXBUFF[0]]._U[1]=*((short*)&RXBUFF[4]);
	makb[RXBUFF[0]]._U[2]=*((short*)&RXBUFF[6]);

	makb[RXBUFF[0]]._Ub[0]=makb[RXBUFF[0]]._U[0];
	if(makb[RXBUFF[0]]._Ub[0]<0)makb[RXBUFF[0]]._Ub[0]=0;
	makb[RXBUFF[0]]._Ub[1]=makb[RXBUFF[0]]._U[1]-makb[RXBUFF[0]]._U[0];
	if(makb[RXBUFF[0]]._Ub[1]<0)makb[RXBUFF[0]]._Ub[1]=0;
	makb[RXBUFF[0]]._Ub[2]=makb[RXBUFF[0]]._U[2]-makb[RXBUFF[0]]._U[1];
	if(makb[RXBUFF[0]]._Ub[2]<0)makb[RXBUFF[0]]._Ub[2]=0;

	makb[RXBUFF[0]]._cnt=0;
     }

if( (RXBUFF[1]==0xE3)&&(RXBUFF[0]>=0)&&(RXBUFF[0]<=3))
     {
	makb[RXBUFF[0]]._U[3]=*((short*)&RXBUFF[2]);
	makb[RXBUFF[0]]._U[4]=*((short*)&RXBUFF[4]);
	makb[RXBUFF[0]]._T[0]=(signed short)(*((signed char*)&RXBUFF[6]));
	makb[RXBUFF[0]]._T[1]=(signed short)(*((signed char*)&RXBUFF[7]));

	makb[RXBUFF[0]]._Ub[3]=makb[RXBUFF[0]]._U[3]-makb[RXBUFF[0]]._U[2];
	if(makb[RXBUFF[0]]._Ub[3]<0)makb[RXBUFF[0]]._Ub[3]=0;
	makb[RXBUFF[0]]._Ub[4]=makb[RXBUFF[0]]._U[4]-makb[RXBUFF[0]]._U[3];
	if(makb[RXBUFF[0]]._Ub[4]<0)makb[RXBUFF[0]]._Ub[4]=0;

	makb[RXBUFF[0]]._cnt=0;
     }

if( (RXBUFF[1]==0xE4)&&(RXBUFF[0]>=0)&&(RXBUFF[0]<=3))
     {
	makb[RXBUFF[0]]._T[2]=(signed short)(*((signed char*)&RXBUFF[2]));
	makb[RXBUFF[0]]._T[3]=(signed short)(*((signed char*)&RXBUFF[3]));
	makb[RXBUFF[0]]._T[4]=(signed short)(*((signed char*)&RXBUFF[4]));

	if(RXBUFF[5]&0x01)makb[RXBUFF[0]]._T_nd[0]=1;
	else makb[RXBUFF[0]]._T_nd[0]=0;
	if(RXBUFF[5]&0x02)makb[RXBUFF[0]]._T_nd[1]=1;
	else makb[RXBUFF[0]]._T_nd[1]=0;
	if(RXBUFF[5]&0x04)makb[RXBUFF[0]]._T_nd[2]=1;
	else makb[RXBUFF[0]]._T_nd[2]=0;
	if(RXBUFF[5]&0x08)makb[RXBUFF[0]]._T_nd[3]=1;
	else makb[RXBUFF[0]]._T_nd[3]=0;
	if(RXBUFF[5]&0x10)makb[RXBUFF[0]]._T_nd[4]=1;
	else makb[RXBUFF[0]]._T_nd[4]=0;

	makb[RXBUFF[0]]._cnt=0;
     }




































 
	
if((RXBUFF[1]&0xf8)==0x18)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
	
	if(temp==0) 
		{	
		lakb_damp[temp][0]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][1],&RXBUFF[2],6);
	
		ccc_plazma[0]++;
		ccc_plazma[7]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}	

if((RXBUFF[1]&0xf8)==0x78)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
	
	if(temp==0) 
		{		
		lakb_damp[temp][7]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][8],&RXBUFF[2],6);
		
		ccc_plazma[1]++;
		ccc_plazma[8]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}

if((RXBUFF[1]&0xf8)==0x38)
     {
	char temp;
	temp=RXBUFF[1]&0x07;

	if(temp==0) 
		{
		lakb_damp[temp][14]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][15],&RXBUFF[2],6);
		
		ccc_plazma[2]++;
		ccc_plazma[9]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}	

if((RXBUFF[1]&0xf8)==0x48)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
	
	if(temp==0) 
		{
		lakb_damp[temp][21]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][22],&RXBUFF[2],6);
		
		ccc_plazma[3]++;
		ccc_plazma[10]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}

if((RXBUFF[1]&0xf8)==0x58)
     {
	char temp;
	temp=RXBUFF[1]&0x07;

	if(temp==0) 
		{		
		lakb_damp[temp][28]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][29],&RXBUFF[2],6);

		ccc_plazma[4]++;
		ccc_plazma[11]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}

if((RXBUFF[1]&0xf8)==0x68)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
		
	if(temp==0) 
		{
		lakb_damp[temp][35]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][36],&RXBUFF[2],6);
		
		ccc_plazma[5]++;
		ccc_plazma[12]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;	
		}
	}


if(RXBUFF[1]==0xC1)
    {
	lakb[0]._communication2lvlErrorCnt=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[0]._ch_curr=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[0]._tot_bat_volt=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[0]._cell_temp_1=(signed char)(RXBUFF[6]);
	lakb[0]._cell_temp_2=(signed char)(RXBUFF[7]);
	
	
	
	plazma_ztt[0]++;

	}

if(RXBUFF[1]==0xC2)
    {
	lakb[0]._communication2lvlErrorStat=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[0]._s_o_c=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[0]._s_o_h=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[0]._cell_temp_3=(signed char)(RXBUFF[6]);
	lakb[0]._cell_temp_4=(signed char)(RXBUFF[7]);
	
	
	
	plazma_ztt[1]++;
	}		

if(RXBUFF[1]==0xC3)
    {
	lakb[1]._communication2lvlErrorCnt=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[1]._ch_curr=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[1]._tot_bat_volt=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[1]._cell_temp_1=(signed char)(RXBUFF[6]);
	lakb[1]._cell_temp_2=(signed char)(RXBUFF[7]);
	
	}

if(RXBUFF[1]==0xC4)
    {
	lakb[1]._communication2lvlErrorStat=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[1]._s_o_c=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[1]._s_o_h=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[1]._cell_temp_3=(signed char)(RXBUFF[6]);
	lakb[1]._cell_temp_4=(signed char)(RXBUFF[7]);
	
	}	

if(RXBUFF[1]==0xC5)
    {
	lakb[2]._communication2lvlErrorCnt=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[2]._ch_curr=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[2]._tot_bat_volt=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[2]._cell_temp_1=(signed char)(RXBUFF[6]);
	lakb[2]._cell_temp_2=(signed char)(RXBUFF[7]);
	
	}

if(RXBUFF[1]==0xC6)
    {
	lakb[2]._communication2lvlErrorStat=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[2]._s_o_c=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[2]._s_o_h=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[2]._cell_temp_3=(signed char)(RXBUFF[6]);
	lakb[2]._cell_temp_3=(signed char)(RXBUFF[7]);	
	}	

if(RXBUFF[1]==0xC7)
    {
	lakb[0]._cell_temp_ambient=(signed char)(RXBUFF[0]);
	lakb[0]._cell_temp_power=(signed char)(RXBUFF[2]);
	lakb[1]._cell_temp_ambient=(signed char)(RXBUFF[3]);
	lakb[1]._cell_temp_power=(signed char)(RXBUFF[4]);
	lakb[2]._cell_temp_ambient=(signed char)(RXBUFF[5]);
	lakb[2]._cell_temp_power=(signed char)(RXBUFF[6]);	
	
	
	}	
	
CAN_IN_AN1_end:
bIN2=0;
}





  





  
void CAN_ISR_Rx1( void )
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;


rotor_can[0]++;

  if (!(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->RFS & 0xC0000400L))
  { 

rotor_can[1]++;
    
    
    pDest = (unsigned int *) &(gFullCANList[(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->RFS & 0x000003FFL)].Dat1);
    
    
    buf = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->RFS & 0xC00F0000L; 
    buf |= 0x01002000L; 
    buf |= ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->RID & 0x000007FFL; 

    
    *pDest = buf; 
    pDest++; 
    *pDest = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->RDA; 
    pDest++; 
    *pDest = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->RDB; 

    
    buf |= 0x03000000L; 
    pDest -= 2; 
    *pDest = buf; 
    
	temp=(char)gFullCANList[0].DatA;
	if(temp==0x30) bR=0;
	else bR++;
	
	temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     ptr=(char*)(&gFullCANList[0].DatA);
	
	for(j=0;j<temp;j++)
		{
		RXBUFF[j]=*ptr;
		ptr++;
		}
	can_in_an1();
	    
    
  }

  ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->CMR = 0x04; 
}








  
void CAN_ISR_Rx2( void ) 
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;







	if (!(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RFS & 0xC0000400L))
    		{ 
			
    		
    		
    		
			
    		pDest = (unsigned int *) &(gFullCANList[(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RFS & 0x000003FFL)].Dat1);
    
			plazma_can_pal[plazma_can_pal_index]=(char)(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>8);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>16);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>24);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>8);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>16);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>24);
			plazma_can_pal_index++;

    		
    		buf = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RFS & 0xC00F0000L; 
    		buf |= 0x01002000L; 
    		buf |= ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RID & 0x000007FFL; 

    		
    		*pDest = buf; 
    		pDest++; 
    		*pDest = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA;
			
    		pDest++; 
    		*pDest = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB; 

    		
    		buf |= 0x03000000L; 
    		pDest -= 2; 
    		*pDest = buf; 
    
		
		temp=(char)(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA);
		if(temp==0x30)
			{
			 bR=0;
			 }
		else bR++;
	
		
     
     	
	
		if(!bR)
			{
			



 
			RXBUFF[0]=(char)(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA);
			RXBUFF[1]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>8);
			RXBUFF[2]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>16);
			RXBUFF[3]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>24);
			RXBUFF[4]=(char)(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB);
			RXBUFF[5]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>8);
			RXBUFF[6]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>16);
			RXBUFF[7]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>24);
			
			}
		else if(bR==1)
			{
			RXBUFF[8]=(char)(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA);
			RXBUFF[9]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>8);
			RXBUFF[10]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>16);
			RXBUFF[11]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDA)>>24);
			RXBUFF[12]=(char)(((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB);
			RXBUFF[13]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>8);
			RXBUFF[14]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>16);
			RXBUFF[15]=(char)((((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->RDB)>>24);
			} 		
	
	
	
		
		temp=((RXBUFF[1]&0x1f)+4);
    		
		if((CRC1_in()==RXBUFF[temp+1])&&(CRC2_in()==RXBUFF[temp+2])&&bR)
			{
  
			bIN=1;
  			
  			can_in_an2();
			
			}    
    
  		}

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->CMR = 0x04; 
}





  

void can_isr_tx1 (void) 
{


char temp;




can_tx_cnt++;

rotor_can[5]++;

if(ptr_can1_tx_wr!=ptr_can1_tx_rd)
	{
	((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TFI1=can1_info[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TID1=can1_id[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TDA1=can1_data[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->TDB1=can1_datb[ptr_can1_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
	}
else bOUT_FREE=1;
temp=((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->ICR;

}

 
void can_isr_tx2 (void) 
{
char temp;
can2_tx_cnt++;



if(ptr_can2_tx_wr!=ptr_can2_tx_rd)
	{
	((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TFI1=can2_info[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TID1=can2_id[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TDA1=can2_data[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->TDB1=can2_datb[ptr_can2_tx_rd];
     ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->CMR=0x00000021;
     ptr_can2_tx_rd++;
     if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
	}
else bOUT_FREE2=1;
temp=((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->ICR;
}




  
short can1_init (unsigned int can_btr)
{
((LPC_SC_TypeDef *) ((0x40080000UL) + 0x7C000) )->PCONP |= (1<<13);   

((LPC_PINCON_TypeDef *) ((0x40000000UL) + 0x2C000) )->PINSEL0 &= ~0x0000000F;   
((LPC_PINCON_TypeDef *) ((0x40000000UL) + 0x2C000) )->PINSEL0 |= 0x00000005;

gCANFilter = 0; 

((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->AFMR = 0x00000001L; 

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->MOD = 1; 

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->IER = 0;

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->GSR = 0; 

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->BTR = can_btr; 



((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->MOD = 0; 



NVIC_EnableIRQ(CAN_IRQn);
((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->IER =0x0003;
return 1;
}




  
short can2_init (unsigned int can_btr)
{
((LPC_SC_TypeDef *) ((0x40080000UL) + 0x7C000) )->PCONP |= (1<<14);   

((LPC_PINCON_TypeDef *) ((0x40000000UL) + 0x2C000) )->PINSEL2 &= ~0x0003c000;   
((LPC_PINCON_TypeDef *) ((0x40000000UL) + 0x2C000) )->PINSEL4 |= 0x00014000;

gCANFilter = 0; 

((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->AFMR = 0x00000001L; 

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->MOD = 1; 

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->IER = 0;

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->GSR = 0; 

((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->BTR = can_btr; 



((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->MOD = 0; 



NVIC_EnableIRQ(CAN_IRQn);
((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->IER =0x0003;
return 1;
}




  
short FullCAN_SetFilter  (
                         unsigned short can_port, 
                         unsigned int CANID 
                         )
{
unsigned int p, n;
unsigned int buf0, buf1;
unsigned int ID_lower, ID_upper;
unsigned int candata;
unsigned int *pAddr;

 


((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->AFMR = 0x00000001L;

if (gCANFilter == 0)
     {    
     
     gFullCANList[0].Dat1 = 0x000037FFL; 
     }
if (gCANFilter >= 2)
     {
     return 0;
     }

CANID &= 0x000007FFL; 
CANID |= (can_port << 13); 



p = 0;
while (p < gCANFilter) 
     {
     if ((gFullCANList[p].Dat1 & 0x0000FFFFL) > CANID)
          {
          break;
          }
     p++;
     }


buf0 = gFullCANList[p].Dat1; 
gFullCANList[p].Dat1 = CANID; 


gCANFilter++;
while (p < gCANFilter)
     {
     p++;
     buf1 = gFullCANList[p].Dat1;
     gFullCANList[p].Dat1 = buf0;
     buf0 = buf1;
     }



p = 0;



((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->SFF_sa = p;

pAddr = (unsigned int *) ((0x40000000UL) + 0x38000);
for (n = 0; n < ((gCANFilter+1)/2); n++)
     {
     ID_lower = gFullCANList[n * 2].Dat1 & 0x0000FFFFL;
     ID_upper = gFullCANList[n * 2 + 1].Dat1 & 0x0000FFFFL;
     candata = (ID_lower << 16) + ID_upper;
     *pAddr = candata;
     p += 4;
     pAddr++;
     }


  


((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->SFF_GRP_sa = p;



((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->EFF_sa = p;



((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->EFF_GRP_sa = p;



((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->ENDofTable = p;


((LPC_CANAF_TypeDef *) ((0x40000000UL) + 0x3C000) )->AFMR = 0;
  
return 1;



















































































 
}


void CAN_IRQHandler(void)  
{

CANStatus = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x44000) )->ICR;




		
if ( CANStatus & (1 << 0) )
     {
	CAN_ISR_Rx1();
	plazma_can1++;
     }

if ( CANStatus & (1 << 1) )
     {
	can_isr_tx1();
	plazma_can2++;
	
     }

CANStatus = ((LPC_CAN_TypeDef *) ((0x40000000UL) + 0x48000) )->ICR;




plazma_can++;		
if ( CANStatus & (1 << 0) )
     {
	CAN_ISR_Rx2();
	plazma_can3++;
	cnt_can_pal=0;

     }

if ( CANStatus & (1 << 1) )
     {
	can_isr_tx2();
	 plazma_can4++;
	
     }

return;
}










