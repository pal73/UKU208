#include <rtl.h>

#ifdef UKU_TELECORE2016
#define UKU_TELECORE2015
#define UKU2071x
#endif

#ifdef UKU2071x
#define MCP2515_CAN
#define SC16IS740_UART
//#define can1_out mcp2515_transmit
#endif

#define SOFT_NUM	1051
#define SOFT_DATE	21112UL

#define _ACDC_

//#define _IPS_	100

#define NUM_OF_SET_TABL	2
#define DEEP_OF_SET_TABL 19

#define CONTROL_BYTE_FOR_XPORT 0

#define MINIM_INV_ADRESS	20
//-минималный адрес инвертора в кановской сети, не может быть меньше 16
#define MAX_NET_ADRESS		31
//-максимальный адрес устройства в кановской сети ИБЭПа

#define BIN__N(x) (x) | x>>3 | x>>6 | x>>9
#define BIN__B(x) (x) & 0xf | (x)>>12 & 0xf0
#define BIN8(v) (BIN__B(BIN__N(0x##v)))

#ifndef UKU_KONTUR
#define OID_ENTERPRISE 	OID0(1,3), 6, 1, 4, 1, 130, 131, 31
#endif
#ifdef UKU_KONTUR
#define OID_ENTERPRISE 	OID0(1,3), 6, 1, 4, 1, 130, 167, 60
#endif

#ifndef UKU_KONTUR

#define OID_DEVICE 		14

#define DISPLAY_DEVICE_INFO			1
#define DISPLAY_DEVICE_INFO_CODE			1
#define DISPLAY_DEVICE_INFO_SERIAL			2
#define DISPLAY_DEVICE_INFO_LOCATION 		3
#define DISPLAY_DEVICE_INFO_NUMOFBAT 		4
#define DISPLAY_DEVICE_INFO_NUMOFBPS 		5
#define DISPLAY_DEVICE_INFO_NUMOFINV 		6
#define DISPLAY_DEVICE_INFO_NUMOFAVT 		7
#define DISPLAY_DEVICE_INFO_NUMOFDT 		8
#define DISPLAY_DEVICE_INFO_NUMOFSK 		9
#define DISPLAY_DEVICE_INFO_NUMOFEVENTS		10
#define DISPLAY_DEVICE_INFO_MODEL_NAME		11

#define DISPLAY_MAINS_POWER			2
#define DISPLAY_MAINS_POWER_VOLTAGE		1
#define DISPLAY_MAINS_POWER_FREQUENCY		2
#define DISPLAY_MAINS_POWER_STATUS			3
#define DISPLAY_MAINS_POWER_ALARM			4
#define DISPLAY_MAINS_POWER_VOLTAGE_PHASEA	5
#define DISPLAY_MAINS_POWER_VOLTAGE_PHASEB	6
#define DISPLAY_MAINS_POWER_VOLTAGE_PHASEC	7


#define DISPLAY_LOAD				3
#define DISPLAY_LOAD_VOLTAGE				1
#define DISPLAY_LOAD_CURRENT				2

#define DISPLAY_PSU					4
#define DISPLAY_PSU_ENTRY_NUMBER			1,1
#define DISPLAY_PSU_ENTRY_VOLTAGE 			1,2
#define DISPLAY_PSU_ENTRY_CURRENT			1,3
#define DISPLAY_PSU_ENTRY_TEMPERATURE		1,4
#define DISPLAY_PSU_ENTRY_STATUS			1,5

#define DISPLAY_BAT					5
#define DISPLAY_BAT_NUMBER				1,1
#define DISPLAY_BAT_VOLTAGE				1,2
#define DISPLAY_BAT_CURRENT				1,3
#define DISPLAY_BAT_TEMPERATURE			1,4
#define DISPLAY_BAT_CAPACITY				1,5
#define DISPLAY_BAT_CHARGE				1,6
#define DISPLAY_BAT_STATUS				1,7

#define DISPLAY_SPEC				6
#define DISPLAY_SPEC_STAT				1
#define DISPLAY_SPEC_COMMAND				2

#define DISPLAY_SPEC_TRAP_MESSAGE			5
#define DISPLAY_SPEC_TRAP_VALUE_0			6
#define DISPLAY_SPEC_TRAP_VALUE_1			7
#define DISPLAY_SPEC_TRAP_VALUE_2			8


#define DISPLAY_INV					14
#define DISPLAY_INV_ENTRY_NUMBER			1,1
#define DISPLAY_INV_ENTRY_VOLTAGE 			1,2
#define DISPLAY_INV_ENTRY_CURRENT			1,3
#define DISPLAY_INV_ENTRY_TEMPERATURE		1,4
#define DISPLAY_INV_ENTRY_STATUS			1,5

#define LCD_SIZE 200

#define SNMP_COMMAND				8
#define COMMAND_ANSWER					1
#define COMMAND_PARAMETR					2

#define SYSPARAMS					10
#define SYSPARAMSSOUNDALARMEN				1
#define SYSPARAMSALARMAUTODISABLE			2
#define SYSPARAMS_BAT_TEST_TIME			3
#define SYSPARAMS_U_MAX					4
#define SYSPARAMS_U_MIN					5
#define SYSPARAMS_U_0_GRAD				6
#define SYSPARAMS_U_20_GRAD				7 
#define SYSPARAMS_U_SIGN					8
#define SYSPARAMS_U_MIN_POWER				9
#define SYSPARAMS_U_WITHOUT_BAT			10
#define SYSPARAMS_IBK					11
#define SYSPARAMS_IZMAX					12
#define SYSPARAMS_IMAX					13
#define SYSPARAMS_IMIN					14
#define SYSPARAMS_UVZ					15
#define SYSPARAMS_TZAS					16
#define SYSPARAMS_TSIGN_BAT				17
#define SYSPARAMS_TMAX_BAT				18
#define SYSPARAMS_TSIGN_BPS				19
#define SYSPARAMS_TMAX_BPS				20	
#define SYSPARAMS_BAT_PART_ALARM			21
#define SYSPARAMS_POWER_CNT_ADRESS			22	

#define DISPLAY_AVT					11
#define DISPLAY_AVT_ENTRY_NUMBER			1,1
#define DISPLAY_AVT_ENTRY_STAT 			1,2

#define DISPLAY_ENERGY				12
#define DISPLAY_ENERGY_VVOD_PHASE_A		1
#define DISPLAY_ENERGY_VVOD_PHASE_B		2
#define DISPLAY_ENERGY_VVOD_PHASE_C		3
#define DISPLAY_ENERGY_PES_PHASE_A			4
#define DISPLAY_ENERGY_PES_PHASE_B			5
#define DISPLAY_ENERGY_PES_PHASE_C			6
#define DISPLAY_ENERGY_TOTAL_ENERGY		7
#define DISPLAY_ENERGY_CURRENT_ENERGY		8


#define DISPLAY_SK					15
#define DISPLAY_SK_ENTRY_NUMBER			1,1
#define DISPLAY_SK_AKTIVITY	 			1,2
#define DISPLAY_SK_ALARM_AKTIVITY 			1,3
#define DISPLAY_SK_ALARM 	 			1,4

#define DISPLAY_DT					17
#define DISPLAY_DT_ENTRY_NUMBER			1,1
#define DISPLAY_DT_TEMPER	 			1,2
#define DISPLAY_DT_ERROR 				1,3

#define DISPLAY_MAKB				16
#define DISPLAY_MAKB_ENTRY_NUMBER			1,1
#define DISPLAY_MAKB_CONNECT_STATUS		1,2
#define DISPLAY_MAKB_VOLTAGE0				1,3
#define DISPLAY_MAKB_VOLTAGE1				1,4
#define DISPLAY_MAKB_VOLTAGE2				1,5
#define DISPLAY_MAKB_VOLTAGE3				1,6
#define DISPLAY_MAKB_VOLTAGE4				1,7
#define DISPLAY_MAKB_TEMPER0				1,8
#define DISPLAY_MAKB_TEMPER1				1,9
#define DISPLAY_MAKB_TEMPER2				1,10
#define DISPLAY_MAKB_TEMPER3				1,11
#define DISPLAY_MAKB_TEMPER4				1,12
#define DISPLAY_MAKB_TEMPER0_STAT			1,13
#define DISPLAY_MAKB_TEMPER1_STAT			1,14
#define DISPLAY_MAKB_TEMPER2_STAT			1,15
#define DISPLAY_MAKB_TEMPER3_STAT			1,16
#define DISPLAY_MAKB_TEMPER4_STAT			1,17

#define DISPLAY_LAKB				18
#define DISPLAY_LAKB_ENTRY_NUMBER			1,1
#define DISPLAY_LAKB_MAX_CELL_VOLTAGE		1,2
#define DISPLAY_LAKB_MIN_CELL_VOLTAGE		1,3
#define DISPLAY_LAKB_MAX_CELL_TEMPERATURE	1,4
#define DISPLAY_LAKB_MIN_CELL_TEMPERATURE	1,5
#define DISPLAY_LAKB_VOLTAGE				1,6
#define DISPLAY_LAKB_CH_CURR				1,7
#define DISPLAY_LAKB_DSCH_CURR				1,8
#define DISPLAY_LAKB_RAT_CAP				1,9
#define DISPLAY_LAKB_SOH					1,10
#define DISPLAY_LAKB_SOC					1,11	
#define DISPLAY_LAKB_CCLV					1,12
#define DISPLAY_LAKB_RBT					1,13
#define DISPLAY_LAKB_FLAGS1					1,14
#define DISPLAY_LAKB_FLAGS2					1,15
#define DISPLAY_LAKB_CELL_TEMPERATURE_1		1,16
#define DISPLAY_LAKB_CELL_TEMPERATURE_2		1,17
#define DISPLAY_LAKB_CELL_TEMPERATURE_3		1,18
#define DISPLAY_LAKB_CELL_TEMPERATURE_4		1,19
#define DISPLAY_LAKB_CELL_TEMPERATURE_AMBIENT	1,20
#define DISPLAY_LAKB_CELL_TEMPERATURE_POWER		1,21

#define DISPLAY_LAKB_DAMP1				1,22
#define DISPLAY_LAKB_DAMP2				1,23
#define DISPLAY_LAKB_DAMP3				1,24
#define DISPLAY_LAKB_DAMP4				1,25
#define DISPLAY_LAKB_DAMP5				1,26






#define COMMAND_OK		0x5555
#define COMAND_FAIL		0xaaaa
#define COMMAND_INVALID	0xeeee
#define WRONG_PARAMETER	0xeeef

#define SNMP_BPS_DISABLE		5
#define SNMP_BPS_UNDISABLE	8
#define SNMP_SPEC_VZ		3
#define SNMP_SPEC_KE		4
#define SNMP_SPEC_DISABLE	7


#define DISPLAY_LOG					9
#define DISPLAY_LOG_ENTRY_EVENTS 			1,1
//#define DISPLAY_LOG_ENTRY_EVENTS 			1,1

#endif




#ifdef UKU_KONTUR

#define OID_DEVICE 		1,2

#define DISPLAY_DEVICE_INFO			1
#define DISPLAY_DEVICE_INFO_CODE			1
#define DISPLAY_DEVICE_INFO_SERIAL			2
#define DISPLAY_DEVICE_INFO_LOCATION 		3
#define DISPLAY_DEVICE_INFO_NUMOFBAT 		4
#define DISPLAY_DEVICE_INFO_NUMOFBPS 		5
#define DISPLAY_DEVICE_INFO_NUMOFINV 		6
#define DISPLAY_DEVICE_INFO_NUMOFAVT 		7
#define DISPLAY_DEVICE_INFO_NUMOFDT 		8
#define DISPLAY_DEVICE_INFO_NUMOFSK 		9
#define DISPLAY_DEVICE_INFO_NUMOFEVENTS		10

#define DISPLAY_MAINS_POWER			1
#define DISPLAY_MAINS_POWER_VOLTAGE		1
#define DISPLAY_MAINS_POWER_FREQUENCY		2
#define DISPLAY_MAINS_POWER_STATUS			3
#define DISPLAY_MAINS_POWER_ALARM			4
#define DISPLAY_MAINS_POWER_VOLTAGE_PHASEA	5
#define DISPLAY_MAINS_POWER_VOLTAGE_PHASEB	6
#define DISPLAY_MAINS_POWER_VOLTAGE_PHASEC	7


#define DISPLAY_LOAD				3
#define DISPLAY_LOAD_VOLTAGE				1
#define DISPLAY_LOAD_CURRENT				2

#define DISPLAY_PSU					4
#define DISPLAY_PSU_ENTRY_NUMBER			1,1
#define DISPLAY_PSU_ENTRY_VOLTAGE 			1,2
#define DISPLAY_PSU_ENTRY_CURRENT			1,3
#define DISPLAY_PSU_ENTRY_TEMPERATURE		1,4
#define DISPLAY_PSU_ENTRY_STATUS			1,5

#define DISPLAY_BAT					5
#define DISPLAY_BAT_NUMBER				1,1
#define DISPLAY_BAT_VOLTAGE				1,2
#define DISPLAY_BAT_PART_VOLTAGE			1,3
#define DISPLAY_BAT_CURRENT				1,4
#define DISPLAY_BAT_TEMPERATURE			1,5
#define DISPLAY_BAT_CAPACITY				1,6
#define DISPLAY_BAT_CHARGE				1,7
#define DISPLAY_BAT_STATUS				1,8

#define DISPLAY_SPEC				6
#define DISPLAY_SPEC_STAT				1
#define DISPLAY_SPEC_COMMAND				2

#define DISPLAY_SPEC_TRAP_MESSAGE			5
#define DISPLAY_SPEC_TRAP_VALUE_0			6
#define DISPLAY_SPEC_TRAP_VALUE_1			7
#define DISPLAY_SPEC_TRAP_VALUE_2			8




#define LCD_SIZE 200

#define SNMP_COMMAND				8
#define COMMAND_ANSWER					1
#define COMMAND_PARAMETR					2

#define SYSPARAMS					10
#define SYSPARAMSSOUNDALARMEN				1
#define SYSPARAMSALARMAUTODISABLE			2
#define SYSPARAMS_BAT_TEST_TIME			3
#define SYSPARAMS_U_MAX					4
#define SYSPARAMS_U_MIN					5
#define SYSPARAMS_U_0_GRAD				6
#define SYSPARAMS_U_20_GRAD				7 
#define SYSPARAMS_U_SIGN					8
#define SYSPARAMS_U_MIN_POWER				9
#define SYSPARAMS_U_WITHOUT_BAT			10
#define SYSPARAMS_IBK					11
#define SYSPARAMS_IZMAX					12
#define SYSPARAMS_IMAX					13
#define SYSPARAMS_IMIN					14
#define SYSPARAMS_UVZ					15
#define SYSPARAMS_TZAS					16
#define SYSPARAMS_TSIGN_BAT				17
#define SYSPARAMS_TMAX_BAT				18
#define SYSPARAMS_TSIGN_BPS				19
#define SYSPARAMS_TMAX_BPS				20	
#define SYSPARAMS_BAT_PART_ALARM			21
#define SYSPARAMS_POWER_CNT_ADRESS			22


#define DISPLAY_AVT					11
#define DISPLAY_AVT_ENTRY_NUMBER			1,1
#define DISPLAY_AVT_ENTRY_STAT 			1,2

#define DISPLAY_ENERGY				12
#define DISPLAY_ENERGY_VVOD_PHASE_A		1
#define DISPLAY_ENERGY_VVOD_PHASE_B		2
#define DISPLAY_ENERGY_VVOD_PHASE_C		3
#define DISPLAY_ENERGY_PES_PHASE_A			4
#define DISPLAY_ENERGY_PES_PHASE_B			5
#define DISPLAY_ENERGY_PES_PHASE_C			6
#define DISPLAY_ENERGY_TOTAL_ENERGY		7
#define DISPLAY_ENERGY_CURRENT_ENERGY		8


#define DISPLAY_SK					14
#define DISPLAY_SK_ENTRY_NUMBER			1,1
#define DISPLAY_SK_NAME					1,2
#define DISPLAY_SK_AKTIVITY	 			1,3
#define DISPLAY_SK_ALARM_AKTIVITY 			1,4
#define DISPLAY_SK_ALARM 	 			1,5

#define DISPLAY_DT					15
#define DISPLAY_DT_EXT					1
#define DISPLAY_DT_MSAN	 				2
#define DISPLAY_DT_EPU 					3

#define DISPLAY_KLIMAT				16
#define DISPLAY_KLIMAT_BOX_TEMPER				1
#define DISPLAY_KLIMAT_SETTINGS_BOX_ALARM_TEMPER	2
#define DISPLAY_KLIMAT_SETTINGS_VENT_ON			3
#define DISPLAY_KLIMAT_SETTINGS_VENT_OFF		4
#define DISPLAY_KLIMAT_SETTINGS_WARM_ON			5
#define DISPLAY_KLIMAT_SETTINGS_WARM_OFF		6
#define DISPLAY_KLIMAT_SETTINGS_LOAD_ON			7
#define DISPLAY_KLIMAT_SETTINGS_LOAD_OFF		8
#define DISPLAY_KLIMAT_SETTINGS_BATT_ON			9
#define DISPLAY_KLIMAT_SETTINGS_BATT_OFF		10



#define COMMAND_OK		0x5555
#define COMAND_FAIL		0xaaaa
#define COMMAND_INVALID	0xeeee
#define WRONG_PARAMETER	0xeeef

#define SNMP_BPS_DISABLE		5
#define SNMP_BPS_UNDISABLE	8
#define SNMP_SPEC_VZ		3
#define SNMP_SPEC_KE		4
#define SNMP_SPEC_DISABLE	7


#define DISPLAY_LOG					9
#define DISPLAY_LOG_ENTRY_EVENTS 			1,1
//#define DISPLAY_LOG_ENTRY_EVENTS 			1,1
#endif

//#define SEC_IN_HOUR	36000L

#define LCD_SIZE 200


#define MAX_NUM_OF_BAT	2
#define MAX_NUM_OF_BPS	12
//#define PAROL_ALL_ZERO

#define AH_CONSTANT		36000L

//***********************************************
//Состояние источников




#define MASK(lengt) 		(0xffffffff>>(32-lengt))
#define MASK_OFFSET(shift,lengt)	(MASK(lengt)<<shift)

#define GET_REG( reg, shift, lengt) 		( (reg & MASK_OFFSET(shift,lengt)) >> shift)
#define SET_REG( reg, val, shift, lengt)  	reg = ( (reg & ~MASK_OFFSET(shift,lengt)) | (val << shift) )
//#define CHK_REG( reg, mask ) ( (reg) & (mask) == (mask) )



#define delay_ms(x) {long xx; xx=(unsigned long)x * 12000UL; while(xx)xx--;}
#define delay_us(x) {long xx; xx=(unsigned long)x * 12UL; while(xx)xx--;}

//*************************************************
//сообщения
#define MESS_DEEP	10

#define 	MESS_ZERO 		0
#define 	MESS_BAT1_OFF 		1
#define 	MESS_BAT2_OFF		2
#define 	MESS_ALL_SRC_OFF	3
#define 	MESS_ALL_SRC_ON	4
//#define 	MESS_RELSAM_ON		5
#define 	MESS_SRC1_OFF		6
#define 	MESS_SRC2_OFF		7
#define 	MESS_SRC3_OFF		8
#define 	MESS_SRC4_OFF		9
#define 	MESS_SRC5_OFF		10
#define 	MESS_SRC6_OFF		11
#define 	MESS_SRC7_OFF		12
#define 	MESS_SRC8_OFF		13
#define 	MESS_SRC9_OFF		14
#define 	MESS_SRC10_OFF		15
#define 	MESS_SRC11_OFF		16
#define 	MESS_SRC12_OFF		17
#define 	MESS_BAT_CONTROL	18
#define 	MESS_SRC_CONTROL	19
#define 	MESS_LOAD2_WAIT	9 
#define 	MESS_PONG			100
#define	MESS_SPA_UART_PONG	101 
#define	MESS_SPA_BLOK_BPS1	102
#define	MESS_SPA_BLOK_BPS2	103
#define	MESS_SPA_LEAVE_BPS1	104
#define	MESS_SPA_LEAVE_BPS2	105
#define 	MESS_SRC_ON_OFF	150
#define   _MESS_SRC_MASK_BLOK_2SEC		151
#define   _MESS_SRC_MASK_UNBLOK		152
#define 	_MESS_SRC_MASK_ON			153
#define	_MESS_SRC_PWM				154
#define	_MESS_U_NECC				155
#define   _MESS_FAST_REG				156
//#define   _MESS_U_AVT_GOOD			157

#define 	MESS_BAT_ON_OFF	160
#define   _MESS_BAT_MASK_BLOK_AFTER_2SEC		161
#define	_MESS_BAT_MASK_ON					162
#define	_MESS_BAT_MASK_OFF					163

		
//#define	MESS_SPA_UART_SRAM	200 
//#define	MESS_SPA_UART_CMND	201 

#define	MESS2UNECC_HNDL   					190
#define  		PARAM_UNECC_SET				 	191
#define	MESS2BAT_HNDL   					200
//#define	MESS2BAT_HNDL1   					201
#define		PARAM_BAT_ALL_OFF_AFTER_2SEC			201
#define		PARAM_BAT_MASK_OFF_AFTER_2SEC			202
//#define		PARAM_BAT_ON						202
#define	MESS2BPS_HNDL   					205
#define		PARAM_BPS_ALL_OFF_AFTER_2SEC			206
#define		PARAM_BPS_MASK_OFF_AFTER_2SEC			207
#define		PARAM_BPS_MASK_ON_OFF_AFTER_2SEC		208
#define		PARAM_BPS_MASK_ON					209
#define		PARAM_BPS_ALL_ON					210
#define 	MESS2RELE_HNDL						210
#define		PARAM_RELE_SAMOKALIBR			100
#define		PARAM_RELE_AV						101
#define		PARAM_RELE_AV_NET					102
#define		PARAM_RELE_AV_BAT					103
#define		PARAM_RELE_LOAD_OFF					103
#define		PARAM_RELE_LIGHT					104
//#define		PARAM_RELE_WARM					104
#define		PARAM_RELE_AV_COMM					105
#define		PARAM_RELE_AV_BPS					106
#define		PARAM_RELE_VENT						107
#define		PARAM_RELE_VENT_WARM				107
#define		PARAM_RELE_AV_BAT1					108
#define		PARAM_RELE_AV_BAT2					109
#define		PARAM_RELE_NPN						110
#define		PARAM_RELE_WARM				     	111
#define 		PARAM_RELE_VVENT				112
#define 		PARAM_RELE_EXT					113
#define 		PARAM_RELE_BAT_IS_DISCHARGED	114

#define	MESS2IND_HNDL						215
#define		PARAM_SAMOKALIBR					216
#define 		PARAM_U_AVT_GOOD					217
#define	MESS2MATEMAT						220
#define		PARAM_SAMOKALIBR					216
#define	MESS2CNTRL_HNDL   					225
#define		PARAM_CNTRL_STAT_PLUS				100
#define		PARAM_CNTRL_STAT_MINUS				105
#define		PARAM_CNTRL_STAT_STEP_DOWN			110
#define 		PARAM_CNTRL_STAT_SET		    		229
#define 		PARAM_CNTRL_STAT_FAST_REG		    	230	
#define	MESS2KB_HNDL   					230
#define		PARAM_CNTRL_IS_DOWN					231
#define	MESS2VENT_HNDL   					240
#define		PARAM_VENT_CB					241

#define MESS2NET_DRV							33
#define	PARAM_BPS_NET_OFF						34

#define LCD_SIZE 200



#define BIN__N(x) (x) | x>>3 | x>>6 | x>>9
#define BIN__B(x) (x) & 0xf | (x)>>12 & 0xf0
#define BIN8(v) (BIN__B(BIN__N(0x##v)))



#define BAUD_RATE0 9600UL
#define BAUD_RATE1 9600UL





#ifndef PAROL_ALL_ZERO
#define PAROL_KALIBR 873
#define PAROL_SET 184
#define PAROL_MODE 0 
#define PAROL_ALLER 815 
#define PAROL_BAT_IN 722 
#define PAROL_BAT_OUT 722
#define PAROL_KE 125
#define PAROL_VZ 126
#define PAROL_TST 999 
#define PAROL_DEFAULT 295
#define PAROL_AUSW 949
#endif                

#ifdef PAROL_ALL_ZERO
#define PAROL_KALIBR 0
#define PAROL_SET 0
#define PAROL_MODE 0 
#define PAROL_ALLER 0 
#define PAROL_BAT_IN 0 
#define PAROL_BAT_OUT 0
#define PAROL_KE 0
#define PAROL_VZ 0
#define PAROL_TST 0
#define PAROL_DEFAULT 0
#define PAROL_AUSW 0
#endif


#define CNT_SRC_MAX	60



//

//#define SHIFT_REL_AV_BPS	     4
 


#ifdef UKU_MGTS
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_AV_COMM	9
#define SHIFT_REL_LOAD_OFF	5
#define SHIFT_REL_VENT	     7
#define SHIFT_REL_LIGHT 	     4
#endif

#ifdef UKU_RSTKM
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_AV_COMM	9
#define SHIFT_REL_LOAD_OFF	5
#define SHIFT_REL_VENT	     7
#define SHIFT_REL_LIGHT 	     4
#endif

#ifdef UKU_3U
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_AV_BAT1	4
#define SHIFT_REL_AV_BAT2	9
#define SHIFT_REL_AV_BPS	     7
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#endif

#ifdef UKU_GLONASS
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_AV_BAT1	4
#define SHIFT_REL_AV_BAT2	9
#define SHIFT_REL_AV_BPS	     7
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#endif

#ifdef UKU_KONTUR
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_AV_COMM	9
#define SHIFT_REL_LOAD_OFF	5
#define SHIFT_REL_VENT	     7
#define SHIFT_REL_VENT_WARM   7
#define SHIFT_REL_WARM 	     4
#define SHIFT_REL_LIGHT 	     4
#endif

#ifdef UKU_6U
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_AV_BAT1	4
#define SHIFT_REL_AV_BAT2	9
#define SHIFT_REL_AV_BPS	     7
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_VENT		5
#endif

#ifdef UKU_220
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_AV_BAT	4
#define SHIFT_REL_AV_BPS	     7
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_VENT		9
#endif

#ifdef UKU_220_IPS_TERMOKOMPENSAT
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_AV_BPS	     5
#define SHIFT_REL_AV_BAT	     4
#endif

#ifdef UKU_220_V2
#define SHIFT_REL_AV_NET		25
#define SHIFT_REL_AV_BAT	4
#define SHIFT_REL_AV_BPS	     7
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_VENT		9
#endif

#ifdef UKU_TELECORE2015
#define SHIFT_REL_AV_NET		5
#define SHIFT_REL_AV_BAT	4
#define SHIFT_REL_AV_BPS	     7
#define SHIFT_REL_BAT1	     8
#define SHIFT_REL_BAT2	     6
#define SHIFT_REL_LIGHT		9
#define SHIFT_REL_WARM		4
#define SHIFT_REL_VENT	     7
#define SHIFT_REL_VVENT	     6
#endif

//***********************************************
//Таймер
extern char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz;
extern short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7;
extern char bFL5,bFL2,bFL,bFL_;
extern signed short main_10Hz_cnt;
extern signed short main_1Hz_cnt;

//***********************************************
//Структура ИБЭПа
extern char cnt_of_slave;
//char cnt_of_wrks;   //колличество работающих источников , для индикации




//***********************************************
//Индикация
typedef enum {
	#ifdef UKU_IP55
	iMn_IP55,
	#endif
	#ifdef UKU_220_IPS_TERMOKOMPENSAT
	iMn_220_IPS_TERMOKOMPENSAT,
	#endif
	#ifdef UKU_220
	iMn_220,
	#endif
	#ifdef UKU_KONTUR
	iMn_KONTUR,
	#endif
	#ifdef UKU_6U
	iMn_6U,
	#endif
	#ifdef UKU_GLONASS
	iMn_GLONASS,
	#endif
	#ifdef UKU_220_V2
	iMn_220_V2,
	#endif
	#ifdef UKU_TELECORE2015
	iMn_TELECORE2015, 
	#endif
	iMn,iMn_3U,iMn_RSTKM,
	#ifndef UKU_220_IPS_TERMOKOMPENSAT
	iMn_220_IPS_TERMOKOMPENSAT,
	#endif
	#ifndef UKU_220
	iMn_220,
	#endif
	#ifndef UKU_KONTUR
	iMn_KONTUR,
	#endif
	#ifndef UKU_6U
	iMn_6U,
	#endif
	#ifndef UKU_GLONASS
	iMn_GLONASS,
	#endif
	#ifndef UKU_220_V2
	iMn_220_V2,
	#endif 
	#ifndef UKU_TELECORE2015
	iMn_TELECORE2015,
	#endif 
	#ifndef UKU_IP55
	iMn_IP55,
	#endif
	iSrv_sl,iNet,iNet3,iNetEM,
	iSet,iSet_3U,iSet_RSTKM,iSet_GLONASS,iSet_KONTUR,iSet_6U,iSet_220,iSet_220_IPS_TERMOKOMPENSAT,iSet_220_V2,iInv_set_sel,
	iBat,iBat_simple,iBat_li,iBat_SacredSun,iBat_universe,iInv_set,iSet_IP55,
	iMakb,
	iBps,iS2,iSet_prl,iK_prl,iDnd,iDcdc,
	iK,iK_3U,iK_RSTKM,iK_GLONASS,iK_KONTUR,iK_6U,iK_220,iK_220_380,iK_220_IPS_TERMOKOMPENSAT,iK_220_IPS_TERMOKOMPENSAT_IB,iK_IP55,
	iSpcprl,iSpc,k,Crash_0,Crash_1,iKednd,iAv_view_avt,iAKE,iSpc_termocompensat,
	iLoad,iSpc_prl_vz,iSpc_prl_ke,iKe,iVz,iAvz,iAVAR,
	iStr,iStr_3U,iStr_RSTKM,iStr_GLONASS,iStr_KONTUR,iStr_6U,iStr_220_IPS_TERMOKOMPENSAT,iStr_IP55,
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
	iTst_bps,/*iJAv_bat,iJAv_bat_sel,*/iAusw,iAusw_prl,iAusw_set,
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
	iOut_volt_contr,iDop_rele_set,iBlok_ips_set,
	iInputs}i_enum;

typedef struct  
{

i_enum i;
signed char s_i;
signed char s_i1;
signed char s_i2;
signed char i_s;
} stuct_ind;

#define ind     a_ind.i
#define sub_ind     a_ind.s_i
#define sub_ind1     a_ind.s_i1
#define sub_ind2     a_ind.s_i2
#define index_set     a_ind.i_s

extern stuct_ind a_ind,b_ind[10],c_ind;
extern signed short ptr_ind;
extern char lcd_buffer[LCD_SIZE+100];
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



//***********************************************
//Состояние батарей
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
	//0бит - подогрев
	//1бит - перегрев
	signed short 	_sign_temper_cnt;
	signed short 	_max_temper_cnt;
	signed long 	_resurs_cnt;
	signed short 	_cnt_as; 	//счетчик несимметрии, считает до 5 минут при выполнении условий несимметрии, когда досчитывает - пишет в журнал
     //signed short   _max_cell_volt;
	//signed short   _min_cell_volt;
	} BAT_STAT; 
extern BAT_STAT bat[2],bat_ips;
extern signed short		bat_u_old_cnt;
extern signed short 	Ib_ips_termokompensat;

//#ifdef UKU_TELECORE2015
typedef enum {bsOFF=0,bsCOMM_ON,bsOK} enum_batStat;
//***********************************************
//Состояние литиевой батареи
typedef struct
     {
	//char 		_cnt_to_block;
	signed short	_Ub;
     //signed short	_Ubm;
     //signed short	_dUbm;
	signed short	_Ib;
	signed short	_Tb;
	char 		_nd;
	char   		_soh;
	char 		_soc;
	signed short   _ratCap;
	char 		_comErrStat;	//Состояние связи с батареей: 1-ошибка, 0-связь в норме
	enum_batStat	_batStat;
	signed short 	_cclv;
	char 		_rbt;
	short 		_canErrorCnt;
	char			_canError;
	char 		_485Error;
	short 		_485ErrorCnt;
	//char 		_full_ver;
	//signed long 	_zar_cnt;
	//signed long 	_zar_cnt_ke;
	//unsigned short _Iintegr,_Iintegr_; 
	//signed short 	_u_old[8];
	//signed short	_u_old_cnt;
	//unsigned long 	_wrk_date[2];
	//char 		_rel_stat;
	//char			_av;
	//char			_time_cnt;
	//char 		_temper_stat;
	//0бит - подогрев
	//1бит - перегрев
	//signed short 	_sign_temper_cnt;
	//signed short 	_max_temper_cnt;
	//signed long 	_resurs_cnt;
	//signed short 	_cnt_as; 	//счетчик несимметрии, считает до 5 минут при выполнении условий несимметрии, когда досчитывает - пишет в журнал
     //signed short   _max_cell_volt;
	//signed short   _min_cell_volt;
	} LI_BAT_STAT; 
extern LI_BAT_STAT li_bat;
//#endif
//***********************************************
//Состояние байпаса
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

//***********************************************
//Мониторы АКБ
typedef struct
     {
	signed short	_U[5];
	signed short	_Ub[5];
	signed short	_T[5];
	signed short	_T_nd[5];
	signed short 	_cnt; 	
	} MAKB_STAT; 
extern MAKB_STAT makb[4];

//***********************************************
//Литиевые АКБ
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
	signed short 	_communication2lvlErrorStat; 	//флаг аварийности низовой связи с батареей, вычисляется в плате расширения
	signed short	_communication2lvlErrorCnt;  	//счетчик аварийности низовой связи с батареей
	signed short 	_cnt;
	signed short 	_communicationFullErrorStat;	//флаг аварийности всего канала связи с батареей, 0 - норма, 1 - отсутствует связь с промежуточной платой, 2 - отсутствует связь промежуточной платы и батареи  	
	signed short   _battIsOn;		//0 - отсутствует, 1 - присутствует
	char 		_plazma[8];		//переменные для отладки
	signed short 	_isOnCnt;
	signed short	_s_o_c_abs;		//остаточный заряд в абсолютном выражении
	signed short 	_s_o_c_percent; //остаточный заряд в процентном выражении
	signed short	_plazma_ss;
	signed short	_zar_percent;	//заряд батареи в процетах
	signed char		_cell_temp_1;	//температура 1-го датчика батареи(ZTT)
	signed char		_cell_temp_2;	//температура 2-го датчика батареи(ZTT)
	signed char		_cell_temp_3;	//температура 3-го датчика батареи(ZTT)
	signed char		_cell_temp_4;	//температура 4-го датчика батареи(ZTT)
	signed char		_cell_temp_ambient;	//температура датчика окружающей среды батареи(ZTT)
	signed char		_cell_temp_power;	//температура датчика силовой части батареи(ZTT)
	signed char 	_voltage_event_code;							//(ZTT)

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
extern char lakb_error_cnt;	//счетчик неправильного показания ннапряжения батареи
extern short numOfPacks,numOfPacks_;
extern short numOfCells, numOfTemperCells, baseOfData;
extern short lakb_stat_comm_error;	//аварийность канала связи с литиевыми батареями. 0 означает исправность платы расширения и наличие связи со всеми литиевыми батареями
extern short lakbNotErrorNum;		//колличество литиевых батарей с исправной связью
extern short lakbKanErrorCnt;		//Счетчик аварийности канала связи с платой расширения
extern short lakbKanErrorStat;		//Состояние аварийности канала связи с платой расширения



//***********************************************
//Телеметрия по внутренней шине
extern char can_slot[12][16];
extern char plazma_can_inv[3];


//***********************************************
//Состояние инверторов
typedef struct
     {
	char _av;
	//0бит - авария по перегреву
	//1бит - авария по завышенному Uвых
	//2бит - авария по заниженному Uвых
	//3бит - авария по обрыву связи	    
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
     //int _ist_blok_host_cnt_; //блокирование источников извне(CAN или RS), если не 0 то источник заблокирован.
     int _ist_blok_host_cnt;
     short _blok_cnt; //блокирование источников 
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
#ifdef UKU_220_V2
extern INV_STAT inv[3];
#endif
#ifndef UKU_220_V2
extern INV_STAT inv[20];
#endif
extern char first_inv_slot;

//***********************************************
//Состояние нагрузки
extern signed short load_U;
extern signed short load_I;

//***********************************************
//Состояние выхода
extern signed short bps_U;
extern signed short out_U;
extern signed short bps_I;

//***********************************************
//Состояние первичной сети
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


//***********************************************
//Состояние внешних датчиков
//signed short tout[4];
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

//***********************************************
//Звуки
extern BOOL bSILENT;

//***********************************************
//Тест
typedef enum {tstOFF,tst1,tst2} enum_tst_state;
extern enum_tst_state tst_state[15];

//-----------------------------------------------
//Контроль заряда
extern char sign_U[2],sign_I[2];
extern char superviser_cnt;

//-----------------------------------------------
//Плата расширения
extern unsigned short adc_buff_ext_[3];
extern unsigned short Uvv[3];
extern unsigned short Uvv0;
extern short pos_vent;
extern short t_ext_can;
extern char t_ext_can_nd;

//-----------------------------------------------
//Плата расширения 2
extern char eb2_data[30];
extern short eb2_data_short[10];
extern short Uvv_eb2[3],Upes_eb2[3];
extern short Kvv_eb2[3],Kpes_eb2[3];

//-----------------------------------------------
//Состояние вводов
extern signed short vvod_pos;

//-----------------------------------------------
//Работа со щетчиком
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

//-----------------------------------------------
//Климатконтроль и вентиляторы
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
#ifdef UKU_KONTUR
extern short t_box_vent_on_cnt;
extern short t_box_warm_on_cnt;
typedef enum {vsOFF,vsON} enum_vent_stat;
extern enum_vent_stat vent_stat_k;
typedef enum {wsOFF,wsON} enum_warm_stat;
extern enum_warm_stat warm_stat_k;
#endif

#ifdef UKU_TELECORE2015
extern short t_box_vent_on_cnt;
extern short t_box_warm_on_cnt;
extern short t_box_vvent_on_cnt;
typedef enum {vsOFF,vsON} enum_vent_stat;
extern enum_vent_stat vent_stat_k,vvent_stat_k;
typedef enum {wsOFF,wsON} enum_warm_stat;
extern enum_warm_stat warm_stat_k;
extern signed short TELECORE2015_KLIMAT_WARM_ON_temp;
#endif



extern char ext_can_cnt;


signed short abs_pal(signed short in);
void ADC_IRQHandler(void);


//-----------------------------------------------
//Состояние контролируемых автоматов нагрузки 
typedef enum  {avtOFF,avtON} enum_avt_stat;
extern enum_avt_stat avt_stat[12],avt_stat_old[12]; 

//-----------------------------------------------
//Показания АЦП на плате измерения тока батареи
extern signed long ibat_metr_buff_[2];
extern short bIBAT_SMKLBR;

//-----------------------------------------------
//Управление низкоприоритетной нагрузкой
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

//-----------------------------------------------
//Климатконтроль TELECORE2015	
//#ifdef UKU_TELECORE2015
extern signed short TELECORE2015_KLIMAT_WARM_SIGNAL;
extern signed short TELECORE2015_KLIMAT_VENT_SIGNAL;
extern signed short TELECORE2015_KLIMAT_WARM_ON;
extern signed short TELECORE2015_KLIMAT_WARM_OFF;
extern signed short TELECORE2015_KLIMAT_CAP;
extern signed short TELECORE2015_KLIMAT_VENT_ON;
extern signed short TELECORE2015_KLIMAT_VENT_OFF;
extern signed short TELECORE2015_KLIMAT_VVENT_ON;
extern signed short TELECORE2015_KLIMAT_VVENT_OFF;
//#endif



#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

//-----------------------------------------------
//Ускоренный заряд
extern signed short speedChrgCurr;			//максимальный ток ускоренного заряда, отображение из ЕЕПРОМ
extern signed short speedChrgVolt;			//максимальное напряжение ускоренного заряда, отображение из ЕЕПРОМ
extern signed short speedChrgTimeInHour; 	//максимальное время ускоренного заряда в часах, отображение из ЕЕПРОМ
extern signed short speedChrgAvtEn;	 	//Автоматическое включение Ускоренного заряда включено/выключено
extern signed short speedChrgDU;	    		//Просадка напряжения необходимая для включения ускоренного заряда
extern signed short speedChIsOn;			//Текущее состояние ускоренного заряда вкл/выкл
extern signed long  speedChTimeCnt;		//Счетчик времени прямой ускоренного заряда
extern signed short speedChrgBlckSrc;		//Источник сигнала блокировки, 0-выкл., 1-СК1, 2-СК2
extern signed short speedChrgBlckLog;		//Логика сигнала блокировки, 1 - блокировка по замкнутому СК, 0 - по разомкнутому
extern signed short speedChrgBlckStat;		//Сигнал блокировки для выравнивающего и ускоренного заряда.
extern char  		speedChrgShowCnt;		//Счетчик показа информационного сообщения

//-----------------------------------------------
//Алгоритм содержания батареи 	
//signed short TELECORE2017_USTART;		//Напряжение включения
//signed short TELECORE2017_ULINECC;		//Напряжение содержания из установок
extern signed short LI_UNECC_;					//Напряжение содержания мгновенное, с учетом аварий батареи
extern signed short LI_AVAR_CNT;				//Счетчик аварийности батареи для снижения напряжения содержания

//signed short TELECORE2017_AVAR_CNT;		//Счетчик аварийности батареи для снижения напряжения содержания
//signed short TELECORE2017_Q;			//Заряд батари (%) при котором переходим с тока IZMAX1 на IZMAX2
//signed short TELECORE2017_IZMAX1;		//Максимальный ток заряда батареи при разряженной батарее(заряд < TELECORE2017_Q)
//signed short TELECORE2017_IZMAX2;	   	//Максимальный ток заряда батареи при заряженной батарее(заряд >= TELECORE2017_Q)
//signed short TELECORE2017_K1;			//Шаг регулирования(ед/с) при Uвыпр<(Uбат-2В)
//signed short TELECORE2017_K2;			//Шаг регулирования(ед/с) при Uвыпр>(Uбат-2В) и отсутствии токов батарей
//signed short TELECORE2017_K3;			//Шаг регулирования(ед/с) при токе батарей в интервале 0-70% от Izmax
//signed short TELECORE2017_T4;			//Период регулирования(сек) еденичными шагами при токе батарейц в интервале 70-110%от Izmax 
//#endif 


//-----------------------------------------------
//Блокировка ИПС
extern signed short ipsBlckSrc;
extern signed short ipsBlckLog;
extern signed short ipsBlckStat;

//-----------------------------------------------
//Контроль выходного напряжения
extern signed short outVoltContrHndlCnt;		//Счетчик, считает в плюс в случае выполнения условия аварии
extern signed short outVoltContrHndlCnt_;		//Счетчик, считает в плюс в случае отсутствия выполнения условия аварии
extern char uout_av;


extern short plazma_numOfCells;
extern short plazma_numOfTemperCells;
extern short plazma_numOfPacks;

extern char plazma_ztt[2];
extern short ft_plazma;
//extern FT_PROGMEM ft_prog_uchar8_t SAMApp_Metric_L1[];
//extern FT_PROGMEM ft_prog_uchar8_t SAMApp_L1[];
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
